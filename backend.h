//
//  backend.h
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//

#ifndef backend_h
#define backend_h

#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include "config_core.h"


namespace bigintnat {

template <typename I>
class NativeIntegerT;

#if NATIVEINT == 128
#define MAX_MODULUS_SIZE 121
using BasicInteger = unsigned __int128;
typedef NativeIntegerT<unsigned __int128> NativeInteger;
typedef NativeIntegerT<unsigned __int128> NativeInteger128;
#elif NATIVEINT == 64 && !defined(HAVE_INT128)
#define MAX_MODULUS_SIZE 58
using BasicInteger = uint64_t;
typedef NativeIntegerT<uint64_t> NativeInteger;
typedef NativeIntegerT<uint64_t> NativeInteger64;
#elif NATIVEINT == 64 && defined(HAVE_INT128)
#define MAX_MODULUS_SIZE 60
using BasicInteger = uint64_t;
typedef NativeIntegerT<uint64_t> NativeInteger;
typedef NativeIntegerT<uint64_t> NativeInteger64;
#elif NATIVEINT == 32  // NOLINT
#define MAX_MODULUS_SIZE 28
using BasicInteger = uint32_t;
typedef NativeIntegerT<uint32_t> NativeInteger;
typedef NativeIntegerT<uint32_t> NativeInteger32;
#endif

}  // namespace bigintnat

#include <initializer_list>
#include "NatVec.hpp"
#include "NatInt.hpp"

#if NATIVEINT == 128
typedef bigintnat::NativeIntegerT<unsigned __int128> NativeInteger128;
typedef bigintnat::NativeVector<NativeInteger128> NativeVector128;
#elif NATIVEINT == 64
typedef bigintnat::NativeIntegerT<uint64_tt> NativeInteger64;
typedef bigintnat::NativeVector<NativeInteger64> NativeVector64;
#elif NATIVEINT == 32
typedef bigintnat::NativeIntegerT<uint32_t> NativeInteger32;
typedef bigintnat::NativeVector<NativeInteger32> NativeVector32;
#endif


#if NATIVEINT == 128
typedef NativeInteger128 NativeInteger;
typedef NativeVector128 NativeVector;
#elif NATIVEINT == 64
typedef NativeInteger64 NativeInteger;
typedef NativeVector64 NativeVector;
#elif NATIVEINT == 32  // NOLINT
typedef NativeInteger32 NativeInteger;
typedef NativeVector32 NativeVector;
#endif


#endif /* backend_h */
