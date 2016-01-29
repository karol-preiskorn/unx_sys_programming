# README #



## Uzupełnij program shell z o „ręczną” obsługę potoków.

Napisz program, który zbiera komunikaty od wielu programów i wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego. Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie kolejki FIFO i czytanie z niej danych.

* Q: W jaki sposób przekażesz wspólną nazwę kolejki FIFO do tych programów?
* A: przez zmienną statyczą
* Q: W jaki sposób zapewnić działanie programu zbierającego komunikaty również wtedy, kiedy nie ma programu piszącego do łącza?
* A: przez proces pętli nieskończonej ze sleep
* Q: Jak zapewnić to, że komunikaty pochodzące od różnych programów wyświetlane są w całości, tzn. nie są rozdzielane  komunikatami od innych programów?
* A: flush? (do sprawdzenia).

Zrzut z działania:

[23:30:20](pid 17400) DEBUG: Passed rdfifo 73 - while1

karol@carlo:~/eclipse-workspaces/unx_sys_programming/Debug$ ./unx_sys_programming -w

Input option value=(null) set program to write to FIFO[23:30:20](pid 17411) DEBUG: Passed wrfifo 148 : mkfifo exist: 17
[23:30:20](pid 17411) DEBUG: Passed wrfifo 157 - pipe opened to read-write
[23:30:20](pid 17400) DEBUG: Passed rdfifo 104 - Remove FIFO
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #0 test PID: 17411: text -> Thu Jan 28 23:36:02 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #0 test PID: 17411: text -> Thu Jan 28 23:36:02 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #1 test PID: 17411: text -> Thu Jan 28 23:36:03 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #1 test PID: 17411: text -> Thu Jan 28 23:36:03 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #2 test PID: 17411: text -> Thu Jan 28 23:36:04 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #2 test PID: 17411: text -> Thu Jan 28 23:36:04 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #3 test PID: 17411: text -> Thu Jan 28 23:36:05 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #3 test PID: 17411: text -> Thu Jan 28 23:36:05 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #4 test PID: 17411: text -> Thu Jan 28 23:36:06 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #4 test PID: 17411: text -> Thu Jan 28 23:36:06 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #5 test PID: 17411: text -> Thu Jan 28 23:36:07 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #5 test PID: 17411: text -> Thu Jan 28 23:36:07 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #6 test PID: 17411: text -> Thu Jan 28 23:36:08 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #6 test PID: 17411: text -> Thu Jan 28 23:36:08 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #7 test PID: 17411: text -> Thu Jan 28 23:36:09 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #7 test PID: 17411: text -> Thu Jan 28 23:36:09 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #8 test PID: 17411: text -> Thu Jan 28 23:36:10 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #8 test PID: 17411: text -> Thu Jan 28 23:36:10 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 174 : client succesed write to pipe: #9 test PID: 17411: text -> Thu Jan 28 23:36:11 2016
[23:30:20](pid 17400) DEBUG: Passed rdfifo 107 : reader reads record: #9 test PID: 17411: text -> Thu Jan 28 23:36:11 2016
[23:30:20](pid 17411) DEBUG: Passed wrfifo 180 - close fd
[23:30:20](pid 17400) DEBUG: Passed rdfifo 112 - EOF reader
[10]   Done                    ./unx_sys_programming -r
karol@carlo:~/eclipse-workspaces/unx_sys_programming/Debug$ ./unx_sys_programming -h

## Program FIFO

Program bez argumentów tworzy named pipe a w procesie potomnym zapisuje do niego dane.

Program mozna wywołać z argumentami tak aby działał jako odczyt (r) z pipe lub zapis do pipe (w).

Zapisywane są do pipe couner, PID i curenttime.

Usage: ./unx_sys_programming [-r] [-w]


## Fork/environ Zadania

* z1: Napisz program, który pokazuje, które atrybuty procesu macierzystego są dziedziczone przez proces potomny  uruchomiony za pomocą funkcji fork(), które zaś otrzymują nową wartość.
* z2: Napisz program, który pokazuje, które atrybuty procesu są zachowane przez proces po wykonaniu funkcji exec().
* z3: Napisz program, który wyświetla identyfikator procesu (PID) i nazwę związanego z nim polecenia dla wszystkich procesów uruchomionych przez użytkownika podanego w wierszu wywołania programu. Wskazówka: informacje te można uzyskać przeglądając katalog /proc z plików (interesują nas katalogi, których właścicielem jest dany  użytkownik) i pliki /proc/PID/status
 
Każdy proces charakteryzuje się pewnymi atrybutami. Należą do nich

 * Identyfikator procesu PID
 * Identyfikator procesu macierzystego PPID
 * Rzeczywisty identyfikator właściciela procesu
 * Rzeczywisty identyfikator grupy procesu
 * Efektywny identyfikator właściciela procesu
 * Efektywny identyfikator grupy procesu
 * Katalog bieżący i katalog główny
 * Maska tworzenia pliku
 * Identyfikator sesji
 * Terminal sterujący
 * Deskryptory otwartych plików
 * Ustalenia dotyczące obsługi sygnałów
 * Ustawienia zmiennych środowiskowych
 * Ograniczenia zasobów
 
Potomek dziedziczy z procesu potomnego wiele własności: rzeczywisty identyfikator użytkownika, rzeczywisty identyfikator grupy, obowiązujący identyfikator użytkownika, obowiązujący identyfikator grupy, identyfikatory dodatkowych grup, identyfikator sesji, terminal sterujący, sygnalizator ustanowienia identyfikatora użytkownika oraz sygnalizator ustanowienia identyfikatora grupy, deskryptory otwartych plików (są kopiowane) bieżący katalog roboczy, katalog główny,
 maskę tworzenia plików, maskę sygnałów oraz dyspozycje obsługi sygnałów, sygnalizator zamykania przy wywołaniu funkcji exec (close-on-exec) dla wszystkich otwartych deskryptorów plików, środowisko, przyłączone segmenty pamięci wspólnej,
 ograniczenia zasobów systemowych. Są jednak pewne różnice między procesem macierzystym a potomnym:
 wartość powrotu z funkcji fork, różne identyfikatory procesów, inne identyfikatory procesów macierzystych - w procesie potomnym jest to identyfikator procesu macierzystego; w procesie macierzystym identyfikator procesu macierzystego nie zmienia się, w procesie potomnym wartości tms_utime, tms_cutime i tms_ustime są równe 0,
 potomek nie dziedziczy rygli plików, ustalonych w procesie macierzystym, w procesie potomnym są zerowane wszystkie zaległe alarmy, w procesie potomnym jest zerowany zbiór zaległych sygnałów.