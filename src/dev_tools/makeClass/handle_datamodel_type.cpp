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
#include "acctlib.h"
#include "options.h"

//------------------------------------------------------------------------------------------------------------
string_q type_2_GoType(const CParameter& field) {
    string_q type = field.type;
    if (startsWith(type, 'C')) {
        return type_2_ModelName(type, false);
    }
    if (type == "blknum")
        return "uint64";
    if (type == "timestamp")
        return "int64";
    if (type == "hash" || type == "bytes32")
        return "common.Hash";
    if (type == "datetime" || type == "bytes")
        return "string";
    if (type == "address")
        return "common.Address";
    if (type == "gas")
        return "Gas";
    if (type == "wei")
        return "Wei";
    return type;
}

string_q debug(const CParameter& field) {
    ostringstream os;
    // os << " //";
    // os << " doc: " << field.doc;
    // os << " disp: " << field.disp;
    // os << " omit: " << (field.is_flags & IS_OMITEMPTY);
    return os.str();
}

//------------------------------------------------------------------------------------------------------------
void generate_go_type_code(COptions* opts, const CClassDefinition& modelIn) {
    CClassDefinition model = modelIn;

    string_q fn = getPathToSource("apps/chifra/pkg/types/types_" + toLower(model.base_name) + ".go");
    string_q contents = asciiFileToString(getPathToTemplates("blank_type.go.tmpl"));
    replaceAll(contents, "[{CLASS_NAME}]", type_2_ModelName(model.gogen, false));

    CParameter raw;
    raw.type = "*Raw" + type_2_ModelName(model.gogen, false);
    raw.name = "raw";
    model.fieldArray.push_back(raw);

    size_t maxNameWid = 0, maxTypeWid = 0;
    for (auto& field : model.fieldArray) {
        string_q type = type_2_GoType(field);
        maxNameWid = max(maxNameWid, field.name.length());
        if (field.name != "raw") {
            maxTypeWid = max(maxTypeWid, type.length());
            field.name = firstUpper(field.name);
        }
        field.type = type_2_GoType(field);
    }

    ostringstream fieldStream, rawStream, modelStream, orderStream;
    for (auto field : model.fieldArray) {
        // if (field.is_flags & IS_ARRAY) {
        //     type = "[]" + type_2_ModelName(type, false);
        // } else if (field.is_flags & IS_OBJECT) {
        //     type = "*" + type_2_ModelName(type, false);
        // }
        string_q type = (field.name % "raw") ? field.type : padRight(field.type, maxTypeWid);
        string_q name = padRight(field.name, maxNameWid);
        fieldStream << "\t" << name << " " << type;
        bool isOmitEmpty = (field.is_flags & IS_OMITEMPTY);
        if (!(field.name % "raw")) {
            rawStream << "\t" << name << " string";
            fieldStream << " `json:\"" << firstLower(field.name);
            rawStream << " `json:\"" << firstLower(field.name);
            if (!isOmitEmpty) {
                modelStream << "\t\t" << padRight("\"" + firstLower(field.name) + "\":", maxNameWid + 3) << " s."
                            << firstUpper(field.name) << "," << debug(field) << endl;
                orderStream << "\t\t\"" << firstLower(field.name) << "\""
                            << "," << debug(field) << endl;
            } else {
                fieldStream << ",omitempty";
            }
            fieldStream << "\"`";
            rawStream << "\"`" << debug(field) << endl;
        }
        fieldStream << debug(field) << endl;
    }

    replaceAll(contents, "[{FIELDS}]", fieldStream.str());
    replaceAll(contents, "[{RAWFIELDS}]", rawStream.str());
    replaceAll(contents, "[{MODEL_FIELDS}]", modelStream.str());
    replaceAll(contents, "[{ORDER_FIELDS}]", orderStream.str());

    codewrite_t cw(fn, contents + "\n");
    cw.nSpaces = 0;
    writeCodeIn(opts, cw);
    // cerr << fn << endl;
}
