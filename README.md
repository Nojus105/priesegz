Pasikartojančių Žodžių ir URL Nuskaitymo Programa
=================================================

Ši programa skirta nuskaityti tekstinį failą, išrinkti pasikartojančius žodžius bei visus URL adresus. Rezultatai saugomi atskiruose failuose "bin" direktorijoje.

Naudojimas
==========

Komandos terminale:

  make all      - Sukuria .exe vykdomąjį failą
  cd bin        - Įeiti į direktoriją, kur yra sukurtas .exe failas
  cd ..         - Grįžti į aukštesnį katalogą
  make clean    - Pašalina sukurtus failus (išvalymas)

Paleidimas
==========

1. Paleiskite programą per terminalą.
2. Įveskite failo pavadinimą su extension pavadinimu, pvz.:
   sample.txt

Rezultatai
==========

- Pasikartojantys žodžiai ir URL adresai bus išsaugoti atskiruose failuose "bin" kataloge.

Reikalavimai
============

- make įrankis
- C++ kompiliatorius (pvz. gcc)
