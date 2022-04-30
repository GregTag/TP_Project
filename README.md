# TCP chat project

Проект реализует клиент-серверное приложение чата по протоколу `tcp` с использованием библиотеки `boost::asio` и минимум сторонних библиотек.

## Contents

* [Changelog](CHANGELOG.md)
* [Description](DESCRIPTION.md)
* [UML Class diagram](ClassDiagram.svg)

## How to build
### Linux
Сборка осуществляется средставми `cmake`. Требуется поддержка компилятором `C++17`.
Для сборки достаточно запустить
```bash
$ ./build.sh
```
В системе должна быть установлена библиотека `boost` минимальной версии `1.78`.
### Windows
Сборка осуществляется с помощью тулчейна [msys2](https://www.msys2.org/). В msys необходимо установить `g++`, `make` и `cmake`. Также необходимо дополнительно скачать [boost](https://www.boost.org/users/download/). После этого можно начинать сборку:
```cmd
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/mingw/g++.exe -DCMAKE_C_COMPILER=/mingw64/gcc.exe -DBOOST_ROOT=/path/to/boost
make -j
```

## How to launch

### Запуск сервера
```bash
$ ./build/bin/Server <port> <path/to/room_storage>
```
где `<port>` это порт, который прослушивает сервер, `<path/to/room_storage>` это путь до папки, куда будет сохраняться и откуда будет читаться история сообщений в комнатах.


### Запуск клиента
```bash
$ ./build/bin/Client <host> <port>
```
где `<host>` это ip к которому будет подключаться клиент в формате четырёх десятичных чисел от 0 до 255, разделённых точкой, например `127.0.0.1`, `<port>` это порт на сервере, к котрому подключаться. 
