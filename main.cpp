
#include <iterator>
#include "backend.h"
#include "NTT.hpp"
#include "NTT.cpp"
#include "NatInt.cpp"
#include "NatVec.cpp"
#include "inttypes.h"
#include "interface.cpp"

#include <vector>



using namespace std;
using namespace lbcrypto;

//typename NativeVector VecType;



int main() {
NativeVector x(1024); //element
int t = x.GetLength();
cout<<t<<endl;
NativeVector rot(1024); //root_of_unity_table
NativeVector prot(1024);//precon_root_of_unity_table
NativeVector rslt(1024); //result

    NativeInteger modulus("288230376151748609");

    vector<unsigned long long> x_;
    vector<unsigned long long> rot_;
    vector<unsigned long long> prot_;
    vector<unsigned long long> rslt_;

    ifstream file1;
    file1.open("check_element1.txt");
    unsigned long long val1;
    while(file1>>val1){
        x_.push_back(val1);
}

    //cout << x_[0]<<endl;
    for (usint i = 0; i < 1024; i++){
          x.at(i)   = x_[i];
    }
    file1.close();
    ifstream file2;
    file2.open("check_rootOfUnityTable1.txt");
    unsigned long long val2;
    while(file2>>val2){
        rot_.push_back(val2);

    }
    file2.close();
    for (usint i = 0; i < 1024; i++){
        rot.at(i) = rot_[i];
    }
    ifstream file3;
    file3.open("check_preconRootOfUnityTable1.txt");
    unsigned long long val3;
    while(file3>>val3){
        prot_.push_back(val3);
    }
    file3.close();
    for (usint i = 0; i < 1024; i++){
        prot.at(i) = prot_[i];
    }
    int counter = 0;
    while(counter < 1024){
    ForwardTransformToBitReverse(x, rot, prot, &rslt); counter++;}
    return 0;
}



