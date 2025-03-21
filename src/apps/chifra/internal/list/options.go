// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.
/*
 * This file was auto generated with makeClass --gocmds. DO NOT EDIT.
 */

package listPkg

import (
	"encoding/json"
	"net/http"
	"strings"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/internal/globals"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/rpcClient/ens"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/utils"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
)

// ListOptions provides all command options for the chifra list command.
type ListOptions struct {
	Addrs       []string              `json:"addrs,omitempty"`       // One or more addresses (0x...) to list
	Count       bool                  `json:"count,omitempty"`       // Display only the count of records for each monitor
	Appearances bool                  `json:"appearances,omitempty"` // Export each monitor's list of appearances (the default)
	Silent      bool                  `json:"silent,omitempty"`      // Freshen the monitor only (no reporting)
	NoZero      bool                  `json:"noZero,omitempty"`      // Suppress the display of zero appearance accounts
	Unripe      bool                  `json:"unripe,omitempty"`      // List transactions labeled upripe (i.e. less than 28 blocks old)
	FirstRecord uint64                `json:"firstRecord,omitempty"` // The first record to process
	MaxRecords  uint64                `json:"maxRecords,omitempty"`  // The maximum number of records to process
	FirstBlock  uint64                `json:"firstBlock,omitempty"`  // First block to export (inclusive, ignored when freshening)
	LastBlock   uint64                `json:"lastBlock,omitempty"`   // Last block to export (inclusive, ignored when freshening)
	Bounds      bool                  `json:"bounds,omitempty"`      // Report first and last block this address appears
	Globals     globals.GlobalOptions `json:"globals,omitempty"`     // The global options
	BadFlag     error                 `json:"badFlag,omitempty"`     // An error flag if needed
	// EXISTING_CODE
	// EXISTING_CODE
}

var defaultListOptions = ListOptions{
	FirstRecord: 1,
	MaxRecords:  250,
	LastBlock:   utils.NOPOS,
}

// testLog is used only during testing to export the options for this test case.
func (opts *ListOptions) testLog() {
	logger.TestLog(len(opts.Addrs) > 0, "Addrs: ", opts.Addrs)
	logger.TestLog(opts.Count, "Count: ", opts.Count)
	logger.TestLog(opts.Appearances, "Appearances: ", opts.Appearances)
	logger.TestLog(opts.Silent, "Silent: ", opts.Silent)
	logger.TestLog(opts.NoZero, "NoZero: ", opts.NoZero)
	logger.TestLog(opts.Unripe, "Unripe: ", opts.Unripe)
	logger.TestLog(opts.FirstRecord != 1, "FirstRecord: ", opts.FirstRecord)
	logger.TestLog(opts.MaxRecords != 250, "MaxRecords: ", opts.MaxRecords)
	logger.TestLog(opts.FirstBlock != 0, "FirstBlock: ", opts.FirstBlock)
	logger.TestLog(opts.LastBlock != 0 && opts.LastBlock != utils.NOPOS, "LastBlock: ", opts.LastBlock)
	logger.TestLog(opts.Bounds, "Bounds: ", opts.Bounds)
	opts.Globals.TestLog()
}

// String implements the Stringer interface
func (opts *ListOptions) String() string {
	b, _ := json.MarshalIndent(opts, "", "  ")
	return string(b)
}

// listFinishParseApi finishes the parsing for server invocations. Returns a new ListOptions.
func listFinishParseApi(w http.ResponseWriter, r *http.Request) *ListOptions {
	copy := defaultListOptions
	opts := &copy
	opts.FirstRecord = 1
	opts.MaxRecords = 250
	opts.FirstBlock = 0
	opts.LastBlock = utils.NOPOS
	for key, value := range r.URL.Query() {
		switch key {
		case "addrs":
			for _, val := range value {
				s := strings.Split(val, " ") // may contain space separated items
				opts.Addrs = append(opts.Addrs, s...)
			}
		case "count":
			opts.Count = true
		case "appearances":
			opts.Appearances = true
		case "silent":
			opts.Silent = true
		case "noZero":
			opts.NoZero = true
		case "unripe":
			opts.Unripe = true
		case "firstRecord":
			opts.FirstRecord = globals.ToUint64(value[0])
		case "maxRecords":
			opts.MaxRecords = globals.ToUint64(value[0])
		case "firstBlock":
			opts.FirstBlock = globals.ToUint64(value[0])
		case "lastBlock":
			opts.LastBlock = globals.ToUint64(value[0])
		case "bounds":
			opts.Bounds = true
		default:
			if !globals.IsGlobalOption(key) {
				opts.BadFlag = validate.Usage("Invalid key ({0}) in {1} route.", key, "list")
				return opts
			}
		}
	}
	opts.Globals = *globals.GlobalsFinishParseApi(w, r)
	// EXISTING_CODE
	opts.Addrs, _ = ens.ConvertEns(opts.Globals.Chain, opts.Addrs)
	// EXISTING_CODE

	return opts
}

// listFinishParse finishes the parsing for command line invocations. Returns a new ListOptions.
func listFinishParse(args []string) *ListOptions {
	opts := GetOptions()
	opts.Globals.FinishParse(args)
	defFmt := "txt"
	// EXISTING_CODE
	opts.Addrs, _ = ens.ConvertEns(opts.Globals.Chain, args)
	// EXISTING_CODE
	if len(opts.Globals.Format) == 0 || opts.Globals.Format == "none" {
		opts.Globals.Format = defFmt
	}
	return opts
}

func GetOptions() *ListOptions {
	// EXISTING_CODE
	// EXISTING_CODE
	return &defaultListOptions
}

func ResetOptions() {
	// We want to keep writer between command file calls
	w := GetOptions().Globals.Writer
	defaultListOptions = ListOptions{}
	globals.SetDefaults(&defaultListOptions.Globals)
	defaultListOptions.Globals.Writer = w
}
