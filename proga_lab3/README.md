# Лабораторная работа 3. Анализ логов сервера.

**Задача**

Вам предоставлен access.log одного из серверов NASA ([cкачать](https://drive.google.com/file/d/1jjzMocc0Rn9TqkK_51Oo93Fy78KYnm2i/view?usp=sharing))

Это текстовый файл, каждая строка которого имеет следующий формат:

**$remote_addr - - [$local_time] “$request” $status $bytes_send**

$remote_addr - источник запроса

$local_time - время запроса

$request - запрос

$status - статус ответ

$bytes_send - количество переданных в ответе байт

**Например:**

198.112.92.15 - - [03/Jul/1995:10:50:02 -0400] "GET /shuttle/countdown/
HTTP/1.0" 200 3985

**Требуется**
1. Подготовить список запросов, которые закончились 5xx ошибкой, с
количеством неудачных запросов

2. Найти временное окно (длительностью параметризуются), когда
количество запросов на сервер было максимально


<img src=https://github.com/Escaper2/ITMO-Algorithms-Labs/blob/master/itmolog.png>
