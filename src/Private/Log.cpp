/*
 * Log.cpp
 *
 *  Created on: 22/03/2016
 *      Author: demian
 */

#include <Log.h>
#include <iostream>

Log::LogType Log::currentLogType = Log::LOG_NONE;

void Log::logMessage(LogType logType, const char* message){
	if(currentLogType >= logType){
		std::cout<<"LOG: "<<Log::getLogName(logType)
			<<" - Message: "<< message<<std::endl;
	}
}

void Log::setLogType(LogType logType){
	Log::currentLogType  = logType;
}

const char* Log::getLogName(LogType logType){
	switch(logType){
	case Log::LOG_NORMAL:
		return "NORMAL";
		break;
	case Log::LOG_DEBUG:
		return "DEBUG";
		break;
	case Log::LOG_ERROR:
		return "ERROR";
		break;
	default:
		return "UNKNOW LOG TYPE";
		break;
	}
}

