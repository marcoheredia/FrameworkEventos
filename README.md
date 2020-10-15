# Framework Orientado a Eventos #

El repositorio contiene el código de mi proyecto integrador titulado: "Framework orientado a Eventos para desarrollo de Firmware de aplicaciones IoT sobre Sistemas Embebidos"

### Organización de los directorios

El presente repositorio esta dividido en 2: por un lado se tiene el código del proyecto el cual esta contenido en la carpeta API y por otro lado se tiene la carpeta SDK, la cual incluye a la API junto con una serie de archivos necesarios para el desarrollo de un proyecto utilizando el framework.

La carpeta API, contiene subcarpetas para los archivos fuente, headers y para los tests unitarios.

Mientras que la carpeta SDK está estructurada de la siguiente forma:

```
/proyecto --> Directorio principal para el desarrollo de un proyecto. Adentro de esta carpeta ese encuentra:
	/proyecto/main --> Carpeta en la cual contendrá el archivo principal del programa y sobre el cual se creará el archivo binario.
	/proyecto/components --> Carpeta que contiene la API del framework y en la cual el usuario podrá crear nuevos módulos.
	Además cuenta con archivos de makefile, un script para generar automaticamente el archivo main a partir de los módulos y un script para pasar a C un archivo de configuración escrito en JSON.
/components --> Directorio necesario para poder realizar los test unitarios.
/templates --> Directorio que contiene archivos de ejemplo para el desarrollo.
/tools --> Directorio que contiene scripts utilizados en el desarrollo.
```

### Requisitos para el correcto funcionamiento del framework

Es necesario tener instalado previamente

- SDK-IDF v3.2 junto a todas sus dependencias.


### Como crear nuevos modulos del framework

Para crear nuevos modulos que luego serán integrados en el programa principal de la aplicación se recomienda seguir los siguientes pasos:

1- Crear en el directorio ../proyecto/components/ una nueva carpeta con el nombre del módulo (Ejemplo ../proyecto/components/nuevomodulo) y copiar en la misma el archivo component.mk que se encuentra en el directorio ../proyecto/components. Este archivo contiene la estructura de los directorios que esta definida de la siguinete forma:  
```
/src --> Para los archivos .c
/include --> Para los archivos .h
```

En caso de querer continuar con esta estructura se debe crear las carpetas ..proyecto/components/src y ..proyecto/components/include

NOTA: Esta estructura puede ser modificada editando el archivo component.mk

3- Una vez escrito el código del modulo, para que este incluido en la aplicación principal es necesario que exista el archivo fuente y header con el nombre del módulo creado (nuevomodulo.c y nuevomodulo.h) en su correspondiente directorio y dentro de los mismos debe existir una función definida de la siguiente forma

```
void nuevomodulo_init()
```
Esta función es la que se cargará en la aplicación, por lo cual en la misma debe estar inicializadas las funciones del módulo y registrar los eventos y handlers que se quieran. 

NOTA: Tener en cuenta que tanto el nombre de la carpeta que contiene al modulo, el archivo principal del modulo .c y .h y la función \_init() deben tener el mismo nombre.

4- Por último correr el script de python /proyecto/main_creator.py el cual creará un main conteniendo todos las funciones \_init de los módulos que se encuentran en la carpeta /proyecto/components


### Herramientas para el desarrollo de modulos del framework

El script de python /tools/json_to_c.py crea estructuras de configuración en C luego de parsear un archivo en formato .json
Para utilizar el script es necesario utilizarlo de la siguiente manera:

```
python json_to_c.py nombre_del_archivo_de_configuracion.json --c_name nombre_del_archivo_c_a_crear
```
También se puede utilizar el script config_json_to_c.sh que realiza la misma acción a partir de un archivo que se debe llamar config.json y debe estar en la misma carpeta que el script.

### Makefile

El archivo makefile contiene directrices para las siguientes funciones:

Configurar el proyecto:
```
make menuconfig
```

Compilar el proyecto:
```
make build
```

Cargar el binario del proyecto al microcontrolador:
```
make flash
```

Ver en la consola el log de la ejecución del proyecto en el microcontrolador:
```
make monitor
```

También es posible compilar, cargar en la placa y ver la ejecución del mismo con un único comando:
```
make flash monitor
```

### Testing del código

Para crear test unitarios se recomienda hacer lo siguiente:

1- Crear una carpeta que se llame /components/ para contener los test unitarios de los distintos módulos que se deseen testear. En este repositorio esta carpeta ya se encuentra creada en /SDK/components.

2- Crear una carpeta con el nombre del módulo en la carpeta /components creada en el paso 1 (./components/nuevomodulo/) y copiar en la misma las carpetas /src y /include que contengan los archivos implicados en el test a realizar.  

3- Crear en la carpeta del nuevo módulo una nueva carpeta llamada /test (./components/nuevomodulo/test) y crear en la misma los archivos de test con la libreria unity.h

4- Correr el script **testear.sh** y seguir los pasos que indica el script para utilizar la herramienta de testing de ESP-SDK.