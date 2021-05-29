//
//  NatVec.hpp
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//
//#pragma once
#ifndef NatVec_hpp
#define NatVec_hpp

#include <stdio.h>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>
#include "inttypes.h"
#include "interface.h"



namespace bigintnat {

template <class IntegerType>
class NativeVector
        : public lbcrypto::BigVectorInterface<NativeVector<IntegerType>,
                IntegerType>{
    
public:
          // CONSTRUCTORS

            /**
             * Basic constructor.
             */
            NativeVector();

            /**
             * Basic constructor for specifying the length of the vector.
             *
             * @param length is the length of the native vector, in terms of the number of
             * entries.
             */
            explicit NativeVector(usint length);

             /**
              * Basic constructor for copying a vector
              *
              * @param bigVector is the native vector to be copied.
              */
            NativeVector(const NativeVector &bigVector);

            /**
              * Basic constructor for specifying the length of the vector and the modulus.
              *
              * @param length is the length of the native vector, in terms of the number of
              * entries.
              * @param modulus is the modulus of the ring.
              */
            NativeVector(usint length, const IntegerType &modulus);

            /**
               * Basic move constructor for moving a vector
               *
               * @param &&bigVector is the native vector to be moved.
               */
             NativeVector(NativeVector &&bigVector);  // move copy constructor

            /**
             * Basic constructor for specifying the length of the vector
             * the modulus and an initializer list.
             *
             * @param length is the length of the native vector, in terms of the number of
             * entries.
             * @param modulus is the modulus of the ring.
             * @param rhs is an initializer list of strings
             */

            NativeVector(usint length, const IntegerType &modulus,
                         std::initializer_list<std::string> rhs);

            /**
             * Basic constructor for specifying the length of the vector
             * the modulus and an initializer list.
             *
             * @param length is the length of the native vector, in terms of the number of
             * entries.
             * @param modulus is the modulus of the ring.
             * @param rhs is an initializer list of usint
             */
            NativeVector(usint length, const IntegerType &modulus,
                         std::initializer_list<uint64_tt> rhs);


            /**
              * Destructor.
              */
            virtual ~NativeVector();
          
            // ASSIGNMENT OPERATORS

            /**
              * Assignment operator to assign value from rhs
              *
              * @param rhs is the native vector to be assigned from.
              * @return Assigned NativeVector.
              */
            const NativeVector &operator=(const NativeVector &rhs);

            /**
              * Move assignment operator
              *
              * @param rhs is the native vector to be moved.
              * @return moved NativeVector object
              */
            NativeVector &operator=(NativeVector &&rhs);

            /**
              * Initializer list for NativeVector.
              *
              * @param rhs is the list of strings containing integers to be assigned to
              * the BBV.
              * @return NativeVector object
              */
            const NativeVector &operator=(std::initializer_list<std::string> rhs);

            /**
             * Initializer list for NativeVector.
             *
             * @param rhs is the list of integers to be assigned to the BBV.
             * @return NativeVector object
             */
            const NativeVector &operator=(std::initializer_list<uint64_tt> rhs);

            /**
             * Assignment operator to assign value val to first entry, 0 for the rest of
             * entries.
             *
             * @param val is the value to be assigned at the first entry.
             * @return Assigned NativeVector.
             */
            inline const NativeVector &operator=(uint64_tt val) {
              this->m_data[0] = val;
              for (size_t i = 1; i < GetLength(); ++i) {
                this->m_data[i] = 0;
              }
              return *this;
            }
          
          // ACCESSORS

            /**
             * Sets/gets a value at an index.
             * This method is slower than operator[] as it checks if index out of range
             *
             * @param index is the index to set a value at.
             */
            IntegerType &at(size_t i) {
              if (!this->IndexCheck(i)) {
                std::cout<< "NativeVector index out of range" << std::endl;
              }
                    return this->m_data[i];
            }

            const IntegerType &at(size_t i) const {
              if (!this->IndexCheck(i)) {
                  std::cout<< "NativeVector index out of range" << std::endl;
              }
                    return this->m_data[i];
            }

            /**
             * operators to get a value at an index.
             * @param idx is the index to get a value at.
             * @return is the value at the index. return nullptr if invalid index.
             */
            IntegerType &operator[](size_t idx) { return (this->m_data[idx]); }

            const IntegerType &operator[](size_t idx) const {
              return (this->m_data[idx]);
            }

            /**
            * Sets the vector modulus.
            *
            * @param value is the value to set.
            * @param value is the modulus value to set.
            */
           void SetModulus(const IntegerType &value);
          
          /**
            * Gets the vector modulus.
            *
            * @return the vector modulus.
            */
           const IntegerType &GetModulus() const;
          
          /**
            * Gets the vector length.
            *
            * @return vector length.
            */
           size_t GetLength() const { return this->m_data.size(); }
          
          // STRINGS & STREAMS

            /**
             * ostream operator to output vector values to console
             *
             * @param os is the std ostream object.
             * @param ptr_obj is the NativeVector object to be printed.
             * @return std ostream object which captures the vector values.
             */
            template <class IntegerType_c>
            friend std::ostream &operator<<(std::ostream &os,
                                            const NativeVector<IntegerType_c> &ptr_obj) {
              auto len = ptr_obj.m_data.size();
              os << "[";
              for (usint i = 0; i < len; i++) {
                os << ptr_obj.m_data[i];
                os << ((i == (len - 1)) ? "]" : " ");
              }
              os << " modulus: " << ptr_obj.m_modulus;
              return os;
            }
private:
          std::vector<IntegerType> m_data;
          IntegerType m_modulus = 288230376151748609;
          bool IndexCheck(size_t length) const {
              if (length > this->m_data.size()) {
                  return false;
              }
              return true;
          }
};
}
          





#endif /* NatVec_hpp */
