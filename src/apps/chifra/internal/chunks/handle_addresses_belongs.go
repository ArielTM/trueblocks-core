// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package chunksPkg

import (
	"context"
	"fmt"
	"io"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/cache"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/file"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/index"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/output"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/types"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/utils"
)

// HandleIndexBelongs displays the resolved records in a chunk given a single address
func (opts *ChunksOptions) HandleIndexBelongs(blockNums []uint64) error {
	ctx, cancel := context.WithCancel(context.Background())
	fetchData := func(modelChan chan types.Modeler[types.RawModeler], errorChan chan error) {
		showAddressesBelongs := func(walker *index.CacheWalker, path string, first bool) (bool, error) {
			return opts.handleResolvedRecords(modelChan, walker, path, first)
		}

		walker := index.NewCacheWalker(
			opts.Globals.Chain,
			opts.Globals.TestMode,
			10000, /* maxTests */
			showAddressesBelongs,
		)

		if err := walker.WalkBloomFilters(blockNums); err != nil {
			errorChan <- err
			cancel()
		}
	}

	return output.StreamMany(ctx, fetchData, opts.Globals.OutputOpts())
}

// handleResolvedRecords is a helper function for HandleIndexBelongs and verbose versions of
// HandleAddresses and HandleAppearances. It is called once for each chunk in the index and
// depends on the values of opts.Globals.Verbose and opts.Belongs.
func (opts *ChunksOptions) handleResolvedRecords(modelChan chan types.Modeler[types.RawModeler], walker *index.CacheWalker, path string, first bool) (bool, error) {
	if path != cache.ToBloomPath(path) {
		return false, fmt.Errorf("should not happen in showAddressesBelongs")
	}

	path = cache.ToIndexPath(path)
	if !file.FileExists(path) {
		// Bloom files exist, but index files don't. It's okay.
		return true, nil
	}

	indexChunk, err := index.NewChunkData(path)
	if err != nil {
		return false, err
	}
	defer indexChunk.Close()

	_, err = indexChunk.File.Seek(int64(index.HeaderWidth), io.SeekStart)
	if err != nil {
		return false, err
	}

	cnt := 0
	for i := 0; i < int(indexChunk.Header.AddressCount); i++ {
		if opts.Globals.TestMode && i > walker.MaxTests() {
			continue
		}

		s := simpleAppearanceTable{}
		err := s.AddressRecord.ReadAddress(indexChunk.File)
		if err != nil {
			return false, err
		}

		if opts.shouldShow(s.AddressRecord) {
			if uint64(cnt) >= opts.MaxAddrs {
				break
			}

			if s.Appearances, err = indexChunk.ReadAppearanceRecordsAndResetOffset(&s.AddressRecord); err != nil {
				return false, err
			}
			if opts.FirstBlock != 0 || opts.LastBlock != utils.NOPOS {
				good := []index.AppearanceRecord{}
				for _, app := range s.Appearances {
					if uint64(app.BlockNumber) >= opts.FirstBlock && uint64(app.BlockNumber) <= opts.LastBlock {
						good = append(good, app)
					}
				}
				s.Appearances = good
				s.AddressRecord.Count = uint32(len(good))
			}
			if len(s.Appearances) == 0 {
				continue
			}
			modelChan <- &s
			cnt++
		}
	}

	return true, nil
}
