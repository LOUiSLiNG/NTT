//
//  NatVec.cpp
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//
//#pragma once
#include "NatVec.hpp"
#include "backend.h"

namespace bigintnat {

// CONSTRUCTORS
template <class IntegerType>
NativeVector<IntegerType>::NativeVector() {}

template <class IntegerType>
NativeVector<IntegerType>::NativeVector(usint length) {
  this->m_data.resize(length);
}

    template <class IntegerType>
    NativeVector<IntegerType>::NativeVector(usint length,
                                            const IntegerType &modulus) {
        if (modulus.GetMSB() > MAX_MODULUS_SIZE) {
            std::cout << "Modulus size not supportable " << std::endl;
        }
        this->SetModulus(modulus);
        this->m_data.resize(length);
    }

template <class IntegerType>
NativeVector<IntegerType>::NativeVector(const NativeVector &bigVector) {
    m_modulus = bigVector.m_modulus;
    m_data = bigVector.m_data;
    }

    template <class IntegerType>
    NativeVector<IntegerType>::NativeVector(NativeVector &&bigVector) {
        m_data = std::move(bigVector.m_data);
        m_modulus = bigVector.m_modulus;
    }

    template <class IntegerType>
    NativeVector<IntegerType>::NativeVector(
            usint length, const IntegerType &modulus,
            std::initializer_list<std::string> rhs) {
        this->SetModulus(modulus);
        this->m_data.resize(length);
        usint len = rhs.size();
        for (usint i = 0; i < m_data.size(); i++) {  // this loops over each entry
            if (i < len) {
                m_data[i] = IntegerType(*(rhs.begin() + i)) % m_modulus;
            } else {
                m_data[i] = IntegerType(0);
            }
        }
    }

    template <class IntegerType>
    NativeVector<IntegerType>::NativeVector(usint length,
                                            const IntegerType &modulus,
                                            std::initializer_list<uint64_tt> rhs) {
        this->SetModulus(modulus);
        this->m_data.resize(length);
        usint len = rhs.size();
        for (usint i = 0; i < m_data.size(); i++) {  // this loops over each entry
            if (i < len) {
                m_data[i] = IntegerType(*(rhs.begin() + i)) % m_modulus;
            } else {
                m_data[i] = IntegerType(0);
            }
        }
    }

template <class IntegerType>
NativeVector<IntegerType>::~NativeVector() {}

// ASSIGNMENT OPERATORS

template <class IntegerType>
const NativeVector<IntegerType> &NativeVector<IntegerType>::operator=(
    const NativeVector &rhs) {
  if (this != &rhs) {
    if (this->m_data.size() == rhs.m_data.size()) {
      for (usint i = 0; i < m_data.size(); i++) {
        this->m_data[i] = rhs.m_data[i];
      }
    } else {
      m_data = rhs.m_data;
    }
    m_modulus = rhs.m_modulus;
  }
  return *this;
}

template <class IntegerType>
NativeVector<IntegerType> &NativeVector<IntegerType>::operator=(
    NativeVector &&rhs) {
  if (this != &rhs) {
    m_data = std::move(rhs.m_data);
    m_modulus = rhs.m_modulus;
  }
  return *this;
}

template <class IntegerType>
const NativeVector<IntegerType> &NativeVector<IntegerType>::operator=(
    std::initializer_list<std::string> rhs) {
  usint len = rhs.size();
  for (usint i = 0; i < m_data.size(); i++) {  // this loops over each tower
    if (i < len) {
      if (m_modulus != 0) {
        m_data[i] = IntegerType(*(rhs.begin() + i)) % m_modulus;
      } else {
        m_data[i] = IntegerType(*(rhs.begin() + i));
      }
    } else {
      m_data[i] = 0;
    }
  }
  return *this;
}

template <class IntegerType>
const NativeVector<IntegerType> &NativeVector<IntegerType>::operator=(
    std::initializer_list<uint64_tt> rhs) {
  usint len = rhs.size();
  for (usint i = 0; i < m_data.size(); i++) {  // this loops over each tower
    if (i < len) {
      if (m_modulus != 0) {
        m_data[i] = IntegerType(*(rhs.begin() + i)) % m_modulus;
      } else {
        m_data[i] = IntegerType(*(rhs.begin() + i));
      }
    } else {
      m_data[i] = 0;
    }
  }
  return *this;
}

// ACCESSORS

template <class IntegerType>
void NativeVector<IntegerType>::SetModulus(const IntegerType &value) {
  if (value.GetMSB() > MAX_MODULUS_SIZE) {
      std:: cout<< "Error because of condition in line 93 file Natvec.cpp" << std::endl;
  }
        this->m_modulus = value;
}

template <class IntegerType>
const IntegerType &NativeVector<IntegerType>::GetModulus() const {
  return this->m_modulus;
}

//template class NativeVector<NativeInteger>;
}

