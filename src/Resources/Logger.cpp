//
// Created by Juan Manuel Hidalgo on 27/4/16.
//

#include "Logger.h"

const string LoggerManager::logDebug = "DEBUG";
const string LoggerManager::logInfo = "INFO";
const string LoggerManager::logError = "ERROR";
const string LoggerManager::logWarn = "WARN";


LoggerManager* LoggerManager::m_pInstance= NULL;


LoggerManager* LoggerManager::getInstance() {
    if(!m_pInstance){
        m_pInstance = new LoggerManager();
    }
    return m_pInstance;
}

LoggerManager::LoggerManager(){

}

LoggerManager::~LoggerManager() {
    outputStream.close();
}

string getTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y/%m/%d %X", &tstruct);
    return buf;
}

/**
 *
 * @param type of log. See Constants
 * @param message the message to log
 * @return 1 in error, 0 in success
 */

int LoggerManager::log(string type, string message) {
    outputStream.open ("./logs.txt", ios::app);
    if(outputStream.is_open()){
        outputStream << getTime() << " - " << LoggerManager::logInfo << " - " << message << endl;
        outputStream << "." << "\n";
    }
    else{
        cout << "No se pudo abrir el archivo de log." << endl;
        return 1;
    }
    return 0;
}
