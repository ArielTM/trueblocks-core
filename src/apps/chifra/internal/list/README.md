## chifra list

<!-- markdownlint-disable MD041 -->
`chifra list` takes one or more addresses, queries the index of appearances, and builds TrueBlocks
monitors. A TrueBlocks monitor is a file that contains blockNumber.transactionId pairs (transaction
identifiers) representing the history of the address.

Because TrueBlocks only extracts data from the Ethereum node when it's requested, the first time
you list an address it takes about a minute. Subsequent queries are much faster because TrueBlocks
caches the results.

Note that `chifra list` only queries the index, it does not extract the full transactional details.
You may use `chifra export` for that.

```[plaintext]
Purpose:
  List every appearance of an address anywhere on the chain.

Usage:
  chifra list [flags] <address> [address...]

Arguments:
  addrs - one or more addresses (0x...) to list (required)

Flags:
  -U, --count               display only the count of records for each monitor
  -n, --no_zero             suppress the display of zero appearance accounts
  -u, --unripe              list transactions labeled upripe (i.e. less than 28 blocks old)
  -c, --first_record uint   the first record to process (default 1)
  -e, --max_records uint    the maximum number of records to process (default 250)
  -F, --first_block uint    first block to export (inclusive, ignored when freshening)
  -L, --last_block uint     last block to export (inclusive, ignored when freshening)
  -x, --fmt string          export format, one of [none|json*|txt|csv]
  -v, --verbose             enable verbose (increase detail with --log_level)
  -h, --help                display this help screen

Notes:
  - No other options are permitted when --silent is selected.
```

Data models produced by this tool:

- [appearance](/data-model/accounts/#appearance)
- [monitor](/data-model/accounts/#monitor)
- [appearancecount](/data-model/accounts/#appearancecount)
- [bounds](/data-model/accounts/#bounds)

<!-- markdownlint-disable MD041 -->
### Other Options

All tools accept the following additional flags, although in some cases, they have no meaning.

```[plaintext]
  -v, --version         display the current version of the tool
      --wei             export values in wei (the default)
      --ether           export values in ether
      --raw             pass raw RPC data directly from the node with no processing
      --output string   write the results to file 'fn' and return the filename
      --append          for --output command only append to instead of replace contents of file
      --file string     specify multiple sets of command line options in a file
  -x, --fmt string      export format, one of [none|json*|txt|csv]
  -v, --verbose         enable verbose (increase detail with --log_level)
  -h, --help            display this help screen
  ```

**Note:** For the `--file string` option, you may place a series of valid command lines in a file using any
valid flags. In some cases, this may significantly improve performance. A semi-colon at the start
of any line makes it a comment.

**Note:** If you use `--output --append` option and at the same time the `--file` option, you may not switch
export formats in the command file. For example, a command file with two different commands, one with `--fmt csv`
and the other with `--fmt json` will produce both invalid CSV and invalid JSON.

