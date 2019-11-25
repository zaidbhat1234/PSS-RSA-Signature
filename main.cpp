//
//  main.cpp
//  RSA_PSS_SIGNING
//
//  Created by Zaid Bhat on 18/02/19.
//  Copyright © 2019 Zaid Bhat. All rights reserved.
//

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
#include<stdlib.h>
#include <fstream>

#include <sha.h>
#include "filters.h"
#include "base64.h"
#include <hex.h>

#include "integer.h"
#include "osrng.h"
#include "nbtheory.h"
#include "hrtimer.h"
using namespace std;

using namespace CryptoPP;

#include "Gen_prime.hpp"
#include "Gen_dec_key.hpp"

#include "PSS_gen.hpp"
#include "PSS_ver.hpp"



int main(int argc, const char * argv[]) {
  
    
    FILE *ptrP = fopen("Primep.txt", "w");
    FILE *ptrQ = fopen("Primeq.txt", "w");
    
    
    
    
    int length;
    mpz_class p =   Gen_prime(1024,1,ptrP);
    
    mpz_class q = Gen_prime(1024,2,ptrQ);
    fclose(ptrP);
    fclose(ptrQ);
    
    std::ifstream ifs("SampleTextFile_10kb.txt");
    std::string message( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );
    
    
    
    
    
    
    
    mpz_class x,y;
    
    
    
    //find b
    mpz_class n,phi;
    n=p*q;
    // cout<<"n is "<<n<<'\n';
    
    
    
    
    // FILE *ptrP,*ptrQ;
    
    ptrP = fopen("pub_key.txt", "w");
    ptrQ = fopen("pri_key.txt", "w");
    
    
    
    
    
    
    Gen_dec_key(ptrP, ptrQ);
    
    
    
    ptrP = fopen("pub_key.txt", "r");
    ptrQ = fopen("pri_key.txt", "r");
    fscanf(ptrP,"%d",&length);
    //cout<<"LENGTH"<<length;
    char temp_bb[length];
    fscanf(ptrP,"%s",temp_bb);
    mpz_class b;
    b =temp_bb;
    fscanf(ptrQ,"%d",&length);
    //cout<<"LENGTH"<<length;
    char temp_aa[length];
    fscanf(ptrQ,"%s",temp_aa);
    mpz_class a;
    a =temp_aa;
    
    fclose(ptrP);
    fclose(ptrQ);
    
    
    FILE *ptrrsa = fopen("rsapub.txt", "w"); //to store public values of RSA in order n , enc message, public key.
    
    
    
    string tem_f;
    char tem_n[tem_f.length()];
    tem_f = n.get_str();
    fprintf(ptrrsa, "%ld %s ",tem_f.length(),tem_n);
    
    fclose(ptrrsa);
    
    PSS(n);
    
    
    ptrP =fopen("PSS.txt", "r");
    PSS_ver(ptrP,n);
    
    
    
    
    fclose(ptrP);
    
}
