# TCP chat project

Проект реализует клиент-серверное приложение чата по протоколов `TCP` для коммуникации и `SSL/TLS` для шифрования с использованием библиотеки `boost::asio` и `OpenSSL`.

## Contents

* [Changelog](CHANGELOG.md)
* [Description](DESCRIPTION.md)
* [UML Class diagram](ClassDiagram.svg)
* [Doxygen interactive UML](doxygen/index.html)
* [How feature was added](feature.md)

## How to build
### Linux
Сборка осуществляется средставми `cmake`. Требуется поддержка компилятором `C++17`.
Для сборки достаточно запустить
```bash
$ ./build.sh
```
В системе должна быть установлена библиотека `boost` минимальной версии `1.78`, а также OpenSSL.
### Windows
Сборка осуществляется с помощью тулчейна [msys2](https://www.msys2.org/). В msys необходимо установить `g++`, `make` и `cmake`. Также необходимо дополнительно скачать [boost](https://www.boost.org/users/download/) и OpenSSL. После этого можно начинать сборку:
```cmd
mkdir build
cd build
cmake .. -DCMAKE_CXX_COMPILER=/mingw64/g++.exe -DCMAKE_C_COMPILER=/mingw64/gcc.exe -DBOOST_ROOT=/path/to/boost
make -j
```

## Server

### How to launch
```bash
$ ./build/bin/Server <port> <path/to/room_storage> <certificate.csr> <private.key> <dhparam.pem>
```
* `<port>` это порт, который прослушивает сервер, 
* `<path/to/room_storage>` это путь до папки, куда будет сохраняться и откуда будет читаться история сообщений в комнатах, 
* `<certificate.csr>` это сертификат, 
* `<private.key>` это приватный ключ, подписанный сертификатом, 
* `<dhparam.pem>` это файл с параметрами для протокола Диффи-Хеллмана. 
Чтобы сгенерировать сертификат, приватный ключ и файл параметров, достаточно запустить
```bash
$ ./keygen.sh
```

### How to use commands
```
- help                              Print this.
- broadcast/say <some text>         Send everyone info message with <some text>.
- account/database/db <subcommand>  Manage user's available rooms:
    - get <name>                        get all avaialable rooms for user <name>,
    - add <name> <room>                 add <room> to user <name> to available rooms,
    - remove <name> <room>              remove <room> to user <name> to available rooms.
- permissions/perm <subcommand>     Manage user's permissions:
    - get <room> <name>                 get permissions user <name> in <room>,
    - set <room> <name> <permission>    set permissions user <name> in <room>,
    - setdefault <room> <permission>    set <permission> as default for <room>.
- stop/Ctrl+D                       Save all data and safely stop the server.
```

## Client

### How to launch
```bash
$ ./build/bin/Client <host> <port> <certificate.csr>
```
* `<host>` это ip к которому будет подключаться клиент в формате четырёх десятичных чисел от 0 до 255, разделённых точкой, например `127.0.0.1`, 
* `<port>` это порт на сервере, к котрому подключаться,
* `<certificate.csr>` это сертификат.

### How to use commands
```
- help                                      Print this.
- register/signup <name> <password>         Register account with <name> and <password>.
- login/signin  <name> <password>           Authorizate with account with <name> and <password>.
- rooms                                     Print available rooms for you
- join <room>                               Join to <room>.
- leave <room>                              Leave <room>.
- users <room>                              Get all users, who are currently online in <room>.
- history <room>                            Get all messages in <room>.
- send/s <room> <some text>                 Send message with <some text> to <room>.
- whisper/tell/w <room> <name> <some text>  Send private message with <some text> to user <name> in <room>.
- manage <subcommand>                       Manage user's permissions:
    - get <room> <name>                         get permissions user <name> in <room>,
    - set <room> <name> <permission>            set permissions user <name> in <room>,
    - setdefault <room> <permission>            set <permission> as default for <room>.
- exit/quit/Ctrl+D                          Close connection and exit from app.
```
