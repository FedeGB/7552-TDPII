Documentación técnica
*********************

.. image:: diagramas/EventHandler.png
	:scale: 50 %

*Diagrama de clases del manejo de eventos de request que llegan a la API del server.*  

Implementados hay varios más de los mostrados en el diagrama. Cada request de la API tiene su propia clase que hereda de EventHandler y maneja el evento según corresponda. Entre el manejo tenemos la validación de la entrada del request. Esto incluye validar que los requisitos de la llamada se cumplan (el tipo de llamada sea el correcto, todos los parámetros obligatorios estén, validar header, etc). Luego también tiene un manejo sobre qué hacer en su caso. Para ello, a este se le provee de parte del server el Manager y el SharedManager siendo el primero la clase que tiene acceso a la clase de la Database y el segundo la clase que sirve como cliente para realizar llamadas al Shared Server.  

.. image:: diagramas/EventFlow.png
	:scale: 50 %

*Diagrama de flujo al llegar un request al Server*  





