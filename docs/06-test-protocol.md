# Testprotokoll – MicroHydros

## 1. Syfte

Detta dokument beskriver hur MicroHydros-prototypen testas och vilka testresultat som har uppnåtts.

Testningen ska visa att projektets viktigaste krav fungerar och att systemet kan:

- hantera de fyra efterfrågade mätvärdena,
- validera rimliga och orimliga värden,
- hantera gränsvärden korrekt,
- fortsätta fungera efter felaktiga mätvärden,
- bygga korrekt för ESP32,
- senare verifieras genom integrationstest och systemtest.

Dokumentet uppdateras löpande under projektets utveckling.

---

## 2. Testmiljö

### 2.1 Utvecklingsmiljö

Projektet använder:

- Visual Studio Code,
- PlatformIO,
- C++,
- Arduino Framework,
- ESP32 som målplattform.

### 2.2 Automatisk testmiljö

Validator-tester körs i en separat native-miljö med Unity.

Relevant konfiguration i `platformio.ini`:

```ini
[env:native]
platform = native
build_flags = -std=c++17 -Iinclude
test_framework = unity
build_src_filter = +<validator.cpp>
test_build_src = yes
```

Testfil:

```text
test/test_validator/test_validator.cpp
```

Tester kan köras från en terminal där PlatformIO CLI är tillgängligt:

```bash
pio test -e native
```

ESP32-versionen kan byggas med:

```bash
pio run -e esp32dev
```

Samma funktioner kan även köras via PlatformIO-tillägget i Visual Studio Code.

Om kommandot `pio` inte finns tillgängligt i den vanliga terminalen kan PlatformIO-terminalen i Visual Studio Code användas, eller motsvarande lokala PlatformIO-installation för användarens operativsystem.

---

## 3. Koppling till krav och beslut

Validator-testerna är främst kopplade till:

- **F8 – Validering av mätvärden**
- **F9 – Kontrollerad felhantering**
- **NF1 – Stabilitet**

Gränsvärdena kommer från projektets beslut **D08 – Valideringsgränser**.

| Mätvärde | Minimum | Maximum |
|---|---:|---:|
| Lufttemperatur inne | -10 °C | 60 °C |
| Lufttemperatur ute | -30 °C | 60 °C |
| Vattentemperatur | 0 °C | 50 °C |
| Relativ luftfuktighet inne | 0 % | 100 % |

Dessa gränser används som tekniska rimlighetsgränser i prototypen och ska inte tolkas som optimala odlingsförhållanden.

---

# 4. Validator – automatiserade tester

## 4.1 Basdata

Testerna använder en giltig basmätning:

```cpp
static MeasurementData baseMeasurement() {
    MeasurementData d;

    d.timestampMs = 1000;
    d.airInsideC = 22.0f;
    d.airOutsideC = 15.0f;
    d.waterC = 20.0f;
    d.humidityInsidePct = 55.0f;

    return d;
}
```

Varje test ändrar normalt endast ett fält åt gången.

Det gör det enklare att avgöra vilken valideringsregel som orsakar ett godkänt eller underkänt resultat.

---

## 4.2 Testfall

### TC-01 – Giltig basmätning

**Kopplat krav:** F8  
**Syfte:** Kontrollera att en mätning där alla värden ligger inom D08-gränserna accepteras.

**Testdata:**

```text
airInsideC = 22.0
airOutsideC = 15.0
waterC = 20.0
humidityInsidePct = 55.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-02 – Luftfuktighet över maxgräns

**Kopplat krav:** F8, F9  
**Syfte:** Kontrollera att luftfuktighet över 100 % identifieras som ogiltig.

**Testdata:**

```text
humidityInsidePct = 101.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `false`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-03 – Luftfuktighet exakt på maxgräns

**Kopplat krav:** F8  
**Syfte:** Kontrollera att exakt 100 % accepteras eftersom gränsen är inkluderande.

**Testdata:**

```text
humidityInsidePct = 100.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-04 – Inomhustemperatur under minimum

**Kopplat krav:** F8, F9  
**Syfte:** Kontrollera att ett värde precis under D08-gränsen för inomhustemperatur nekas.

**Testdata:**

```text
airInsideC = -10.1
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `false`.

**Första faktiska resultat:**  
`FAILED`

Testet visade:

```text
Expected FALSE Was TRUE
```

**Orsak:**  
`Validator` använde tidigare `-20.0 °C` som nedre gräns för inomhustemperatur, medan beslut D08 anger `-10.0 °C`.

Tidigare implementation:

```cpp
const bool airInsideOk = inRange(data.airInsideC, -20.0f, 60.0f);
```

**Korrigering:**

```cpp
const bool airInsideOk = inRange(data.airInsideC, -10.0f, 60.0f);
```

**Resultat efter korrigering:**  
`PASSED`

**Slutlig status:** Godkänd

---

### TC-05 – Inomhustemperatur exakt på minimum

**Kopplat krav:** F8  
**Syfte:** Kontrollera att exakt `-10.0 °C` accepteras.

**Testdata:**

```text
airInsideC = -10.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-06 – Utomhustemperatur under minimum

**Kopplat krav:** F8, F9  
**Syfte:** Kontrollera att ett värde under `-30 °C` identifieras som ogiltigt.

**Testdata:**

```text
airOutsideC = -30.1
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `false`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-07 – Utomhustemperatur exakt på minimum

**Kopplat krav:** F8  
**Syfte:** Kontrollera att exakt `-30.0 °C` accepteras.

**Testdata:**

```text
airOutsideC = -30.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-08 – Vattentemperatur under minimum

**Kopplat krav:** F8, F9  
**Syfte:** Kontrollera att negativ vattentemperatur under den valda prototypgränsen identifieras som ogiltig.

**Testdata:**

```text
waterC = -0.1
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `false`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-09 – Vattentemperatur exakt på minimum

**Kopplat krav:** F8  
**Syfte:** Kontrollera att exakt `0.0 °C` accepteras.

**Testdata:**

```text
waterC = 0.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-10 – Luftfuktighet under minimum

**Kopplat krav:** F8, F9  
**Syfte:** Kontrollera att luftfuktighet under 0 % identifieras som ogiltig.

**Testdata:**

```text
humidityInsidePct = -0.1
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `false`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

### TC-11 – Luftfuktighet exakt på minimum

**Kopplat krav:** F8  
**Syfte:** Kontrollera att exakt 0 % accepteras.

**Testdata:**

```text
humidityInsidePct = 0.0
```

**Förväntat resultat:**  
`Validator::isValid()` returnerar `true`.

**Faktiskt resultat:**  
`PASSED`

**Status:** Godkänd

---

# 5. Sammanfattning av Validator-tester

Senaste körningen gav:

```text
native:test_validator [PASSED]
11 test cases: 11 succeeded
```

Sammanfattning:

| Test | Resultat |
|---|---|
| TC-01 Giltig basmätning | PASS |
| TC-02 Luftfuktighet över max | PASS |
| TC-03 Luftfuktighet på max | PASS |
| TC-04 Innetemperatur under min | PASS efter korrigering |
| TC-05 Innetemperatur på min | PASS |
| TC-06 Utetemperatur under min | PASS |
| TC-07 Utetemperatur på min | PASS |
| TC-08 Vattentemperatur under min | PASS |
| TC-09 Vattentemperatur på min | PASS |
| TC-10 Luftfuktighet under min | PASS |
| TC-11 Luftfuktighet på min | PASS |

**Totalt:** 11 tester  
**Godkända:** 11  
**Underkända efter slutlig korrigering:** 0

---

# 6. Identifierat fel och korrigering

Testarbetet identifierade en avvikelse mellan projektets dokumenterade beslut och implementationen.

## Problem

Beslut D08 anger:

```text
Lufttemperatur inne: -10 °C till 60 °C
```

Men Validator använde:

```text
-20 °C till 60 °C
```

Det innebar att exempelvis:

```text
-10.1 °C
```

felaktigt accepterades.

## Hur felet upptäcktes

Ett nytt boundary-test skapades:

```cpp
d.airInsideC = -10.1f;
TEST_ASSERT_FALSE(Validator::isValid(d));
```

Testet misslyckades eftersom Validator returnerade `true`.

## Åtgärd

Den nedre gränsen ändrades från:

```cpp
-20.0f
```

till:

```cpp
-10.0f
```

## Verifiering

Efter korrigeringen kördes hela testsviten igen.

Resultat:

```text
11 test cases: 11 succeeded
```

Detta visar att automatiserade gränsvärdestester kunde identifiera en faktisk skillnad mellan dokumenterat beslut och implementation.

---

# 7. ESP32-build

Efter ändringarna i Validator kördes projektet även genom den vanliga ESP32-builden.

Kommando:

```bash
pio run -e esp32dev
```

Resultat:

```text
Environment    Status    Duration
-------------  --------  ------------
esp32dev       SUCCESS   00:00:30.337

1 succeeded
```

**Status:** Godkänd

Detta verifierar att ändringarna i Validator och teststrukturen inte gjorde att den vanliga ESP32-versionen slutade kompilera.

---

# 8. Nuvarande Validator-implementation

Efter korrigeringen används följande tekniska rimlighetsgränser:

```cpp
const bool airInsideOk =
    inRange(data.airInsideC, -10.0f, 60.0f);

const bool airOutsideOk =
    inRange(data.airOutsideC, -30.0f, 60.0f);

const bool waterOk =
    inRange(data.waterC, 0.0f, 50.0f);

const bool humidityOk =
    inRange(data.humidityInsidePct, 0.0f, 100.0f);
```

En komplett mätning är giltig endast om samtliga fyra kontroller är godkända.

---

# 9. Tester som återstår

Validator-testerna är genomförda, men hela systemet är ännu inte sluttestat.

Följande tester ska kompletteras senare.

## T12 – Återkommande mätningar

**Kopplat krav:** F5, NF1  
**Status:** Ej genomfört

### Syfte

Verifiera att systemet genomför flera mätcykler utan att startas om.

### Ska kontrollera

- att nya värden skapas återkommande,
- att programmet fortsätter köra,
- att valt mätintervall används.

---

## T13 – Komplett MeasurementData

**Kopplat krav:** F6  
**Status:** Ej genomfört som separat dokumenterat test

### Syfte

Verifiera att samtliga fyra mätvärden kan lagras samtidigt i samma struktur.

### Ska kontrollera

- `airInsideC`,
- `airOutsideC`,
- `waterC`,
- `humidityInsidePct`,
- `valid`.

---

## T14 – Kontrollerad felhantering över flera mätcykler

**Kopplat krav:** F9, NF1  
**Status:** Ej genomfört

### Syfte

Verifiera att en ogiltig mätning inte avslutar programmet.

### Testidé

1. skapa en giltig mätning,
2. skapa en ogiltig mätning,
3. verifiera `valid = false`,
4. genomför nästa mätcykel,
5. kontrollera att programmet fortfarande fungerar.

---

## T15 – Strukturerat dataformat

**Kopplat krav:** F11  
**Status:** Ej genomfört som separat dokumenterat test

### Syfte

Verifiera att Communication skapar ett konsekvent dataformat med alla fyra mätvärden och giltighetsstatus.

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

---

## T16 – Kommunikation till externt system

**Kopplat krav:** F10  
**Status:** Ej genomfört

### Syfte

Verifiera att en komplett mätning kan lämna embedded-systemet och tas emot eller läsas av ett externt system.

Testmetoden beror på projektets slutliga kommunikationslösning.

---

## T17 – Komplett integrationstest

**Kopplade krav:** F1–F11, NF1  
**Status:** Ej genomfört

### Dataflöde

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

### Ska verifiera

- fyra mätvärden produceras,
- värden lagras tillsammans,
- värden valideras,
- ogiltiga situationer hanteras,
- data formateras,
- data kommuniceras vidare,
- flera mätcykler kan genomföras.

---

## T18 – Stabilitetstest

**Kopplat krav:** NF1  
**Status:** Ej genomfört

### Syfte

Verifiera att systemet kan köra under ett större antal mätcykler utan oväntat programavbrott.

Exakt antal mätcykler beslutas senare.

---

# 10. Spårbarhet mellan krav och tester

| Krav | Test |
|---|---|
| F1 – Lufttemperatur inne | TC-01, TC-04, TC-05, T17 |
| F2 – Lufttemperatur ute | TC-01, TC-06, TC-07, T17 |
| F3 – Vattentemperatur | TC-01, TC-08, TC-09, T17 |
| F4 – Luftfuktighet inne | TC-01, TC-02, TC-03, TC-10, TC-11, T17 |
| F5 – Återkommande mätningar | T12, T17 |
| F6 – Gemensam datastruktur | T13, T17 |
| F7 – Databehandling | T17 |
| F8 – Validering | TC-01–TC-11 |
| F9 – Felhantering | TC-02, TC-04, TC-06, TC-08, TC-10, T14 |
| F10 – Kommunikation | T16, T17 |
| F11 – Strukturerat dataformat | T15, T17 |
| NF1 – Stabilitet | T12, T14, T17, T18 |

---

# 11. Teststatus

Nuvarande status:

| Område | Status |
|---|---|
| Native testmiljö | ✅ Klar |
| Validator automatiserade tester | ✅ 11/11 godkända |
| D08-gränser implementerade | ✅ Klar |
| ESP32 build efter Validator-ändring | ✅ SUCCESS |
| Återkommande mätningar | ⬜ Återstår |
| Kontrollerad felhantering över flera cykler | ⬜ Återstår |
| JSON/dataformat | ⬜ Återstår som dokumenterat test |
| Extern kommunikation | ⬜ Återstår |
| Komplett integrationstest | ⬜ Återstår |
| Längre stabilitetstest | ⬜ Återstår |

---

# 12. Slutsats hittills

Den automatiserade Validator-testningen fungerar och samtliga 11 nuvarande testfall passerar efter korrigering.

Testningen har redan varit värdefull eftersom den identifierade en verklig avvikelse mellan beslut D08 och implementationen.

Det visar att testmiljön inte enbart dokumenterar redan fungerande kod, utan även kan användas för att upptäcka och verifiera fel.

Projektets testarbete fortsätter när SensorManager, återkommande mätningar och den slutliga kommunikationslösningen är färdigställda.
