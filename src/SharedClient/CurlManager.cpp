#include "CurlManager.h"
#include <iostream>

CurlManager::CurlManager() {
	this->curl = curl_easy_init();
	this->headers = NULL;
	this->url = "http://tp-7552-g05-sharedserver.herokuapp.com";
	this->bodyParams = Json::Value();
}

CurlManager::~CurlManager() {
	if(this->headers) {
		curl_slist_free_all(this->headers);
	}
	if(this->curl) {
		curl_easy_cleanup(this->curl);
	}
}

bool CurlManager::init_string(struct cstring *s) {
	s->len = 0;
	s->ptr = (char*)malloc(s->len+1);
	if (s->ptr == NULL) {
		LoggerManager::getInstance()->log(LoggerManager::logError, "struct cstring malloc() failed");
		return false;
	}
	s->ptr[0] = '\0';
	return true;
}

void EscapeJSON(const std::string& sSrc, std::string& sDest) {
	size_t sz = sSrc.length();
	sDest.erase();
	for (size_t i = 0; i < sz; ++i) {
		string sTmp;
		switch(sSrc[i]) {
			case '\"':
				sTmp = '\"';
				break;
			case '\\':
				sTmp = "\\";
				break;
			case '\r':
				sTmp = "\r";
				break;
			case '\t':
				sTmp = "\t";
				break;
			case '\n':
				sTmp = "\n";
				break;
			default:
				sTmp = sSrc[i];
				break;
		};
		sDest += sTmp;
	}
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct cstring *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = (char*)realloc(s->ptr, new_len+1);
	if (s->ptr == NULL) {
		LoggerManager::getInstance()->log(LoggerManager::logError, "struct cstring realloc() failed");
		return 0;
	}
	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}

void CurlManager::setMethodType(std::string method) {
	if(method.compare(POST) == 0) {
		curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "POST");
	} else if(method.compare(PUT) == 0) {
		curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "PUT");
	} else if(method.compare(DELETE) == 0) {
		curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	}
}

void CurlManager::addHeader(std::string header) {
	this->headers = curl_slist_append(this->headers, header.c_str());
}

void CurlManager::setUri(std::string uri) {
	this->uri = uri;
}

void CurlManager::addUriParameter(std::string param) {
	params.push_back(param);
}

void CurlManager::addUniqueParameter(std::string key, std::string value) {
	bodyParams[key.c_str()] = value;
}

void CurlManager::addJsonParameter(std::string key, Json::Value value) {
	bodyParams[key.c_str()] = value;
}

Json::Value CurlManager::execute() {
	if(!this->curl) {
		return 0;
	}
	if(this->headers) {
		curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->headers);
	}
	std::string URL = this->url + "/" + this->uri;
	std::vector<std::string>::iterator it = params.begin();
	std::string parameters = "";
	while(it != params.end()) {
		parameters += *it + "&";
		++it;	
	}
	if(parameters.length()) {
		parameters.pop_back();
		URL += "/" + parameters;
	}
	curl_easy_setopt(this->curl, CURLOPT_URL, URL.c_str());
	//curl_easy_setopt(this->curl, CURLOPT_VERBOSE, 1L);
	char* postData = NULL;
	if(!bodyParams .empty()) {
		Json::FastWriter fast;
		std::string body = fast.write(this->bodyParams);
		static std::string bodySender;
		EscapeJSON(body, bodySender);
		postData = new char[bodySender.length()]();
		strcpy(postData, bodySender.c_str());
    	curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, postData);
	}
	struct cstring s;
	Json::Value val = Json::Value();
    if(this->init_string(&s)) {
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		CURLcode res;
		res = curl_easy_perform(this->curl);
		long responseCode;
		CURLcode info = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
		if(res != CURLE_OK) {
			val["error"] = std::string(curl_easy_strerror(res));
		} else {
			std::string response(s.ptr);
		    free(s.ptr);
			if(responseCode == 200 || responseCode == 201) {
			    Json::Reader r = Json::Reader();
				r.parse(response.c_str(), val);
			} else {
				val["error"] = response;
			}
		}
		if(info == CURLE_OK) {
			val["status"] = (int)responseCode;
		} else {
			val["status"] = 500;
		}
	} else {
		val["status"] = 500;
		val["error"] = "Internal Error with cstring struct init";
	}
	if(postData != NULL) {
		delete[] postData;
	}
	return val;
}
