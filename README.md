# Prueba para postulación de trabajo en arandasoft
Repositorio para desarrollar la prueba de C++

# Pre-requisitos

## Instalar cmake y librerías de compilación

### Windows
* Se recomienda instalar Visual Studio agregando los componentes de c++. Así como también cmake

### Linux
* Instalar cmake gcc de acuerdo a la distribución


### MacOS
* Instalar cmake descargando el archivo con formato .dmg desde la página oficial de cmake. Dar doble click una vez de haya descargado. Arrastrar el logo de cmake a Applications. Seguir instrucciones de esta [página](https::/tudat.tudelft.nl/installation/setupDevMacOs.html)
* Para tener acceso a cmake en la terminal ejecutar el siguiente comando:

```
sudo mkdir -p /usr/local/bin
sudo /Applications/Cmake.app/Contents/bin/cmake-gui --install=/usr/local/bin
```

* Instalar HomeBrew en MacOS por medio del siguiente comando:

```
/bin/bash -c "$(curl -fsSL https://githubusercontent.com/Homebrew/install/master/install.sh)"
```

* Confirmar se tenga clang instalado con clang --version. En caso contrario instalar gcc con brew install gcc
* Confirmar se tenga git instalado git --version. En caso contrario instalar git con brew install git


## Tener instalado sqlite3 de acuerdo al sistema operativo:


### MacOS
* Confirmar seencuentre pre instalado por medio del comando:

```
sqlite3 --version

```
En la mayoría de los casos MacOS viene con sqlite3 instalado.


### Windows:

* Descargar los archivos de la página oficial [Sqlite](https://www.sqlite.org/download.html) de la sección **Precompiled Binaries for Windows** los dll de x64. Estos archivos van en una carpeta lib
* Descargar el código fuente. Estos archivos van en una carpeta include.
* Instalar en c:/Program Files/Sqlite3/[version]/ o en algún directorio que sigan el [patrón de búsqueda de SOCI](https://github.com/SOCI/soci/blob/master/cmake/modules/FindSQLite3.cmake)

### Linux y MacOS
* Descargar el código fuente de la página oficial [Sqlite](https://www.sqlite.org/download.html). El archivo autoconf
* Descomprimir: 

```
tar xvfz sqlite-autoconf-xxx.tar.gz
```

* Ir al directorio creado

```
cd sqlite-autoconf-xxx
```

* Configurar la construcción. El prefijo se puede cambiar, pero se debe tener en cuenta [patrón de búsqueda de SOCI](https://github.com/SOCI/soci/blob/master/cmake/modules/FindSQLite3.cmake)

```
./configure --prefix=/usr/local
```

* Instalar. Ejecutar con permisos de super usuario.

```
make
make install
```

## Instalar GIT

Se require instalar git. En distribuciones linux y en MacOS es sencillo. En windows se recomienda agregar la variable de entorno.


# Clonar proyecto

Debido a que el proyecto hace referencia a otros repositorios como submódulos, se debe:

* Clonar, ya sea con git clone o descargando el zip

```
git clone https://github.com/JoseManuelVargas/cpp-prueba-arandasoft
```

* Descargar los submódulos.

```
git submodule init
git submodule update
```

* Opcionalmente se puede clonar y actualizar en un solo comando

```
git clone --recurse-submodules https://github.com/JoseManuelVargas/cpp-prueba-arandasoft.git
```


# Estructura del proyecto.

## Módulos

El proyecto cuenta con diferentes submódulos, ya sea tomados de otros repositorios o creados. Cada módulo tiene su propio archivo cmake, facilitando la construcción y permitiendo compilación multiplataforma. Cada módulo tiene una carpeta de test que se ejecuta una vez se compila.

* appdb: Este módulo gestiona la escritura y lectura de clases del proyecto a base de datos. Se define la clase task para permitir almacenarla en base de datos.
* cpuinfo: Se encarga de leer la información del computador para los diferentes sistemas operativos. Define las clases para empaquetar la misma.
* fileinfo: Lee la información de archivos en cada sistema operativo, igualmente define las clases para empaquetar la información.
* googletest: Para poder hacer test. Se toma del [repositorio](https://github.com/google/googletest)
* json: Para manejar los json, necesarios para recibir las tareas. Tomado del [repositorio](https://github.com/nlohmann/json)
* scheduler: Maneja la agenda para las tareas. Se toma del [repositorio](https://github.com/Bosma/Scheduler) Haciendo cambios en el archivo cmake para convertirlo en una librería. Se usa el [archivo](https://github.com/vit-vit/CTPL/blob/master/ctpl_stl.h)
* soci: ORM para la base de datos. En este caso se usa SQLite3. Se toma del [repositorio](https://github.com/SOCI/soci)
* socket: Módulo que crea un servidor socket para recibir las solicitudes de las tareas. **Por desarrollar**.
* taskmanager: Módulo que une todos los anteriores para crear la aplicación en conjunto.


# Compilación

* Se recomienda crear una carpeta build y ejecutar desde allí

* Se recomienda usar el siguiente comando, ya que sólo se usará sqlite3

```
cmake -DWITH_BOOST=OFF -DWITH_ORACLE=OFF -DWITH_POSTGRESQL=OFF -DSOCI_TESTS=OFF -DWITH_DB2=OFF -DWITH_FIREBIRD=OFF -DWITH_MYSQL=OFF -DWITH_ODBC=OFF ..
```

* Ejecutar el siguiente comando

```
cmake --build .
```

* En adelante, una vez creado el archivo CMakeCache.txt en la carpeta build, solo hace falta correr

```
 cmake .. 
```

en caso que se haga algún cambio en las configuraciones cmake seguido de 

```
cmake --build .
```



# Inconvenientes

* En windows no consigue ubicar el archivo soci/soci-config.h: Esto se solucionó agregando el directorio de include de soci con la siguiente línea:

```
include_directories(${CMAKE_CURRENT_BINARY_DIR}/soci/include)
```

* En windows no ejecuta el código aún después de haber compilado correctamente.



