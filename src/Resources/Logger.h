//
// Created by Juan Manuel Hidalgo on 27/4/16.
//

#ifndef TINDER_LOGGER_H
#define TINDER_LOGGER_H


#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stddef.h>
#include <fstream>

using namespace std;

class LoggerManager {
public:
    static const std::string logDebug;
    static const std::string logError;
    static const std::string logWarn;
    static const std::string logInfo;

    static LoggerManager* getInstance();
    virtual ~LoggerManager();
    int log(string type, string message);

private:
    LoggerManager();
    static const char* logFileName;
    static LoggerManager* m_pInstance;
    std::ofstream outputStream;
};


#endif //TINDER_LOGGER_H
