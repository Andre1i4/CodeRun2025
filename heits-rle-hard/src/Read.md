# 4.bin - Utilitar de Compresie RLE

Acesta este proiectul echipei *4.bin* pentru proba tehnică Heits. Aplicația este un utilitar web scris în *ReactJS* care comprimă și decomprimă text eficient, respectând toate restricțiile (fără librării externe pentru logică).

## 👨‍💻 Echipa
* *4.bin*

## ⚙ Soluția Tehnică

Am implementat un algoritm RLE modificat pentru a obține performanță maximă:

1. *RLE Adaptiv (Smart Compression)*
   Algoritmul decide dinamic când să comprime. Dacă o secvență este scurtă (ex: aa), o lasă intactă pentru a nu mări dimensiunea fișierului inutil. Comprimăm doar când câștigăm spațiu real.

2. *Optimizare Base36*
   Pentru a reduce rata de compresie sub 0.5, convertim numărul de repetiții din baza 10 în *baza 36* (0-9, a-z).
   * Exemplu: O repetiție de 15 caractere devine f (un singur caracter) în loc de 15.
   * Asta ne ajută să scurtăm semnificativ output-ul final.

3. *Manipulare Date*
   * *File Upload:* Folosim API-ul nativ FileReader pentru citirea fișierelor .txt prin Drag & Drop.
   * *Unicode:* Folosim Array.from() pentru a procesa corect caracterele speciale și Emoji (🚀), evitând erorile clasice de string parsing din JavaScript.

## 🚀 Rulare Proiect

1. npm install (instalare pachete)
2. npm start (pornire server pe localhost:3000)

## 📊 Validare Bonus (Rata < 0.5)

Pentru a demonstra eficiența algoritmului pe texte complexe (cu cifre și simboluri), am folosit următorul input de test:

aaaaaaabbbbbbbbbbbbbbbv3333zzffffffffaaaaaaaaaagFFF222244444444fg44444444444422hhhhhhhhaBc1aaa3bbbffffffffffffff

*Rezultate:*
* Datorită optimizării Base36 și a logicii adaptive, obținem o rată de compresie de *~0.47* (Sub pragul de 0.5).
* Decompresia funcționează corect, reconstruind textul original bit cu bit.