package output

import (
	"context"
	"encoding/csv"
	"fmt"
	"io"
	"strings"
	"sync"
	"text/template"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
)

// OutputOptions allow more granular configuration of output details
// TODO (dawid): This used to be "type OutputOptions = struct" (the '=' sign). Was that a typo or purposful? I couldn't embed it in the GlobalOptions data structure, so I removed the '='
type OutputOptions struct {
	// If set, raw data from the RPC will be printed instead of the model
	ShowRaw bool
	// If set, hidden fields will be printed as well (depends on the format)
	Verbose bool
	// If Verbose is true, this is the level of detail (verbose alone implies LogLevel=1)
	LogLevel uint64
	// If set, the first line of "txt" and "csv" output will NOT (the keys) will squelched
	NoHeader bool
	// The format in which to print the output
	Format string
	// How to indent JSON output
	JsonIndent string
	// Chain name
	Chain string
	// Flag to check if we are in test mode
	TestMode bool
	// Output file name. If present, we will write output to this file
	OutputFn string
	// If true and OutputFn is non-empty, open OutputFn for appending (create if not present)
	Append bool
	// The writer
	Writer io.Writer
	// Extra options passed to model, for example command-specific output formatting flags
	Extra map[string]interface{}
}

var formatToSeparator = map[string]rune{
	"csv": ',',
	"txt": '\t',
}

// StreamWithTemplate executes a template `tmpl` over Model `model`
func StreamWithTemplate(w io.Writer, model types.Model, tmpl *template.Template) error {
	return tmpl.Execute(w, model.Data)
}

// StreamModel streams a single `Model`
func StreamModel(w io.Writer, model types.Model, options OutputOptions) error {
	if options.Format == "json" {
		jw, ok := w.(*JsonWriter)
		if !ok {
			// This should never happen
			panic("streaming JSON requires JsonWriter")
		}
		_, err := jw.WriteCompoundItem("", model.Data)
		if err != nil {
			return err
		}
		return nil
	}

	// Store map items as strings. All formats other than JSON need string data
	strs := make([]string, 0, len(model.Order))
	for _, key := range model.Order {
		strs = append(strs, fmt.Sprint(model.Data[key]))
	}

	var separator rune
	if len(options.Format) == 1 {
		separator = rune(options.Format[0])
	} else {
		separator = formatToSeparator[options.Format]
	}
	if separator == 0 {
		return fmt.Errorf("unknown format %s", options.Format)
	}
	outputWriter := csv.NewWriter(w)
	outputWriter.Comma = rune(separator)
	if !options.NoHeader { // notice double negative
		outputWriter.Write(model.Order)
	}
	outputWriter.Write(strs)
	// This Flushes for each printed item, but in the exchange the user gets
	// the data printed as it comes
	outputWriter.Flush()

	err := outputWriter.Error()
	if err != nil {
		return err
	}

	return nil
}

// StreamRaw outputs raw `Raw` to `w`
func StreamRaw[Raw types.RawData](w io.Writer, raw *Raw) (err error) {
	jw, ok := w.(*JsonWriter)
	if !ok {
		// This should never happen
		panic("streaming raw data requires JsonWriter")
	}
	_, err = jw.WriteCompoundItem("", raw)
	return
}

func logErrors(errsToReport []string) {
	for _, errMessage := range errsToReport {
		logger.Error(errMessage)
	}
}

type fetchDataFunc[Raw types.RawData] func(modelChan chan types.Modeler[Raw], errorChan chan error)

// StreamMany outputs models or raw data as they are acquired
func StreamMany[Raw types.RawData](ctx context.Context, fetchData fetchDataFunc[Raw], options OutputOptions) error {
	errsToReport := make([]string, 0)

	modelChan := make(chan types.Modeler[Raw])
	errorChan := make(chan error)

	first := true
	go func() {
		fetchData(modelChan, errorChan)
		close(modelChan)
		close(errorChan)
	}()

	isJson := options.Format == "json" || options.ShowRaw
	var jw *JsonWriter
	if !isJson {
		defer func() {
			if len(errsToReport) == 0 {
				return
			}
			logErrors(errsToReport)
		}()
	} else {
		// If this hits, perhaps you've not added an entry to enabledForCmds
		jw = options.Writer.(*JsonWriter)
	}

	// If user wants custom format, we have to prepare the template
	customFormat := strings.Contains(options.Format, "{")
	tmpl, err := template.New("").Parse(options.Format)
	if customFormat && err != nil {
		return err
	}

	errsMutex := sync.Mutex{}
	for {
		select {
		case model, ok := <-modelChan:
			if !ok {
				return nil
			}

			// If the output is JSON and we are printing another item, put `,` in front of it
			var err error
			if options.ShowRaw {
				err = StreamRaw(options.Writer, model.Raw())
			} else {
				modelValue := model.Model(options.Verbose, options.Format, options.Extra)
				if customFormat {
					err = StreamWithTemplate(options.Writer, modelValue, tmpl)
				} else {
					err = StreamModel(options.Writer, modelValue, OutputOptions{
						NoHeader:   !first || options.NoHeader,
						Format:     options.Format,
						JsonIndent: "  ",
					})
				}
			}
			if err != nil {
				return err
			}
			first = false

		case err, ok := <-errorChan:
			if !ok {
				continue
			}
			errsMutex.Lock()
			if isJson {
				jw.WriteError(err)
			} else {
				errsToReport = append(errsToReport, err.Error())
			}
			errsMutex.Unlock()

		case <-ctx.Done():
			err = ctx.Err()
			if err == context.Canceled {
				return nil
			}
			return err
		}
	}
}
