# Лабораторная работа 4. Редактор метаинформации mp-3 файла

**Задача**

Реализовать редактор текстовой метаинформации mp3 файла. В качестве стандарта метаинформации используется ID3v2.

Редактор представляет из себя консольную программу, принимающую в качестве аргументов имя файла через параметр **--filepath**, а также одну из выбранных команд:

1.	--show - отображение всей метаинформации в виде таблицы

2.	--set=prop_name --value=prop_value - выставляет значение определенного поля метаинформации с именем prop_name в значение prop_value

3.	--get=prop_name - вывести определенное поле метаинформации с именем prop_name

**Например:**

app.exe --filepath=Song.mp3 --show

app.exe --filepath=Song.mp3 --get=TIT2

app.exe --filepath=Song.mp3 --set=COMM --value=Test



<img src=https://github.com/Escaper2/ITMO-Algorithms-Labs/blob/master/itmolog.png>

