# Smart Garden

### Duje Nikolić Malora

---

# 1. Uvod

## Sustav za automatsko navodnjavanje

Motivacija, a ujedno i cilj odabranog projekta bili su stvoriti **sustav** koji vrši **automatsko navodnjavanje** biljaka na temelju očitanih vrijednosti iz okoline. Ideja je bila simulirati rad sustava u laboratoriju te pokušati predočiti kako bi konceptualno takav sustav funkcionirao ukoliko bi ga se implementiralo među velike plantaže i vrtlove. Projekt je nazvan ***Smart Garden***.

![Automatic Watering System.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Automatic_Watering_System.jpg)

Da bismo uspjeli realizirati zamišljen proizvod, prvo je bilo potrebno razumijeti kako biljke funkcioniraju, u kojim uvjetima te koje su moguće opasnosti za biljku. Odgovore na postavljena pitanja je dala formula **fotosinteze** te ih je objedinila u jedan jedinstven odgovor.

---

## Fotosinteza

> **Fotosinteza** je proces u kojem se sunčeva energija pretvara u kemijsku pohranjenu u organskim molekulama. Proces gdje iz ugljikova dioksida i vode uz pomoć Sunčeve svjetlosti i klorofila nastaje šećer i kisik.
> 

![Fotosinteza.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Fotosinteza.jpg)

### **Kemijska formula:**

<aside>
💡 $6CO2 + 6H2O + light → C6H12O6 + 6O2$

</aside>

- **6CO2** — 6 molekula *ugljikovog dioksida*
- **6H20** — 6 molekula vode
- **light** — energija Sunčeve svjetlosti
- **C6H12O6** — glukoza
- **6O2** — 6 molekula kisika

---

## Potrebne informacije za početak rada na projektu

**Voda** je glavni faktor za rast biljaka. Biljka u svakom trenutku mora imati dovoljno vode kako bi mogla vršiti proces **fotosinteze**, a na nama je bilo da to osiguramo. Na vlažnost tla utječe **temperatura** i **vlažnost zraka**, tako da smo za naše potrebe trebali mjeriti i ta dva faktora. Pomoću njihovih trenutnih vrijednosti smo mogli aproksimirati za koliko će vremena tlo presušiti te na taj način maksimalno optimizirati naš sustav.

Pomoću kemijske formule **fotosinteze** saznali smo također i da je za rast biljaka uz vodu potrebna i (Sunčeva) svjetlost. S obzirom na to da Sunce ne obasjava istu točku na Zemlji cijeli dan potrebno je bilo u sustav dodati još jednu komponentu. Radi se o **LED diodi** koja bi se po potrebi palila i gasila s obzirom na vanjsko osvjetljenje. Ona bi u našoj simulaciji predstavljala reflektore koji bi biljkama pružali potrebnu energiju za rast.

---

# 2. Hardware

Kontrolu nad senzorskim osjetilima te radiokomunikaciju vršio je **Arduino Uno WiFi Rev2 mikrokontroler** s ugrađenim WiFi modulom. Glavna komponenta senzorskog čvora je **elektromotorna pumpa za vodu**.

![Arduino Uno WiFi Rev2.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Arduino_Uno_WiFi_Rev2.jpg)

Također, kao senzorska osjetila, korišteni su **BH1750** — senzor razine svjetlosti, **DHT22** — senzor temperature i vlažnosti zraka te **senzor vlažnosti tla**. Za indikaciju nedostatka svjetlosti u okruženju, koristili smo **LED diodu**. **Breadboard** je također poslužio kako bi sve komponente spojili na željene točke potencijala (manjak portova na mikrokontroleru). **Relej** je smo koristili kao sklopku koja kontrolira rad elektromotora. Uz sve navedene komponente, potrebne su nam bile i **žice** kojima smo sve to povezali, te od *vrtnog* hardvera smo koristili: spremnik vode, cijev, izolir traku, posudu za zemlju, te malo vrućeg ljepila i bušilicu kako bi napravili *kućište* za elektromotor.

### Lista komponenti i materijala:

- **Arduino Uno WiFi Rev2**
- **elektromotorna pumpa za vodu**
- **BH1750** — senzor razine svjetlosti
- **DHT22** — senzor temperature i vlažnosti zraka
- **senzor vlažnosti tla**
- **LED dioda**
- **Breadboard**
- **Relej**
- **Žice** — M/M, Ž/Ž, M/Ž
- **Spremnik vode**
- **Cijev**
- **Izolir traka**
- **Posuda za zemlju**
- **Ljepilo**
- **Bušilica**

---

## Elektromotor — mini pumpa za vodu

Glavna komponenta našeg sustava je **pumpa za vodu**. Ona omogućava navodnjavanje tako što električnu energiju pretvara u mehaničku energiju te svojim radom ispumpava vodu iz spremnika u zemlju u koju je posađena biljka.

![Pumpa za vodu.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Pumpa_za_vodu.jpg)

### Karakteristike:

- Napon: **3V-6V**
- Maksimalna visina na koju može podići tekućinu: **40-110cm**
- Brzina protoka: **120L/h**
- Vanjski promjer cjevčice za odvod: **7.5mm**
- Unutarnji promjer cjevčice za odvod: **4.7mm**
- Dimenzije pumpe: **24mm (promjer), 33mm (visina)**

### Challenge

Jedan od glavnih *hardverskih* problema bio je pronaći odgovarajuću dimenziju cijevi.

<aside>
💡 $Q = v * A$

</aside>

- ***Q*** — volumni protok
- ***v*** — brzina fluida u cijevi
- ***A*** — presjek cijevi

Iz priložene formule za volumni protok fluida možemo zaključiti da su brzina fluida u cijevi i presjek cijevi recipročne veličine. Za konstantan volumni pritok fluida vrijedi: ako smanjimo presjek cijevi, tada ćemo povećati brzinu fluida u cijevi i obratno. To znači da nam je u interesu bilo da pronađemo cijev što manjeg presjeka, ali dovoljno veliku da je uspijemo spojiti s pumpon za vodu.

Želimo postići što veću brzinu vode, jer što je veća brzina vode, to će s manje energije dostići veću visinu.

### Spajanje

![Spajanje pumpe za vodu.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Spajanje_pumpe_za_vodu.jpg)

### Challenge

Iz sheme spajanja vidimo da elektromotor spajamo na **napajanje (5V/3.3V)** ili **uzemljenje (GND)**. Ovdje dolazimo do novog izazova. Kada spojimo direktno elektromotor na napajanje i uzemljenje, strujni krug je zatvoren za cijelo vrijeme i elektromotor neprestano radi. Mi želimo postići **kontroliran** rad elektromotora. Problem smo pokušali riješiti spajanjem na **digitalne pinove**, no to nije pomoglo. Digitalni pinovi imaju istu razinu napona (5V) kao i pin za direktno napajanje, međutim, **struja** na digitalnim pinovima je znatno **manja**. Na kraju, pronašli smo idealno, tek malo kompliciranije rješenje — **relej**.

### Relej

Relej je poslužio kao sklopka. Relej se sastoji od 3 pina s donje strane:

- **VCC** — napajanje
- **GND** — uzemljenje
- **IN** — prima impulse električnog signala

**IN** pin smo spojili sa digitalnim pinom preko kojeg ćemo slati impulse releju, a relej će na temelju tih impulsa otvarati i zatvarati strujni krug.

![Relej.jpg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Relej.jpg)

S gornje strane ima 3 slota. Na jedan slot smo spojili uzemljenje Arduina, a na drugi uzemljenje elektromotora. Žicu na napajanje od elektromotora smo spojili na izvor napajanja s Arduina.

### Spajanje — relej kao sklopka

![Spajanje sa relejom.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Spajanje_sa_relejom.png)

### Vrtni hardware

Kao što je već prethodno spomenuto, potreban nam je bio jedan spremnik vode unutar kojeg će biti uronjena pumpa za vodu. Na stijenkama plastičnog spremnika napravili smo rupu tek dovoljno široku da mogu proći žice za napajanje elektromotora. Na krovu spremnika napravili smo prolaz za cijev koja bi tu cijev dodatno fiksirala i usmjerila prema posudi za zemlju. Izolir trakom smo učvrstili pumpu za vodu kako nebi *plesala* dok je uronjena u vodu. Drugi dio cijevi je vodio u posudu za zemlju gdje se nalazila zemlja koja treba biti navodnjavana.

![WhatsApp Image 2022-07-10 at 16.46.34 (3).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.34_(3).jpeg)

![WhatsApp Image 2022-07-10 at 16.46.35.jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.35.jpeg)

![WhatsApp Image 2022-07-10 at 16.46.35 (4).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.35_(4).jpeg)

![WhatsApp Image 2022-07-10 at 16.46.35 (1).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.35_(1).jpeg)

![WhatsApp Image 2022-07-10 at 17.02.21.jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_17.02.21.jpeg)

![WhatsApp Image 2022-07-10 at 17.02.20 (2).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_17.02.20_(2).jpeg)

![WhatsApp Image 2022-07-10 at 16.46.35 (3).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.35_(3).jpeg)

---

## BH1750 — Senzor razine osvjetljenja

Da bismo znali kada paliti, a kada gasiti **LED diodu**, bio nam je potreban senzor koji će pratiti razinu osvjetljenja u našem u okruženju. Za tu potrebu smo koristili **BH1750 senzor**.

### **Pinout**:

- **VCC** — napajanje (3.3V ili 5V)
- **GND** — ****uzemljenje
- **SCL** — “Serial clock” za I2C komunikaciju
- **SDA** — “Serial data” za I2C komunikaciju
- **ADDR** — selektor adrese

### Spajanje

![BH1750 spajanje.jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/BH1750_spajanje.jpeg)

![WhatsApp Image 2022-07-10 at 16.46.22 (1).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.22_(1).jpeg)

### Challenge

U početnoj fazi razvoja projekta, koristili smo **Arduino Uno** mikrokontroler. Gore, sa *sheme* možemo vidjeti da se **SDA** i **SDL** pinovi senzora spajaju na analogne inpute **A4** i **A5**. Ovakvo spajanje je moguće jer pinovi A4 i A5 predstavljaju alternativu za pinove SDA i SCL kao što je vidljivo iz slike ispod.

![Uno Pinout.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Uno_Pinout.png)

Također, moguće je spajanje direktno na SDA i SCL pinove locirane kraj **AREF** pina. Međutim, situacija je drukčija kod **Arduino Uno WiFi Rev2** mikrokontrolera. Kod Rev2 mikrokontrolera, pinovi A4 i A5 **ne predstavljaju** alternativu za SDA i SCL pinove, već su isključivo analog input pinovi. Ovime je Rev2 na obični UNO izgubio alternativu za I2C pinove, ali dobio je dva dodatna analog input pina.

![Pinout Rev2.jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Pinout_Rev2.jpeg)

Za zaključiti je da bismo onda kao idealno rješenje kod Rev2 mikrokontrolera pinove BH1750 senzora spojili direktno na SDA i SCL pinove, međutim, u laboratoriju to nije funkcioniralo. Moguće da je problem bio u industrijskoj grešci samog mikrokontrolera.

Kako je cijeli projekt zamišljen kao simulacija velikog sustava za automatsko navodnjavanje, onda je optimalno rješenje bilo simulirati rad BH1750 senzora pomoću ***random*** funkcije. Ukoliko bi *random* funkcija vraćala vrijednost koja je ispod nekog ***thresholda*** LED dioda bi se upalila, inače bi ostala ugašena.

### LED dioda

**LED diodu** smo koristili u kombinaciji sa **BH1750** senzorom. Na temelju očitanja senzora se LED dioda palila, odnosno gasila. Kao ***threshold*** smo koristili vrijednost od 100 luxa.

<aside>
💡 **lux** — količina osvjetljenja koja se dobiva kada je jedan lumen ravnomjerno raspoređen na površini od jednog kvadratnog metra

</aside>

S obzirom da je LED-ica **dioda** morali smo paziti da pravilno spojimo **anodu** i **katodu**. Anoda se spaja na **pozitivni** pol napajanja, dok se katoda spaja na **negativni**. Distinktivno ih možemo razlikovati jer je nožica od anode nešto **duža** od nožice katode.

![LED dioda.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/LED_dioda.png)

---

## DHT22 — Senzor temperature i vlažnosti zraka

Za naš projekt, odlučili smo da dio važnosti damo **temperaturi** i **vlažnosti zraka**, kako njihov utjecaj na vlažnost samog tla **nije zanemariv**. Ovaj senzor igrao je ključnu ulogu u **uštedi energije** jer smo na temelju njegovih očitanja stvorili **proračun** za koliko će se tek **vremena** senzor vlažnosti tla upaliti — ***timer***.

### **Pinout**:

- **VCC** — napajanje (3.3V ili 5V)
- **DATA** — ****šalje podatke o temperaturi i o vlažnosti zraka
- **NC** — *no connection*, ne koristi se
- **GND** — uzemljenje

### Spajanje

![BH1750 i DHT22 spajanje.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/BH1750_i_DHT22_spajanje.png)

![WhatsApp Image 2022-07-10 at 16.46.22 (2).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.22_(2).jpeg)

### Challenge

Kao što smo već spomenuli, **DHT22** senzor igrat će veliku ulogu kod odlučivanja kada očitati vlažnost tla. Trebalo je smisliti formulu koja bi na temelju ulaznih vrijednosti (temperatura i vlažnost tla) davala na izlazu broj sekundi za koliko će se upaliti senzor tla. **Temperatura** linearno raste. Važno je za napomenuti kako 20°C nije dvostruko toplije od 10°C, dok 300K uistinu jeste dvostruko toplije od 150K. Temperaturi smo dali važnost od **90%** u konačnoj formuli. Logično je da porastom temperature se treba smanjiti vrijeme između dva očitanja vlažnosti tla jer visoke temperature brže isušuju tlo. Stoga smo temperaturu promatrali **recipročno** u konačnoj formuli. S druge strane, **vlažnost zraka** se izražava u postotcima, od 0 do 100 posto. Logično je zaključiti da veća vlažnost zraka može značiti i veću vlažnost tla, međutim, ova informacija znači puno manje od temperature, pa smo vlažnosti zraka dali važnost od **10%**.

<aside>
💡 $**⌊100/temp * 0.9 + hum * 0.1⌋ * 10**$

</aside>

| Temperatura zraka | Vlažnost zraka | Izračunato vrijeme |
| --- | --- | --- |
| 20°C | 45% | 90s |
| 30°C | 60% | 90s |
| 35°C | 50% | 70s |

---

## Senzor vlažnosti tla

**Senzor vlažnosti tla** koristimo kako bismo odredili kada ćemo dovoditi vodu u zemlju.

Senzor je dovoljno paliti svako **12 sati**, ali mi nastojimo simulirati taj rad, tako da smo, kao što je već spomenuto, na vlastitu odgovornost izračunali period paljenja senzora (uz pomoć **DHT22 senzora**).

![Soil-Moisture-Sensor-Pinout.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Soil-Moisture-Sensor-Pinout.png)

### Pinout:

- **VCC** — napajanje (3.3V ili 5V)
- **GND** — uzemljenje
- **DO** — ****digital output
- **AO** — analog output

### Spajanje

Ukoliko bismo spojili senzor na digitalni output, na *serial monitoru* bi dobivali vrijednosti 0 i 1 (bool), zato ga spajamo na analogni output kako bi na *serial monitoru* dobili dekadske vrijednosti i na temelju njih definirali razinu vlažnosti tla.

![Spajanje.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Spajanje.png)

![WhatsApp Image 2022-07-10 at 16.46.34 (1).jpeg](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/WhatsApp_Image_2022-07-10_at_16.46.34_(1).jpeg)

### Princip rada senzora

Princip rada senzora vlažnosti tla je vrlo jednostavan za shvatiti. Senzor se u zemlji ponaša kao **potenciometar**, odnosno **mjeri otpor** unutar medija. Što je tlo vlažnije, odnosno što ima više vode, to će medij bit **konduktivniji** pa će otpor biti manji. S druge strane, što je tlo više suho, odnosno što ima manje vode u tlu, to će medij bit **otporniji** pa će i otpor biti veći.

![Kako radi senzor vlažnosti tla.png](Smart%20Garden%20b220b5b3cafe4b59b8f8827664ca7254/Kako_radi_senzor_vlanosti_tla.png)

Stoga na temelju očitanja s analognog outputa definiramo **dvije granice**, odnosno **tri stanja** vlažnosti tla. 

- **manje od 500** — tlo je mokro
- **između 500 i 750** — optimalna razina vlažnosti
- **veće od 750** — tlo je suho

> **NAPOMENA:** Senzor kojeg smo mi koristili za potrebe našeg projekta sklon je **koroziji**. Tako da se preporuča da se povremeno zamijeni novim. Ovo je ujedno i najveća mana korištenog senzora.
> 

---

# 3. Software

## **Funkcionalnost osvjetljenja**

### BH1750_init()

```cpp
BH1750 lightMeter(0x23);

void SENSORS::BH1750_init(){
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  Serial.println(F("BH1750 test!"));
}
```

<aside>
#️⃣ Funkciju koristimo kako bi **inicijalizirali** rad senzora BH1750.

</aside>

### readLight() — očitanje s BH1750 senzora

```cpp
BH1750 lightMeter(0x23);

uint16_t SENSORS::readLight() {
    uint16_t lux = lightMeter.readLightLevel();

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    return lux;
}
```

<aside>
#️⃣ Deklariramo varijablu *lux*. Varijabla je tipa ***uint16_t*** što znači da može poprimiti maksimalnu vrijednost **65536** (odnosno 2^16). 8 bitova bi bilo premalo jer razina svjetlosti ponekad ide i preko 256 lx, pa smo se oprjedjelili za 16. Unutar funkcije se poziva metoda readLightLevel() koja vraća vrijednost očitanu sa senzora. Vraćenu vrijednost pridjeljujemo varijabli ***lux***. Unutar funkcije također na ***serial monitor*** ispisujemo razinu trenutnog osvjetljenja u okruženju. Funkcija vraća **vrijednost varijable *lux***.

</aside>

### calculateRandomLight()

```cpp
#include <stdlib.h>

uint16_t calculateRandomLight() {
    srand(millis());

    int randomLight = rand() % 50 + 90;

    Serial.print("Light: ");
    Serial.print(randomLight);
    Serial.println(" lx");

    return randomLight;
}
```

<aside>
#️⃣ S obzirom na prethodno navedeni problem gdje BH1750 senzor ne radi na Rev2 mikrokontroleru, bilo je potrebno smisliti funkciju koja će pružiti alternativu kalkuliranja trenutne razine osvjetljenja u okruženju. S obzirom da želimo simulirati rad sustava, dovoljno je bilo napisati funkciju koja će **nasumično** vraćati “razinu osvjetljenja u okruženju senzora”. Korištene su funkcije ***srand()*** i ***rand()***. Funkcija *rand()* vraća nasumičnu vrijednost u intervalu **od 90 do 140**. S obzirom da je naš ***threshold* 100** vjerojatnost je 4:1, odnosno **80%** da se žarulja upali (ostane upaljena), a **20%** da se žarulja ugasi (ostane ugašena).

</aside>

### blinkLed()

```cpp
#define led 13

typedef enum {
  READ_SERIAL,
  READ_SENSORS,
  TURNON_LED,
  TURNOFF_LED
} StateType;

StateType ledState = READ_SERIAL;

uint16_t lux = 0;

void setup() {
  Serial.begin(9600);

	pinMode(led, OUTPUT);	

	lux = calculateRandomLight();

  delay(100);
}

void loop() {
	lux = calculateRandomLight();
	blinkLed(lux);

	delay(2000);
}

void blinkLed(uint16_t lux) {
  switch (ledState) {
    case READ_SERIAL:
      ledState = READ_SENSORS;
      break;
    
    case READ_SENSORS:
      if (lux < 100)
        ledState = TURNON_LED;
      else
        ledState = TURNOFF_LED;
      break;

    case TURNON_LED:
      digitalWrite(led, HIGH);
      ledState = READ_SERIAL;
      break;

    case TURNOFF_LED:
      digitalWrite(led, LOW);
      ledState = READ_SERIAL;
      break;

    default:
      break;
  }
	
	return;
}
```

<aside>
#️⃣ Paljenje i gašenje LED diode smo realizirali preko **state machine**. Unutar state machine definirali smo 4 stanja: READ_SERIAL, READ_SENSORS, TURNON_LED, TURNOFF_LED. Inicijalno smo postavili ***ledState*** u READ_SERIAL. Također, morali smo definirati da nam se LED dioda nalazi na **digitalnom pinu 13** te pozivom funkcije *pinMode()* postaviti taj pin u OUTPUT način rada. Unutar *loop()* funkcije se poziva funkcija ***calculateRandomLight()*** te se njena vraćena vrijednost prosljeđuje funkciji ***blinkLed()*** koja tu vrijednost prima kao parametar. Unutar funkcije *blinkLed()* poziva se **state machine**. Ukoliko parametar funkcije, ***lux*** prelazi ***threshold*** **100**, tada se LED dioda funkcijom *digitalWrite()* gasi (odnosno, ostaje ugašena), a ukoliko ne prelazi, tada se LED dioda istom funkcijom pali (odnosno, ostaje upaljena). Nakon poziva funkcije *digitalWrite()* *ledState* se nanovo stavlja u stanje **READ_SERIAL** te cijeli proces provjere kreće ispočetka. Važno je za primijetiti da će, ukoliko je to potrebno, do **promjene** doći tek između **drugog** i **četvrtog poziva *loop()*** funkcije. Razlog je očit, ukoliko je vrijednost *lux* varijable izazvala promjenu, do promjene na LED diodi će doći tek nakon što se prođe kroz sva navedena stanja.

</aside>

---

## Mjerenje temperature i vlažnosti zraka te proračun *timera*

### DHT_init()

```cpp
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void SENSORS::DHT_init(){
  Serial.println(F("DHTxx test!"));
  dht.begin();
}
```

<aside>
#️⃣ Funkciju koristimo kako bi **inicijalizirali** rad senzora DHT22.

</aside>

### readTemp()

```cpp
float temperature;

float SENSORS::readTemp() {
    temperature = dht.readTemperature();

    if(isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return -1;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    return temperature;
}
```

<aside>
#️⃣ Deklariramo varijablu ***temperature***. Varijabla je tipa ***float*** jer varijabla može poprimiti i decimalne vrijednosti. Unutar funkcije se dohvaća vrijednost sa **DHT22** senzora. Ukoliko je ona uspješno dohvaćena, ispisuje se trenutna temperature te funkcija vraća njenu **vrijednost**. Ukoliko nije uspješno dohvaćena, ispisuje se *error message* te funkcija vraća **-1**.

</aside>

### readHum()

```cpp
float humidity;

float SENSORS::readHum() {
    humidity = dht.readHumidity();

    if(isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return -1;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    return humidity;
}
```

<aside>
#️⃣ Deklariramo varijablu ***humidity***. Varijabla je tipa ***float*** jer varijabla može poprimiti i decimalne vrijednosti. Unutar funkcije se dohvaća vrijednost sa **DHT22** senzora. Ukoliko je ona uspješno dohvaćena, ispisuje se trenutna vlažnost zraka te funkcija vraća njenu **vrijednost**. Ukoliko nije uspješno dohvaćena, ispisuje se *error message* te funkcija vraća **-1**.

</aside>

### calculateCurrentTime()

```cpp
int calculateCurrentTime() {
    return (int)(millis() / 1000);
}
```

<aside>
#️⃣ Funkcija ***millis()*** vraća vrijeme u milisekundama koje je proteklo od početka rada mikrokontrolera. Ukoliko to podijelimo s 1000 i zaokružimo, dobijemo vrijeme u sekundama, što upravo funkcija ***calculateCurrentTime()*** vraća.

</aside>

### calculateTime()

```cpp
int calculateTime(float temp, float hum) {
    int calculatedTime = floor((100/temp) * 0.9 + hum * 0.1) * 10;    
    
    return calculatedTime;
}
```

<aside>
#️⃣ Funkcija **računa** za koliko će se **vremena upaliti senzor** — vraća cjelobrojnu vrijednost koja predstavlja broj sekundi. Računa se na temelju **formule** koja je ranije prokomentirana.

</aside>

### checkTimer()

```cpp
int checkTimer() {
  temp = sensor.readTemp();
  hum = sensor.readHum();

  int startTime = (int)(millis() / 1000);
  int calculatedTime = calculateTime(temp, hum);

  int sum = startTime + calculatedTime;

  Serial.print("Timer: ");
  Serial.println(sum);

  return sum;
}
```

<aside>
#️⃣ Unutar funkcije se pozivaju funkcije ***readTemp()*** i ***readHum()***. Vraćene vrijednosti se prosljeđuju

</aside>

---

# 4. Wireless communication

---

# 5. Source code

## main.cpp

```cpp
#include "Sensors.h"
#include "Calculation.h"
#include "Wireless.h"

#define motor 7
#define sensorPower 8
#define sensorPin A0
#define led 13

#define soilWet 500
#define soilDry 750

SENSORS sensor;

typedef enum {
  READ_SERIAL,
  READ_SENSORS,
  TURNON_LED,
  TURNOFF_LED,
  PUMP_WATER
} StateType;

StateType ledState = READ_SERIAL;
StateType soilState = READ_SERIAL;

int timer = 0;
float temp = 0;
float hum = 0;
uint16_t lux = 0;
int soil = 0;

int checkTimer();
void blinkLed(uint16_t lux);
void pumpWater(int soil);
int readSoil();

char ssid[] = "smartgarden";
char pass[] = "smartgarden123";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

WiFiClient client = server.available();

void connectWiFi();
void printWeb();

void setup() {
  Serial.begin(9600);

  Serial.println("Access Point Web Server");
  enableWiFi();
  connectWiFi();

  delay(10000);

  server.begin();

  printWiFiStatus();

  Serial.println("");
  
  pinMode(motor, OUTPUT);
  pinMode(sensorPower, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(sensorPower, LOW);

  sensor.DHT_init();

  Serial.println("");

  timer = checkTimer();
  lux = calculateRandomLight();

  Serial.println("");

  delay(100);
}

void loop() {
  lux = calculateRandomLight();

  int currentTime = calculateCurrentTime();

  Serial.print("Current time: ");
  Serial.println(currentTime);

  blinkLed(lux);

  if (timer <= currentTime) {
    soil = readSoil();
    pumpWater(soil);
  }

  if (status != WiFi.status()) {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      Serial.println("Device connected to AP");
    } else {
      Serial.println("Device disconnected from AP");
    }
  }

  client = server.available();

  if (client) {
    printWeb();
  }

  Serial.println("");

  delay(2000);
}

int checkTimer() {
  temp = sensor.readTemp();
  hum = sensor.readHum();

  int startTime = (int)(millis() / 1000);
  int calculatedTime = calculateTime(temp, hum);

  int sum = startTime + calculatedTime;

  Serial.print("Timer: ");
  Serial.println(sum);

  return sum;
}

void blinkLed(uint16_t lux) {
  switch (ledState) {
    case READ_SERIAL:
      ledState = READ_SENSORS;
      break;
    
    case READ_SENSORS:
      if (lux < 100)
        ledState = TURNON_LED;
      else
        ledState = TURNOFF_LED;
      break;

    case TURNON_LED:
      digitalWrite(led, HIGH);
      ledState = READ_SERIAL;
      break;

    case TURNOFF_LED:
      digitalWrite(led, LOW);
      ledState = READ_SERIAL;
      break;

    default:
      break;
  }

  return;
}

void pumpWater(int soil) {
  switch (soilState) {
    case READ_SERIAL:
      soilState = READ_SENSORS;
      break;
    
    case READ_SENSORS:
      if (soil >= soilDry)
        soilState = PUMP_WATER;
      else if (soil <= soilWet) {
        soilState = READ_SERIAL;
        timer = checkTimer();
      }
      else
        soilState = READ_SERIAL;
      break;

    case PUMP_WATER:
      digitalWrite(motor, HIGH);
      delay(1000);
      digitalWrite(motor, LOW);
      timer = checkTimer();
      break;

    default:
      break;
  }

  digitalWrite(motor, HIGH);
  delay(1000);
  digitalWrite(motor, LOW);

  return;
}

int readSoil() {
  digitalWrite(sensorPower, HIGH);
  delay(10);

  int soil = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);

  Serial.print("Soil: ");
  Serial.println(soil);

  return soil;
}

void connectWiFi() {
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }
}

void printWeb() {
  if (client) {                             // if you get a client,
    // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 5");
            client.println();
           
            //create the buttons
            client.print("<p>Temperature: ");
            client.print(temp);
            client.print(" degree Celsius</p>");

            client.print("<p>Humidity: ");
            client.print(hum);
            client.print("%</p>");

            client.print("<p>Light: ");
            client.print(lux);
            client.print(" lx</p>");

            client.print("<p>Soil: ");
            client.print(soil);
            client.print("</p>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    // Serial.println("client disconnected");
  }
}
```

## Sensors.h

```cpp
#ifndef Sensors_h
#define Sensors_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

#define DHTPIN 2
#define DHTTYPE DHT22

class SENSORS {
public:
        SENSORS();
        ~SENSORS();
        void DHT_init();
        void BH1750_init();
        float readTemp();
        float readHum();
        uint16_t readLight();
};

#endif
```

## Sensors.cpp

```cpp
#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

SENSORS::SENSORS(){}
SENSORS::~SENSORS(){}

float humidity, temperature;

void SENSORS::DHT_init(){
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void SENSORS::BH1750_init(){
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  Serial.println(F("BH1750 test!"));
}

float SENSORS::readTemp() {
    temperature = dht.readTemperature();

    if(isnan(temperature)) {
        Serial.println("Failed to read temperature from DHT sensor!");
        return -1;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    return temperature;
}

float SENSORS::readHum() {
    humidity = dht.readHumidity();

    if(isnan(humidity)) {
        Serial.println("Failed to read humidity from DHT sensor!");
        return -1;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    return humidity;
}

uint16_t SENSORS::readLight() {
    uint16_t lux = lightMeter.readLightLevel();

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    return lux;
}
```

## Calculation.h

```cpp
#ifndef Calculation_h
#define Calculation_h

#include <math.h>
#include <time.h>
#include <stdlib.h>

int calculateTime(float temp, float hum) {
    int calculatedTime = floor((100/temp) * 0.9 + hum * 0.1) * 10;    
    
    return 10;
}

int calculateCurrentTime() {
    return (int)(millis() / 1000);
}

uint16_t calculateRandomLight() {
    srand(millis());

    int randomLight = rand() % 50 + 90;

    Serial.print("Light: ");
    Serial.print(randomLight);
    Serial.println(" lx");

    return randomLight;
}

#endif
```

## Wireless.h

```cpp
#ifndef Wireless_h
#define Wireless_h

#include <WiFiNINA.h>
#include <WiFi.h>

void enableWiFi() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

#endif
```

---

# 6. Literatura

- [https://hr.wikipedia.org/wiki/Fotosinteza](https://hr.wikipedia.org/wiki/Fotosinteza)
- [https://hr.wikipedia.org/wiki/Volumni_protok](https://hr.wikipedia.org/wiki/Volumni_protok)
- [https://lastminuteengineers.com/soil-moisture-sensor-arduino-tutorial/](https://lastminuteengineers.com/soil-moisture-sensor-arduino-tutorial/)
- [https://e-radionica.com/hr/blog/2018/12/10/kkm-mini-pumpa-za-vodu/](https://e-radionica.com/hr/blog/2018/12/10/kkm-mini-pumpa-za-vodu/)
- [https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-hosting-a-webserver](https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-hosting-a-webserver)
- [https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-web-server-ap-mode](https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-web-server-ap-mode)