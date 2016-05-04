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
	// Devuelve true en caso satisfactorio
	// false en caso de algun error
	bool postUser(User*);
};

#endif /*SHAREDMANAGER_H_*/