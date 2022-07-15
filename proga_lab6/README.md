# proga-6lab
**Лабораторная работа 6. Архиватор файлов.**

Целью лабораторной работы является разработка программы по архивированию
и распаковке нескольких файлов в один архив. Архиватор должен:
1. Уметь архивировать несколько (один и более) указанных файлов в архив с
расширением *.arc
2. Уметь распаковывать файловых архив, извлекая изначально запаковонные
файлы
3. Предоставлять список файлов упакованных в архиве

Архиватор должен быть выполнен в виде консольного приложения,
принимающего в качестве аргументов следующий параметры:

**--file FILE**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Имя файлового архива с которым будет работать архиватор

**--create**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Команда для создания файлового архива

**--extract**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Команда для извлечения из файлового архива файлов

**--list**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Команда для предоставления списка файлов, хранящихся в архиве

**FILE1 FILE2 .... FILEN**&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Свободные аргументы для передачи списка файлов для запаковки

**Примеры использования:**

arc --file data.arc --create a.txt b.bin c.bmp

arc --file data.arc --extract

arc --file data.arc --list
