// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, uint256("0x2ad2fd149210469fb1c86c11e0ff6515eb08e297944694bef5031200ee8b1924"))
        (1, uint256("0xc675a26d254781ad3c1eb8ddb235ba6609011d21c348667e14496c23a59752d7"))
        (2, uint256("0xccd6e9b5f75c97a2dafd9429a9faf177b6c4cfe2c96485338af53578757453c4"))
        (3, uint256("0x176ccd61a77961010910dac3bc603a56967d8f8a1a221c19319e8c39058fd3ae"))
        (4, uint256("0xbc84b28806a3b5205cf8b2a3a7f2c1cf4f3bc00c898f84a8175ebd3a645468ed"))
        (5, uint256("0x5c3ddd6ee1568849e7511df63261c57afb37c60b853dfaf632fc9bb28f8740a5"))
        (6, uint256("0x6549a79d5bb1315ed5e594b3f99813015cfce042cadb837ac29d267ab13ce440"))
        (7, uint256("0x362c4b93eafb505c4d11ea8d1abffc721be22a636aa039aab688305b9539b0e4"))
        (8, uint256("0x290edbb6ac80621d74fb67c8a6068aa5c1dcefc790a867ca5fad0c8b3ddc9bc2"))
        (1000, uint256("0x434fb9700d3e866a606f2a8566a2ee40464c5096a979f180406e62c90f3c23a2"))
        (2000, uint256("0x0412214ce4bdb29d0f893db769147c813967229e2dbb1941ab1eb9c98a3466c8"))
        (3000, uint256("0x8ecd163f0e28dbf9ee331d8ef298e3b35c6ff62349656f34be3a73ac51c126ae"))
        (4000, uint256("0x5a759d334f2848e5fc4a510121779f2b121ccafec8bbe50771f500d35accd583"))
        (5000, uint256("0x2c1cfec8d2069bb0abf348a70821d0db8c2e49f29ab177dec66b3895d8837a86"))
        (6000, uint256("0xedbcbdecb0865d88b3062adf7c625b45d2df2c74a3b6b0a081ad6e9bb7874ea6"))
        (7000, uint256("0xaaff147970c8c626e2f994341869d0db3e8ed544870423493212b5d8c6172127"))
        (8000, uint256("0x4b90eea0f5ee60301e6fb7e6190fb15786208976b5801bf45b30c19959a42ddb"))
        (9000, uint256("0x06f959eb9a8e77a8861dbd15ca475b9f028058f138757cd69438a1d89a85c5d6"))
        (10000, uint256("0xb7dd8e9d625f3f628289bb5bc386004652a6d3ffc0face6be106845ed0e914ec"))
        (10274, uint256("0x63f3b9438a28ebcf69ce00d2934651b559b9a8c44a68b82344f8c0470c9015a3"))
       ;

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (0, uint256("0x000000005d7230f40e4d683770d0e962ecbf90275468b6e9533fb5be06a66c75"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
