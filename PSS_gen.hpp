//
//  PSS_gen.hpp
//  
//
//  Created by Zaid Bhat on 12/02/19.
//

#ifndef PSS_gen_hpp
#define PSS_gen_hpp
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
#include <stdio.h>
void PSS( mpz_class n);
std::string str_xor_(std::string const & s1, std::string const & s2);
static inline unsigned int value(char c);
#endif /* PSS_gen_hpp */
