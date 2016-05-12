#ifndef CURLMANAGER_H_
#define CURLMANAGER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <curl/curl.h>
#include "../json/json.h"
#include <vector>
#include "../Resources/Logger.h"

struct cstring {
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

	// Set del método de envio CURL
	// GET es el método por default
	void setMethodType(std::string);

	// Agregar header a la REQUEST
	void addHeader(std::string);

	// Set del Uri para la REQUEST
	void setUri(std::string);

	// Agregar un parametro a la URI
	// Tener en cuenta que si se quiere especificar una key
	// al parametro se tiene que poner todo en el mismo string
	// Por ej: puede ir value sola 10 o key=value id=10
	void addUriParameter(std::string);

	// Agrega un parametro unico al "body" para las REQUEST
	// que usen (vease POST, PUT)
	void addUniqueParameter(std::string, std::string);

	// Agrega un parametro con Json::Value al "body" para las REQUEST
	// que usen (vease POST, PUT)
	void addJsonParameter(std::string, Json::Value);

	// Ejecuta la llamada de curl y devuevel un Json con la respuesta
	// Si el Json contiene el parametro errorNum y message quiere decir
	// que la llamada tuvo algún error.
	Json::Value execute();

private:
	CURL *curl;
	struct curl_slist *headers;
	std::string uri;
	std::vector<std::string> params;
	Json::Value bodyParams;
	std::string url;

	bool init_string(struct cstring *);
};

#endif /*CURLMANAGER_H_*/