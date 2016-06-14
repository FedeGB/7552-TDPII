//
// Created by Juan Manuel Hidalgo on 22/5/16.
//

#ifndef TINDER_UTILS_H
#define TINDER_UTILS_H

#include <string>
#include <cmath>

#define PI 3.14159265

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);
float harvestineDistance(double, double, double, double);

#endif //TINDER_UTILS_H
