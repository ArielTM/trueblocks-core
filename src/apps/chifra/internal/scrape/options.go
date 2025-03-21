// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.
/*
 * This file was auto generated with makeClass --gocmds. DO NOT EDIT.
 */

package scrapePkg

import (
	"encoding/json"
	"net/http"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/internal/globals"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/config/scrapeCfg"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
)

// ScrapeOptions provides all command options for the chifra scrape command.
type ScrapeOptions struct {
	BlockCnt   uint64                   `json:"blockCnt,omitempty"`   // Maximum number of blocks to process per pass
	Pin        bool                     `json:"pin,omitempty"`        // Pin new chunks (requires locally-running IPFS daemon or --remote)
	Remote     bool                     `json:"remote,omitempty"`     // Pin new chunks to the gateway (requires pinning service keys)
	Sleep      float64                  `json:"sleep,omitempty"`      // Seconds to sleep between scraper passes
	StartBlock uint64                   `json:"startBlock,omitempty"` // First block to visit (available only for blaze scraper)
	Settings   scrapeCfg.ScrapeSettings `json:"settings,omitempty"`   // Configuration items for the scrape
	Globals    globals.GlobalOptions    `json:"globals,omitempty"`    // The global options
	BadFlag    error                    `json:"badFlag,omitempty"`    // An error flag if needed
	// EXISTING_CODE
	// EXISTING_CODE
}

var defaultScrapeOptions = ScrapeOptions{
	BlockCnt: 2000,
}

// testLog is used only during testing to export the options for this test case.
func (opts *ScrapeOptions) testLog() {
	logger.TestLog(opts.BlockCnt != 2000, "BlockCnt: ", opts.BlockCnt)
	logger.TestLog(opts.Pin, "Pin: ", opts.Pin)
	logger.TestLog(opts.Remote, "Remote: ", opts.Remote)
	logger.TestLog(opts.Sleep != float64(14), "Sleep: ", opts.Sleep)
	logger.TestLog(opts.StartBlock != 0, "StartBlock: ", opts.StartBlock)
	opts.Settings.TestLog(opts.Globals.Chain, opts.Globals.TestMode)
	opts.Globals.TestLog()
}

// String implements the Stringer interface
func (opts *ScrapeOptions) String() string {
	b, _ := json.MarshalIndent(opts, "", "  ")
	return string(b)
}

// scrapeFinishParseApi finishes the parsing for server invocations. Returns a new ScrapeOptions.
func scrapeFinishParseApi(w http.ResponseWriter, r *http.Request) *ScrapeOptions {
	copy := defaultScrapeOptions
	opts := &copy
	opts.BlockCnt = 2000
	opts.Sleep = 14
	opts.StartBlock = 0
	opts.Settings.Apps_per_chunk = 200000
	opts.Settings.Snap_to_grid = 100000
	opts.Settings.First_snap = 0
	opts.Settings.Unripe_dist = 28
	opts.Settings.Channel_count = 20
	for key, value := range r.URL.Query() {
		switch key {
		case "blockCnt":
			opts.BlockCnt = globals.ToUint64(value[0])
		case "pin":
			opts.Pin = true
		case "remote":
			opts.Remote = true
		case "sleep":
			opts.Sleep = globals.ToFloat64(value[0])
		case "startBlock":
			opts.StartBlock = globals.ToUint64(value[0])
		case "appsPerChunk":
			opts.Settings.Apps_per_chunk = globals.ToUint64(value[0])
		case "snapToGrid":
			opts.Settings.Snap_to_grid = globals.ToUint64(value[0])
		case "firstSnap":
			opts.Settings.First_snap = globals.ToUint64(value[0])
		case "unripeDist":
			opts.Settings.Unripe_dist = globals.ToUint64(value[0])
		case "channelCount":
			opts.Settings.Channel_count = globals.ToUint64(value[0])
		case "allowMissing":
			opts.Settings.Allow_missing = true
		default:
			if !globals.IsGlobalOption(key) {
				opts.BadFlag = validate.Usage("Invalid key ({0}) in {1} route.", key, "scrape")
				return opts
			}
		}
	}
	opts.Globals = *globals.GlobalsFinishParseApi(w, r)
	// EXISTING_CODE
	// EXISTING_CODE

	return opts
}

// scrapeFinishParse finishes the parsing for command line invocations. Returns a new ScrapeOptions.
func scrapeFinishParse(args []string) *ScrapeOptions {
	opts := GetOptions()
	opts.Globals.FinishParse(args)
	defFmt := "txt"
	// EXISTING_CODE
	if len(args) == 1 && (args[0] == "run" || args[0] == "indexer") {
		// these options have been deprecated, so do nothing
	} else if len(args) > 1 {
		opts.BadFlag = validate.Usage("Invalid argument {0}", args[0])
	}
	configFn := "blockScrape.toml"
	// EXISTING_CODE
	opts.Settings, _ = scrapeCfg.GetSettings(opts.Globals.Chain, configFn, &scrapeCfg.Unset)
	if len(opts.Globals.Format) == 0 || opts.Globals.Format == "none" {
		opts.Globals.Format = defFmt
	}
	return opts
}

func GetOptions() *ScrapeOptions {
	// EXISTING_CODE
	// EXISTING_CODE
	return &defaultScrapeOptions
}

func ResetOptions() {
	// We want to keep writer between command file calls
	w := GetOptions().Globals.Writer
	defaultScrapeOptions = ScrapeOptions{}
	globals.SetDefaults(&defaultScrapeOptions.Globals)
	defaultScrapeOptions.Globals.Writer = w
}
