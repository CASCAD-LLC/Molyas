# Molyas
Molyas - установщик *.deb пакетов на Debian-подобных системах. Идеален для новичков в Linux. в частности Debian. Не требует знаний терминала.

# Использование
Сначала подготовим среду, нам понадобятся: clang, Qt6 также рекомендуем Qt Creator. Установим Clang:

```bash
   sudo apt install clang
```
Далее установим библиотеки Qt6 и Qt Creator (по желанию):

```bash
   sudo apt install qt6-base-dev # библиотеки Qt6
   sudo apt install qtcreator # рекомендуется, но можете запустить проект другим способом
```
После подготовки среды, клонируем репозиторий:
```bash
   git clone https://github.com/CASCAD-LLC/Molyas.git
```
Открываем CMakeLists.txt в Qt Creator и нажимаем на кнопку запуска. Перед нами будет такое окно:
