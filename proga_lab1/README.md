# Лабораторная работа 1. Утилита WordCount

**Задача**

Реализовать утилиту WordCount подсчитывающую количество строк, слов и байт для указанного файла и выводить эту информацию в поток вывода.

Программа должна поддерживать следующие опции:

-l, --lines&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; вывод только количества строк

-c, --bytes&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;вывод размера файла в байтах

-w, --words&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;вывод количества слов

Название файла и опции передаются через аргументы командной строки в следующем формате:


&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;**WordCont.exe [OPTION] filename**
