Замечания по первой попытке:
1) надо декомпозировать декларацию класса и его методов, от их реализации. Декларация в хедере, имплементация в *cpp
2) помечать константными методы не меняющие состояние - например вывод на экран
3) использовать константные ссылки
4) в rff можно подавать строчку по ссылке - это вообще говоря хорошая практика, передавать complicated объекты не через
копирование побитовое, а по ссылке

5) рекомендовали придерживаться google-code-style https://google.github.io/styleguide/cppguide.html
6) использовать assert() для проверки корректности вводимых значений - очень важно для будущих больших проектов.
7) избегать не используемых заголовочных файлов и include - избегать дублирования последних
8)


Примечание ко второй попытке:
Все имплементированно по новой, на вторую попытку хочу ввести подкласс строк - для нормального доступа к элементам, по
индексу - как в математической нотации.


