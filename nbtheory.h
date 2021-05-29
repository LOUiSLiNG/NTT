//
// Created by Puneet Rehal on 5/9/21.
//

#ifndef FINAL_NBTHEORY_H
#define FINAL_NBTHEORY_H

#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>
#include "inttypes.h"

namespace lbcrypto {

    template <typename IntType>
    inline usint GetMSB(IntType x) {
        std::cout<<"Unsupported integer type (GetMSB() supports 64- and 128-bit"<<std::endl;
    }

    template<>
    inline usint GetMSB(uint64_tt x) {
        if (x == 0) return 0;

        // hardware instructions for finding MSB are used are used;
#if defined(_MSC_VER)
        // a wrapper for VC++
      unsigned long msb;
      _BitScanReverse64(&msb, x);
      return msb + 1;
#else
        // a wrapper for GCC
        return 64 -
               (sizeof(unsigned long) == 8 ? __builtin_clzl(x) : __builtin_clzll(x));
#endif
    }

/**
 * Get MSB of an unsigned 64 bit integer.
 *
 * @param x the input to find MSB of.
 *
 * @return the index of the MSB bit location.
 */
    inline usint GetMSB64(uint64_tt x) { return GetMSB(x); }
}

#endif //FINAL_NBTHEORY_H
