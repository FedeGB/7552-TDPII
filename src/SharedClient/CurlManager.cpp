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


void CurlManager::init_string(struct string *s) {
  s->len = 0;
  s->ptr = (char*)malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = (char*)realloc(s->ptr, new_len+1);
	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
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

Json::Value CurlManager::execute() {
	if(this->headers) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, this->headers);
	}
	std::string URL = this->url + "/" + this->uri;
	if(params.size()) {
		// TODO: Añadir parametros	
	}
	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
	struct string s;
    this->init_string(&s);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	CURLcode res;
	res = curl_easy_perform(curl);
	Json::Value val = Json::Value();
	if(res != CURLE_OK) { 
		val["errorNum"] = (int)res;
		val["message"] = std::string(curl_easy_strerror(res));
	} else {
		std::string response(s.ptr);
	    free(s.ptr);
	    Json::Reader r = Json::Reader();
		r.parse(response.c_str(), val);
	}
	return val;
}