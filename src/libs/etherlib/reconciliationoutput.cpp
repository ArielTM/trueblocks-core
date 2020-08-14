/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018, 2019 TrueBlocks, LLC (http://trueblocks.io)
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
 * This file was generated with makeClass. Edit only those parts of the code inside
 * of 'EXISTING_CODE' tags.
 */
#include <algorithm>
#include "reconciliationoutput.h"
#include "etherlib.h"

namespace qblocks {

//---------------------------------------------------------------------------
IMPLEMENT_NODE(CReconciliationOutput, CBaseNode);

//---------------------------------------------------------------------------
static string_q nextReconciliationoutputChunk(const string_q& fieldIn, const void* dataPtr);
static string_q nextReconciliationoutputChunk_custom(const string_q& fieldIn, const void* dataPtr);

//---------------------------------------------------------------------------
void CReconciliationOutput::Format(ostream& ctx, const string_q& fmtIn, void* dataPtr) const {
    if (!m_showing)
        return;

    // EXISTING_CODE
    // EXISTING_CODE

    string_q fmt = (fmtIn.empty() ? expContext().fmtMap["reconciliationoutput_fmt"] : fmtIn);
    if (fmt.empty()) {
        toJson(ctx);
        return;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    while (!fmt.empty())
        ctx << getNextChunk(fmt, nextReconciliationoutputChunk, this);
}

//---------------------------------------------------------------------------
string_q nextReconciliationoutputChunk(const string_q& fieldIn, const void* dataPtr) {
    if (dataPtr)
        return reinterpret_cast<const CReconciliationOutput*>(dataPtr)->getValueByName(fieldIn);

    // EXISTING_CODE
    // EXISTING_CODE

    return fldNotFound(fieldIn);
}

//---------------------------------------------------------------------------
string_q CReconciliationOutput::getValueByName(const string_q& fieldName) const {
    // Give customized code a chance to override first
    string_q ret = nextReconciliationoutputChunk_custom(fieldName, this);
    if (!ret.empty())
        return ret;

    // EXISTING_CODE
    // EXISTING_CODE

    // Return field values
    switch (tolower(fieldName[0])) {
        case 'a':
            if (fieldName % "asset") {
                return asset;
            }
            break;
        case 'b':
            if (fieldName % "blockNum") {
                return uint_2_Str(blockNum);
            }
            if (fieldName % "begBal") {
                return begBal;
            }
            if (fieldName % "begBalDiff") {
                return begBalDiff;
            }
            break;
        case 'e':
            if (fieldName % "endBal") {
                return endBal;
            }
            if (fieldName % "endBalCalc") {
                return endBalCalc;
            }
            if (fieldName % "endBalDiff") {
                return endBalDiff;
            }
            break;
        case 'g':
            if (fieldName % "gasCostOutflow") {
                return gasCostOutflow;
            }
            break;
        case 'i':
            if (fieldName % "inflow") {
                return inflow;
            }
            if (fieldName % "intInflow") {
                return intInflow;
            }
            if (fieldName % "intOutflow") {
                return intOutflow;
            }
            break;
        case 'm':
            if (fieldName % "minerRewardInflow2") {
                return minerRewardInflow2;
            }
            if (fieldName % "minerAddInflow") {
                return minerAddInflow;
            }
            if (fieldName % "minerTxFeeInflow") {
                return minerTxFeeInflow;
            }
            break;
        case 'o':
            if (fieldName % "outflow") {
                return outflow;
            }
            break;
        case 'p':
            if (fieldName % "prefundInflow") {
                return prefundInflow;
            }
            break;
        case 'r':
            if (fieldName % "reconciliationType") {
                return reconciliationType;
            }
            if (fieldName % "reconciled") {
                return bool_2_Str(reconciled);
            }
            break;
        case 's':
            if (fieldName % "selfDestructInflow") {
                return selfDestructInflow;
            }
            if (fieldName % "selfDestructOutflow") {
                return selfDestructOutflow;
            }
            break;
        case 't':
            if (fieldName % "timestamp") {
                return ts_2_Str(timestamp);
            }
            break;
        case 'u':
            if (fieldName % "uncleRewardInflow") {
                return uncleRewardInflow;
            }
            break;
        default:
            break;
    }

    // EXISTING_CODE
    // EXISTING_CODE

    // Finally, give the parent class a chance
    return CBaseNode::getValueByName(fieldName);
}

//---------------------------------------------------------------------------------------------------
bool CReconciliationOutput::setValueByName(const string_q& fieldNameIn, const string_q& fieldValueIn) {
    string_q fieldName = fieldNameIn;
    string_q fieldValue = fieldValueIn;

    // EXISTING_CODE
    // EXISTING_CODE

    switch (tolower(fieldName[0])) {
        case 'a':
            if (fieldName % "asset") {
                asset = fieldValue;
                return true;
            }
            break;
        case 'b':
            if (fieldName % "blockNum") {
                blockNum = str_2_Uint(fieldValue);
                return true;
            }
            if (fieldName % "begBal") {
                begBal = fieldValue;
                return true;
            }
            if (fieldName % "begBalDiff") {
                begBalDiff = fieldValue;
                return true;
            }
            break;
        case 'e':
            if (fieldName % "endBal") {
                endBal = fieldValue;
                return true;
            }
            if (fieldName % "endBalCalc") {
                endBalCalc = fieldValue;
                return true;
            }
            if (fieldName % "endBalDiff") {
                endBalDiff = fieldValue;
                return true;
            }
            break;
        case 'g':
            if (fieldName % "gasCostOutflow") {
                gasCostOutflow = fieldValue;
                return true;
            }
            break;
        case 'i':
            if (fieldName % "inflow") {
                inflow = fieldValue;
                return true;
            }
            if (fieldName % "intInflow") {
                intInflow = fieldValue;
                return true;
            }
            if (fieldName % "intOutflow") {
                intOutflow = fieldValue;
                return true;
            }
            break;
        case 'm':
            if (fieldName % "minerRewardInflow2") {
                minerRewardInflow2 = fieldValue;
                return true;
            }
            if (fieldName % "minerAddInflow") {
                minerAddInflow = fieldValue;
                return true;
            }
            if (fieldName % "minerTxFeeInflow") {
                minerTxFeeInflow = fieldValue;
                return true;
            }
            break;
        case 'o':
            if (fieldName % "outflow") {
                outflow = fieldValue;
                return true;
            }
            break;
        case 'p':
            if (fieldName % "prefundInflow") {
                prefundInflow = fieldValue;
                return true;
            }
            break;
        case 'r':
            if (fieldName % "reconciliationType") {
                reconciliationType = fieldValue;
                return true;
            }
            if (fieldName % "reconciled") {
                reconciled = str_2_Bool(fieldValue);
                return true;
            }
            break;
        case 's':
            if (fieldName % "selfDestructInflow") {
                selfDestructInflow = fieldValue;
                return true;
            }
            if (fieldName % "selfDestructOutflow") {
                selfDestructOutflow = fieldValue;
                return true;
            }
            break;
        case 't':
            if (fieldName % "timestamp") {
                timestamp = str_2_Ts(fieldValue);
                return true;
            }
            break;
        case 'u':
            if (fieldName % "uncleRewardInflow") {
                uncleRewardInflow = fieldValue;
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
void CReconciliationOutput::finishParse() {
    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------------------------------
bool CReconciliationOutput::Serialize(CArchive& archive) {
    if (archive.isWriting())
        return SerializeC(archive);

    // Always read the base class (it will handle its own backLevels if any, then
    // read this object's back level (if any) or the current version.
    CBaseNode::Serialize(archive);
    if (readBackLevel(archive))
        return true;

    // EXISTING_CODE
    // EXISTING_CODE
    archive >> blockNum;
    archive >> timestamp;
    archive >> asset;
    archive >> begBal;
    archive >> begBalDiff;
    archive >> inflow;
    archive >> outflow;
    archive >> intInflow;
    archive >> intOutflow;
    archive >> selfDestructInflow;
    archive >> selfDestructOutflow;
    archive >> minerRewardInflow2;
    archive >> minerAddInflow;
    archive >> minerTxFeeInflow;
    archive >> uncleRewardInflow;
    archive >> prefundInflow;
    archive >> gasCostOutflow;
    archive >> endBal;
    archive >> endBalCalc;
    archive >> endBalDiff;
    archive >> reconciliationType;
    archive >> reconciled;
    finishParse();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool CReconciliationOutput::SerializeC(CArchive& archive) const {
    // Writing always write the latest version of the data
    CBaseNode::SerializeC(archive);

    // EXISTING_CODE
    // EXISTING_CODE
    archive << blockNum;
    archive << timestamp;
    archive << asset;
    archive << begBal;
    archive << begBalDiff;
    archive << inflow;
    archive << outflow;
    archive << intInflow;
    archive << intOutflow;
    archive << selfDestructInflow;
    archive << selfDestructOutflow;
    archive << minerRewardInflow2;
    archive << minerAddInflow;
    archive << minerTxFeeInflow;
    archive << uncleRewardInflow;
    archive << prefundInflow;
    archive << gasCostOutflow;
    archive << endBal;
    archive << endBalCalc;
    archive << endBalDiff;
    archive << reconciliationType;
    archive << reconciled;

    return true;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CReconciliationOutputArray& array) {
    uint64_t count;
    archive >> count;
    array.resize(count);
    for (size_t i = 0; i < count; i++) {
        ASSERT(i < array.capacity());
        array.at(i).Serialize(archive);
    }
    return archive;
}

//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& archive, const CReconciliationOutputArray& array) {
    uint64_t count = array.size();
    archive << count;
    for (size_t i = 0; i < array.size(); i++)
        array[i].SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
void CReconciliationOutput::registerClass(void) {
    // only do this once
    if (HAS_FIELD(CReconciliationOutput, "schema"))
        return;

    size_t fieldNum = 1000;
    ADD_FIELD(CReconciliationOutput, "schema", T_NUMBER, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "deleted", T_BOOL, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "showing", T_BOOL, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "cname", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "blockNum", T_BLOCKNUM, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "timestamp", T_TIMESTAMP, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "asset", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "begBal", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "begBalDiff", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "inflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "outflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "intInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "intOutflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "selfDestructInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "selfDestructOutflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "minerRewardInflow2", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "minerAddInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "minerTxFeeInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "uncleRewardInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "prefundInflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "gasCostOutflow", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "endBal", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "endBalCalc", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "endBalDiff", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "reconciliationType", T_TEXT, ++fieldNum);
    ADD_FIELD(CReconciliationOutput, "reconciled", T_BOOL, ++fieldNum);

    // Hide our internal fields, user can turn them on if they like
    HIDE_FIELD(CReconciliationOutput, "schema");
    HIDE_FIELD(CReconciliationOutput, "deleted");
    HIDE_FIELD(CReconciliationOutput, "showing");
    HIDE_FIELD(CReconciliationOutput, "cname");

    builtIns.push_back(_biCReconciliationOutput);

    // EXISTING_CODE
    // EXISTING_CODE
}

//---------------------------------------------------------------------------
string_q nextReconciliationoutputChunk_custom(const string_q& fieldIn, const void* dataPtr) {
    const CReconciliationOutput* rec = reinterpret_cast<const CReconciliationOutput*>(dataPtr);
    if (rec) {
        switch (tolower(fieldIn[0])) {
            // EXISTING_CODE
            case 'd':
                if (fieldIn % "day") {
                    return ts_2_Date(rec->timestamp).Format(FMT_JSON).substr(0,10);
                }
                break;
            case 'h':
                if (fieldIn % "hour") {
                    return BOH(ts_2_Date(rec->timestamp)).Format(FMT_EXPORT).substr(0,13);
                }
                break;
            case 'i':
                if (fieldIn % "issuance") {
                    bigint_t val = rec->nums.minerRewardInflow2 + rec->nums.minerAddInflow + rec->nums.uncleRewardInflow;
                    //cerr << rec->nums << endl;
                    //cerr << padLeft(bni_2_Ether(rec->nums.minerRewardInflow2), 40) << endl;
                    //cerr << padLeft(bni_2_Ether(rec->nums.minerAddInflow), 40) << endl;
                    //cerr << padLeft(bni_2_Ether(rec->nums.uncleRewardInflow), 40) << endl;
                    //cerr << padLeft(bni_2_Ether(val), 40) << endl;
                    if (expContext().asEther) {
                        return bni_2_Ether(val);
                    } else if (expContext().asDollars) {
                        return bni_2_Dollars(rec->nums.timestamp, val);
                    } else {
                        return bni_2_Str(val);
                    }
                }
                break;
            case 'm':
                if (fieldIn % "month") {
                    return ts_2_Date(rec->timestamp).Format(FMT_EXPORT).substr(0,7);
                }
                if (fieldIn % "minerissuance") {
                    bigint_t val = rec->nums.minerRewardInflow2 + rec->nums.minerAddInflow;
                    if (expContext().asEther) {
                        return bni_2_Ether(val);
                    } else if (expContext().asDollars) {
                        return bni_2_Dollars(rec->nums.timestamp, val);
                    } else {
                        return bni_2_Str(val);
                    }
                }
                break;
            case 'w':
                if (fieldIn % "week") {
                    return BOW(ts_2_Date(rec->timestamp)).Format(FMT_EXPORT).substr(0,10);
                }
                break;
            case 'y':
                if (fieldIn % "year") {
                    return ts_2_Date(rec->timestamp).Format(FMT_EXPORT).substr(0,4);
                }
                break;
            // EXISTING_CODE
            case 'p':
                // Display only the fields of this node, not it's parent type
                if (fieldIn % "parsed")
                    return nextBasenodeChunk(fieldIn, rec);
                // EXISTING_CODE
                // EXISTING_CODE
                break;

            default:
                break;
        }
    }

    return "";
}

//---------------------------------------------------------------------------
bool CReconciliationOutput::readBackLevel(CArchive& archive) {
    bool done = false;
    // EXISTING_CODE
    // EXISTING_CODE
    return done;
}

//---------------------------------------------------------------------------
CArchive& operator<<(CArchive& archive, const CReconciliationOutput& rec) {
    rec.SerializeC(archive);
    return archive;
}

//---------------------------------------------------------------------------
CArchive& operator>>(CArchive& archive, CReconciliationOutput& rec) {
    rec.Serialize(archive);
    return archive;
}

//-------------------------------------------------------------------------
ostream& operator<<(ostream& os, const CReconciliationOutput& item) {
    // EXISTING_CODE
    // EXISTING_CODE

    item.Format(os, "", nullptr);
    os << "\n";
    return os;
}

//---------------------------------------------------------------------------
const char* STR_DISPLAY_RECONCILIATIONOUTPUT = "";

//---------------------------------------------------------------------------
// EXISTING_CODE
//---------------------------------------------------------------------------
string_q bni_2_Ether(const bigint_t& num) {
    if (num == 0)
        return "";

    bigint_t n = num;
    bool negative = false;
    if (n < 0) {
        negative = true;
        n = n * -1;
    }

    string_q ret = wei_2_Ether(str_2_Wei(bni_2_Str(n)));
    CStringArray parts;
    explode(parts, ret, '.');
    ret = parts[0] + ".";
    if (parts.size() == 1)
        return (negative ? "-" : "") + ret + "0000000";
    if (parts[1].length() >= 7)
        return (negative ? "-" : "") + ret + parts[1].substr(0, 7);
    return (negative ? "-" : "") + ret + parts[1] + string_q(7 - parts[1].length(), '0');
}

//---------------------------------------------------------------------------
string_q bni_2_Dollars(const timestamp_t& ts, const bigint_t& num) {
    if (num == 0)
        return "";
    bigint_t n = num;
    bool negative = false;
    if (n < 0) {
        negative = true;
        n = n * -1;
    }
    return (negative ? "-" : "") + wei_2_Dollars(ts, str_2_Wei(bni_2_Str(n)));
}

//---------------------------------------------------------------------------
CReconciliationOutput::CReconciliationOutput(const CReconciliation& numsIn) {
    nums = numsIn;
    reconciliationType = nums.reconciliationType;
    reconciled = nums.reconciled;
    blockNum = nums.blockNum;
    timestamp = nums.timestamp;
    if (expContext().asEther) {
        asset = "ETH";
        begBal = bni_2_Ether(nums.begBal);
        begBalDiff = bni_2_Ether(nums.begBalDiff);
        inflow = bni_2_Ether(nums.inflow);
        outflow = bni_2_Ether(nums.outflow);
        intInflow = bni_2_Ether(nums.intInflow);
        intOutflow = bni_2_Ether(nums.intOutflow);
        selfDestructInflow = bni_2_Ether(nums.selfDestructInflow);
        selfDestructOutflow = bni_2_Ether(nums.selfDestructOutflow);
        minerRewardInflow2 = bni_2_Ether(nums.minerRewardInflow2);
        minerAddInflow = bni_2_Ether(nums.minerAddInflow);
        minerTxFeeInflow = bni_2_Ether(nums.minerTxFeeInflow);
        uncleRewardInflow = bni_2_Ether(nums.uncleRewardInflow);
        prefundInflow = bni_2_Ether(nums.prefundInflow);
        gasCostOutflow = bni_2_Ether(nums.gasCostOutflow);
        endBal = bni_2_Ether(nums.endBal);
        endBalCalc = bni_2_Ether(nums.endBalCalc);
        endBalDiff = bni_2_Ether(nums.endBalDiff);
    } else if (expContext().asDollars) {
        asset = "USD";
        begBal = bni_2_Dollars(nums.timestamp, nums.begBal);
        begBalDiff = bni_2_Dollars(nums.timestamp, nums.begBalDiff);
        inflow = bni_2_Dollars(nums.timestamp, nums.inflow);
        outflow = bni_2_Dollars(nums.timestamp, nums.outflow);
        intInflow = bni_2_Dollars(nums.timestamp, nums.intInflow);
        intOutflow = bni_2_Dollars(nums.timestamp, nums.intOutflow);
        selfDestructInflow = bni_2_Dollars(nums.timestamp, nums.selfDestructInflow);
        selfDestructOutflow = bni_2_Dollars(nums.timestamp, nums.selfDestructOutflow);
        minerRewardInflow2 = bni_2_Dollars(nums.timestamp, nums.minerRewardInflow2);
        minerAddInflow = bni_2_Dollars(nums.timestamp, nums.minerAddInflow);
        minerTxFeeInflow = bni_2_Dollars(nums.timestamp, nums.minerTxFeeInflow);
        uncleRewardInflow = bni_2_Dollars(nums.timestamp, nums.uncleRewardInflow);
        prefundInflow = bni_2_Dollars(nums.timestamp, nums.prefundInflow);
        gasCostOutflow = bni_2_Dollars(nums.timestamp, nums.gasCostOutflow);
        endBal = bni_2_Dollars(nums.timestamp, nums.endBal);
        endBalCalc = bni_2_Dollars(nums.timestamp, nums.endBalCalc);
        endBalDiff = bni_2_Dollars(nums.timestamp, nums.endBalDiff);
    } else {
        asset = "WEI";
        begBal = bni_2_Str(nums.begBal);
        begBalDiff = bni_2_Str(nums.begBalDiff);
        inflow = bni_2_Str(nums.inflow);
        outflow = bni_2_Str(nums.outflow);
        intInflow = bni_2_Str(nums.intInflow);
        intOutflow = bni_2_Str(nums.intOutflow);
        selfDestructInflow = bni_2_Str(nums.selfDestructInflow);
        selfDestructOutflow = bni_2_Str(nums.selfDestructOutflow);
        minerRewardInflow2 = bni_2_Str(nums.minerRewardInflow2);
        minerAddInflow = bni_2_Str(nums.minerAddInflow);
        minerTxFeeInflow = bni_2_Str(nums.minerTxFeeInflow);
        uncleRewardInflow = bni_2_Str(nums.uncleRewardInflow);
        prefundInflow = bni_2_Str(nums.prefundInflow);
        gasCostOutflow = bni_2_Str(nums.gasCostOutflow);
        endBal = bni_2_Str(nums.endBal);
        endBalCalc = bni_2_Str(nums.endBalCalc);
        endBalDiff = bni_2_Str(nums.endBalDiff);
    }
}
// EXISTING_CODE
}  // namespace qblocks
