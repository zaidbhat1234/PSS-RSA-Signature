//
//  PSS_gen.cpp
//  
//
//  Created by Zaid Bhat on 12/02/19.
//

#include "PSS_gen.hpp"
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

#include "FDH_ver_sig.hpp"
using namespace std;

using namespace CryptoPP;

static inline unsigned int value(char c)
{
    if (c >= '0' && c <= '9') { return c - '0';      }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    return -1;
}

std::string str_xor_(std::string const & s1, std::string const & s2)
{
    assert(s1.length() == s2.length());
    
    static char const alphabet[] = "0123456789abcdef";
    
    std::string result;
    result.reserve(s1.length());
    
    for (std::size_t i = 0; i != s1.length(); ++i)
    {
        unsigned int v = value(s1[i]) ^ value(s2[i]);
        
        assert(v < sizeof alphabet);
        
        result.push_back(alphabet[v]);
    }
    
    return result;
}

void PSS( mpz_class n){
    
    
    FILE *ptr = fopen("pri_key.txt", "r");
    
    
    int length;
    fscanf(ptr,"%d",&length);
    //cout<<"LENGTH"<<length;
    char temp_a[length];
    fscanf(ptr,"%s",temp_a);
    mpz_class d;
    d =temp_a;
    fclose(ptr);
    
    
    
    
    
    
    std::ifstream ifs("SampleTextFile_10kb.txt");
    std::string message( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );
    
    
    
    int l = 1024;
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
    string T;
    
    
    
    Integer xw;
    AutoSeededRandomPool(prng);
    xw.Randomize(prng, 160);
    string Hex;
    
    std::stringstream sf;
    sf<<std::hex<<xw;
    sf>>Hex;
    
    Hex.erase(20,Hex.length());
    //cout<<Hex;
    seed=Hex;
    //cout<<"SEED IS "<<seed<<'\n';
    
    w=seed+message;
    w=FDH_(w);
    
    w.erase(20,w.length()-20);
    //cout<<"W IS :"<<w<<'\n';
    
    expandedW = FDH_(w);
    expandedW.erase(olen-20,expandedW.length());
    //cout<<"EX W"<<expandedW<<'\n';
    
    seedmask = expandedW;
    seedmask.erase(20,seedmask.length());
    // cout<<"seedmask"<<seedmask<<'\n';
    
    remainmask = expandedW;
    remainmask.erase(0,20);
    // cout<<"remainmask"<<remainmask<<'\n';
    /*
     std::stringstream stream1;
     mpz_class s1,s2;
     
     stream1<<seed;
     stream1>>s1;
     std::stringstream stream2;
     stream2<<seedmask;
     
     stream2>>s2;
     //cout<<"GSG"<<s1;
     cout<<'\n'<<s1<<"S1"<<'\n'<<s2<<"S2";
     s1=s1^s2;
     cout<<'\n'<<"S!"<<s1;
     
     
     */
    maskedseed = str_xor_(seed, seedmask);
    // cout<<"maskedseed"<<maskedseed<<'\n';
    T= w+maskedseed+remainmask;
    // cout<<"T:"<<'\n'<<T;
    Integer x;
    std::stringstream s;
    s<<T;
    mpz_class f;
    s>>std::hex>>f;
    // cout<<"F IS "<<f;
    // cout<<"X:"<<x;
    
    //cout<<"Tis "<<T<<'\n';
    
    
    mpz_class sig = power_1(f, d, n);
    // cout<<"SIGNED BY PSS:"<<sig;
    
    FILE *PssF= fopen("PSS.txt", "w");
    
    //storing l and sig in a file
    fprintf(PssF, "%d ",l);
    
    
    string temp_f = sig.get_str();
    char temp_h[temp_f.length()];
    strcpy(temp_h, temp_f.c_str());
    fprintf(PssF, "%ld %s ",temp_f.length(),temp_h);
    
    fclose(PssF);
    
    
    // cout<<"F is :"<<f;
    //cout<<"S!"<<s1;
    //stream1>>maskedseed;
    
    
    
    
}
