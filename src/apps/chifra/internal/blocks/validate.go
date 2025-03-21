// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package blocksPkg

import (
	"errors"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/node"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
)

func (opts *BlocksOptions) validateBlocks() error {
	opts.testLog()

	if opts.BadFlag != nil {
		return opts.BadFlag
	}

	for _, emitter := range opts.Emitter {
		valid, err := validate.IsValidAddressE(emitter)
		if !valid {
			return err
		}
	}

	for _, topic := range opts.Topic {
		valid, err := validate.IsValidTopicE(topic)
		if !valid {
			return err
		}
	}

	if opts.Cache && (opts.List > 0 || opts.ListCount > 0) {
		return validate.Usage("You may not use the {0} option with the {1} options.", "--cache", "--list")
	}

	if opts.ListCount == 0 {
		err := validate.ValidateIdentifiers(
			opts.Globals.Chain,
			opts.Blocks,
			validate.ValidBlockIdWithRange,
			1,
			&opts.BlockIds,
		)
		if err != nil {
			if invalidLiteral, ok := err.(*validate.InvalidIdentifierLiteralError); ok {
				return invalidLiteral
			}

			if errors.Is(err, validate.ErrTooManyRanges) {
				return validate.Usage("Specify only a single block range at a time.")
			}

			return err
		}
		if opts.List > 0 {
			return validate.Usage("You must supply a non-zero value for the {0} option with {1}.", "--list_count", "--list")
		}
	} else {
		if opts.List == 0 {
			return validate.Usage("You must supply a non-zero value for the {0} option with {1}.", "--list", "--list_count")
		}
	}

	if len(opts.Flow) > 0 {
		if !opts.Apps && !opts.Uniq {
			return validate.Usage("The {0} option is only available with the {1} option", "--flow", "--apps or --uniq")
		}
		err := validate.ValidateEnum("flow", opts.Flow, "[from|to|reward]")
		if err != nil {
			return err
		}
	}

	if len(opts.Globals.File) > 0 {
		// Do nothing
	} else {
		if opts.List == 0 {
			if len(opts.Blocks) == 0 && opts.ListCount == 0 {
				return validate.Usage("Please supply one or more block identifiers or the --list_count option.")
			}
			if !opts.Logs && (len(opts.Emitter) > 0 || len(opts.Topic) > 0) {
				return validate.Usage("The {0} option are only available with the {1} option.", "--emitter and --topic", "--log")
			}
			if opts.Cache && opts.Uncles {
				return validate.Usage("The {0} option is not available{1}.", "--cache", " with the --uncles option")
			}
			if opts.Traces && opts.Hashes {
				return validate.Usage("The {0} option is not available{1}.", "--traces", " with the --hashes option")
			}
			if !validate.CanArticulate(opts.Articulate) {
				return validate.Usage("The {0} option requires an Etherscan API key.", "--articulate")
			}
			if opts.Articulate && !opts.Logs {
				return validate.Usage("The {0} option is available only with {1}.", "--articulate", "the --logs option")
			}
			if opts.Uniq {
				if opts.Traces {
					return validate.Usage("The {0} option is not available{1}.", "--traces", " with the --uniq option")
				}
				if opts.Cache {
					return validate.Usage("The {0} option is not available{1}.", "--cache", " with the --uniq option")
				}
				if opts.Uncles {
					return validate.Usage("The {0} option is not available{1}.", "--uncles", " with the --uniq option")
				}
			}
			if opts.Apps {
				if opts.Traces {
					return validate.Usage("The {0} option is not available{1}.", "--traces", " with the --apps option")
				}
				if opts.Cache {
					return validate.Usage("The {0} option is not available{1}.", "--cache", " with the --apps option")
				}
			}
			if opts.BigRange != 500 && !opts.Logs {
				return validate.Usage("The {0} option is only available with the {1} option.", "--big_range", "--logs")
			}

			if opts.Traces && !node.IsTracingNode(opts.Globals.TestMode, opts.Globals.Chain) {
				return validate.Usage("Tracing is required for this program to work properly.")
			}
		}
	}

	return opts.Globals.Validate()
}
