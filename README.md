# TCP chat project

## How to build
Достаточно запустить
```bash
./build.sh
```

## Changelog

### Checkpoint 1

#### Iteration 0
* [Составлены](DESCRIPTION.md) описание, логическая модель и диаграмма классов проекта.
* Реализована логическая модель, представленная на [диаграмме](ClassDiagram.svg). 
* Реализованы методы, не зависящие от конкретных реализаций.
* Написана сборка проекта с помощью cmake.

#### Iteration 1
**[[Файл с архитектурой](ClassDiagram.svg)] | [[Описание проекта](DESCRIPTION.md)]**
* Изменена вся структура файлов, в том числе изменено расширение файлов `.h` на `.hpp`.
* Изменена сборка проекта под структуру файлов.
* `struct Account` заменён на `class Account`.
* Изменена структура каждого класса.
* Убраны не нужные scope'ы в `permissions.cpp`.
* Убрано статическое поле в классе `Account`.
* Добавлен фасад `AccountDatabase` без имплементации. Здесь применён паттерн синглетон.
* Приведена к общему стилю передача объектов в параметрах методов (от константных ссылок к `std::shared_ptr`)
* Переименовано поле `wrapper` в декораторах сообщений.
* `uint32_t` --> `size_t`.
* Создан фасад `MessagesFacade`, чтобы упростить использование декораторов.
* Создан `RequestCreators`, который является обёрткой над `MessageFacade`, для создания наиболее часто используемых сообщений.
* Диаграмма классов соответствует изменениям.
