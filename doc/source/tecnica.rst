Documentación técnica
*********************

Manejo de llamados a la API
===========================

.. image:: diagramas/EventHandler.png
	:scale: 50 %

*Diagrama de clases del manejo de eventos de request que llegan a la API del server.*  

Implementados hay varios más de los mostrados en el diagrama. Cada request de la API tiene su propia clase que hereda de EventHandler y maneja el evento según corresponda. Entre el manejo tenemos la validación de la entrada del request. Esto incluye validar que los requisitos de la llamada se cumplan (el tipo de llamada sea el correcto, todos los parámetros obligatorios estén, validar header, etc). Luego también tiene un manejo sobre qué hacer en su caso. Para ello, a este se le provee de parte del server el Manager y el SharedManager siendo el primero la clase que tiene acceso a la clase de la Database y el segundo la clase que sirve como cliente para realizar llamadas al Shared Server.  

.. image:: diagramas/EventFlow.png
	:scale: 50 %

*Diagrama de flujo al llegar un request al Server*  


Base de datos
=============

Para la base de datos, al utilizar RocksDB, las tablas son de clave - valor. Por ello estas se dividieron en lo siguiente para este proyecto:

Users
-----
username : Json String

Para los usuarios se decidio manejarlos con un username como clave, que a su vez es el email asociado en el Shared Server. Este es el punto en común inicial entre los dos. El id que provee Shared Server también es único y es en común pero este se genera en el Shared y no en el App Server.
Los valores del usuario se guardan en un Json serializado a String. Esto permite un almacenado directo y un pasaje rapido entre string y Json.
Los usuarios persisten los siguientes atributos:

- id -> valor Int al Json
- username
- name
- email
- password
- location -> valor Json con latitude y longitude dentro
- latitude
- longitude 
- distance
- ageRange -> valor Json con minAge y maxAge dentro
- minAge
- maxAge
- token
- lastTimeConnected
- lastCandiatesRequest
- candidatesSend
- likesReceived
- popularOnePercent
- matches -> Json Array con matches usernames

Likes
-----
<username dador> + <username receptor> : Json String

Para los likes se utilizo como clave <username dador> + <username receptor> y como valor el Json String de los atributos de Like. Se podria haber guardado en un principio unicamente el boolean que indica si se le esta dando like o no like, pero para una transformación de String a Json más directa se terminó guardando el Json completo.
Los likes persisten los siguientes atributos:

- user1 -> username del que da el like/no like
- user2 -> username del que recibe el like/no like
- like -> booleano indicando like/no like

Messages
--------
id + <username sender> + <username receptor> : Json String

Para los mensajes, ademas de los username del emisor y receptor del mensaje se agrego el id del mensaje, relativo al de la conversación que están teniendo ese emisor y receptor en particular. Por lo cual todo id comenzaría de 0 en adelante. Como valor nuevamente se puso el Json String de los atributos del mensaje, que son los siguientes:

- id;
- sender
- receptor
- date -> fecha de envío
- data -> Mensaje enviado en cuestión


Conversations
-------------
<username usuario1> + <username usuario2> : Json String

Las conversaciones entre usuario son únicas, aunque no lo parezca por como se están guardando. La idea es que al enviarse el primer mensaje se genera la conversación con clave usuario1 + usuario2. Después para obtener la conversación si estamos del lado del usuario2, únicamente tenemos que probar ambos sentidos y seguir con esa única conversación.
Las conversaciones guardan el siguiente Json String:

- id
- user1
- user2
- numberMessages -> cantidad de mensajes totales en la conversación
- messagesId -> Json Array con los ids de los mensajes
