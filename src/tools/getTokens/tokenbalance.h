#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass --run. Edit only those parts of
 * the code inside of 'EXISTING_CODE' tags.
 */
#include "acctlib.h"

namespace qblocks {

// EXISTING_CODE
typedef enum {
    TOK_NONE = 0,
    TOK_NAME = (1 << 1),
    TOK_ADDRESS = (1 << 2),
    TOK_DECIMALS = (1 << 3),
    TOK_TOTALSUPPLY = (1 << 4),
    TOK_SYMBOL = (1 << 5),
    TOK_PARTS = (TOK_NAME | TOK_ADDRESS | TOK_SYMBOL | TOK_DECIMALS | TOK_TOTALSUPPLY),
    TOK_HOLDER = (1 << 6),
    TOK_BALANCE = (1 << 7),
    TOK_BALRECORD = (TOK_NAME | TOK_HOLDER | TOK_ADDRESS | TOK_SYMBOL | TOK_DECIMALS | TOK_BALANCE)
} tokstate_t;
// EXISTING_CODE

//--------------------------------------------------------------------------
class CTokenBalance : public CMonitor {
  public:
    blknum_t blockNumber;
    string_q date;
    wei_t totalSupply;
    blknum_t transactionIndex;
    address_t holder;
    wei_t priorBalance;
    wei_t balance;
    bigint_t diff;

  public:
    CTokenBalance(void);
    CTokenBalance(const CTokenBalance& to);
    virtual ~CTokenBalance(void);
    CTokenBalance& operator=(const CTokenBalance& to);

    DECLARE_NODE(CTokenBalance);

    // EXISTING_CODE
    // EXISTING_CODE
    bool operator==(const CTokenBalance& it) const;
    bool operator!=(const CTokenBalance& it) const {
        return !operator==(it);
    }
    friend bool operator<(const CTokenBalance& v1, const CTokenBalance& v2);
    friend ostream& operator<<(ostream& os, const CTokenBalance& it);

  protected:
    void clear(void);
    void initialize(void);
    void duplicate(const CTokenBalance& to);
    bool readBackLevel(CArchive& archive) override;

    // EXISTING_CODE
    // EXISTING_CODE
};

//--------------------------------------------------------------------------
inline CTokenBalance::CTokenBalance(void) {
    initialize();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CTokenBalance::CTokenBalance(const CTokenBalance& to) {
    // EXISTING_CODE
    // EXISTING_CODE
    duplicate(to);
}

// EXISTING_CODE
// EXISTING_CODE

//--------------------------------------------------------------------------
inline CTokenBalance::~CTokenBalance(void) {
    clear();
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTokenBalance::clear(void) {
    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTokenBalance::initialize(void) {
    CMonitor::initialize();

    blockNumber = 0;
    date = "";
    totalSupply = 0;
    transactionIndex = 0;
    holder = "";
    priorBalance = 0;
    balance = 0;
    diff = 0;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline void CTokenBalance::duplicate(const CTokenBalance& to) {
    clear();
    CMonitor::duplicate(to);

    blockNumber = to.blockNumber;
    date = to.date;
    totalSupply = to.totalSupply;
    transactionIndex = to.transactionIndex;
    holder = to.holder;
    priorBalance = to.priorBalance;
    balance = to.balance;
    diff = to.diff;

    // EXISTING_CODE
    // EXISTING_CODE
}

//--------------------------------------------------------------------------
inline CTokenBalance& CTokenBalance::operator=(const CTokenBalance& to) {
    duplicate(to);
    // EXISTING_CODE
    // EXISTING_CODE
    return *this;
}

//-------------------------------------------------------------------------
inline bool CTokenBalance::operator==(const CTokenBalance& it) const {
    // EXISTING_CODE
    // EXISTING_CODE
    // Equality operator as defined in class definition
    return address == it.address;
}

//-------------------------------------------------------------------------
inline bool operator<(const CTokenBalance& v1, const CTokenBalance& v2) {
    // EXISTING_CODE
    // EXISTING_CODE
    // Default sort as defined in class definition
    return v1.address < v2.address;
}

//---------------------------------------------------------------------------
typedef vector<CTokenBalance> CTokenBalanceArray;
extern CArchive& operator>>(CArchive& archive, CTokenBalanceArray& array);
extern CArchive& operator<<(CArchive& archive, const CTokenBalanceArray& array);

//---------------------------------------------------------------------------
extern CArchive& operator<<(CArchive& archive, const CTokenBalance& tok);
extern CArchive& operator>>(CArchive& archive, CTokenBalance& tok);

//---------------------------------------------------------------------------
extern const char* STR_DISPLAY_TOKENBALANCE;

//---------------------------------------------------------------------------
// EXISTING_CODE
// EXISTING_CODE
}  // namespace qblocks
