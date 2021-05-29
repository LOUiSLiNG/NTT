//
// Created by Puneet Rehal on 5/9/21.
//

#ifndef FINAL_INTERFACE_H
#define FINAL_INTERFACE_H

#include "inttypes.h"
#include <iostream>

namespace lbcrypto {

    template<typename T>
    class BigIntegerInterface {
    public:
        /**
  * NTL-optimized modular multiplication using a precomputation for the
  * multiplicand. Assumes operands are < modulus. In-place variant.
  *
  * @param &b is the scalar to multiply.
  * @param &modulus is the modulus to perform operations with.
  * @param &bInv NTL precomputation for b.
  * @return is the result of the modulus multiplication operation.
  */
        const T &ModMulFastConstEq(const T &b, const T &modulus, const T &bInv);


        /**
         * Naive modulus operation.
         *
         * @param &modulus is the modulus to perform.
         * @return is the result of the modulus operation.
         *
         *
         */
        /**
  * Barrett modulus operation. In-place variant.
  * Implements generalized Barrett modular reduction algorithm. Uses one
  * precomputed value of mu.
  *
  * @param &modulus is the modulus to perform.
  * @param &mu is the Barrett value.
  * @return is the result of the modulus operation.
  */
        const T& ModEq(const T& modulus, const T& mu);
        T Mod(const T& modulus) const;

        const T& ModEq(const T& modulus);

        // inline operators for the modulus operation.
        inline friend T operator%(const T& a, const T& b) { return a.Mod(b); }

        inline friend const T& operator%=(T& a, const T& b) { return a.ModEq(b); }


        /**
         * Modulus 2 operation, also a least significant bit.
         *
         * @return is the result of the component wise modulus 2 operation, also a
         * least significant bit.
         */
        T ModByTwo() const;

        /**
         * Modulus 2 operation, also a least significant bit. In-place variant.
         *
         * @return is the result of the component wise modulus 2 operation, also a
         * least significant bit.
         */
        const T& ModByTwoEq();

        /**
          * Modulus subtraction operation.
          *
          * @param &b is the scalar to subtract.
          * @param &modulus is the modulus to perform operations with.
          * @return is the result of the modulus subtraction operation.
          */
        T ModSub(const T& b, const T& modulus) const;

        /**
         * Barrett modulus subtraction operation.
         *
         * @param &b is the scalar to subtract.
         * @param &modulus is the modulus to perform operations with.
         * @param &mu is the Barrett value.
         * @return is the result of the modulus subtraction operation.
         */
        T ModSub(const T& b, const T& modulus, const T& mu) const;

        /**
         * Modulus subtraction operation. In-place variant.
         *
         * @param &b is the scalar to subtract.
         * @param &modulus is the modulus to perform operations with.
         * @return is the result of the modulus subtraction operation.
         */
        const T& ModSubEq(const T& b, const T& modulus);




        // CONVERTERS

        /**
         * Convert the value to an int.
         *
         * @return the int representation of the value.
         */
        uint64_tt ConvertToInt() const;

        /**
         * Convert a string representation of a binary number to a NativeIntegerT.
         *
         * @param bitString the binary num in string.
         * @return the binary number represented as a big binary int.
         */


        /**
         * Right shift operation.
         *
         * @param shift # of bits.
         * @return result of the shift operation.
         */
        T RShift(usshort shift) const;

        /**
          * Right shift operation. In-place variant.
          *
          * @param shift # of bits.
          * @return result of the shift operation.
          */
        const T& RShiftEq(usshort shift);

        /// inline operators for the right shift operations.
        inline friend T operator>>(const T& a, usshort shift) {
            return a.RShift(shift);
        }
        inline friend const T& operator>>=(T& a, usshort shift) {
            return a.RShiftEq(shift);
        }

        /**
         * Addition operation.
         *
         * @param &b is the value to add.
         * @return result of the addition operation.
        */
        T Add(const T& b) const;
        const T& AddEq(const T& b);
        inline friend T operator+(const T& a, const T& b) { return a.Add(b); }
        inline friend const T& operator+=(T& a, const T& b) { return a.AddEq(b); }

        T Sub(const T& b) const;
        const T& SubEq(const T& b);
        inline friend T operator-(const T& a, const T& b) { return a.Sub(b); }
        inline friend const T& operator-=(T& a, const T& b) { return a.SubEq(b); }

        // COMPARE


        /**
         * Compares the current BigInteger to BigInteger a.
         *
         * @param a is the BigInteger to be compared with.
         * @return  -1 for strictly less than, 0 for equal to and 1 for strictly
         * greater than conditons.
         */
        int Compare(const T& a) const;

        //// relational operators, using Compare
        friend bool operator==(const T& a, const T& b) { return a.Compare(b) == 0; }
        friend bool operator!=(const T& a, const T& b) { return a.Compare(b) != 0; }

        friend bool operator>(const T& a, const T& b) { return a.Compare(b) > 0; }
        friend bool operator>=(const T& a, const T& b) { return a.Compare(b) >= 0; }
        friend bool operator<(const T& a, const T& b) { return a.Compare(b) < 0; }
        friend bool operator<=(const T& a, const T& b) { return a.Compare(b) <= 0; }






        usint GetMSB() const;

        const std::string ToString() const;
    };
}

    namespace lbcrypto{

    template<typename T, typename I>
    class BigVectorInterface {
    public:
        typedef I Integer;
        // CONSTRUCTORS

        // Constructors should be implemented in the derived classes
        // The derived classes should implement constructors from initializer lists of
        // integers and strings

        // ASSIGNMENT OPERATORS

        /**
         * Copy assignment operator.
         *
         * @param &vec is the vector to be assigned from.
         * @return assigned vector ref.
         */
        const T &operator=(const T &vec);

        /**
         * Move assignment operator.
         *
         * @param &vec is the vector to be assigned from.
         * @return assigned vector ref.
         */
        const T &operator=(T &&vec);

        /**
         * Assignment operator from initializer list of strings.
         *
         * @param &&strvec is the list of strings.
         * @return assigned vector ref.
         */
        const T &operator=(std::initializer_list<std::string> strvec);

        /**
         * Assignment operator from initializer list of unsigned integers.
         *
         * @param &&vec is the list of integers.
         * @return assigned vector ref.
         */
        const T &operator=(std::initializer_list<uint64_tt> vec);

        /**
         * Assignment operator to assign value val to first entry, 0 for the rest of
         * entries.
         *
         * @param val is the unsigned integer the first entry to be assigned from.
         * @return assigned vector ref.
         */
        const T &operator=(uint64_tt val);

        // EQUALS OPERATORS

        /**
         * Equals to operator.
         *
         * @param &b is vector to be compared.
         * @return true if equal and false otherwise.
         */
        friend inline bool operator==(const T &a, const T &b) {
            if ((a.GetLength() != b.GetLength()) ||
                (a.GetModulus() != b.GetModulus())) {
                return false;
            }
            for (size_t i = 0; i < a.GetLength(); ++i) {
                if (a[i] != b[i]) {
                    return false;
                }
            }
            return true;
        }

        /**
         * Not equal to operator.
         *
         * @param b is vector to be compared.
         * @return true if not equal and false otherwise.
         */
        friend inline bool operator!=(const T &a, const T &b) { return !(a == b); }

        // ACCESSORS

        // The derived class must implement at and operator[]
        I &at(size_t idx);

        const I &at(size_t idx) const;

        I &operator[](size_t idx);

        const I &operator[](size_t idx) const;

        /**
         * Vector modulus operator.
         *
         * @param &modulus is the modulus to perform on the current vector entries.
         * @return is the result of the modulus operation on current vector.
         */
        T Mod(const I& modulus) const;

        /**
         * Vector modulus operator. In-place variant.
         *
         * @param &modulus is the modulus to perform on the current vector entries.
         * @return is the result of the modulus operation on current vector.
         */
        const T& ModEq(const I& modulus);

        /// inline operators for the modulus operations.
        inline friend T operator%(const T& a, const I& b) { return a.Mod(b); }
        inline friend const T& operator%=(T& a, const I& b) { return a.ModEq(b); }

        /**
        * Scalar-from-vector modulus subtraction operation.
        *
        * @param &b is the scalar to perform operation with.
        * @return is the result of the modulus subtraction operation.
        */
        T ModSub(const I& b) const;

        /**
         * Scalar-from-vector modulus subtraction operation. In-place variant.
         *
         * @param &b is the scalar to perform operation with.
         * @return is the result of the modulus subtraction operation.
         */
        const T& ModSubEq(const I& b);

        /// inline operators for the scalar-from-vector modulus subtraction
        /// operations.
        inline friend T operator-(const T& a, const I& b) { return a.ModSub(b); }
        inline friend const T& operator-=(T& a, const I& b) { return a.ModSubEq(b); }

        /**
         * Vector component wise modulus subtraction.
         *
         * @param &b is the vector to perform operation with.
         * @return is the result of the component wise modulus subtraction operation.
         */
        T ModSub(const T& b) const;

        /**
         * Vector component wise modulus subtraction. In-place variant.
         *
         * @param &b is the vector to perform operation with.
         * @return is the result of the component wise modulus subtraction operation.
         */
        const T& ModSubEq(const T& b);

        /// inline operators for the vector component wise modulus subtraction
        /// operations.
        //inline friend T operator-(const T& a, const T& b) { return a.ModSub(b); }
        //inline friend const T& operator-=(T& a, const T& b) { return a.ModSubEq(b); }

        /**
         * Sets the vector modulus.
         *
         * @param value is the value to set.
         * @param value is the modulus value to set.
         */
        void SetModulus(const I &value);

        /**
 * Gets the vector modulus.
 *
 * @return the vector modulus.
 */
        const I &GetModulus() const;

        /**
         * Gets the vector length.
         *
         * @return vector length.
         */
        size_t GetLength() const;;

// TODO
        class BigMatrixInterface {
        };
    };


}


#endif //FINAL_INTERFACE_H
