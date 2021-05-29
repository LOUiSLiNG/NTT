//
//  NatInt.hpp
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//

#ifndef NatInt_hpp
#define NatInt_hpp

#include <stdio.h>
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
#include "inttypes.h"
#include "interface.h"
#include "nbtheory.h"
#include "balke2engine.h"


#define NATIVEINT_DO_CHECKS false

using U32BITS = uint32_t;
using U64BITS = uint64_tt;
#if defined(HAVE_INT128)
using U128BITS = unsigned __int128;
#endif

namespace bigintnat {

const double LOG2_10 =
    3.32192809;  //!< @brief A pre-computed  constant of Log base 2 of 10.

const usint BARRETT_LEVELS = 8;  //!< @brief The number of levels (precomputed
                                 //!< values) used in the Barrett reductions.

/**
 * @brief Struct to determine a datatype that is twice as big(bitwise) as utype.
 * sets T as of type void for default case
 *
 * @tparam utype primitive integer data type.
 */
template <typename utype>
struct DoubleDataType {
  using DoubleType = void;
  using SignedType = void;
};

/**
 * @brief Struct to determine a datatype that is twice as big(bitwise) as utype.
 * sets T as of type unsigned integer 64 bit if integral datatype is 32bit
 */
template <>
struct DoubleDataType<uint32_t> {
  using DoubleType = uint64_tt;
  using SignedType = int32_t;
};

/**
 * @brief Struct to determine a datatype that is twice as big(bitwise) as utype.
 * sets T as of type unsigned integer 128 bit if integral datatype is 64bit
 */
template <>
struct DoubleDataType<uint64_tt> {
#if defined(HAVE_INT128)
  using DoubleType = __uint128_t;
#else
  using DoubleType = uint64_tt;
#endif
  using SignedType = int64_t;
};

#if defined(HAVE_INT128)
template <>
struct DoubleDataType<unsigned __int128> {
  using DoubleType = __uint128_t;
  using SignedType = __int128;
};
#endif

/**
 * @brief Main class for big integers represented as an array of native
 * (primitive) unsigned integers
 * @tparam NativeInt native unsigned integer type
 */


template <typename NativeInt>
class NativeIntegerT: public lbcrypto::BigIntegerInterface<NativeIntegerT<NativeInt>> {
 public:
  using Integer = NativeInt;
  using DNativeInt = typename DoubleDataType<NativeInt>::DoubleType;
  using SignedNativeInt = typename DoubleDataType<NativeInt>::SignedType;
    // a data structure to represent a double-word integer as two single-word
      // integers
      struct typeD {
        NativeInt hi = 0;
        NativeInt lo = 0;
        inline std::string ConvertToString() {
          std::string ret("hi [");
          ret += toString(hi);
          ret += "], lo [";
          ret += toString(lo);
          ret += "]";
          return ret;
        }
      };
    /// CONSTRUCTORS

      /**
       * Default constructor.
       */
      NativeIntegerT() : m_value(0) {}
    /**
       * Constructor from an unsigned integer.
       *
       * @param val is the initial integer represented as a NativeInt.
       */
      NativeIntegerT(NativeInt val) : m_value(val) {}

    /**
     * Copy constructor.
     *
     * @param &val is the native integer to be copied.
    */
    NativeIntegerT(const NativeIntegerT &val) : m_value(val.m_value) {}

    /**
   * Constructor from a string.
   *
   * @param &strval is the initial integer represented as a string.
   */
    NativeIntegerT(const std::string &strval) { AssignVal(strval); }

    /**
     * Constructors from smaller basic types
     * @param init
     */
    template <typename T = NativeInt>
    NativeIntegerT(int16_t init,
                   typename std::enable_if<!std::is_same<T, int16_t>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(uint16_t init,
                   typename std::enable_if<!std::is_same<T, uint16_t>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(int32_t init,
                   typename std::enable_if<!std::is_same<T, int32_t>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(uint32_t init,
                   typename std::enable_if<!std::is_same<T, uint32_t>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(
            long init,
            typename std::enable_if<!std::is_same<T, long>::value, bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(unsigned long init,
                   typename std::enable_if<!std::is_same<T, unsigned long>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(long long init,
                   typename std::enable_if<!std::is_same<T, long long>::value,
                           bool>::type = true)
            : m_value(init) {}

    template <typename T = NativeInt>
    NativeIntegerT(
            unsigned long long init,
            typename std::enable_if<!std::is_same<T, unsigned long long>::value,
                    bool>::type = true)
            : m_value(init) {}

            ///OPERATORS

    /**
       * Copy assignment operator
       *
     * @param val is the native integer to be assigned from.
       * @return assigned NativeIntegerT ref.
       */
      const NativeIntegerT &operator=(const NativeIntegerT &val) {
        this->m_value = val.m_value;
        return *this;
      }

      /**
       * Move assignment operator
       *
       * @param val is the native integer to be assigned from.
       * @return assigned NativeIntegerT ref.
       */
      const NativeIntegerT &operator=(const NativeIntegerT &&val) {
        this->m_value = val.m_value;
        return *this;
      }

      /**
       * Assignment operator from string
       *
       * @param strval is the string to be assigned from
       * @return the assigned NativeIntegerT ref.
       */
      const NativeIntegerT &operator=(const std::string strval) {
        *this = NativeIntegerT(strval);
        return *this;
      }

      /**
       * Assignment operator from unsigned integer
       *
       * @param val is the unsigned integer value that is assigned.
       * @return the assigned BigInteger ref.
       */
      const NativeIntegerT &operator=(const NativeInt &val) {
        this->m_value = val;
        return *this;
      }


    // ARITHMETIC OPERATIONS

    /**
     * Addition operation.
     *
     * @param &b is the value to add.
     * @return result of the addition operation.
     */
    NativeIntegerT Add(const NativeIntegerT &b) const {
        return NATIVEINT_DO_CHECKS ? AddCheck(b) : AddFast(b);
    }

    /**
     * Addition operation. In-place variant.
     *
     * @param &b is the value to add.
     * @return result of the addition operation.
     */
    const NativeIntegerT &AddEq(const NativeIntegerT &b) {
        return NATIVEINT_DO_CHECKS ? AddEqCheck(b) : AddEqFast(b);
    }

    /**
     * AddEqCheck is the addition in place operation with bounds checking.
     * In-place variant.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    const NativeIntegerT &AddEqCheck(const NativeIntegerT &b) {
        NativeInt oldv = m_value;
        m_value += b.m_value;
        if (m_value < oldv) {
            std::cout<<"Overflow"<< std::endl;
        }
        return *this;
    }

    /**
       * AddEqFast is the addition in place operation without bounds checking.
       * In-place variant.
       *
       * @param b is the value to add to this.
       * @return result of the addition operation.
       */
    const NativeIntegerT &AddEqFast(const NativeIntegerT &b) {
        m_value += b.m_value;
        return *this;
    }
    
    /**
     * Subtraction operation.
     *
     * @param b is the value to subtract.
     * @return is the result of the subtraction operation.
     */
    NativeIntegerT Sub(const NativeIntegerT &b) const {
      return NATIVEINT_DO_CHECKS ? SubCheck(b) : SubFast(b);
    }
    
    /**
       * SubCheck is the subtraction operation with bounds checking.
       *
       * @param b is the value to add to this.
       * @return result of the addition operation.
       */
      NativeIntegerT SubCheck(const NativeIntegerT &b) const {
        return m_value <= b.m_value ? 0 : m_value - b.m_value;
      }
    
    /**
     * SubFast is the subtraction operation without bounds checking.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    NativeIntegerT SubFast(const NativeIntegerT &b) const {
      return m_value - b.m_value;
    }

    // overloaded binary operators based on integer arithmetic and comparison
     // functions.
     NativeIntegerT operator-() const { return NativeIntegerT(0).Sub(*this); }
    
    /**
       * Modular multiplication using a precomputation for the multiplicand.
       *
       * @param b is the NativeIntegerT to multiply.
       * @param modulus is the modulus to perform operations with.
       * @param bInv precomputation for b.
       * @return is the result of the modulus multiplication operation.
       */
      NativeIntegerT ModMulFastConst(const NativeIntegerT &b,
                                     const NativeIntegerT &modulus,
                                     const NativeIntegerT &bInv) const {
        NativeInt q = MultDHi(this->m_value, bInv.m_value);
        NativeInt yprime = this->m_value * b.m_value - q * modulus.m_value;
        return SignedNativeInt(yprime) - SignedNativeInt(modulus.m_value) >= 0
                   ? yprime - modulus.m_value
                   : yprime;
      }

      /**
       * Modular multiplication using a precomputation for the multiplicand.
       * In-place variant.
       *
       * @param b is the NativeIntegerT to multiply.
       * @param modulus is the modulus to perform operations with.
       * @param bInv precomputation for b.
       * @return is the result of the modulus multiplication operation.
       */
      const NativeIntegerT &ModMulFastConstEq(const NativeIntegerT &b,
                                              const NativeIntegerT &modulus,
                                              const NativeIntegerT &bInv) {
        NativeInt q = MultDHi(this->m_value, bInv.m_value);
        NativeInt yprime = this->m_value * b.m_value - q * modulus.m_value;
        this->m_value =
            SignedNativeInt(yprime) - SignedNativeInt(modulus.m_value) >= 0
                ? yprime - modulus.m_value
                : yprime;
        return *this;
      }

    // MODULAR ARITHMETIC OPERATIONS

    /**
     * Naive modulus operation.
     *
     * @param &modulus is the modulus to perform.
     * @return is the result of the modulus operation.
     */
    NativeIntegerT Mod(const NativeIntegerT &modulus) const {
        return m_value % modulus.m_value;
    }



    // CONVERTERS

    /**
     * Converts the value to an int.
     *
     * @return the int representation of the value as usint.
     */
    template <typename OutputType = NativeInt>
    OutputType ConvertToInt() const {
        if (sizeof(OutputType) < sizeof(m_value))
            std::cout <<"Invalid integer conversion: sizeof(OutputIntType) < sizeof(InputIntType)" <<std::endl;
        return static_cast<OutputType>(m_value);
    }

    /**
     * Converts the value to an double.
     *
     * @return double representation of the value.
     */
    double ConvertToDouble() const { return static_cast<double>(m_value); }

    /**
     * Convert a string representation of a binary number to a NativeIntegerT.
     *
     * @param bitString the binary num in string.
     * @return the binary number represented as a big binary int.
     */
    static NativeIntegerT FromBinaryString(const std::string &bitString) {
        if (bitString.length() > MaxBits()) {
            std::cout << "Bit string is too long to fit in a bigintnat" << std::endl;
        }
        NativeInt v = 0;
        for (size_t i = 0; i < bitString.length(); i++) {
            int n = bitString[i] - '0';
            if (n < 0 || n > 1) {
                std::cout << "Bit string must contain only 0 or 1" << std::endl;
            }
            v <<= 1;
            v |= n;
        }
        return v;
    }

    /**
  * Right shift operation.
  *
  * @param shift # of bits.
  * @return result of the shift operation.
  */
    NativeIntegerT RShift(usshort shift) const { return m_value >> shift; }

    /**
      * Right shift operation. In-place variant.
      *
      * @param shift # of bits.
      * @return result of the shift operation.
      */
    const NativeIntegerT &RShiftEq(usshort shift) {
        m_value >>= shift;
        return *this;
    }

    // COMPARE

    /**
     * Compares the current NativeIntegerT to NativeIntegerT a.
     *
     * @param a is the NativeIntegerT to be compared with.
     * @return  -1 for strictly less than, 0 for equal to and 1 for strictly
     * greater than conditons.
     */
    int Compare(const NativeIntegerT &a) const {
        if (this->m_value < a.m_value)
            return -1;
        else if (this->m_value > a.m_value)
            return 1;
        return 0;
    }

    /**
* Returns the MSB location of the value.
*
* @return the index of the most significant bit.
*/
    usint GetMSB() const { return lbcrypto::GetMSB(this->m_value); }

    /**
     * Get the number of digits using a specific base - support for arbitrary
     * base may be needed.
     *
     * @param base is the base with which to determine length in.
     * @return the length of the representation in a specific base.
     */
    usint GetLengthForBase(usint base) const { return GetMSB(); }

    const std::string ToString() const { return toString(m_value); }
    
    /**
       * Console output operation.
       *
       * @param os is the std ostream object.
       * @param ptr_obj is NativeIntegerT to be printed.
       * @return is the ostream object.
       */
      friend std::ostream &operator<<(std::ostream &os,
                                      const NativeIntegerT &ptr_obj) {
        os << ptr_obj.ToString();
        return os;
      }
    static constexpr unsigned MaxBits() { return m_uintBitLength; }

    template <typename T = NativeInt>
    const NativeIntegerT &ModEq(
            const NativeIntegerT &modulus, const NativeIntegerT &mu,
            typename std::enable_if<std::is_same<T, DNativeInt>::value, bool>::type =
            true) {
        typeD prod;
        prod.lo = this->m_value;
        prod.hi = 0;
        typeD result = prod;

        long n = modulus.GetMSB();
        long alpha = n + 3;
        long beta = -2;

        NativeInt ql = RShiftD(prod, n + beta);
        MultD(ql, mu.m_value, prod);

        ql = RShiftD(prod, alpha - beta);
        MultD(ql, modulus.m_value, prod);
        SubtractD(result, prod);

        this->m_value = result.lo;
        // correction at the end
        if (this->m_value > modulus.m_value) {
            this->m_value -= modulus.m_value;
        }
        return *this;
    }


    const NativeIntegerT &SubEq(const NativeIntegerT &b) {
        return NATIVEINT_DO_CHECKS ? SubEqCheck(b) : SubEqFast(b);
    }

    /**
     * SubEqCheck is the subtraction in place operation with bounds checking.
     * In-place variant.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    const NativeIntegerT &SubEqCheck(const NativeIntegerT &b) {
        m_value = m_value <= b.m_value ? 0 : m_value - b.m_value;
        return *this;
    }

    /**
     * SubEqFast is the subtraction in place operation without bounds checking.
     * In-place variant.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    const NativeIntegerT &SubEqFast(const NativeIntegerT &b) {
        m_value -= b.m_value;
        return *this;
    }



    /**
     * Barrett modulus operation. In-place variant.
     * Implements generalized Barrett modular reduction algorithm. Uses one
     * precomputed value of mu.
     *
     * @param &modulus is the modulus to perform.
     * @param &mu is the Barrett value.
     * @return is the result of the modulus operation.
     */
    template <typename T = NativeInt>
    const NativeIntegerT &ModEq(
            const NativeIntegerT &modulus, const NativeIntegerT &mu,
            typename std::enable_if<!std::is_same<T, DNativeInt>::value, bool>::type =
            true) {
        typeD tmp1;
        tmp1.lo = this->m_value;
        tmp1.hi = 0;
        DNativeInt tmp(this->m_value);

        long n = modulus.GetMSB();
        long alpha = n + 3;
        long beta = -2;

        // RShiftD is more efficient than the right-shifting of DNativeInt
        NativeInt ql = RShiftD(tmp1, n + beta);
        MultD(ql, mu.m_value, tmp1);
        DNativeInt q = GetD(tmp1);

        // we cannot use RShiftD here because alpha - beta > 63
        // for q larger than 57 bits
        q >>= alpha - beta;
        tmp -= q * DNativeInt(modulus.m_value);

        this->m_value = NativeInt(tmp);

        // correction at the end
        if (this->m_value > modulus.m_value) {
            this->m_value -= modulus.m_value;
        }
        return *this;
    }







    /**
     * Modulus subtraction operation. In-place variant.
     *
     * @param &b is the scalar to subtract.
     * @param &modulus is the modulus to perform operations with.
     * @return is the result of the modulus subtraction operation.
     */
    const NativeIntegerT &ModSubEq(const NativeIntegerT &b,
                                   const NativeIntegerT &modulus) {
        NativeInt mod(modulus.m_value);
        NativeInt bv(b.m_value);
        // reduce this to a value lower than modulus
        if (this->m_value >= mod) {
            this->m_value %= mod;
        }
        // reduce b to a value lower than modulus
        if (bv >= mod) {
            bv %= mod;
        }

        if (this->m_value >= bv) {
            this->m_value -= bv;
        } else {
            this->m_value += (mod - bv);
        }
        return *this;
    }



    /**
     * Barrett modulus subtraction operation.
     *
     * @param &b is the scalar to subtract.
     * @param &modulus is the modulus to perform operations with.
     * @param &mu is the Barrett value.
     * @return is the result of the modulus subtraction operation.
     */
    NativeIntegerT ModSub(const NativeIntegerT &b, const NativeIntegerT &modulus,
                          const NativeIntegerT &mu) const {
        NativeInt mod(modulus.m_value);
        NativeIntegerT av(this->m_value);
        NativeIntegerT bv(b.m_value);
        if (av.m_value >= mod) {
            av.ModEq(modulus, mu);
        }
        if (bv.m_value >= mod) {
            bv.ModEq(modulus, mu);
        }

        if (av.m_value >= bv.m_value) {
            av.m_value -= bv.m_value;
        } else {
            av.m_value += (mod - bv.m_value);
        }
        return av;
    }

    /**
     * Barrett modulus subtraction operation. In-place variant.
     *
     * @param &b is the scalar to subtract.
     * @param &modulus is the modulus to perform operations with.
     * @param &mu is the Barrett value.
     * @return is the result of the modulus subtraction operation.
     */
    const NativeIntegerT &ModSubEq(const NativeIntegerT &b,
                                   const NativeIntegerT &modulus,
                                   const NativeIntegerT &mu) {
        NativeIntegerT bv(b.m_value);
        NativeInt mod(modulus.m_value);
        if (this->m_value >= mod) {
            this->ModEq(modulus, mu);
        }
        if (bv.m_value >= mod) {
            bv.ModEq(modulus, mu);
        }

        if (this->m_value >= bv.m_value) {
            this->m_value -= bv.m_value;
        } else {
            this->m_value += (mod - bv.m_value);
        }
        return *this;
    }

protected:
    /**
     * Converts the string v into base-r integer where r is equal to 2^bitwidth
     * of integral data type.
     *
     * @param v The input string
     */
    void AssignVal(const std::string &str) {
        NativeInt test_value = 0;
        m_value = 0;
        for (size_t i = 0; i < str.length(); i++) {
            int v = str[i] - '0';
            if (v < 0 || v > 9) {
                std::cout<< "String contains a non-digit"<<std::endl;
            }
            m_value *= 10;
            m_value += v;

            if (m_value < test_value) {
                std::cout<< "String is too large to fit in this native integer object" <<std::endl;
            }
            test_value = m_value;
        }
    }
    
private:
  // representation as a
  NativeInt m_value;
    static constexpr unsigned m_uintBitLength = sizeof(NativeInt) * 8;
    static constexpr NativeInt NATIVEINTMASK = NativeInt(~0);
    static constexpr NativeInt m_uintMax = std::numeric_limits<NativeInt>::max();


    inline DNativeInt GetD(const typeD &x) const {
        return (DNativeInt(x.hi) << MaxBits()) | x.lo;
    }
    /**
     * AddCheck is the addition operation with bounds checking.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    inline NativeIntegerT AddCheck(const NativeIntegerT &b) const {
        NativeInt newv = m_value + b.m_value;
        if (newv < m_value || newv < b.m_value) {
            std::cout<< "Overflow"<<std::endl;
        }
            return newv;

    }

    // Computes res -= a;
    static inline void SubtractD(typeD &res, const typeD &a) {
        if (res.lo < a.lo) {
            res.lo += m_uintMax + 1 - a.lo;
            res.hi--;
        } else {
            res.lo -= a.lo;
        }

        res.hi -= a.hi;
    }

    /**
      * Right shifts a typeD integer by a specific number of bits
      * and stores the result as a single-word integer.
      *
      * @param &x double-word input
      * @param shift the number of bits to shift by
      * @return the result of right-shifting
      */
    static inline NativeInt RShiftD(const typeD &x, long shift) {
        return (x.lo >> shift) | (x.hi << (MaxBits() - shift));
    }


    /**
     * AddFast is the addition operation without bounds checking.
     *
     * @param b is the value to add to this.
     * @return result of the addition operation.
     */
    inline NativeIntegerT AddFast(const NativeIntegerT &b) const {
        return m_value + b.m_value;
    }
    
    static inline std::string toString(uint32_t value) {
      return std::to_string(value);
    }

    static inline std::string toString(uint64_tt value) {
      return std::to_string(value);
    }
    
    static inline void MultD(U32BITS a, U32BITS b, typeD &res) {
       DNativeInt prod = DNativeInt(a) * DNativeInt(b);
       res.hi = (prod >> MaxBits()) & NATIVEINTMASK;
       res.lo = prod & NATIVEINTMASK;
     }

    /**
     * Multiplies two single-word integers and stores the high word of the
     * result
     *
     * @param a multiplier
     * @param b multiplicand
     * @return the high word of the result
     */
    static inline NativeInt MultDHi(NativeInt a, NativeInt b) {
      typeD x;
      MultD(a, b, x);
      return x.hi;
    }
};
}




#endif /* NatInt_hpp */
