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
 * Parts of this file were generated with makeClass --options. Edit only those parts of
 * the code outside of the BEG_CODE/END_CODE sections
 */
#include "options.h"
#include "measure.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
    // BEG_CODE_OPTIONS
    // clang-format off
    COption("mode", "m", "enum[cmd*|api|both]", OPT_FLAG, "determine which set of tests to run"),
    COption("filter", "f", "enum[fast*|medi|slow|all]", OPT_FLAG, "determine how long it takes to run tests"),
    COption("skip", "s", "<uint64>", OPT_HIDDEN | OPT_FLAG, "run only every 'skip' test (faster)"),
    COption("report", "r", "", OPT_SWITCH, "display performance report to screen"),
    COption("", "", "", OPT_DESCRIPTION, "Run TrueBlocks' test cases with options."),
    // clang-format on
    // END_CODE_OPTIONS
};
static const size_t nParams = sizeof(params) / sizeof(COption);

extern void establishTestData(void);
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {
    if (!standardOptions(command))
        return false;

    ::setenv("NO_USERQUERY", "true", 1);

    // BEG_CODE_LOCAL_INIT
    string_q mode = "";
    // END_CODE_LOCAL_INIT
    string_q path;

    bool hasKey = getGlobalConfig("")->getConfigStr("keys.etherscan", "apiKey", "<not_set>") != "<not_set>";
    bool wantsTest = getEnvStr("TEST_SLURPS") == "true";
    bool runSlurps = hasKey && wantsTest;

    CToml config(rootConfigToml_makeClass);

    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        if (false) {
            // do nothing -- make auto code generation easier
            // BEG_CODE_AUTO
        } else if (startsWith(arg, "-m:") || startsWith(arg, "--mode:")) {
            if (!confirmEnum("mode", mode, arg))
                return false;
        } else if (arg == "-m" || arg == "--mode") {
            return flag_required("mode");

        } else if (startsWith(arg, "-f:") || startsWith(arg, "--filter:")) {
            if (!confirmEnum("filter", filter, arg))
                return false;
        } else if (arg == "-f" || arg == "--filter") {
            return flag_required("filter");

        } else if (startsWith(arg, "-s:") || startsWith(arg, "--skip:")) {
            if (!confirmUint("skip", skip, arg))
                return false;
        } else if (arg == "-s" || arg == "--skip") {
            return flag_required("skip");

        } else if (arg == "-r" || arg == "--report") {
            report = true;

        } else if (startsWith(arg, '-')) {  // do not collapse

            if (!builtInCmd(arg)) {
                return invalid_option(arg);
            }

            // END_CODE_AUTO
        } else {
            arg = trim(arg, '/');
            if (arg == "libs" || arg == "libs/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("libs/utillib");
                tests.push_back("libs/etherlib");
                tests.push_back("libs/acctlib");

            } else if (arg == "dev_tools" || arg == "dev_tools/") {
                break;

            } else if (arg == "tools" || arg == "tools/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                if (runSlurps) {
                    tests.push_back("tools/ethslurp");
                }
                tests.push_back("tools/ethNames");
                tests.push_back("tools/getBlocks");
                tests.push_back("tools/getLogs");
                tests.push_back("tools/getReceipts");
                tests.push_back("tools/getState");
                tests.push_back("tools/getTokens");
                tests.push_back("tools/getTraces");
                tests.push_back("tools/getTrans");
                tests.push_back("tools/grabABI");
                tests.push_back("tools/whenBlock");

            } else if (arg == "apps" || arg == "apps/") {
                static bool been_here = false;
                if (been_here)
                    break;
                been_here = true;
                tests.push_back("apps/acctExport");
                tests.push_back("apps/blockScrape");
                tests.push_back("apps/cacheStatus");
                tests.push_back("apps/chunkMan");
                tests.push_back("apps/chifra");
                tests.push_back("apps/config");
                tests.push_back("apps/fireStorm");
                tests.push_back("apps/init");
                tests.push_back("apps/daemon");

            } else {
                tests.push_back(arg);
            }
        }
    }

    if (getGlobalConfig("")->getConfigBool("dev", "debug_curl", false))
        return usage("[dev]debug_curl is set in config file. All tests will fail.");

    modes = (mode == "both" ? BOTH : (mode == "api" ? API : CMD));
    if (!isNodeRunning())
        return usage("Ethereum at " + getCurlContext()->baseURL + " was not found. All tests will fail.");

    if (filter.empty())
        filter = "fast";
    else if (filter == "all")
        filter = "";

    if (tests.empty()) {
        full_test = true;
        tests.push_back("libs/utillib");
        tests.push_back("libs/etherlib");
        tests.push_back("libs/acctlib");
        if (runSlurps) {
            tests.push_back("tools/ethslurp");
        }
        tests.push_back("tools/ethNames");
        tests.push_back("tools/getBlocks");
        tests.push_back("tools/getLogs");
        tests.push_back("tools/getReceipts");
        tests.push_back("tools/getState");
        tests.push_back("tools/getTokens");
        tests.push_back("tools/getTraces");
        tests.push_back("tools/getTrans");
        tests.push_back("tools/grabABI");
        tests.push_back("tools/whenBlock");
        tests.push_back("apps/acctExport");
        tests.push_back("apps/blockScrape");
        tests.push_back("apps/cacheStatus");
        tests.push_back("apps/chunkMan");
        tests.push_back("apps/chifra");
        tests.push_back("apps/config");
        tests.push_back("apps/fireStorm");
        tests.push_back("apps/init");
        tests.push_back("apps/daemon");
    }

    SHOW_FIELD(CTestCase, "test_id");

    apiProvider = getGlobalConfig("testRunner")->getConfigStr("settings", "api_provider", "http://localhost:8080");
    if (!endsWith(apiProvider, '/'))
        apiProvider += "/";

    establishTestData();

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    // BEG_CODE_GLOBALOPTS
    registerOptions(nParams, params, 0);
    // END_CODE_GLOBALOPTS

    // BEG_CODE_INIT
    filter = "";
    skip = 1;
    report = false;
    // END_CODE_INIT

    full_test = false;
    minArgs = 0;
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void) {
    CMeasure::registerClass();

    Init();

    // BEG_CODE_NOTES
    // clang-format off
    // clang-format on
    // END_CODE_NOTES

    // BEG_ERROR_STRINGS
    // END_ERROR_STRINGS
}

//---------------------------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//---------------------------------------------------------------------------------------------------
bool COptions::cleanTest(const string_q& path, const string_q& testName) {
    ostringstream os;
    // clang-format off
    os << "find ../../../working/" << path << "/" << testName << "/ -maxdepth 1 -name \"" << testName << "_*.txt\" -exec rm '{}' ';' 2>/dev/null ; ";
    os << "find ../../../working/" << path << "/" << testName << "/api_tests/ -maxdepth 1 -name \"" << testName << "_*.txt\" -exec rm '{}' ';' 2>/dev/null ; ";
    if (system(os.str().c_str())) {}  // Don't remove cruft. Silences compiler warnings
    // clang-format on
    return true;
}

//---------------------------------------------------------------------------------------------------
void establishTestData(void) {
    cleanFolder(cacheFolder_tmp);

    // TODO(tjayrush): This code is a hack to make test cases pass. We should fix the underlyign reason
    // TODO(tjayrush): these tests fail. To reproduce, delete the entire cache, comment the lines below
    // TODO(tjayrush): and re-run. You will see the tests that fail.

    // Forces a few blocks into the cache
    doCommand("chifra blocks --uniq 0");
    doCommand("chifra blocks --cache 2768801 1995314 1958017 2769609 2799895 2872831 3076260");
    doCommand("chifra blocks --cache 4369999 1001001 1234567 1590000 4000001-4000004 3657480");
    doCommand("chifra transactions --cache 47055.0");
    doCommand("chifra transactions --cache 46147.0");

    doCommand("chifra monitors --decache 0xf503017d7baf7fbc0fff7492b751025c6a78179b 2>/dev/null");
    doCommand("chifra monitors --decache 0x9531c059098e3d194ff87febb587ab07b30b1306 2>/dev/null");
    doCommand("chifra monitors --decache 0x5deda52dc2b3a565d77e10f0f8d4bd738401d7d3 2>/dev/null");
    doCommand("chifra monitors --decache 0xd0b3462481c33f63a288cd1923e2a261ee65b4ff 2>/dev/null");

    doCommand("chifra abis --clean 0x45f783cce6b7ff23b2ab2d70e416cdb7d6055f51 2>/dev/null");
    doCommand("chifra abis --clean 0xd7edd2f2bcccdb24afe9a4ab538264b0bbb31373 2>/dev/null");
    doCommand("chifra abis --clean 0x89d24a6b4ccb1b6faa2625fe562bdd9a23260359 2>/dev/null");
    doCommand("chifra abis --clean 0x226159d592e2b063810a10ebf6dcbada94ed68b8 2>/dev/null");
    doCommand("chifra abis --clean 0x17996cbddd23c2a912de8477c37d43a1b79770b8 2>/dev/null");
    doCommand("chifra abis --clean 0x0000000000004946c0e9f43f4dee607b0ef1fa1c 2>/dev/null");
    doCommand("chifra abis --clean 0x7c66550c9c730b6fdd4c03bc2e73c5462c5f7acc 2>/dev/null");
    doCommand("chifra abis --clean 0xa478c2975ab1ea89e8196811f51a7b7ade33eb11 2>/dev/null");
    doCommand("chifra abis --clean 0x7d655c57f71464b6f83811c55d84009cd9f5221c 2>/dev/null");
    doCommand("chifra abis --clean 0x0000000000004946c0e9f43f4dee607b0ef1fa1c 2>/dev/null");
    doCommand("chifra abis --clean 0x30f938fed5de6e06a9a7cd2ac3517131c317b1e7 2>/dev/null");

    // Forces the retreival of a few ABI files without which some tests will fail
    doCommand("chifra abis 0x45f783cce6b7ff23b2ab2d70e416cdb7d6055f51");
    doCommand("chifra abis 0xd7edd2f2bcccdb24afe9a4ab538264b0bbb31373");
    doCommand("chifra abis 0x89d24a6b4ccb1b6faa2625fe562bdd9a23260359");
    doCommand("chifra abis 0x226159d592e2b063810a10ebf6dcbada94ed68b8");
    doCommand("chifra abis 0x17996cbddd23c2a912de8477c37d43a1b79770b8");
    doCommand("chifra abis 0x0000000000004946c0e9f43f4dee607b0ef1fa1c");
    doCommand("chifra abis 0x7c66550c9c730b6fdd4c03bc2e73c5462c5f7acc");
    doCommand("chifra abis 0xa478c2975ab1ea89e8196811f51a7b7ade33eb11");
    doCommand("chifra abis 0x7d655c57f71464b6f83811c55d84009cd9f5221c");
    doCommand("chifra abis 0x0000000000004946c0e9f43f4dee607b0ef1fa1c");
    doCommand("chifra abis 0x30f938fed5de6e06a9a7cd2ac3517131c317b1e7");
}
