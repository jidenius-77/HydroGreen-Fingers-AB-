# Beslutslogg – MicroHydros

## 1. Syfte

Detta dokument samlar viktiga tekniska och praktiska beslut för MicroHydros-projektet.

Besluten används för att:

- undvika att samma frågor behöver diskuteras flera gånger,
- göra projektets tekniska val spårbara,
- dokumentera vilka alternativ som övervägts,
- visa varför en viss lösning valdes,
- göra det möjligt att senare ompröva beslut om nya krav eller problem uppstår.

Eftersom alla gruppmedlemmar inte alltid är tillgängliga kan vissa beslut tas som **arbetsbeslut** för att projektet ska kunna gå vidare. Sådana beslut kan senare omprövas av gruppen.

---

## Statusnivåer

- **Beslutat** – används som projektets nuvarande lösning.
- **Arbetsbeslut** – används tills vidare för att arbetet ska kunna fortsätta.
- **Öppet** – inget slutligt val är gjort ännu.
- **Ersatt** – beslutet har ersatts av ett senare beslut.

---

# D01 – Utvecklingsplattform

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Projektets nuvarande målplattform är:

- ESP32,
- C++,
- Arduino Framework,
- PlatformIO,
- Visual Studio Code.

## Alternativ som övervägts

- annan mikrokontroller,
- ren simulering på dator,
- annan utvecklingsmiljö.

## Motivering

ESP32 och PlatformIO används redan i projektets proof-of-concept och projektet bygger utan fel i denna miljö.

ESP32 ger också stöd för framtida nätverkskommunikation via Wi-Fi och passar därför bra för ett IoT-projekt.

Att byta plattform utan ett tydligt tekniskt behov skulle skapa extra arbete och risk.

## Konsekvens

Projektets kod och arkitektur utvecklas med ESP32 som målplattform.

---

# D02 – Utvecklingsstrategi: simulering först, fysisk hårdvara förbereds

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

Projektet fortsätter med simulerade mätvärden under den tidiga utvecklingen.

Arkitekturen ska samtidigt utformas så att simulerade datakällor senare kan ersättas av riktiga sensorer utan att Validator, MeasurementData eller Communication behöver byggas om.

## Alternativ som övervägts

1. endast fysisk hårdvara från början,
2. endast simulering,
3. simulering först och fysisk integration senare.

## Motivering

Simulerade värden gör det möjligt att utveckla och testa:

- datastruktur,
- validering,
- felhantering,
- återkommande mätcykler,
- kommunikationsformat,

utan att projektet blockeras av komponenter eller hårdvaruproblem.

Samtidigt är projektets arkitektur avsedd för ett embedded-system och bör därför vara redo för riktiga sensorer.

## Konsekvens

SensorManager ska kunna använda simulerade värden nu och senare bytas till riktig sensorläsning.

Den slutliga demonstrationsformen behöver fortfarande bekräftas med läraren.

---

# D03 – Sensor för lufttemperatur och luftfuktighet inne

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

SHT40 används som projektets referenssensor för:

- lufttemperatur inne,
- relativ luftfuktighet inne.

Om fysisk implementation används bör en variant eller kapsling med lämpligt skydd för den fuktiga miljön övervägas.

## Alternativ som övervägts

- SHT40,
- SHT31,
- BME280.

## Motivering

Sensorjämförelsen visar att SHT40 ger en bra kombination av:

- hög noggrannhet,
- låg strömförbrukning,
- digitalt I²C-gränssnitt,
- relativt enkel integration,
- möjlighet till skyddade varianter för mer krävande miljö.

BME280 innehåller dessutom lufttrycksmätning som projektet inte behöver.

## Konsekvens

Projektets sensorinterface och simulering kan utformas med SHT40 som referens.

---

# D04 – Sensor för lufttemperatur ute

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

En andra SHT40 används som referenssensor för lufttemperaturen utanför odlingsmiljön.

## Alternativ som övervägts

- andra SHT40,
- separat temperatursensor,
- annan kombinerad temperatur-/luftfuktighetssensor.

## Motivering

Genom att använda samma sensorfamilj för inne- och uteluft minskar:

- antalet olika sensorbibliotek,
- mängden integrationskod,
- felsökningskomplexiteten,
- antalet olika komponenter som gruppen behöver förstå.

Att den andra SHT40 även kan mäta luftfuktighet innebär inte att detta extra värde måste användas i grundprototypen.

## Konsekvens

Projektet behöver i huvudsak bara hantera två sensorfamiljer: SHT40 och DS18B20.

---

# D05 – Sensor för vattentemperatur

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

DS18B20 i en lämpligt kapslad probe används som referenslösning för temperatur i vatten eller näringslösning.

## Alternativ som övervägts

- DS18B20,
- TMP117,
- PT100/PT1000.

## Motivering

DS18B20 bedöms ge en bra balans mellan:

- tillräcklig noggrannhet,
- enkel digital integration,
- låg kostnad och komplexitet,
- god tillgänglighet,
- möjlighet att använda färdig probe.

TMP117 erbjuder högre precision men kräver en mer genomtänkt kapsling för vatten.

PT100/PT1000 kan ge mycket bra mätprestanda men kräver mer elektronik och ger högre komplexitet än vad grundprototypen behöver.

## Begränsning

Själva DS18B20-kretsen är inte automatiskt vattentät. Vid fysisk implementation måste den specifika probens kapsling och lämplighet för vätskan kontrolleras.

---

# D06 – Gemensam datastruktur

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

En komplett mätning representeras av en gemensam `MeasurementData`-struktur.

Den ska minst innehålla:

```cpp
struct MeasurementData
{
    float airInsideC;
    float airOutsideC;
    float waterC;
    float humidityInsidePct;
    bool valid;
};
```

En tidsstämpel eller ytterligare statusfält kan läggas till senare om behov finns.

## Motivering

En gemensam datastruktur gör att samma mätning enkelt kan skickas genom:

```text
SensorManager
      |
      v
MeasurementData
      |
      v
Validator
      |
      v
Communication
```

Det minskar beroenden mellan systemets olika delar.

---

# D07 – Mätintervall

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

Normalt mätintervall för prototypen sätts till:

**60 sekunder**

För utveckling och tester ska intervallet kunna ändras till exempelvis:

**5 sekunder**

utan att övrig programlogik behöver ändras.

## Alternativ som övervägts

- 5 sekunder,
- 30 sekunder,
- 60 sekunder,
- flera minuter.

## Motivering

Temperatur och relativ luftfuktighet i en hydroponisk odlingsmiljö förändras normalt långsammare än exempelvis rörelse- eller styrsignaler.

Ett intervall på 60 sekunder ger därför tillräckligt täta värden för prototypens historiska miljödata utan att generera onödigt många mätningar.

Kortare intervall används under utveckling så att tester kan genomföras snabbare.

## Konsekvens

Mätintervallet ska definieras på ett ställe i programmet och vara enkelt att ändra.

---

# D08 – Valideringsgränser

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

Prototypen använder breda tekniska rimlighetsgränser för att identifiera tydligt felaktiga mätvärden.

| Mätvärde | Min | Max |
|---|---:|---:|
| Lufttemperatur inne | -10 °C | 60 °C |
| Lufttemperatur ute | -30 °C | 60 °C |
| Vattentemperatur | 0 °C | 50 °C |
| Relativ luftfuktighet inne | 0 % | 100 % |

## Motivering

Syftet med Validator är i första hand att hitta tekniskt orimliga eller uppenbart felaktiga värden.

Gränserna ska därför inte tolkas som optimala odlingsförhållanden.

Exempel:

- 105 % relativ luftfuktighet är ogiltigt,
- -100 °C inomhustemperatur är uppenbart felaktigt,
- negativa vattenvärden är orimliga för den avsedda prototypmiljön.

## Konsekvens

Mer avancerade odlingsspecifika gränsvärden kan senare läggas till som varningsnivåer utan att ändra den grundläggande valideringen.

---

# D09 – Hantering av ogiltiga mätningar

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Om minst ett viktigt mätvärde är ogiltigt ska:

1. mätningen markeras med `valid = false`,
2. felet loggas,
3. programmet fortsätta köras,
4. nästa mätcykel genomföras normalt.

En ogiltig mätning får inte krascha hela systemet.

## Motivering

Detta uppfyller projektets krav på kontrollerad felhantering och gör systemet mer robust.

Att behålla informationen om att en mätning var ogiltig gör också felsökning enklare.

---

# D10 – Kommunikationsformat

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Mätdata representeras i ett JSON-liknande eller giltigt JSON-format.

Exempel:

```json
{
  "air_inside_c": 22.4,
  "air_outside_c": 18.7,
  "water_c": 20.1,
  "humidity_inside_pct": 55.2,
  "valid": true
}
```

## Motivering

JSON är:

- lätt att läsa för människor,
- lätt att generera,
- vanligt i IoT- och webbsystem,
- kompatibelt med MQTT, HTTP och många framtida tjänster.

## Konsekvens

Communication-modulen ansvarar för att översätta `MeasurementData` till detta format.

---

# D11 – Kommunikationslösning

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

Projektet använder två nivåer av kommunikation:

### Utveckling och felsökning

**Seriell kommunikation** används för att snabbt kunna se mätvärden och felsöka systemet.

### Slutlig IoT-kommunikation

**MQTT över Wi-Fi** är projektets huvudspår för kommunikation till ett externt system.

## Alternativ som övervägts

- endast seriell kommunikation,
- MQTT,
- HTTP/REST,
- Bluetooth/BLE.

## Motivering

Seriell kommunikation är enkel och stabil under utveckling.

MQTT är däremot mer lämpat för projektets IoT-karaktär och framtida arkitektur där en eller flera MicroHydros-enheter kan skicka data till en broker eller server.

MQTT ger också en tydlig separation mellan embedded-enheten och det externa systemet.

## Konsekvens

Communication-modulen bör utformas så att själva `MeasurementData` inte är beroende av MQTT.

Om MQTT inte kan färdigställas inom projektperioden ska den seriella proof-of-concept-lösningen fortfarande kunna demonstrera dataflödet, och begränsningen dokumenteras.

---

# D12 – MQTT-topic

**Datum:** 2026-09-19  
**Status:** Arbetsbeslut

## Beslut

Ett enkelt topic-format används:

```text
microhydros/measurement
```

En framtida version med flera enheter kan istället använda exempelvis:

```text
microhydros/<device-id>/measurement
```

## Motivering

Ett enkelt topic räcker för en enda prototyp men strukturen kan enkelt byggas ut senare.

---

# D13 – Hantering av Wi-Fi- och MQTT-hemligheter

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Riktiga:

- Wi-Fi-lösenord,
- användarnamn,
- MQTT-lösenord,
- API-nycklar,
- tokens

får inte commitas till repositoryt.

## Motivering

Projektets GitHub-repository ska kunna delas utan att privata uppgifter exponeras.

## Konsekvens

Om credentials behövs ska de lagras separat från versionshanterad kod.

En exempelkonfiguration kan läggas i repositoryt utan riktiga hemligheter.

---

# D14 – Programarkitektur

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Projektet använder följande huvudsakliga dataflöde:

```text
Sensorer / simulering
        |
        v
SensorManager
        |
        v
MeasurementData
        |
        v
Validator
        |
        v
Communication
        |
        v
Externt system
```

## Motivering

Strukturen separerar:

- datainsamling,
- datarepresentation,
- validering,
- kommunikation.

Det gör lösningen enklare att testa och vidareutveckla.

## Konsekvens

Nya funktioner ska så långt som möjligt placeras i rätt modul istället för att all logik läggs i `main.cpp`.

---

# D15 – Git-arbetssätt

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

`main` används som stabil branch.

Ny funktionalitet utvecklas i separata branches och integreras genom Pull Requests när det är relevant.

Exempel:

```text
feature/measurement-data
feature/sensor-simulation
feature/data-validation
feature/mqtt-communication
docs/sensor-research
test/system-flow
```

## Motivering

Det ger:

- tydligare versionshistorik,
- mindre risk att stabil kod förstörs,
- bättre spårbarhet mellan gruppmedlemmarnas arbete,
- möjlighet till code review.

---

# D16 – Prioriteringsprincip

**Datum:** 2026-09-19  
**Status:** Beslutat

## Beslut

Projektet prioriterar:

1. fungerande P0-krav,
2. stabilitet,
3. testning,
4. dokumentation,
5. P1-funktioner,
6. P2-funktioner.

## Motivering

En liten, fungerande och väl dokumenterad prototyp är viktigare än många extra funktioner som inte fungerar stabilt.

---

# 2. Öppna beslut

Följande behöver fortfarande bekräftas eller beslutas senare:

| Fråga | Status |
|---|---|
| Krävs fysisk hårdvara i slutdemonstrationen? | Öppet – bekräftas med läraren |
| Exakt SHT40-modell/breakout-kort | Öppet |
| Exakt DS18B20-probe | Öppet |
| MQTT-broker | Öppet |
| MQTT-bibliotek | Öppet |
| Ska tidsstämpel inkluderas i `MeasurementData`? | Öppet |
| Hur långt stabilitetstest ska genomföras? | Öppet |

---

# 3. Beslut som kan omprövas

Arbetsbeslut kan ändras om:

- läraren förtydligar projektkraven,
- fysisk hårdvara inte finns tillgänglig,
- en sensor visar sig olämplig,
- en kommunikationslösning skapar oproportionerligt mycket komplexitet,
- tester visar att en annan lösning är bättre.

När ett beslut ändras ska det gamla beslutet inte raderas.

Det ska istället markeras som **Ersatt** och hänvisa till det nya beslutet så att projektets utveckling förblir spårbar.
