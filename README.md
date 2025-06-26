# Molyas 2.0
Molyas - установщик пакетов на Linux системах. Идеален для новичков в Linux. Не требует знаний терминала.

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
![image](https://github.com/user-attachments/assets/3e9246d5-da71-4328-943a-e4279b2cf6ac)

Нажимаем на эту кнопку (в зависимости от вашего графического окружения, иконка может поменяться): 

![image](https://github.com/user-attachments/assets/9578bbc9-cf18-4f99-bd53-8c265ded3665)

Перед вами будет файловый диалог, выберите нужный *.deb файл и дождитесь окончания установки, прогресс установки будет виден на шкале прогресса.
Видео пример использования:
![aaa (1)](https://github.com/user-attachments/assets/d80833cc-a1d9-4f6b-8129-65f66c76dc12)

# Поддерживаемые системы
Molyas 2.0 поддерживает только Debian, Fedora и Arch-подобные системы.
