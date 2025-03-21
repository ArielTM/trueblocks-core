// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package monitorsPkg

import (
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/file"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/monitor"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/validate"
)

// HandleCrudCommands
//
// [State]     | Delete | Undelete | Remove | Decache                    |
// ------------|--------|------------------------------------------------|
// Not Deleted | Delete	| Error    | Error  | Delete, Remove and Decache |
// Deleted     | Error  | Undelete | Remove | Remove and Decache         |
// ------------|--------|------------------------------------------------|
func (opts *MonitorsOptions) HandleCrudCommands() error {
	for _, addr := range opts.Addrs {
		m := monitor.NewMonitor(opts.Globals.Chain, addr, false)
		if !file.FileExists(m.Path()) {
			return validate.Usage("No monitor was found for address " + addr + ".")

		} else {
			if opts.Undelete && !m.IsDeleted() {
				return validate.Usage("Monitor for {0} must be deleted before being undeleted.", addr)

			} else {
				if opts.Delete && opts.Remove {
					// do nothing, it will be resolved below...

				} else {
					if opts.Delete && m.IsDeleted() {
						return validate.Usage("Monitor for {0} is already deleted.", addr)

					} else if opts.Remove && !m.IsDeleted() {
						return validate.Usage("Cannot remove a file that has not previously been deleted.")
					}
				}
			}
		}
	}

	for _, addr := range opts.Addrs {
		m := monitor.NewMonitor(opts.Globals.Chain, addr, false)
		if opts.Undelete {
			m.ReadMonitorHeader()
			m.UnDelete()
			m.Close()
			logger.Info(("Monitor " + addr + " was undeleted."))

		} else {
			if opts.Delete {
				m.ReadMonitorHeader()
				m.Delete()
				m.Close()
				logger.Info(("Monitor " + addr + " was deleted but not removed."))
			}

			if opts.Remove {
				wasRemoved, err := m.Remove()
				if !wasRemoved || err != nil {
					logger.Info(("Monitor for " + addr + " was not removed (" + err.Error() + ")"))
				} else {
					logger.Info(("Monitor for " + addr + " was permanently removed."))
				}
			}
		}
	}

	return nil
}
