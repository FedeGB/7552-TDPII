
Manual para Docker:

1- En el directorio donde se encuentra el dockerfile ejecutar:
      docker build -t juanmahidalgo/match .

2- Para ingresar al bash del contenedor:
      docker run -it --entrypoint /bin/bash juanmahidalgo/match

3- Para correr el contenedor con el entrypoint default
      docker run -it juanmahidalgo/match
