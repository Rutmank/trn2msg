Svarīgi!

1. Lai programma darbotos, nepieciešams sagatavots Transaction.txt fails.
   Šis fails jau atrodas repozitorijā, tomēr, ja jūs to noņemsit no repozitorija, programma nedarbosies.
2. Arī, lai pareizi darbotos, jāievada tikai pa vienai datu rindai (šīs problēmas cēloņi tiks rakstīti vēlāk), piemēram:
   00966796969690609300000000459920181111143445840 
   vai
   01823725897110587900000000150020171112095612643

Paskaidrojumi par koda darbību:

1. Lietotājs var ievadīt tikai 47 ciparus, kuros jābūt pareizai informācijai par bankas pārskaitījumu, kā norādīts uzdevumā.
Ir ieviestas pārbaudes, ja lietotājs ciparu vietā ievada nepareizu informāciju vai ievada kādas rakstzīmes, tad viņam tiks parādīta kļūda.
Turpmākam darbam ar ievadīto informāciju, tā tiek ierakstīta Char masīvā; 

2. Pēc tam tiek atvērts jau sagatavotais fails Transaction.txt, no kura notiek secīga rindu nolasīšana.
Tiek pārbaudīta lietotāja ievadītā informācija, pēc kuras tiek noteikts valūtas tips, kā arī transakcijas tips.

3. Tālāk tiek noteikta lietotāja ievadītā informācija par bankas kartes numuru.
Tiek šifrēts viss kartes numurs, izņemot pēdējos četrus ciparus.
Karte tiek ierakstīta logos arī šifrētā veidā.

4. Tad tiek noteikta ievadītā transakcijas summa. 
Tas arī īsteno visu nulļu noņemšanu summas priekšā, tāpēc tas var būt līdz 9,99 miljardiem.

5. Tiek noteikts transakcijas datums un laiks.

6. Pēc tam, pamatojoties uz saņemto informāciju, tiek izveidots messageFile.xml.
Šis fails tiek aizpildīts rindā pa rindai atbilstoši uzdevumam.
Tomēr šeit ir viena neīstenota funkcija, kas tika pieminēta iepriekš (šīs problēmas cēloņi tiks rakstīti vēlāk).
Tā kā lietotājs vienlaikus var ievadīt tikai vienu rindu ar informāciju par transakciju, failā ir informācija tikai par vienu pieprasījumu.
Arī šī informācija par darījumu pēc programmas kompilacijas tiek dublēta tulkā.

7. Pēc visu darbību pabeigšanas tiek izveidots trn2msg.log, kurā tiek ierakstīta informācija par visām darbībām programmā.
Faila nosaukums atbalsta šo formātu: <program_name>_YYMMDD.log.
Diemžēl katram atkārtojumam nebija iespējams pievienot laiku, izņemot faila izveidošanas laiku (šīs problēmas cēloņi tiks rakstīti vēlāk).
