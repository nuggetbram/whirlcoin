// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xf7;
        pchMessageStart[1] = 0x26;
        pchMessageStart[2] = 0xa1;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("04e41db2a8b8dc3981f819d46060875ce483bf303613b108e673d7bb636f7786bd0458e2ced6e8b337be32d024562f3e69776412b55a7210396ad7a9944812b445");
        nDefaultPort = 48481;
        nRPCPort = 48480;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 262800;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
        const char* pszTimestamp = "Tone Abbet Does it again";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = COIN / 10000;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1403758350;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 1532698;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit.GetCompact());
        genesis.print();

        /*if (false && (genesis.GetHash() != hashGenesisBlock)) {

        // This will figure out a valid hash and Nonce if you're
        // creating a different genesis block:
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
               {
                   ++genesis.nNonce;
                   if (genesis.nNonce == 0)
                   {
                       printf("NONCE WRAPPED, incrementing time");
                       ++genesis.nTime;
                   }
               }
        }

        //// debug print
        genesis.print();
        printf("genesis.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        printf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("genesis.nTime = %u \n", genesis.nTime);
        printf("genesis.nNonce = %u \n", genesis.nNonce);
              */
        assert(hashGenesisBlock == uint256("0x000000c1d37af38ced9ceff1ee37e0dfbbdd86cfa3bc2befb0a63ee85603b8d5"));
        assert(genesis.hashMerkleRoot == uint256("0x94076775c950c86d89bc2225c87bcb4e29621b57d5e9b430d7fa190078b0e980"));

        vSeeds.push_back(CDNSSeedData("162.248.4.167", "162.248.4.167"));
        vSeeds.push_back(CDNSSeedData("seed2.whirlcoin.org", "seed2.whirlcoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3.whirlcoin.org", "seed3.whirlcoin.org"));
        vSeeds.push_back(CDNSSeedData("whirlcoin.zapto.org", "whirlcoin.zapto.org"));
        vSeeds.push_back(CDNSSeedData("whirlcoin.no-ip.org", "whirlcoin.no-ip.org"));
        vSeeds.push_back(CDNSSeedData("whirlcoin.strangled.net", "whirlcoin.strangled.net"));
        vSeeds.push_back(CDNSSeedData("whirlcoin.ignorelist.com", "whirlcoin.ignorelist.com"));

        base58Prefixes[PUBKEY_ADDRESS] = 73;
        base58Prefixes[SCRIPT_ADDRESS] = 12;
        base58Prefixes[SECRET_KEY] = 226;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
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
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0x25;
        pchMessageStart[3] = 0x03;
        vAlertPubKey = ParseHex("0490ce131d0e51eacddb074906fc0be1990214ec9880c2da9bfc15d649236f211e3950670fee0c45f8ea00d425d84da61425778617ba73d64e1880abc4607de965");
        nDefaultPort = 27711;
        nRPCPort = 37711;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1382385267;
        genesis.nNonce = 416003859;
                
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();
        
        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("whirlcoin.test", "test.whirlcoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 56;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 237;

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
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 4;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        //assert(hashGenesisBlock == uint256("0x"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
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
