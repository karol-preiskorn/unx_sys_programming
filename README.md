# README #



## Uzupełnij program shell z o „ręczną” obsługę potoków.

Napisz program, który zbiera komunikaty od wielu programów i wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego. Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie kolejki FIFO i czytanie z niej danych.

* Q: W jaki sposób przekażesz wspólną nazwę kolejki FIFO do tych programów?
* A: przez zmienną statyczą
* Q: W jaki sposób zapewnić działanie programu zbierającego komunikaty również wtedy, kiedy nie ma programu piszącego do łącza?
* A: przez proces pętli nieskończonej ze sleep
* Q: Jak zapewnić to, że komunikaty pochodzące od różnych programów wyświetlane są w całości, tzn. nie są rozdzielane  komunikatami od innych programów?
* A: flush? (do sprawdzenia).