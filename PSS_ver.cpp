//
//  PSS_ver.cpp
//  RSA
//
//  Created by Zaid Bhat on 12/02/19.
//  Copyright © 2019 Zaid Bhat. All rights reserved.
//

#include "PSS_ver.hpp"
#include <iostream>
#include <math.h>
#include <gmpxx.h>
#include <primesieve.hpp>
#include <math.h>
#include <time.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <functional>
#include <cryptlib.h>
#include <iomanip>

#include <fstream>

#include <sha.h>
#include "filters.h"
#include "base64.h"
#include <hex.h>

#include "integer.h"
#include "osrng.h"
#include "nbtheory.h"
#include "hrtimer.h"
#include "PSS_gen.hpp"
using namespace std;

using namespace CryptoPP;


void PSS_ver(FILE *ptr,mpz_class n){
    string T;
    FILE *ptr1 = fopen("pub_key.txt", "r");
    std::ifstream ifs("SampleTextFile_10kb.txt");
    std::string message( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );
    int length;
    fscanf(ptr1,"%d",&length);
    //cout<<"LENGTH"<<length;
    char temp_e[length];
    fscanf(ptr1,"%s",temp_e);
    mpz_class e;
    e =temp_e;
    fclose(ptr1);
    fscanf(ptr,"%d",&length);
    //cout<<"LENGTH"<<length;
    int  l=length;
    fscanf(ptr,"%d",&length);
    //cout<<"LENGTH"<<length;
    char temp_s[length];
    fscanf(ptr,"%s",temp_s);
    mpz_class sig;
    sig =temp_s;
    //cout<<"SIG is "<<sig<<'\n';
    mpz_class f = power_1(sig, e, n);
    //cout<<"F is "<<f;
    std::stringstream sq;
    sq<<std::hex<<f;
    sq>>T;
    transform(T.begin(), T.end(), T.begin(), ::toupper);
    // cout<<"T"<<T;
    // cout<<"X in ver is "<<x<<'\n';
    int olen = l/8;
    int wlen,seedlen;
    wlen=seedlen=20;
    string seed="";
    string temp;
    string w;
    string expandedW;
    string seedmask;
    string remainmask;
    string maskedseed;
    // string T;
    //std::stringstream s;
    //s<<x;
    //s>>T;
    w=T;
    w.erase(20,w.length()-20);
    //  cout<<'\n'<<"W:"<<w;
    maskedseed = T;
    maskedseed.erase(40,maskedseed.length()-40);
    maskedseed.erase(0,20);
    //  cout<<'\n'<<"masked:"<<maskedseed;
    remainmask = T;
    remainmask.erase(0,40);
    //  cout<<'\n'<<"remainmasked:"<<remainmask;
    expandedW= FDH_(w);
    expandedW.erase(olen-20,expandedW.length());
    // cout<<'\n'<<"EXW"<<expandedW<<'\n';
    seedmask=expandedW;
    seedmask.erase(20,seedmask.length());
    string remainmask2 = expandedW;
    remainmask2.erase(0,20);
    seed = str_xor_(maskedseed, seedmask);
    seed+=message;
    seed = FDH_(seed);
    seed.erase(20,seed.length());
    //cout<<'\n'<<"rr"<<remainmask<<'\n'<<"r"<<remainmask2;
    if(remainmask2==remainmask&&seed==w){
        cout<<"verified";
    }
    else
        cout<<"NOT verified";
    
    
}



