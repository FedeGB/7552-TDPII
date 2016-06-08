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
	// Requiere en el Json::Value: name, alias, email, sex, photoProfile, interests, location
	// Devuelve el id en el Shared Server en caso satisfactorio
	// Si hubo algun error el numero de id devuelto es 0
	long postUser(Json::Value);

	// Ejecuta un request de delete hacia el Shared Server del id de usuario pasado
	// Devuelve true en caso satisfactorio o flase en caso contrario
	bool deleteUser(int);

	// Ejecuta un request de put para modificaciones en un usuario.
	// La información que se pasa debe ser completa con diferencias en los cambios que se quiera
	// realizar. 
	// Pre: Recibe un Json::Value con toda la data del usuario. En principio se puede hacer un put
	// de la misma información que ya se tiene del usuario, no se veria ningun cambio reflejado
	// Requiere en el Json::Value: id, name, alias, email, sex, photoProfile, interests, location
	// Post: 1 en caso satisfactorio, 0 en caso erroneo.
	int putUser(Json::Value);

	// Ejecuta request para hacer put modificación de únicamente la imagen del usuario que se pase.
	// Pre: Recibe un Json::Value que debe tener un "id", del usuario a aplicar el put en Shared Server
	// y "photo", que es la foto a subir en base64. 
	int putUserPhoto(Json::Value);

	// Obtiene el listado de los intereses del Shared Server
	// Devuelve un Json Array con cada interes
	Json::Value getInterests();

	// Da de alta un interest en el Shared Server
	// Pre: Interes con "category" y "value"
	// Devuelve true en caso satisfactorio, false en caso contrario
	Json::Value postInterest(Json::Value);
};

#endif /*SHAREDMANAGER_H_*/