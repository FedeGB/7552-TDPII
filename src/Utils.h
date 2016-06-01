//
// Created by Juan Manuel Hidalgo on 22/5/16.
//

#ifndef TINDER_UTILS_H
#define TINDER_UTILS_H

#include <string>


std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


#endif //TINDER_UTILS_H
