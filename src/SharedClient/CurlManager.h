#ifndef CURLMANAGER_H_
#define CURLMANAGER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <curl/curl.h>
#include "json/json.h"
#include <vector>

struct string {
	char *ptr;
	size_t len;
};

class CurlManager {
public:
	
	std::string POST = "POST";
	std::string PUT = "PUT";
	std::string DELETE = "DELETE";

	CurlManager();
	~CurlManager();

	void setMethodType(std::string);
	void addHeader(std::string);
	void setUri(std::string);
	void addParameter(std::string);
	Json::Value execute();

private:
	CURL *curl;
	struct curl_slist *headers;
	std::string uri;
	std::vector<std::string> params;
	std::string url;

	void init_string(struct string *);
};

#endif /*CURLMANAGER_H_*/