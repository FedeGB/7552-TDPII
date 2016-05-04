#include "CurlManager.h"
#include <iostream>

CurlManager::CurlManager() {
	this->curl = curl_easy_init();
	this->headers = NULL;
	this->url = "http://tp-7552-g05-sharedserver.herokuapp.com";
}

CurlManager::~CurlManager() {
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
		curl_easy_setopt(this->curl, CURLOPT_POST, true);
	} else if(method.compare(PUT) == 0) {
		curl_easy_setopt(this->curl, CURLOPT_PUT, true);
	} else if(method.compare(DELETE) == 0) {
		//curl_easy_setopt(this->curl, CURLOPT_DELETE);
		// How to perform a delete?
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

void CurlManager::addParameter(std::string key, std::string value) {
	this->bodyParams.push_back(key + "=" + value);
}

Json::Value CurlManager::execute() {
	if(!curl) {
		return 0;
	}
	if(this->headers) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, this->headers);
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
	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	std::vector<std::string>::iterator itBod = bodyParams.begin();
	std::string body = "";
	while(itBod != bodyParams.end()) {
		body += *it + "&";
		std::cout << body << std::endl;
		++itBod;
	}
	if(body.length()) {
		body.pop_back();
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(body.c_str()));
	}
	struct cstring s;
	Json::Value val = Json::Value();
    if(this->init_string(&s)) {
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		CURLcode res;
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) { 
			val["status"] = (int)res;
			std::cout << res << std::endl;
			val["message"] = std::string(curl_easy_strerror(res));
		} else {
			std::string response(s.ptr);
		    free(s.ptr);
		    Json::Reader r = Json::Reader();
			r.parse(response.c_str(), val);
		}
	} else {
		val["status"] = 500;
		val["message"] = "Internal Error";
	}
	return val;
}