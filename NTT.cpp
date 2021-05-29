//
//  NTT.cpp
//  practise
//
//  Created by Puneet Rehal on 5/9/21.
//

#include "NTT.hpp"
#include <fstream>
#include <iostream>
#include "NatVec.hpp"
#include "NatInt.hpp"
#include "backend.h"
#include "nbtheory.h"


using namespace std;
//using namespace lbcrypto;
//using namespace bigintnat;

//typedef NativeVector VecType;

namespace lbcrypto {
    template<typename VecType>
//    void NumberTheoreticTransform<VecType>::
    void ForwardTransformToBitReverse(
            const VecType &element, const VecType &rootOfUnityTable,
            const NativeVector &preconRootOfUnityTable, VecType *result) {
//        usint n = element.GetLength();
//        //cout<< "n is: " <<n<< endl;
//        // usint rot = rootOfUnityTable.GetLength();
//        // usint prot = preconRootOfUnityTable.GetLength();
//
//
//
//        //cout<< "the length of the element is " << n << " " << rot << " " << prot << " "  << endl;
//
//        ofstream ele;
//        ele.open("element.txt");
//        ele << element << endl;
//        ele.close();
//
//        ofstream rot;
//        rot.open("rootOfUnityTable.txt");
//        rot << rootOfUnityTable << endl;
//        rot.close();
//
//        ofstream prot;
//        prot.open("preconRootOfUnityTable.txt");
//        prot << preconRootOfUnityTable << endl;
//        prot.close();
//
//
//
//        if (result->GetLength() != n) {
//        std::cout<<
//        "size of input element and size of output element not of same size" <<std::endl;
//        }
//
//        IntType modulus = element.GetModulus();
//        //cout<< "modulus is: " << modulus <<endl;
//        //cout<< "type is: " << typeid(modulus).name() <<endl;
//
//        result->SetModulus(modulus);
//        for (uint32_t i = 0; i < n; ++i) {
//            (*result)[i] = element[i];
//        }
//
//        ofstream ptrx1;
//        ptrx1.open("chekcheck.txt");
//        for (uint32_t i = 0; i < n; ++i) {
//           ptrx1<<  (*result)[i] <<" " <<n <<endl;
//        }
//        ptrx1.close();
//
//        //cout << "*result is" << *result <<endl;
//
//        uint32_t indexOmega, indexHi;
//        NativeInteger preconOmega;
//        IntType omega, omegaFactor, loVal, hiVal, zero(0); //Nativeintegers
//
//       // cout << indexOmega << " " << indexHi << " " << preconOmega << " " << omega << " "<< omegaFactor << " " << loVal << " " << hiVal << " " << zero << endl;
////        int cc = 0;
////
//        usint t = (n >> 1); //cout<< "t is " << t<<endl; //correct
//        usint logt1 = GetMSB64(t); //cout << "logt1 is " << logt1 <<endl; //correct
//        ofstream ptrx;
//        ptrx.open("chekcheck.txt");
//        for (uint32_t m = 1; m < n; m <<= 1, t >>= 1, --logt1) {
//            uint32_t j1, j2;
//            for (uint32_t i = 0; i < m; ++i) {
//                j1 = i << logt1;
//                ptrx<<  j1 <<" "<< i<<endl;
//                j2 = j1 + t;
//                indexOmega = m + i; //correct
//
//
//
//                //cout<< "indexOmega is " << indexOmega <<endl;
//                //omega = rootOfUnityTable[indexOmega];
//                //cout<< "Omega is " <<omega <<endl;
//                //cout<< "omega type is: " << omega <<endl;
//                //cout<< "omega type is: " << typeid(omega).name() <<endl;
//                omega = rootOfUnityTable[indexOmega]; //correct
//
//                preconOmega = preconRootOfUnityTable[indexOmega]; //NativeInteger //correct
//
//                //cout << "preconRootOfUnityTable " << preconRootOfUnityTable.at(1) <<endl;
//                for (uint32_t indexLo = j1; indexLo < j2; ++indexLo) {
//                    indexHi = indexLo + t; ptrx<< "inedxHi is" <<indexHi<<endl; //correct
//
//                    loVal = (*result)[indexLo]; ptrx << "indexlo is" << indexLo << endl; //issue
//
//                    omegaFactor = (*result)[indexHi]; //cout<< "omegafactor is: " << omegaFactor <<endl;
//                    if (omegaFactor != zero) {
//                        omegaFactor.ModMulFastConstEq(omega, modulus, preconOmega); //cout<< "omegafactor is: "<< omegaFactor <<endl;
//                        hiVal = loVal + omegaFactor;
//                        //cout<< "hiVal is "<< hiVal <<endl;
//                        if (hiVal >= modulus) {
//                            hiVal -= modulus;
//                        }
//
//                        if (loVal < omegaFactor) {
//                            loVal += modulus;
//                        }
//                        loVal -= omegaFactor;
//                        //cout<< "loVal is "<< loVal <<endl;
//
//                        (*result)[indexLo] = hiVal;
//                        (*result)[indexHi] = loVal;
//                    } else {
//                        (*result)[indexHi] = loVal;
//                    }
//                }
//            }
//        }
//        ptrx.close();
//
//        ofstream ele1;
//        ele1.open("element1.txt");
//        ele1 << element << endl;
//        ele1.close();
//
//        ofstream rot1;
//        rot1.open("rootOfUnityTable1.txt");
//        rot1 << rootOfUnityTable << endl;
//        rot1.close();
//
//        ofstream prot1;
//        prot1.open("preconRootOfUnityTable1.txt");
//        prot1 << preconRootOfUnityTable << endl;
//        prot1.close();
//
//        ofstream rslt;
//        rslt.open("result.txt");
//        rslt << *result << endl;
//        rslt.close();
//
//
//        return;
    }
}
