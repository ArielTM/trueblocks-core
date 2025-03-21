// Copyright 2021 The TrueBlocks Authors. All rights reserved.
// Use of this source code is governed by a license that can
// be found in the LICENSE file.

package blocksPkg

import (
	"os"
	"path/filepath"
	"strings"

	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/base"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/cache"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/file"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/logger"
	"github.com/TrueBlocks/trueblocks-core/src/apps/chifra/pkg/rpcClient"
)

func (opts *BlocksOptions) HandleDecache() error {
	pairs := []base.NumPair[uint32]{}
	for _, br := range opts.BlockIds {
		blockNums, err := br.ResolveBlocks(opts.Globals.Chain)
		if err != nil {
			return err
		}
		for _, bn := range blockNums {
			rawBlock, err := rpcClient.GetBlockByNumberWithTxs(opts.Globals.Chain, bn, false)
			if err != nil {
				return err
			}
			for _, tx := range rawBlock.Transactions {
				pairs = append(pairs, base.NumPair[uint32]{N1: uint32(bn), N2: uint32(tx.TransactionIndex)})
			}
		}
	}

	testMode := opts.Globals.TestMode
	itemsSeen := int64(0)
	itemsRemoved := int64(0)
	bytesRemoved := int64(0)
	processorFunc := func(fileName string) bool {
		itemsSeen++
		if !file.FileExists(fileName) {
			logger.Progress(!testMode && itemsSeen%203 == 0, "Already removed ", fileName)
			return true // continue processing
		}

		itemsRemoved++
		bytesRemoved += file.FileSize(fileName)
		logger.Info(!testMode && itemsRemoved%20 == 0, "Removed ", itemsRemoved, " items and ", bytesRemoved, " bytes.", fileName)

		os.Remove(fileName)
		if opts.Globals.Verbose {
			logger.Info(fileName, "was removed.")
		}
		path, _ := filepath.Split(fileName)
		if empty, _ := file.IsFolderEmpty(path); empty {
			os.RemoveAll(path)
			if opts.Globals.Verbose {
				logger.Info("Empty folder", path, "was removed.")
			}
		}

		return true
	}

	caches := []string{"blocks", "txs", "traces"}
	if cont, err := cache.DecacheItems(opts.Globals.Chain, "", processorFunc, caches, pairs); err != nil || !cont {
		return err
	}

	if itemsSeen == 0 {
		logger.Info("No items matching the query were found in the cache.", strings.Repeat(" ", 60))
	} else {
		logger.Info(itemsRemoved, "items totaling", bytesRemoved, "bytes were removed from the cache.", strings.Repeat(" ", 60))
	}

	return nil
}

// TODO: We could use a Modeler that only delivers a message (i.e. SimpleModeler). Use it here and in monitors --decache to report some data in case the standard error is redirected.
