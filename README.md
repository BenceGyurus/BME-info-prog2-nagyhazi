# Felhasználói dokumentáció

	Készítette: Gyürüs Bence
# Leírás
A program költségeket tud nyilvántartani. Lehet új költségeket hozzáadni, a meglévőket 
kilistázni, szerkeszteni ls törölni, valamint 2 dátum között összegzi a kiadott pénzt. A költségekhez 4 adatot tárol: egy azonosítót, egy dátumot egy összeget és egy leírást. Az azonosító minden esetben egy nem negatív egész szám, a dátum egy `YYYY-MM-DD` formátumú dátum, az össze egy nem negatív valós szám és a leírás pedig egy nem üres karakterlánc.
# Program használata
A program indításakor beolvassa a fájlból az adatokat, ilyenkor ha a fájl formátuma nem megfelelő, tehát nem a fenti leírásnak megfelelő típusú vagy hiányos vagy rossz sorrendben vannak az adatok, akkor azokat a sorokat megjelöli hibásnak és a beolvasás végén még a menü kihozása előtt megkérdezi a felhasználót, hogy szeretné-e megjavítani a fájl, akkor ha a felhasználó javítást kér akkor a hibás adatok törlődnek az adatbázisból. A javítás kérés előtt kiírja a program, hogy mit tudott beolvasni illetve ha volt akkor milyen hibák voltak, innen tud a felhasználó tájékozódni. Ha ez a fájl (`adatok.cs`) nem található, akkor a program hibát ad és kilép, ennélkül nem tud működni a program. Ha a beolvasás sikeres volt vagy a felhasználó javítást kért, akkor bejön a menü:

```bash
************************************
*         KÖLTSÉG  LISTÁZÓ         *
************************************
* 1. Költség hozzáadása            *
* 2. Költségek listázása           *
* 3. Összegzés                     *
* 4. Szerkesztés                   *
* 5. Törlés                        *
* 6. Kilépés                       *
************************************


Válasszon egy menüpontot (1-6): 
```

A program kéri, hogy válasszunk egy menüpontot, ekkor a fentebb felsorol menük sorszámát kell beírni a kiválasztáshoz, ha ettől eltérőt írunk be akkor a program kiírja, hogy `Kérlek a felsorolt műveletekből válassz` majd ismét a menüt írja ki.

### Hozzáadás
Az első menüpontot választva a költséget tudunk hozzáadni, ekkor a program kéri, hogy írjuk be a hozzáadandó elem dátumát, itt is a fentebb említett `YYYY-MM-DD` formátumban kell megadni, és a dátumnak validnak kell lennie, minden ettől eltérő dátumnál a program hibaüzenetet dob és visszalép a menübe. Ha a dátum helyes volt akkor bekéri az összeget, ekkor a egy valós számot kell megadni és a a program csak számokat és maximum 1db tizedes pontot tartalmazó számot fogad el, minden más esetben hibaüzenetet dob. és visszadobja a felhasználót a menüben Majd bekéri a leírást, itt az egyetlen kritérium, hogy ne legyen üres, ha üres hibaüzenetet dob és visszakerül a felhasználó a menübe, ha helyes volt minden formátum akkor hozzáadja a listához a költséget és kiírja a menüt.

### Listázás
A második menüpont a költségek listázása. Ekkor kiírja, hogy `Add meg, hogy mire szeretnél szűrni (Ha nem szeretnél akkor csak hagy üresen) :` itt a leírásban tudunk szűrni, itt tartalmazást néz, de csak pontos egyezés esetén talál, például.: leírás: autópálya, keresett szó: autó, ilyenkor talál, de az auto-ra nem talál. Ha nem szeretnénk keresési feltételt adni akkor üresen kell hagyni és minden költséget ki fog listázni.

### Összegzés
A harmadik menüpontot választva az összegzést érjük el, itt összegzi 2 dátum közötti költségek értékét. Amikor belépünk ebbe a menübe akkor megkéri a program, hogy melyik az a dátum, ahonnan szeretné a felhasználó az összegzést kezdeni, itt a dátum formátumok és a helytelen dátum a programban ugyanazt eredményezi, ha az összes költséget szeretné a felhasználó összegezni akkor ezt üresen kell hagyni, ilyenkor egyből kiírja az összeget, ha nem hagyja üresen és helyes a formátum akkor megkérdezni, hogy melyik az a dátum ameddig szeretné az összegzést, de itt már meg kell adni a dátumot és ennek is a formátumára a fentiekre vonatkozik.


### Szerkesztés
A negyedik menüpontot választva szerkeszteni tudjuk a költséget. A menüpontba belépve bekéri a program, a szerkeszteni kívánt költség azonosítóját (az azonosítót listázáskor lehet megnézni) ha ez nem egy létező azonosító akkor hibaüzenetet kapunk, ha helyes azonosító akkor elsőnek a dátumot lehet szerkeszteni, itt is a korábbiak érvényesek, ha nem szeretnénk a dátumot szerkeszteni akkor üresen kell hagyni, következő az összeg szerkesztése, itt is a korábbiak érvényesek, szintén ha nem szeretnénk szerkeszteni üresen kell hagyni majd a leírás szerkesztése amit szintén üresen kell hagyni ha nem szeretnénk szerkeszteni, ha pedig igen akkor pedig amire szeretnénk szerkeszteni.

### Törlés
Az 5. menüpont a törlés, itt azonosító alapján törölni tudunk költséget. Belépve a menüpontba bekéri a törölni kívánt elem azonosítóját, itt ha nem létező az azonosító akkor hibát dob a program, különben törli a beírt azonosítójú elemet.


### Kilépés
A 6. pont kilép a programból és az eddigi listát kimenti a fáljba, hogy ha legközelebb elindítjuk a programot onnan folytathassuk ahol abbahagytuk.

### Fordítás és futtatás
#### Menüs program
```bash
g++ -DMEMTRACE -Wall -Werror *.cpp -o koltsegek && ./koltsegek -menu
```
#### Teszt program
```bash
g++ -DMEMTRACE -Wall -Werror *.cpp -o koltsegek && ./koltsegek
```

A menü futtatásához a `-menu` flaggel kell elindítani a programot, alapértelmezetten a program tesztje indul el.


# Programozói dokumentáció

	Készítette: Gyürüs Bence
## 1. Feladat

Költés követő program, amiben nyomon lehet követni, hogy mire költött a felhasználó és mennyi pénz. Lehet hozzáadni költséget, illetve lehet ezeket törölni és szerkeszteni, valamint keresni, kilistázni az eddigi költségeket és két dátum közötti összes költést is meg tudja mondani.

---
## 2. Feladatspecifikáció

A feladat egy program amiben nyomon lehet követni a kötéseket, lehet keresni rájuk, szerkeszteni törölni, hozzáadni és mindezeket eltárolja, tehát a program leállítása után is megmaradnak.

Egy költség tárol egy dátumot YYYY-MM-DD formátumban, egy leírást, ehhez a String osztályt használja valamit a költés összegét, ami egy nem negatív valós szám, minden költség rendelkezni fog egy azonosítóval, ami egy nem negatív egész szám, ezzel lehet rájuk hivatkozni a műveletek során (szerkesztés, törlés).

Ha a programnak nem megfelelő formátumban adják meg az adatokat akkor hibaüzenetet dob és kilép a menübe. Az elvárt formátumok: a dátum YYYY-MM-DD formátumban, csak érvényes dátum adható meg, 0. évtől, ellentétes esetben Invalid dátum hibaüzenetet fog dobni. Az összeg csak nem negatív valós szám lehet. A költség leírása egy 0 karakternél hosszabb szöveg. Ha a felhasználó menüben használja a programot akkor a felsorolt összes adat megadása kötelező, ha az adatbázis fájlt szeretné szerkeszteni, akkor az azonosító megadása is kötelező.

A felhasználó egy menüből tud választani, hogy milyen műveletet szeretne végezni. A lehetséges műveletek: kilistázás, összegzés, hozzáadás, szerkesztés, törlés, kilépés. Ezeket a műveletek a menüben számok fogják reprezentálni. Nem megfelelő művelet kiválasztásakor a hibaüzenetet fog kapni a felhasználó: „Kérlek a felsorolt műveletekből válassz”, majd ismét megjelenik a menü.

Listázáskor a felhasználó tud keresni leírás alapján, ha ezt üresen hagyja kiírja az összes adatot táblázatosan a szabványos kimenetre. Ha nincs adat akkor „Nincs a keresési feltételnek megfelelő adat” feliratot fogja kiírni.

Összegzésnél meg kell adnia a felhasználónak egy intervallumot a fentebb említett formátumban, elsőnek a tól másodiknak az ig dátumot megadni és kiírja az eddig összes elköltött pénzt abban az intervallumban. Nem megfelelő formátum esetén „A dátum formátuma hibás. A helyes dátum: YYYY-MM-DD” vagy a „Nem létező dátum” szöveget fogja kiírni. Ha üresen hagyja a felhasználó ezeket akkor az összes az adatbázisban található költséget fogja kiírni.

Hozzáadásnál elsőnek meg kell adnia a felhasználónak a dátumot, majd a leírást és végül az összeget. Ha valamelyik érték üres vagy nem a formátumnak megfelelő, tehát a dátum nem a fent említett formátumban van vagy az összeg nem szám akkor a kimenetre az ehhez megfelelő hibaüzenetet fogja kiadni és visszadobja a felhasználót a menübe. Az azonosító automatikusan lesz generálva.

Szerkesztésnél elsőnek be kell írni a szerkesztendő elem azonosítóját, majd végigmegy elsőnek a dátumon, a leíráson majd az összegen és amelyiket szerkeszteni szeretnénk be kell írni az új értéket amelyiket változatlanul szeretnénk hagyni azt üresen kell hagyni. Ha nem található ilyen id akkor kiírja, hogy „Nem található ilyen elem”. Ha valamelyik adat beírásánál rossz a formátum, akkor a megfelelő hibaüzenetet fogja kidobni és visszakerül a felhasználó a menübe.

A törléskor meg kell adni az azonosítót és az elem törlődik. Ha nem található az azonosító akkor kiírja a kimenetre, hogy „Nem található ilyen elem”, majd visszadobja a felhasználót a menübe.

A program futásához szükséges az `adatok.csv` állomány. Ebben tárolja, olvassa be, majd a végén ide is írja ki az adatbázist.

A kilépéskor leáll a program.

---
## 3. Objektum Terv:

Egy költség a Koltseg osztályban lesz eltárolva, ez használni fogja a String és a Datum osztályt. A String osztály dinamikusan foglal memóriát a karakterláncnak, amit minden alkalommal bővít. Lesz neki indexelő operátor, értékadó operátor és emiatt copy constructora, destruktora, egyenlőséget ellenőrző operátora és += operátora illetve egy include függvénye ami megmondja egy másik karakterláncról, hogy benne van-e a stringben valamint lesz egy olyan függvény ami stringből előjel nélküli int-be vált valamint egy olyan ami Stringből előjel nélküli doublebe vált. A Datum osztály az évet, a hónapot és a napot tudja tárolni, ehhez lesz egy összehasonlító operátora amit Datummal hasonlít össze illetve egy egyenlőséget ellenőrző operátor. A költségek egy láncolt listában lesznek tárolva. Ennek lesz egy push tagfüggvénye amivel hozzáad a végéhez egy új elemet, lesz egy torol függvénye ami id alapján kivesz egy elemet a listából. Lesz indexelő operátora amivel megkapható az i-edik eleme a listának, ez túlindexeles esetén hibát fog dobni. A kiir függvény paraméter nélküli függvénye kiírja az összes költséget, a paraméteres pedig a paraméterként kapott tól, ig Dátum közötti költséget írja ki. A kiírOsszeg függvény ez előzőhöz hasonlóan paraméter nélkül az összes költség összegének szummáját írja ki, a paraméteres a két dátum közöttit. A szerkeszt függvény felülírja a paraméterként kapott költséget a listában és a destruktora felaszabadítja a listát. A Koltseg, a Datum és a String függvénynek mind lesz egy inserter operátora amit majd a standard kimenetra íráshoz fog használni. Ezen kívül lesz a String osztálynak egy beolvasó operátora is.
![[prog2nagyhaziUMLSkeleton.drawio.png]]
Az UML ábra nem tartalmazza a konstruktorokat és a destruktorokat. (Ez a TERV UML árbrája)

---
## 4. Objektum megvalósítás
A program megvalósítása egy sablon osztály megvalósítását, egy `String`, egy `Koltseg` osztály, egy `KoltsegLista` osztály, egy `Datum` oszály, egy vezérlés a programhoz és egy tesztprogram elkészítését igényelte. Az eredeti tervtől eltérve a `KoltsegLista` osztályom nem származik a `Vektor` osztályből, hanem tartalmazza, ennek megfelelően megvalósításra kerültek az `KoltsegLista` oszályban az indexelő operátorok illetve a length függvény és lett egy find függvénye is, amivel id alapján könnyen meg lehet mondani, hogy egy adott elem benne van-e a listában. Emellett a `Vektor` osztály megkapta a törlés függvényt, amiből a törölni kívánt elem pointerét beadva lehet törölni. A `String` osztály bővült a split függvénnyel, ami a szöveget tudja egy bizonyos karakter mentén feldarabolni, ezt korábban a fájlmegnyitásban csináltam, de logikusabbnak tűnt, ha a `String` osztály ezt kezeli, mivel többször is használom és stringen kell végrehajtani. Valamint tudja kezelni a `toInt()` függvényem ezután már a negatív számokat is. Ezen kívül a `Datum` osztálynak szükségesek voltak getter függvények, amikkel meg lehet kapni az évet, a hónapot és a napot. Mind a `String`-ben mind a `Vektor`-ban a hosszát nyilvántartó változókat `size_t` típusúra cseréltem és ennek megfelelően az indexelők is ezt a típust várják. A fájlkezeléshez végül egy osztályt készítettem, aminek egyszerűen elég definiáláskor megadni a fájlnevet és utána könnyen végezhető vele olvasás illetve írás. A teszteléshez használom az `std::stringstream`  külső könyvtárat a kimenet ellenőrzéséhez valamit a teszteseteket a _gtest_lite_-al ellenőrzöm.

Így a megvalósítás után a következőképp néznek ki az osztályok és a köztük lévő kapcsolatok:
![[dLJ1ZjCm4BttAuOULd4tEIp7Y5OhiKYiMC61mWMXbHjRhHNNZcodWY3-dIJsU9qsAe9JxJTlNiRlsRstZXhN7kNYbJlm8uT6Kg4MbQJMmWFjA_1h0L00FvKWb1lN1wreyx9DDhU-9oF9EdJcIHkiuIw7T9Ssi18-EoFKteEwuOOwRJPzmJD82JkjvRIwlbf-SxrwlNazNzvpz-wK4N_s0BmVpdY6VKoH0codQys7HfGgu4Ib.png]]
## 5. Főbb Osztályok
### 5.1 `class Datum` - `datum.cpp` /  `datum.h`
A dátumok kezelésére és tárolására szolgáló objektum. Az osztályban tárolt dátumok között könnyen végezhető összehasonlítás és létrehozás előtt ellenőrzi, hogy valós-e az adott dátum.
#### Főbb tagfüggvényei:
##### Konstruktorok:
2 konstruktora van a `Datum` osztálynak, egyik ahol egyesével kell megadni paraméterül az évet, a hónapot és a napot, a másik pedig egy `String`-et vár aminek formátuma `YYYY-MM-DD`
`Datum(int ev, int honap, int nap)` és `Datum(String d)`
##### Publikus tagfüggvények:
A dátum publikus tagfüggvényei a következők:
- `getEv()` - visszaadja az évet (`int`)
- `getHonap()` - visszaadja a hónapot (`int`)
-  `getNap()` - visszaadja a napot(`int`)
Definiált operátorok: `>` , `>=` , `<` , `<=` `==`
Az operátorok mind `Datum` és `Datum` között használhatók

Az osztályon kívül, de az osztályhoz kapcsolódóan definiáltam egy `<<` stream operátort, amivel lehetséges kiírni a kimenetre a dátumot. A következőképpen fog kiíródni a dátum: pl.: `2025-05-16`

### 5.2 `class String` - `string.cpp` /  `string.h`
A String karakterláncok kezelésére szolgáló osztály, ami dinamikusan tárolja a karaktereket a memóriában és egyszerűbbé teszi egy karakterlánc bővítését illetve néhány műveletet a karakterláncokon, mint a hozzáfűzés, összehasonlítás és van benne tartalmazást vizsgáló és daraboló függvény is
#### Főbb tagfüggvényei:
##### Konstruktorok:
A `String`-nek 4db konstruktora van:
- `String()` - alapértelmezett konstruktor
- `String(const char c);` - karakterrel deklarált
- `String(const char* c);` - `char*`-al deklarált
- `String(const String& s);` - copy konstruktor
##### Publikus tagfüggvények:
- Az osztályon elvégezhető műveletek: jobbról való összeadás `char`, `char*` és `String` típussal és jobbról használható vele a `+=` operátor szintén `char`, `char*` és `String` típusokkal
- Definiáltam `==` és `!=` operátorokat is amik segítségével a `String`-et össze lehet hasonlítani jobbról `const char*`-al és `String`-el

- `length()` visszaadja `size_t` típusként a karakterlánc hosszát

- `operator[](const size_t i)` visszaadja a karakterlánc `i`. elemét a karaterláncnak

- `includes(const String& str)` visszaadja, hogy a paraméterül kapott `String` benne van-e az adott karakterláncban és egy `bool` értékkel tér vissza - `true` ha benne van `false` ha nincs. Pl.: ```
	``` c
	String test = "automata";
	String test2 = "auto";
	String test3 = "mataauto";
	test.includes(test2);    // true
	test.includes(test3);    // false
	```
- `toInt()` függvény visszatér `int` típussal, amennyiben át lehet alakítani a `String` értékét egy egész számmá, ehhez az kell, hogy csak számok szerepeljenek benne, illetve az első helyen lehet egy `-` az előjelnek
	```c
	String szam = "123";
	int intben = szam.toInt();    // 123
	```

- `toUnsignedDouble()` a `toInt()`-hez hasonlóan számmal tér vissza, annyi különbséggel, hogy ez `double`-el tér vissza, illetve nem kezeli az előjelet, csak pozitív számokat tud átalakítani.
	```c
	String szam = "123.456";
	double doubleben = szam.toUnsignedDouble();    //123.456
	```

- `split(const char c)`  ami a paraméterként kapott karakter mentén feldarabolja a String értékét és visszaadja `Vektor<String>` típusként.
- `getC()` a C-s str-ként adja vissza a `String` értékét.

- Az osztályon kívül, de az osztályhoz kapcsolódóan definiálva van `<<` és `>>` operátor. A kiíró operátor kiírja a teljes `String`-et a paraméterül kapott stream-re az inserter operátor pedig addig olvas bele a `String`-be a paraméterül kapott streamről amíg a beérkező karakter az nem `\n`.

### 5.3 `Vektor<T>` - `vektor.hpp`
A vektor egy templete osztály, ami az benne lévő adatot láncolt listában tárolja. Az osztály nem szabadítja fel az eltárolt adatot megszűnésekor.
#### Főbb tagfüggvényei:
##### Konstruktorok:
A `Vektor`-nak 3 konstruktora van:
 - default konstruktor
 - `Vektor(T& adat)` - az első elemmel való definíció
 - `Vektor(const Vektor& v)` - copy konstruktor
##### Publikus tagfüggvények:
- `length()` - `size_t` típusként visszaadja a tömb hosszát

- `push_back(T adat)` - a paraméterül kapott elemet hozzáadja a lista végére, nincs visszatérési értéke

- `T& operator[](size_t index)` - visszaadja a tömb paraméterül kapott elemének a referenciáját
- `clear()` - kitörli a lista összes elemét, üressé teszi a listát

- `Vektor<T>& operator=(Vektor<T>& ujLista)` - értékadó operátor, ami egy `Vektor`-t ad értékül egy másik `Vektor`-nak

- `torol(T* torlendo)` - paraméterül egy pointert kap és kitörli a tömbből ha benne van

- `~Vektor` - destruktor - felszabadítja a tömböt
### 5.4 `Koltseg` (Költség entitás)
Egy költség tárolására és rajtuk való műveletek végzésére szolgáló osztály.
#### Főbb tagfüggvényei:
##### Konstruktorok:
- default konstruktor
- `Koltseg(Datum d, String l, double o, int id)` - paraméterül kap egy `Datum` típusú dátumot, egy `String` típusú karakterláncot, egy lebegőpontos értéket és egy pozitív egész típusú azonosítót, ha valamelyik nem paraméter üres, nincs értéke vagy az azonosító negatív akkor hibát dob vissza
##### Publikus tagfüggvények:
Publikus függvényei csak setterek és getterek, beállítják a dátumot, az értéket, a leírást és a getter függvények visszaadják a dátumot, az összeget, a leírást és az azonosítót
- `Datum& getIdo()` - `Datum` típusban adja vissza a dátumot
- `double getOsszeg()` - `double` típusban adja vissza az összeget
- `String& getLeiras()` - `String` típusban adja vissza a leírást
- `int getId()` - `int` típusban adja vissza az id-t
- `void setIdo(const Datum& d);` - beállítja a dátumot, várt paraméter `Datum&` típusú
- `void setOsszeg(double o);` - double típusban várja az összeg értéket amit beállít
- `void setLeiras(String& leiras);` - `String&` típusban várja a leírást és beállítja
A `Koltseg`-hez tartozik egy `<<` operátor ami kiírja a költséget az alábbi módon:
`<id>    <datum>    <osszeg>    <leiras>`
### 5.5 `KoltsegLista` - `koltsegLista.cpp` / `koltsegLista.h`
A Koltseg osztály elemeit tároló lista ami felelős a listán végzendő műveletekért, mint a hozzáadás, törlés, szerkesztés, összegzés, kiírás.
#### Főbb tagfüggvényei:
##### Konstruktorok:
- alapértelmezett konstruktor - üres listát csinál
- copy konstruktor - lemásol egy másik `KoltsegLista` objektumot
##### Publikus tagfüggvények:
- `find(const int id);` - visszadja, hogy a paraméterül kapott id-val rendelkező költség benne van-e a listában, `true` értéke ad vissza ha benne van `false`-t ha nincs

- `push_back(Datum d, double osszeg, String leiras)` - a paraméterül kapott `Datum`típusú dátumból, `double`  összegből és `String` leírásból csinál egy `Koltseg`-et, úgy, hogy az id-t automatikusan adja, nincs visszatérési értéke

- `push_back(Koltseg);` - hozzáadja a paraméterül kapott `Koltseg` típusú költséget, nincs visszatérési értéke

- `KiirOsszeg(Datum d1, Datum d2, std::ostream& os);` - kiírja összesítve két dátum között, első két paraméternek egy-egy `Datum` típust vár, első ahonnan szeretnénk, második ameddig szeretnénk kiírni az összegét a kötségeknek, harmadik paraméternek pedig megkapja, hogy hova írja ki, ennek az alapértelmezett értéke az `std::cout`. Üres dátumot kell beadni ha feltétel nélkül szeretnénk összegezni

- `kiir(String szures = String(), std::ostream& os = std::cout);` - kiírja a szűrésnek megfelelő költségeket, első paraméter egy a szűrési feltétel, ami üres ha nem szeretnék feltétellel szűrni, ilyenkor az összeset kiírja, a második paraméter pedig ahova szeretnénk kiírni, alapértelmezett értéket az `std::cout`

- `szerkeszt(int id, Datum d = Datum(), double osszeg = -1, String leiras = String());` - szerkeszti az id-nak megfelelő elemet, első paramétere az azonosító `int` típusú, amire szeretnénk szerkeszteni a dátumot `Datum` típus, ami szeretnénk szerkeszteni az összeget `double` típusú és amire a leírást `String` típusú, ha valamelyik értéket nem szeretnénk frissíteni akkor üresen kell hagyni.

- `length()` - visszaadja, hogy hány db költség van a listában `size_t` típusban

- `operator[](size_t index)` - visszaadja a paraméterként kapott indexű költséget `Koltseg&` típusként
### 5.6 `File` - `file.cpp` / `file.h`
Az adatbázis mentése fájlba, fájlkezelés. CSV fájl tud kezelni, a benne lévő adatok formátuma:
`<int azonosító>    <datum YYYY-MM-DD>    <double összeg>    <leírás, nem üres>`
#### Főbb tagfüggvényei:
##### Konstruktorok:
- `File(String fileName)` - `fileName` a kezelendő fájl neve
##### Publikus tagfüggvények:
- `read();` - beolvassa és feldolgozza a fájlban lévő adatokat és visszadja KoltsegLista pointerként

- `write(KoltsegLista* lista);` - kiírja a `KoltsegLista*` típusként kapott költséglistát a fájlba

### 5.7 `Vezerles` - `vezerles.cpp` / `vezerles.hpp`
 A kezelőfelület működése, bekéri a az adatokat és a bemenetnek megfelelő műveletet hajtja végre, kezeli a hibákat
#### Főbb tagfüggvényei:
##### Konstruktorok:
`Vezerles(const String& filename, std::ostream& os = std::cout, std::istream& in = std::cin);` - paraméterek `String&` típusként a fájl neve, ezután `std::ostream&` típusú stream ahova ki tud írni és `std::istream&` ahonnan be tud olvasni.
##### Publikus tagfüggvények:
- `void run();` - futtatja a menüt
##### Privát tagfüggvények:
- `void menuKiir(std::ostream& os) const;` - kiírja a menüt
- `void handleUj();` - Az új költség hozzáadásakor hívja meg a menü, ez kiírja és be is olvassa az adatokat, kezeli a hibákat
- `handleListaz();` - A költségeket listázza ki és bekéri az ehhez szükséges adatokat
- `handleOsszegez();` - Az összegző menüpontot kezeli, ez hívódik meg összegzéskor ami bekéri a megfelelő adatokat
- `handleSzerkeszt();` - Minden szerkesztéshez szükséges folyamatot kezel
- `handleTorol();` - A törléshez szükséges adatok bekérése és a törlés elvégzése
## 6. Hibakezelés

A program a beépített kivételeken kívül használ :

| **Kivétel**    | **Ok**                                         | Származtatva          |
| -------------- | ---------------------------------------------- | --------------------- |
| `HibasDatum`   | Érvénytelen dátum formátum vagy érték          | std::invalid_argument |
| `HibasBemenet` | Helytelen felhasználói input (pl. üres leírás) | std::invalid_argument |
| `MemoriaHiba`  | Memóriafoglalási hiba                          | std::invalid_argument |
| `FileHiba`     | Fájl megnyitása/olvasása/írása sikertelen      | std::runtime_error    |
|                |                                                |                       |
![[VLF1Zjem4BtxAznJGnj-05K8LLLL2LKzW7f5JZ8YNZisiYUiO7S_OYzxvyWFy0FH_jTw2HaPoP2Rn--DttipcNaK3jj6iozOGmDyeuKqZ7tbSxdjZWWQ52kry9x_aONmlqG0yoV6m_SzAcMbDHvvMGltRSHUOifYBuX1bNk4dz200IHEN4pJVaiDdwY1GeKq_2yqraaHCwYM88KmkZVNdPH-VwswesTH4kFdAVTOJIRIR8MM 1.png]]

---

## 7. Tesztelés - `test.h` / `test.cpp`

A program tesztelése a `gtest_lite.h`-val illetve egy teszt bemenettel történik. A tesztelést több külön részre bontottam:
- `Datum` tesztelése:
	- **Konstruktorok tesztelése:** ez teszteli az összes konstruktort, ellenőrzi a szökőévet
	- **Helytelen bemenetek:** String-es kontruktorral megnézzük invalid dátumra, formátumnak nem megfelelő évvel, hónappal, és nappal, valamint egy nem dátum formátummal
	- **Operátorok ellenőrzése:** definiálunk 3 különböző dátumot és egyet ami azonos az elsővel, majd ezekkel ellenőrizzük az operátorokat, kisebb, nagyobb, kisebb egyenlő, nagyobb egyenlő, és egyenlő operátorok
- `String` tesztelése:
	- **Konstruktorok tesztelése:** Konstruktorok ellenőrzése, default kontruktor, karakter konstruktor és char* kontruktor
	- **Plusz és plusz egyenlő operátorok tesztelése:** megnézzük Stringhez char* hozzáadását, String hozzáadását + operátorral is és plusz egyenlő operátorral is és ugyanezt karakterekre is
	- **Beolvasó operátor tesztelése**
	- **Az intté és doublé alakítás ellenőrzése:** Megnézzük az int-et pozitív és negatív számokra, megnézzük double-re majd hibás számokra is, ami az, hogy van benne számok kívül más karakter is
	- A String osztály Split és includes tagfüggvényének ellenőrzése,  valamint itt teszteli az indexelő operátor és az egyenlőség és nem nem egyenlő operátort
- `Koltseg` tesztelése:
	- Konstruktorok tesztelése, helyes adatokkal, hibás dátummal, negatív összeggel és negatív id-val
- `KoltsegLista` tesztelése:
	- **Költségek hozzáadásának ellenőrzése:** Hozzáadunk 3 elemet, megnézzük a hosszát, majd ellenőrizzük mind a három elemnek az id-ját, összegét, leírását
	- **A költségek törlésének ellenőrzése**: Hozzáadjunk 3 elemet a listához, majd ellenőrzések után töröljük a 2-es idjú elemet és ezután megnézzük a hosszát újra, ekkor változnia kell 2-re. Ellenőrizzük, hogy a másik 2 elem id-ja maradt-e és nem-e egy másik elem törlődött. Utána törlünk egy olyan idjú elemet ami nem létezik, így a lista hossza nem változik
	- **A költségek szerkesztésének ellenőrzése:** létrehozunk egy 2 elemű `KoltsegLista`-t, szerkesztjük, majd szerkesztés után maradnia kell a méretnek ugyanakkorának, meg nézzük, hogy az összeg, a leírás és a dátum változott-e. Módosítunk egy másikat és megnézzük, hogy az előző is módolsult-e
	- **Szűrések ellenőrzése:** létrehozunk egy 4 elemű `KoltsegLista`-t dátum összegzésre szűrés, megnézzük, hogy az összeg 8000-e, szűrés olyan stringre ami szerepel az egyik leírásában, megnézzük, hogy benne van-e a kíírt szövegben az összes leírása, erre csak egyre szabad (vasarlas) true-t kapnunk, szűrünk üres adatokra, ekkor Nincs a keresésnek megfelelő adat kíírást kell kapnunk
- `Vektor` tesztelése:
	- Az elemek hozzáadása és azok elérése
- `File` tesztelése:
	- megnyitjuk az `adatok.csv`-t majd ellenőrizzük a beolvasott adatokat
	- megpróbálunk megnyitni egy nem létező fájlt
- `Throw`-ok ellenőrzése:
	- Költség létrehozáskor, invalid dátummmal, üres dátummal, üres leírással, negatív idval

**Memóriaszivárgás ellenőrzése**:
A memóriaszivárgást a `MEMTRACE`-el ellenőrzöm, ami szerint nincs a programban futás közben és a futás befejezésekor sem memória szivárgás a programban.
