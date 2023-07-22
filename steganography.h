/*
This file declares the namespace and classes that deal with encrypting & decrypting files
Written by Dallas Hart
Copyright May 15 2020
*/

#include <fstream>
#include "bitmap.h"

unsigned long max_fit_size(bitmap&, unsigned = 2);
bitmap encrypt(bitmap&, const char*, unsigned = 2);
bitmap decrypt(bitmap&, const char*, unsigned = 2);

