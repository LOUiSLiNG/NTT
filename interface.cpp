//
// Created by Puneet Rehal on 5/10/21.
//
#include "interface.h"
#include "inttypes.h"
//typedef uint64_t PlaintextModulus;
namespace lbcrypto{
    template <typename T>
   inline const typename BigIntegerInterface<T>:: T& operator-=(T& a, const T& b) { return a.SubEq(b); }

    /**
            * Equals to operator.
            *
            * @param &b is vector to be compared.
            * @return true if equal and false otherwise.
            */
//    template <typename T>
//    friend inline bool operator==(const T &a, const T &b) {
//               if ((a.GetLength() != b.GetLength()) ||
//                   (a.GetModulus() != b.GetModulus())) {
//                   return false;
//               }
//               for (size_t i = 0; i < a.GetLength(); ++i) {
//                   if (a[i] != b[i]) {
//                       return false;
//                   }
//               }
//               return true;
//           }
//
//    template <typename T>
//    friend inline bool operator!=(const T &a, const T &b) { return !(a == b); }
}
