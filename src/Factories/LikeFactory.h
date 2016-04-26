//
// Created by Juan Manuel Hidalgo on 26/4/16.
//

#ifndef TINDER_LIKEFACTORY_H
#define TINDER_LIKEFACTORY_H

#include "Factory.h"
#include <string>
#include "../Like.h"

class LikeFactory: public Factory {
public:
    LikeFactory();
    virtual ~LikeFactory();
    Like* createWithJsonValue(Json::Value value);
    Like* createWithJsonString(string json);
};


#endif //TINDER_LIKEFACTORY_H
