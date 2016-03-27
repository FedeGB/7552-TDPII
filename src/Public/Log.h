/*
 * Log.h
 *
 *  Created on: 22/03/2016
 *      Author: demian
 */

#ifndef LOG_H_
#define LOG_H_

class string;

class Log {
public:
	enum LogType {
		LOG_NONE,
		LOG_NORMAL,
		LOG_DEBUG,
		LOG_ERROR
	};

	static void logMessage(LogType logType, const char* message);
	static void setLogType(LogType logType);
	virtual ~Log(){}
private:
	static LogType currentLogType;
	static const char* getLogName(LogType logType);
};

#endif /* LOG_H_ */
