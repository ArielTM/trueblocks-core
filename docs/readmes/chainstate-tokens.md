## chifra tokens

<!-- markdownlint-disable MD041 -->
Given the address of an ERC20 token contract, the `chifra tokens` tool reports token balances for one or
more additional addresses. Alternatively, the tool can report the token balances for multiple ERC20
tokens for a single addresses.

In normal operation the **first item** in the `address_list` is assumed to be an ERC20 token
contract whose balances are being queried, whereas the remainder of the list is assumed to be
addresses on which to report.

In `--byAcct` mode, **all addresses** in the `address_list` are assumed to be ERC20 token contracts,
except the final one which is the account whose token balances are reported.

You may optionally specify one or more blocks at which to report. If no block is specified, the
latest block is assumed. You may also optionally specify which parts of the token data to extract.

```[plaintext]
Purpose:
  Retrieve token balance(s) for one or more addresses at given block(s).

Usage:
  chifra tokens [flags] <address> <address> [address...] [block...]

Arguments:
  addrs - two or more addresses (0x...), the first is an ERC20 token, balances for the rest are reported (required)
  blocks - an optional list of one or more blocks at which to report balances, defaults to 'latest'

Flags:
  -p, --parts strings   which parts of the token information to retrieve
                        One or more of [ name | symbol | decimals | totalSupply | version | all ]
  -b, --by_acct         consider each address an ERC20 token except the last, whose balance is reported for each token
  -n, --no_zero         suppress the display of zero balance accounts
  -x, --fmt string      export format, one of [none|json*|txt|csv]
  -v, --verbose         enable verbose (increase detail with --log_level)
  -h, --help            display this help screen

Notes:
  - An address must start with '0x' and be forty-two characters long.
  - Blocks is a space-separated list of values, a start-end range, a special, or any combination.
  - If the token contract(s) from which you request balances are not ERC20 compliant, the results are undefined.
  - If the queried node does not store historical state, the results are undefined.
  - Special blocks are detailed under chifra when --list.
```

Data models produced by this tool:

- [tokenbalance](/data-model/chainstate/#tokenbalance)

Links:

- [api docs](/api/#operation/chainstate-tokens)
- [source code](https://github.com/TrueBlocks/trueblocks-core/tree/master/src/apps/chifra/internal/tokens)

