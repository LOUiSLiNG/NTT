//#pragma once

#include "backend.h"
#include "NTT.cpp"

using namespace lbcrypto;
//typedef NativeVector VecType;

void t_funct(const VecType& element, const VecType& rootOfUnityTable, const NativeVector& preconRootOfUnityTable, VecType* result){
NativeVector elem;
NativeVector rotf;
NativeVector protf;
NativeVector rsult;

NumberTheoreticTransform<VecType> NTTf;
NTTf.ForwardTransformToBitReverse(elem, rotf, protf, &rsult);
}


