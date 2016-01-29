# README #



## Uzupełnij program shell z o „ręczną” obsługę potoków.

Napisz program, który zbiera komunikaty od wielu programów i wyświetla je na ekranie. Do komunikacji użyj potoku nazwanego. Wskazówka: Utwórz program rdfifo, którego zadaniem jest utworzenie kolejki FIFO i czytanie z niej danych.

* Q: W jaki sposób przekażesz wspólną nazwę kolejki FIFO do tych programów?
* A: przez zmienną statyczą
* Q: W jaki sposób zapewnić działanie programu zbierającego komunikaty również wtedy, kiedy nie ma programu piszącego do łącza?
* A: przez proces pętli nieskończonej ze sleep
* Q: Jak zapewnić to, że komunikaty pochodzące od różnych programów wyświetlane są w całości, tzn. nie są rozdzielane  komunikatami od innych programów?
* A: flush? (do sprawdzenia).


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