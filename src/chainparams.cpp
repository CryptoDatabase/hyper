// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xfb;
        pchMessageStart[2] = 0xfa;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("04b8d49de838594c2289037043e5330f12f4cb98f0a2f0cda90a2a957c3358c95480bb6db13fd5a50368c1f24096495eb473be801e5c919b0668a2f7acf74ed291");
        nDefaultPort = 11194;
        nRPCPort = 11195;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "R3 Consortium And Hong Kong Monetary Authority Aim to Develop National Digital Currency - JP Buntinx - April 12, 2017";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1491998400, vin, vout, 0); // Wed, 12 Apr 2017 12:00:00 GMT
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1491998400; // Wed, 12 Apr 2017 12:00:00 GMT
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 60366;

        /*
        Hashed MainNet Genesis Block Output
        block.hashMerkleRoot == 19701eeb6c8cf39dbe6d4ba80a7fc8d1159bedcf2f3200408ae0ddb1a5d6e1a4
        block.nTime = 1491998400
        block.nNonce = 60366
        block.GetHash = 0000067c1bf612492b2200b253d3a523efd323ee627bddcfcacbfd7d11ef8775
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000067c1bf612492b2200b253d3a523efd323ee627bddcfcacbfd7d11ef8775"));
        assert(genesis.hashMerkleRoot == uint256("0x19701eeb6c8cf39dbe6d4ba80a7fc8d1159bedcf2f3200408ae0ddb1a5d6e1a4"));

        vSeeds.push_back(CDNSSeedData("hyper-v2.thecryptochat.net", "195.74.52.227"));
        vSeeds.push_back(CDNSSeedData("seed", "NULL"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 100);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 101);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 104);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 40320;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 11199;
        nRPCPort = 11200;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 148408;

        /*
        Hashed TestNet Genesis Block Output
        block.hashMerkleRoot == 19701eeb6c8cf39dbe6d4ba80a7fc8d1159bedcf2f3200408ae0ddb1a5d6e1a4
        block.nTime = 1491998400
        block.nNonce = 148408
        block.GetHash = 0000024551a7ceb01f17bcfee40f05e18b8f83c0fd49f2fbafc9bf95b77614f2
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000024551a7ceb01f17bcfee40f05e18b8f83c0fd49f2fbafc9bf95b77614f2"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xf9;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xee;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1492041699;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19111;
        strDataDir = "regtest";

        /*
        Hashed RegNet Genesis Block Output
        block.hashMerkleRoot == 19701eeb6c8cf39dbe6d4ba80a7fc8d1159bedcf2f3200408ae0ddb1a5d6e1a4
        block.nTime = 1492041699
        block.nNonce = 2
        block.GetHash = dbb14212dcad85087dc0e43ed1e549f3b25883d0b4b0c01805d3d02e6f85b841
        */

        assert(hashGenesisBlock == uint256("0xdbb14212dcad85087dc0e43ed1e549f3b25883d0b4b0c01805d3d02e6f85b841"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
