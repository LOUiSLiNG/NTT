//
//  NTT.hpp
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//

#ifndef NTT_hpp
#define NTT_hpp

#include <stdio.h>
#include <time.h>
#include <chrono>
#include <complex>
#include <fstream>
#include <map>
#include <thread>
#include <utility>
#include <vector>
#include "backend.h"
#include "NatVec.hpp"
#include "NatInt.hpp"
#include <cmath>

typedef NativeVector VecType;



namespace lbcrypto {
template <typename VecType>
class NumberTheoreticTransform {
  using IntType = typename VecType::Integer;
//
// public:
    /**
     * Forward transform in the ring Z_q[X]/(X^n+1) with prime q and power-of-two
     * n s.t. 2n|q-1. Bit reversing indexes. The method works for the
     * NativeInteger case based on NTL's modular multiplication. [Algorithm 1 in
     * https://eprint.iacr.org/2016/504.pdf]
     *
     * @param &element is the input to the transform of type VecType and length n.
     * @param &rootOfUnityTable is the table with the root of unity powers in bit
     * reverse order.
     * @param &preconRootOfUnityTable is NTL-specific precomputations for
     * optimized NativeInteger modulo multiplications.
     * @return is the result of the transform, a VecType should be of the same
     * size as input or a throw of an error occurs.
     */
  public:void ForwardTransformToBitReverse(
        const VecType& element, const VecType& rootOfUnityTable,
        const NativeVector& preconRootOfUnityTable, VecType* result);
//    VecType operator()(const VecType& element, const VecType& rootOfUnityTable,
//        const NativeVector& preconRootOfUnityTable, VecType* result);
};
}

#endif /* NTT_hpp */
