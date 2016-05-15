#ifndef SHAREDMANAGER_H_
#define SHAREDMANAGER_H_

#include "CurlManager.h"
#include "../User.h"

class SharedManager {
public:
	SharedManager();
	virtual ~SharedManager();

	// Obtiene el listado de los usuarios del Shared Server
	// Devuelve un Json Array con cada usuario
	Json::Value getUsers();

	// Obtiene un usuario del Shared Server particular segun el id pasado por parametro
	// Devuelve un Json con la informacion del usuario
	Json::Value getUser(std::string);

	// Da de alta un usuario en el Shared Server
	// Pre: User con datos del usuario (valido) para enviar al Shared Server
	// Requiere: name, alias, email, sex, photoProfile, interests, location
	// Devuelve el id en el Shared Server en caso satisfactorio
	// Si hubo algun error el numero de id devuelto es 0
	long postUser(Json::Value);

	// Ejecuta un request de delete hacia el Shared Server del id de usuario pasado
	// Devuelve true en caso satisfactorio o flase en caso contrario
	bool deleteUser(int);

	int putUser(Json::Value);
};

#endif /*SHAREDMANAGER_H_*/