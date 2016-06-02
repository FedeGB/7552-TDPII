API Documentation
*****************
En esta sección estará documentada la REST API del App Server

Users
=====
**URI del recurso** /users

GET ALL
-------
Obtener información sobre todos los usuarios.


Parámetros
++++++++++
No toma parametros

Respuesta
+++++++++

- errorNum: código de error (0 indica success)
- message: mensaje asociado al código de error
- metadata: Información de metadata sobre la respuesta  
1. size: Cantidad de elementos devueltos en el payload

- payload: Elementos pertinentes a devolver (si no necesita devolver nada éste esta vacio)
1. id  
2. name  
3. alias  
4. email  
5. photo_profile
6. interests  
7. location

Ejemplo de la respuesta:
++++++++++++++++++++++++
.. code-block:: json

	{
	  "errorNum": 0,
	  "message": "",
	  "metadata": {
	    "size": 1
	  },
	  "payload": {
	    "Users": [
	      {
	        "latitude": 0,
	        "longitude": 0,
	        "matches": [],
	        "name": "juan",
	        "password": "hola",
	        "perfilImage": "",
	        "token": "juanmahola",
	        "username": "juanma"
	      }
	    ]
	  }
	}

POST
----
Dar de alta a un usuario nuevo 

Parámetros
++++++++++
**username**, **name**, **password**

*Ejemplo:*
.. code-block:: json

	{"username":"juanma", "name": "juan", "password":"hola", "sex":"M"}

Sex puede ser "M" o "W"

Respuesta
+++++++++
- errorNum: código de error (0 indica success)
- message: mensaje asociado al código de error
- metadata: Información de metadata sobre la respuesta  
1. size: Cantidad de elementos devueltos en el payload

- payload: Elementos pertinentes a devolver (si no necesita devolver nada éste esta vacio)  
1. id  
2. name  
3. alias  
4. email  
5. photo_profile
6. interests  
7. location

Ejemplo de la respuesta:
++++++++++++++++++++++++
.. code-block:: json

	{
	  "errorNum": 0,
	  "message": "Registered",
	  "metadata": {
	    "size": 0
	  },
	  "payload": 0
	}

GET SPECIFIC
------------

Obtener usuario especifico por su username

Parámetros
++++++++++
**username**: ID del usuario (mail del usuario)

Respuesta
+++++++++
- errorNum código de error (0 indica success)
- message mensaje asociado al código de error
metadata: Información de metadata sobre la respuesta  
1. size: Cantidad de elementos devueltos en el payload

- payload: Elementos pertinentes a devolver (si no necesita devolver nada éste esta vacio)  
1. id  
2. name  
3. alias  
4. email  
5. photo_profile
6. interests  
7. location

*Ejemplo de payload!*

.. code-block:: json

	{ 
	   "id": 1,
	   "name": "usuario",
	   "alias": "not a user",
	   "email": "usuario@usuario.com",
	   "photo_profile": "< base64 >",
	   "sex" : "male",
	   "interests": [
	      {"category": "music/band", "value": "michael jackson"},
	      {"category": "music/band", "value": "pearl jam"},
	      {"category": "outdoors", "value": "running"}
	   ],
	   "location": {"latitude": -121.45356, "longitude": 46.51119}
	}


PUT
---

Editar usuario especifico /users/username

Parámetros
++++++++++

**username**: ID del usuario (mail del usuario) Requierido

Respuesta
+++++++++

- errorNum: código de error (0 indica success)
- message: mensaje asociado al código de error
- metadata: Información de metadata sobre la respuesta  
1. size: Cantidad de elementos devueltos en el payload

- payload: Elementos pertinentes a devolver (si no necesita devolver nada éste esta vacio)  
1. id  
2. name  
3. alias  
4. email  
5. photo_profile
6. interests  
7. location

*Ejemplo de PUT parametros de body de PUT request:*

.. code-block:: json

	{
	"username": "username",
	"name": "usuario",
	"alias": "not a user",
	"email": "usuario@usuario.com",
	"sex": "M",
	"age": 30,
	"photo_profile": "< base64 >",
	"interests": [{
		"category": "music / band",
		"value": "radiohead"
		}, {
		"category": "music / band",
		"value": "pearl jam"
		}, {
		"category": "outdoors",
		"value": "running"
		}],
	"location": { 
	        "latitude": -121.45356,
	        "longitude": 46.51119
	        }
	}

DELETE
------

Eliminar usuario especifico por username

Parámetros
++++++++++
**username**: ID del usuario (mail del usuario)

Respuesta
+++++++++

- errorNum: código de error (0 indica success)
- message: mensaje asociado al código de error
- metadata: Información de metadata sobre la respuesta  
1. size: Cantidad de elementos devueltos en el payload  
- payload: Elementos pertinentes a devolver (si no necesita devolver nada éste esta vacio)  
1. id  
2. name  
3. alias  
4. email  
5. photo_profile
6. interests  
7. location  

*Ejemplo de body de Delete request*

.. code-block:: json

	{
	    "username":"ff5"
	}