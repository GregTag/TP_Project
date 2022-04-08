# TCP chat project

Проект реализует клиент-серверное приложение чата по протоколу `tcp` с использованием библиотеки `boost::asio` и минимум сторонних библиотек.

## Contents

* [Changelog](CHANGELOG.md)
* [Description](DESCRIPTION.md)
* [UML Class diagram](ClassDiagram.svg)

## How to build
Сборка осуществляется средставми `cmake`. Требуется поддержка компилятором `C++17`.
Для сборки достаточно запустить
```bash
$ ./build.sh
```
В системе должна быть установлена библиотека `boost` минимальной версии `1.78`.
