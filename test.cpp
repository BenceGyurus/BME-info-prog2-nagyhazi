#include "gtest_lite.h"
#include "datum.h"
#include "string.h"
#include "koltseg.h"
#include "koltsegLista.h"
#include <sstream>
#include <stdexcept>
#include "file.h"

void test() {

/**
 * Dátum konstruktorok, alap kontruktorra, 3 paraméteres konstuktorra és stringes kontruktorra, ami egy szökőév
*/
TEST(DatumEllenorzes, Konstruktorok) {
    Datum alapDatum;
    EXPECT_EQ(-1, alapDatum.getEv());

    Datum specifikusDatum(2025, 3, 15);
    EXPECT_EQ(2025, specifikusDatum.getEv());
    EXPECT_EQ(3, specifikusDatum.getHonap());
    EXPECT_EQ(15, specifikusDatum.getNap());

    Datum szokoEveiDatum("2028-02-29");
    EXPECT_EQ(2028, szokoEveiDatum.getEv());
    EXPECT_EQ(2, szokoEveiDatum.getHonap());
    EXPECT_EQ(29, szokoEveiDatum.getNap());
} END
/**
 * Dátum konstruktorai, hibás formátumokkal, nem létező dátummal, negatív évvel, honappal és nappal
 * String-es kontruktorral megnézzük invalid dátumra, formátumnak nem megfelelő évvel, hónappal, és nappal, valamint egy nem dátum formátummal
 */
TEST(DatumEllenorzes, HelytelenBejegyzesek) {
    EXPECT_THROW(Datum(2024, 1, 32), HibasDatum);
    EXPECT_THROW(Datum(2024, 0, 1), HibasDatum);
    EXPECT_THROW(Datum(2024, 13, 1), HibasDatum);
    EXPECT_THROW(Datum(2024, 13, -1), HibasDatum);
    EXPECT_THROW(Datum(2024, -12, 1), HibasDatum);
    EXPECT_THROW(Datum(-1, 13, 1), HibasDatum);
    EXPECT_THROW(Datum("2025-02-29"), HibasDatum);
    EXPECT_THROW(Datum("2025-0a-29"), HibasDatum);
    EXPECT_THROW(Datum("202-02-29"), HibasDatum);
    EXPECT_THROW(Datum("2024--1-29"), HibasDatum);
    EXPECT_THROW(Datum("2024-1-29"), HibasDatum);
    EXPECT_THROW(Datum("2024-01-2"), HibasDatum);
    EXPECT_THROW(Datum("nem-datum-formatum"), HibasDatum);
} END

/**
 * Dátum operátorainak ellenőrzése
 * definiálunk 3 különböző dátumot és egyet ami azonos az elsővel, majd ezekkel ellenőrizzük az operátorokat, kisebb, nagyobb, kisebb egyenlő, nagyobb egyenlő, és egyenlő operátorok
 */
TEST(DatumEllenorzes, RelaciosOperatorok) {
    Datum korabbi("2024-07-10");
    Datum kesobbi("2024-07-11");
    Datum masikEv("2025-01-01");
    Datum pontosEgyezes("2024-07-10");

    EXPECT_TRUE(korabbi < kesobbi);
    EXPECT_FALSE(korabbi < pontosEgyezes);
    EXPECT_TRUE(kesobbi < masikEv);
    EXPECT_FALSE(korabbi > kesobbi);
    EXPECT_FALSE(kesobbi > masikEv);
    EXPECT_TRUE(masikEv > korabbi);
    EXPECT_TRUE(masikEv >= korabbi);
    EXPECT_FALSE(masikEv <= korabbi);
    EXPECT_TRUE(pontosEgyezes <= korabbi);
    EXPECT_TRUE(korabbi >= pontosEgyezes);
    EXPECT_TRUE(korabbi==pontosEgyezes);
} END

/**
 * Konstruktorok ellenőrzése, default kontruktor, karakter konstruktor és char* kontruktor
 */
TEST(StringManipulacio, Kontruktorok) {
    String ures;
    EXPECT_STREQ("", ures.getC());
    EXPECT_EQ(0, ures.length());

    String egyKarakter('K');
    EXPECT_STREQ("K", egyKarakter.getC());
    EXPECT_EQ(1, egyKarakter.length());

    String kezdoSzoveg("Ez a char* kontruktor");
    EXPECT_STREQ("Ez a char* kontruktor", kezdoSzoveg.getC());
    EXPECT_EQ(21, kezdoSzoveg.length());
} END

/**
 * A pluszegyenlő és az összeadás operátorok ellenőrzése
 * megnézzük Stringhez char* hozzáadását, String hozzáadását + operátorral is és plusz egyenlő operátorral is és ugyanezt karakterekre is
 */
TEST(StringManipulacio, pluszEgyenloEsPluszMegEgyenlo) {
    String elsoResz = "Auto";
    elsoResz += "palya";
    EXPECT_STREQ("Autopalya", elsoResz.getC());

    String masodikResz = elsoResz + String(" matrica");
    EXPECT_STREQ("Autopalya matrica", masodikResz.getC());

    masodikResz += String(" vasarlas");
    EXPECT_STREQ("Autopalya matrica vasarlas", masodikResz.getC());

    String negedikResz = String("valami") + ' ';
    negedikResz += 'k';
    EXPECT_STREQ("valami k", negedikResz.getC());
} END

/**
 * Az intté és doublé alakítás ellenőrzése
 * Megnézzük az int-et pozitív és negatív számokra, megnézzük double-re majd hibás számokra is, ami az, hogy van benne számok kívül más karakter is
 */
TEST(StringManipulacio, szamma) {
    String szamString("1024");
    EXPECT_EQ(1024, szamString.toInt());

    String negativSzamString("-50");
    EXPECT_EQ(-50, negativSzamString.toInt());

    String tortSzamString("1.414");
    EXPECT_DOUBLE_EQ(1.414, tortSzamString.toUnsignedDouble());

    EXPECT_THROW(String("123x45").toInt(), HibasSzam);
    EXPECT_THROW(String("123-45").toInt(), HibasSzam);
    EXPECT_THROW(String("").toInt(), HibasSzam);
    EXPECT_THROW(String("abc").toUnsignedDouble(), HibasSzam);
} END

/**
 * Teszteli a beolvasó operátort
 */
TEST(String, istream_operator){
        std::istringstream iss("Hello Világ\nEz nem lesz beovasva (remélem)");
        String s;
        iss >> s;
        EXPECT_STREQ("Hello Világ", s.getC());
}
END

/**
 * A String osztály Split és includes tagfüggvényének ellenőrzése
 * 
 * Egy vesszővel elválasztott stringet elválasztunk a split függvénnyel, majd megnézzük, hogy az elemeket helyensen választotta-e szét, itt megnézzük az indexelő, opearátort, a nem egyenlő és az egyenlőség ellenőrző operátort is
 * megnézzük ugyanezt kettő darab vesszőre is
 * és egy teljesen üres stringre is, itt ellenőrizzük, hogy nem-e csinált több elemet
 * Ezután az includes függvényben ellenőrizzük, hogy adott szavak benne vannak e egy mondatban
 * Ezután egy teljes egyezést is megnézünk egy elrontott és egy jó mondatra is
 */
TEST(StringManipulacio, SplitEsIncludeEsOpearatorok) {
    String vesszosLista("kocsi,motor,bringa,busz");
    Vektor<String> jarmuvek = vesszosLista.split(',');
    EXPECT_EQ(4, jarmuvek.length());
    EXPECT_STREQ("motor", jarmuvek[1].getC());
    EXPECT_STREQ("bringa", jarmuvek[2].getC());
    EXPECT_STREQ("busz", jarmuvek[3].getC());
    EXPECT_EQ('o', jarmuvek[1][1]);
    EXPECT_TRUE(jarmuvek[1] != jarmuvek[2]);
    EXPECT_FALSE(jarmuvek[1] == jarmuvek[2]);
    String bringa = "bringa";
    EXPECT_TRUE(jarmuvek[2] == bringa);
    EXPECT_FALSE(jarmuvek[2] != bringa);

    String uresVesszok(",,");
    Vektor<String> uresek = uresVesszok.split(',');
    EXPECT_STREQ("", uresek[0].getC());
    EXPECT_STREQ("", uresek[1].getC());
    
    String fullUres("");
    Vektor<String> semmi = fullUres.split(',');
    EXPECT_STREQ("", semmi[0].getC());
    EXPECT_THROW(semmi[1], std::out_of_range);

    String mondat("valamit ide kell írni");
    EXPECT_TRUE(mondat.includes("valamit"));
    EXPECT_FALSE(mondat.includes("nincs"));
    EXPECT_TRUE(mondat.includes("ide"));
    EXPECT_TRUE(mondat.includes("kell írni"));
    EXPECT_FALSE(mondat.includes("nincs benne"));
    String teljesMondat("Teljes egyezéses mondat");
    EXPECT_FALSE(teljesMondat.includes("Teljes egyezéses mondet"));      // elrontva
    EXPECT_TRUE(teljesMondat.includes("Teljes egyezéses mondat"));

} END

/**
 * Költségek tesztelése
 * Konstruktorok
 * Konstruktorok negatív idval
 * Konstruktorok hibás dátummal
 * negatív összeggel
 */

TEST(KoltsegTest, KontruktorokEsHibak) {
    Datum d1("2024-05-12");
    Koltseg elso(d1, "valami egész dárga", 8000, 1);
    EXPECT_EQ(1, elso.getId());
    EXPECT_EQ(d1, elso.getIdo());
    EXPECT_STREQ("valami egész dárga", elso.getLeiras().getC());
    EXPECT_DOUBLE_EQ(8000.0, elso.getOsszeg());
    EXPECT_THROW(Koltseg masodik = Koltseg(Datum("2024-05-12"), "valami egész dárga", -8000, 1), HibasBemenet);
    EXPECT_THROW(Koltseg harmadik = Koltseg(Datum(), "valami egész dárga", 8000, 1), HibasDatum);
    EXPECT_THROW(Koltseg harmadik = Koltseg(Datum("2024-05-12"), "valami egész dárga", 8000, -1), HibasBemenet);
} END

/**
 * Költségek hozzáadásának ellenőrzése
 * Hozzáadunk 3 elemet, megnézzük a hosszát, majd ellenőrizzük mind a három elemnek az id-ját, összegét, leírását
 * Majd a find függvénnyel megnézzük, hogy van-e ilye azonosítójú elem
 */
TEST(KoltseglistaKezeles, Hozzaadas) {
    KoltsegLista koltsegek;
    koltsegek.push_back(Datum("2024-05-10"), 3500, "Ebed");     // id: 1
    koltsegek.push_back(Datum("2024-05-11"), 1200, "Tea");     // id: 2
    Koltseg harmasId(Datum("2024-05-12"), "valami egész dárga", 8000, 3);
    koltsegek.push_back(harmasId);                              // id: 3
    Koltseg ugyanolyan(Datum("2024-05-12"), "ugyanolyan id", 20000, 3);
    EXPECT_THROW(koltsegek.push_back(ugyanolyan), HibasBemenet);    // ugyanolyan id-val adjuk hozzá

    EXPECT_EQ(3, koltsegek.length());

    EXPECT_EQ(1, koltsegek[0].getId());
    EXPECT_EQ(Datum("2024-05-10"), koltsegek[0].getIdo());
    EXPECT_DOUBLE_EQ(3500.0, koltsegek[0].getOsszeg());
    EXPECT_STREQ("Ebed", koltsegek[0].getLeiras().getC());

    EXPECT_EQ(2, koltsegek[1].getId());
    EXPECT_EQ(Datum("2024-05-11"), koltsegek[1].getIdo());
    EXPECT_DOUBLE_EQ(1200.0, koltsegek[1].getOsszeg());
    EXPECT_STREQ("Tea", koltsegek[1].getLeiras().getC());

    EXPECT_EQ(3, koltsegek[2].getId());
    EXPECT_EQ(Datum("2024-05-12"), koltsegek[2].getIdo());
    EXPECT_DOUBLE_EQ(8000.0, koltsegek[2].getOsszeg());
    EXPECT_STREQ("valami egész dárga", koltsegek[2].getLeiras().getC());

    EXPECT_TRUE(koltsegek.find(2));
    EXPECT_FALSE(koltsegek.find(5));
} END

/**
 * A költségek törlésének ellenőrzése
 * 
 * Hozzáadjunk 3 elemet a listához, majd ellenőrzések után töröljük a 2-es idjú elemet és ezután megnézzük a hosszát újra, ekkor változnia kell 2-re
 * Ellenőrizzük, hogy a másik 2 elem id-ja maradt-e és nem-e egy másik elem törlődött
 * utána törlünk egy olyan idjú elemet ami nem létezik, így a lista hossza nem változik
 */
TEST(KoltseglistaKezeles, KoltsegTorlese) {
    KoltsegLista kLista;
    kLista.push_back(Datum("2024-06-01"), 500, "csipsz"); // id: 1
    kLista.push_back(Datum("2024-06-02"), 999, "fagyasztott krumpli (Lidl)"); // id: 2
    kLista.push_back(Datum("2024-06-03"), 4000, "koncert jegy"); // id: 3

    EXPECT_EQ(3, kLista.length());
    EXPECT_STREQ("fagyasztott krumpli (Lidl)", kLista[1].getLeiras().getC());

    kLista.torles(2);

    EXPECT_EQ(2, kLista.length());
    EXPECT_EQ(1, kLista[0].getId());
    EXPECT_EQ(3, kLista[1].getId());
    EXPECT_STREQ("csipsz", kLista[0].getLeiras().getC());
    EXPECT_STREQ("koncert jegy", kLista[1].getLeiras().getC());

    kLista.torles(4);
    EXPECT_EQ(2, kLista.length());
} END

/**
 * A költségek szerkesztésének ellenőrzése
 * Megnézzzük elsőnek, hogy helyes-e lista hossza
 * Ellenőrizzük az első elem összegét
 * szerkesztjük, majd szerkesztés után maradnia kell a méretnek ugyanakkorának, meg nézzük, hogy az összeg, a leírás és a dátum változott-e
 * Módosítunk egy másikat és megnézzük, hogy az előző is módolsult-e
 */
TEST(KoltseglistaKezeles, KoltsegSzerkesztese) {
    KoltsegLista kLista;
    kLista.push_back(Datum("2024-07-01"), 10000, "Ruhadarab"); // id: 1
    kLista.push_back(Datum("2024-07-02"), 2000, "Kave"); // id: 2

    EXPECT_EQ(2, kLista.length());
    EXPECT_DOUBLE_EQ(10000.0, kLista[0].getOsszeg());

    kLista.szerkeszt(1, Datum("2025-06-16"), 12000, "Masik ruhadarab");

    EXPECT_EQ(2, kLista.length()); // Méretnek maradnia kell
    EXPECT_DOUBLE_EQ(12000.0, kLista[0].getOsszeg());
    EXPECT_STREQ("Masik ruhadarab", kLista[0].getLeiras().getC());
    EXPECT_EQ(Datum("2025-06-16"), kLista[0].getIdo());

    kLista.szerkeszt(99, Datum("2024-08-01"), 5000, "Hibas szerkesztes");
    EXPECT_EQ(2, kLista.length());
    EXPECT_DOUBLE_EQ(12000.0, kLista[0].getOsszeg());       // a minden jól megy akkor ez nem módosul
} END

/**
 * Szűrések
 * 
 * dátum összegzésre szűrés, megnézzük, hogy az összeg 8000-e
 * szűrés olyan stringre ami szerepel az egyik leírásában, megnézzük, hogy benne van-e a kíírt szövegben az összes leírása, erre csak egyre szabad (vasarlas) true-t kapnunk
 * szűrünk üres adatokra, ekkor Nincs a keresésnek megfelelő adat kíírást kell kapnunk
 */
TEST(KoltseglistaKezeles, Szures) {
    KoltsegLista szuroLista;
    szuroLista.push_back(Datum("2025-01-15"), 5000, "vonat jegy");
    szuroLista.push_back(Datum("2025-02-20"), 7000, "vasarlas");
    szuroLista.push_back(Datum("2025-01-25"), 3000, "Lidl");
    szuroLista.push_back(Datum("2025-03-05"), 9000, "husveti ajandek");

    std::stringstream datumOsszegStream;
    szuroLista.KiirOsszeg(Datum("2025-01-01"), Datum("2025-01-31"), datumOsszegStream);
    String kimenetDatumOsszegzes(datumOsszegStream.str().c_str());

    EXPECT_TRUE(kimenetDatumOsszegzes.includes("8000"));       // megnézzük benne van e a 8000

    std::stringstream vasarlasSzuresStream;
    szuroLista.kiir("vasarlas", vasarlasSzuresStream);
    String kimenetSzoveg(vasarlasSzuresStream.str().c_str());

    EXPECT_FALSE(kimenetSzoveg.includes("vonat jegy"));         // Ha minden jól meg nincs benne
    EXPECT_TRUE(kimenetSzoveg.includes("vasarlas"));            // benne van
    EXPECT_FALSE(kimenetSzoveg.includes("Lidl"));               // nincs benne
    EXPECT_FALSE(kimenetSzoveg.includes("husveti ajandek"));    // nincs benne

    std::stringstream uresSzuresStream;
    szuroLista.kiir("nincs ilyen hihi", uresSzuresStream);
    EXPECT_STREQ("Nincs a keresésnek megfelelő adat\n\n", uresSzuresStream.str().c_str());  // nincs ilyen elem elvileg
} END

/**
 * Vektor osztály tesztelése
 * 
 * Az elemek hozzáadása és azok elérése
 * megnézzük a hosszát
 * egyesével megpróbáljuk elérni az indexeket
 * az utolsó az túlindexelés, ekkor std::out_of_ranget kell kapnunk
*/
TEST(VektorVizsgalat, ElemekHozzaadasaEsElerese) {
    Vektor<double> ertekek;
    ertekek.push_back(1.23);
    ertekek.push_back(4.56);
    ertekek.push_back(7.89);

    EXPECT_EQ(3, ertekek.length());
    EXPECT_DOUBLE_EQ(1.23, ertekek[0]);
    EXPECT_DOUBLE_EQ(4.56, ertekek[1]);
    EXPECT_DOUBLE_EQ(7.89, ertekek[2]);
    EXPECT_THROW(ertekek[3], std::out_of_range);
} END

/**
 * Throw-ok ellenőrzése
 * Költség létrehozáskor, invalid dátummmal, üres dátummal, üres leírással, negatív idval
 */
TEST(HibakezelesTeszt, VarhatoKivetelTipusok) {
    EXPECT_THROW(Koltseg(Datum("2025-02-30"), "Hibas datum", 100, 1), HibasDatum);

    EXPECT_THROW(Koltseg(Datum("2025-10-10"), "Negativ ID-val", 200, -5), HibasBemenet);
    
    EXPECT_THROW(Koltseg(Datum("2025-10-10"), "", 200, 10), HibasBemenet);

    EXPECT_THROW(KoltsegLista().push_back(Datum(2025,10,10), 50, String()), HibasBemenet);

    EXPECT_THROW(String("abc").toInt(), HibasSzam);

    // String toInt üres stringre
    EXPECT_THROW(String("").toInt(), HibasSzam);

} END

/**
 * Fájlkezelés ellenőrzése
 * megpróváljuk megnyitni az adatok.csv-t
 * ellenőrizzük a beolvasott adatokat, kiírunk újat, majd az töröljük
 * ellenőrizzük nem létező fájlal is
 */
TEST(fajlkezeles, fileMegnyitasIrasEsOlvasas) {
    const char* filename = "adatok.csv";
    File f(String(filename).getC());
    KoltsegLista* lista = f.read();
    EXPECT_TRUE(lista != nullptr);
    EXPECT_EQ(lista->length(), 4);
    lista->push_back(Koltseg(Datum("2025-10-10"), String("test hozzaad"), 100000, 99));
    f.write(lista);
    lista->torles(99);
    f.write(lista);
    File f2("nincsilyen.txt");
    EXPECT_THROW(f2.read(), FileHiba);
    delete lista;
} END

}