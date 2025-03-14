// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package tracesPkg

import (
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/node"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
)

func (opts *TracesOptions) validateTraces() error {
	opts.testLog()

	if opts.BadFlag != nil {
		return opts.BadFlag
	}

	if len(opts.Globals.File) > 0 {
		// Do nothing
	} else {
		if len(opts.Transactions) == 0 && len(opts.Filter) == 0 {
			return validate.Usage("Please supply one or more transaction identifiers or filters.")
		}

		if !node.IsTracingNode(opts.Globals.TestMode, opts.Globals.Chain) {
			return validate.Usage("Tracing is required for this program to work properly.")
		}

		if !validate.CanArticulate(opts.Articulate) {
			return validate.Usage("The {0} option requires an Etherscan API key.", "--articulate")
		}

		if len(opts.Filter) > 0 {
			// TODO: Check validity of the filter string
			if opts.Globals.TestMode {
				v := types.SimpleTraceFilter{}
				logger.Info(v.ParseBangString(opts.Filter))
			}
		}
	}

	err := validate.ValidateIdentifiers(
		opts.Globals.Chain,
		opts.Transactions,
		validate.ValidTransId,
		-1,
		&opts.TransactionIds,
	)
	if err != nil {
		if invalidLiteral, ok := err.(*validate.InvalidIdentifierLiteralError); ok {
			return invalidLiteral
		}
		return err
	}

	return opts.Globals.Validate()
}
