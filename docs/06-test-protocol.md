**# Testprotokoll – MicroHydros**

**## 1. Syfte**

Detta dokument beskriver hur MicroHydros-prototypen testas och vilka testresultat som har uppnåtts.

Testningen ska visa att projektets viktigaste krav fungerar och att systemet kan:

\- hantera de fyra efterfrågade mätvärdena,

\- validera rimliga och orimliga värden,

\- hantera gränsvärden korrekt,

\- fortsätta fungera efter felaktiga mätvärden,

\- bygga korrekt för ESP32,

\- verifieras genom enhetstest, integrationstest och systemtest.

Dokumentet uppdateras löpande under projektets utveckling.

**---**

**## 2. Testmiljö**

**### 2.1 Utvecklingsmiljö**

Projektet använder:

\- Visual Studio Code,

\- PlatformIO,

\- C++,

\- Arduino Framework,

\- ESP32 som målplattform.

**### 2.2 Automatisk testmiljö**

Projektet använder två separata native-testmiljöer med Unity.

Den första miljön används för automatiserade tester av `Validator`:

```ini
[env:native]
platform = native

build_flags =
    -std=c++17
    -Iinclude

test_framework = unity
build_src_filter = +<validator.cpp>
test_build_src = yes
test_filter = test_validator
```

Testfil:

```text
test/test_validator/test_validator.cpp
```

Validator-tester kan köras med:

```bash
pio test -e native
```

Den andra miljön används för B20 och testar dataflödet mellan `SensorManager`, `MeasurementData` och `Validator` med simulerade sensorer:

```ini
[env:native-flow]
platform = native

build_flags =
    -std=c++17
    -Iinclude
    -Itest/stubs
    -D USE_SIMULATED_SENSORS=1

test_framework = unity

build_src_filter =
    +<sensor_manager.cpp>
    +<validator.cpp>

test_build_src = yes
test_filter = test_data_flow
```

Testfil:

```text
test/test_data_flow/test_data_flow.cpp
```

För native-testet används även en enkel Arduino-stub:

```text
test/stubs/Arduino.h
```

Integrationstestet körs med:

```bash
pio test -e native-flow
```

ESP32-versionen kan byggas med:

```bash
pio run -e esp32dev
```

Samma funktioner kan även köras via PlatformIO-tillägget i Visual Studio Code.

Om kommandot `pio` inte finns tillgängligt i den vanliga terminalen kan PlatformIO-terminalen i Visual Studio Code användas, eller motsvarande lokala PlatformIO-installation för användarens operativsystem.

**---**

**## 3. Koppling till krav och beslut**

Validator-testerna är främst kopplade till:

\- **\*\*F8 – Validering av mätvärden\*\***

\- **\*\*F9 – Kontrollerad felhantering\*\***

\- **\*\*NF1 – Stabilitet\*\***

Gränsvärdena kommer från projektets beslut **\*\*D08 – Valideringsgränser\*\***.

\| Mätvärde | Minimum | Maximum |

\|---|---:|---:|

\| Lufttemperatur inne | -10 °C | 60 °C |

\| Lufttemperatur ute | -30 °C | 60 °C |

\| Vattentemperatur | 0 °C | 50 °C |

\| Relativ luftfuktighet inne | 0 % | 100 % |

Dessa gränser används som tekniska rimlighetsgränser i prototypen och ska inte tolkas som optimala odlingsförhållanden.

**---**

**# 4. Validator – automatiserade tester**

**## 4.1 Basdata**

Testerna använder en giltig basmätning:

\`\`\`cpp

static MeasurementData baseMeasurement() {

    MeasurementData d;

    d.timestampMs = 1000;

    d.airInsideC = 22.0f;

    d.airOutsideC = 15.0f;

    d.waterC = 20.0f;

    d.humidityInsidePct = 55.0f;

    return d;

}

\`\`\`

Varje test ändrar normalt endast ett fält åt gången.

Det gör det enklare att avgöra vilken valideringsregel som orsakar ett godkänt eller underkänt resultat.

**---**

**## 4.2 Testfall**

**### TC-01 – Giltig basmätning**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att en mätning där alla värden ligger inom D08-gränserna accepteras.

**\*\*Testdata:\*\***

\`\`\`text

airInsideC = 22.0

airOutsideC = 15.0

waterC = 20.0

humidityInsidePct = 55.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-02 – Luftfuktighet över maxgräns**

**\*\*Kopplat krav:\*\*** F8, F9  

**\*\*Syfte:\*\*** Kontrollera att luftfuktighet över 100 % identifieras som ogiltig.

**\*\*Testdata:\*\***

\`\`\`text

humidityInsidePct = 101.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`false\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-03 – Luftfuktighet exakt på maxgräns**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att exakt 100 % accepteras eftersom gränsen är inkluderande.

**\*\*Testdata:\*\***

\`\`\`text

humidityInsidePct = 100.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-04 – Inomhustemperatur under minimum**

**\*\*Kopplat krav:\*\*** F8, F9  

**\*\*Syfte:\*\*** Kontrollera att ett värde precis under D08-gränsen för inomhustemperatur nekas.

**\*\*Testdata:\*\***

\`\`\`text

airInsideC = -10.1

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`false\`.

**\*\*Första faktiska resultat:\*\***  

\`FAILED\`

Testet visade:

\`\`\`text

Expected FALSE Was TRUE

\`\`\`

**\*\*Orsak:\*\***  

\`Validator\` använde tidigare \`-20.0 °C\` som nedre gräns för inomhustemperatur, medan beslut D08 anger \`-10.0 °C\`.

Tidigare implementation:

\`\`\`cpp

const bool airInsideOk = inRange(data.airInsideC, -20.0f, 60.0f);

\`\`\`

**\*\*Korrigering:\*\***

\`\`\`cpp

const bool airInsideOk = inRange(data.airInsideC, -10.0f, 60.0f);

\`\`\`

**\*\*Resultat efter korrigering:\*\***  

\`PASSED\`

**\*\*Slutlig status:\*\*** Godkänd

**---**

**### TC-05 – Inomhustemperatur exakt på minimum**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att exakt \`-10.0 °C\` accepteras.

**\*\*Testdata:\*\***

\`\`\`text

airInsideC = -10.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-06 – Utomhustemperatur under minimum**

**\*\*Kopplat krav:\*\*** F8, F9  

**\*\*Syfte:\*\*** Kontrollera att ett värde under \`-30 °C\` identifieras som ogiltigt.

**\*\*Testdata:\*\***

\`\`\`text

airOutsideC = -30.1

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`false\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-07 – Utomhustemperatur exakt på minimum**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att exakt \`-30.0 °C\` accepteras.

**\*\*Testdata:\*\***

\`\`\`text

airOutsideC = -30.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-08 – Vattentemperatur under minimum**

**\*\*Kopplat krav:\*\*** F8, F9  

**\*\*Syfte:\*\*** Kontrollera att negativ vattentemperatur under den valda prototypgränsen identifieras som ogiltig.

**\*\*Testdata:\*\***

\`\`\`text

waterC = -0.1

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`false\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-09 – Vattentemperatur exakt på minimum**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att exakt \`0.0 °C\` accepteras.

**\*\*Testdata:\*\***

\`\`\`text

waterC = 0.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-10 – Luftfuktighet under minimum**

**\*\*Kopplat krav:\*\*** F8, F9  

**\*\*Syfte:\*\*** Kontrollera att luftfuktighet under 0 % identifieras som ogiltig.

**\*\*Testdata:\*\***

\`\`\`text

humidityInsidePct = -0.1

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`false\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**### TC-11 – Luftfuktighet exakt på minimum**

**\*\*Kopplat krav:\*\*** F8  

**\*\*Syfte:\*\*** Kontrollera att exakt 0 % accepteras.

**\*\*Testdata:\*\***

\`\`\`text

humidityInsidePct = 0.0

\`\`\`

**\*\*Förväntat resultat:\*\***  

\`Validator::isValid()\` returnerar \`true\`.

**\*\*Faktiskt resultat:\*\***  

\`PASSED\`

**\*\*Status:\*\*** Godkänd

**---**

**# 5. Sammanfattning av Validator-tester**

Senaste körningen gav:

\`\`\`text

native\:test_validator [PASSED]

11 test cases: 11 succeeded

\`\`\`

Sammanfattning:

\| Test | Resultat |

\|---|---|

\| TC-01 Giltig basmätning | PASS |

\| TC-02 Luftfuktighet över max | PASS |

\| TC-03 Luftfuktighet på max | PASS |

\| TC-04 Innetemperatur under min | PASS efter korrigering |

\| TC-05 Innetemperatur på min | PASS |

\| TC-06 Utetemperatur under min | PASS |

\| TC-07 Utetemperatur på min | PASS |

\| TC-08 Vattentemperatur under min | PASS |

\| TC-09 Vattentemperatur på min | PASS |

\| TC-10 Luftfuktighet under min | PASS |

\| TC-11 Luftfuktighet på min | PASS |

**\*\*Totalt:\*\*** 11 tester  

**\*\*Godkända:\*\*** 11  

**\*\*Underkända efter slutlig korrigering:\*\*** 0

**---**

**# 6. Identifierat fel och korrigering**

Testarbetet identifierade en avvikelse mellan projektets dokumenterade beslut och implementationen.

**## Problem**

Beslut D08 anger:

\`\`\`text

Lufttemperatur inne: -10 °C till 60 °C

\`\`\`

Men Validator använde:

\`\`\`text

-20 °C till 60 °C

\`\`\`

Det innebar att exempelvis:

\`\`\`text

-10.1 °C

\`\`\`

felaktigt accepterades.

**## Hur felet upptäcktes**

Ett nytt boundary-test skapades:

\`\`\`cpp

d.airInsideC = -10.1f;

TEST_ASSERT_FALSE(Validator::isValid(d));

\`\`\`

Testet misslyckades eftersom Validator returnerade \`true\`.

**## Åtgärd**

Den nedre gränsen ändrades från:

\`\`\`cpp

-20.0f

\`\`\`

till:

\`\`\`cpp

-10.0f

\`\`\`

**## Verifiering**

Efter korrigeringen kördes hela testsviten igen.

Resultat:

\`\`\`text

11 test cases: 11 succeeded

\`\`\`

Detta visar att automatiserade gränsvärdestester kunde identifiera en faktisk skillnad mellan dokumenterat beslut och implementation.

**---**

**# 7. ESP32-build**

Efter B20-ändringarna kördes projektet genom den vanliga ESP32-builden.

Kommando:

```bash
pio run -e esp32dev
```

Senaste resultat:

```text
Environment    Status    Duration
-------------  --------  ------------
esp32dev       SUCCESS   00:00:03.272

1 succeeded
```

**Status:** Godkänd

Builden verifierar att projektet fortfarande kompilerar för ESP32 efter tillägget av MQTT-kommunikation, native-flow-testmiljö och integrationstest.

**---**

**# 8. Nuvarande Validator-implementation**

Efter korrigeringen används följande tekniska rimlighetsgränser:

\`\`\`cpp

const bool airInsideOk =

    inRange(data.airInsideC, -10.0f, 60.0f);

const bool airOutsideOk =

    inRange(data.airOutsideC, -30.0f, 60.0f);

const bool waterOk =

    inRange(data.waterC, 0.0f, 50.0f);

const bool humidityOk =

    inRange(data.humidityInsidePct, 0.0f, 100.0f);

\`\`\`

En komplett mätning är giltig endast om samtliga fyra kontroller är godkända.

**---**

**# 9. Integrationstester och återstående tester**

Validator-testerna är genomförda och projektet har även kompletterats med integrationstest för det kompletta programvarubaserade dataflödet.

**## T12 – Återkommande mätningar**

**Kopplat krav:** F5, NF1  
**Status:** Genomfört

### Syfte

Verifiera att systemet kan genomföra flera mätcykler efter varandra utan att startas om.

### Genomförande

I `native-flow` kördes fem efterföljande simulerade mätcykler.

För varje cykel verifierades att:

- en ny timestamp skapades,
- alla fyra mätvärden producerades,
- mätvärdena låg inom valideringsgränserna,
- mätningen godkändes av `Validator`,
- nästa mätcykel kunde genomföras.

**Resultat:** `PASSED`

---

**## T13 – Komplett MeasurementData**

**Kopplat krav:** F6  
**Status:** Genomfört som del av B20

### Syfte

Verifiera att samtliga fyra mätvärden kan lagras samtidigt i samma `MeasurementData`.

### Verifierade fält

- `airInsideC`,
- `airOutsideC`,
- `waterC`,
- `humidityInsidePct`,
- `timestampMs`,
- `valid`.

Testet genomfördes som del av `test_complete_measurement_flow`.

**Resultat:** `PASSED`

---

**## T14 – Kontrollerad felhantering över flera mätcykler**

**Kopplat krav:** F9, NF1  
**Status:** Genomfört

### Genomförande

En mätning skapades och gjordes medvetet ogiltig genom:

`humidityInsidePct = 101.0f`

`Validator` markerade mätningen som ogiltig.

Därefter genomfördes en ny mätcykel med timestamp `10000 ms`.

Den nya mätningen producerades och godkändes av `Validator`, vilket visar att ett ogiltigt värde inte blockerar efterföljande mätningar.

**Resultat:** `PASSED`


### Syfte

Verifiera att en ogiltig mätning inte avslutar programmet och att nästa mätcykel fortfarande kan genomföras.

### Återstår

1. skapa eller injicera en ogiltig mätning,
2. verifiera `valid = false`,
3. genomför nästa mätcykel,
4. kontrollera att systemet fortsätter fungera.

Validatorns hantering av ogiltiga värden är redan verifierad genom TC-02, TC-04, TC-06, TC-08 och TC-10.

---

**## T15 – Strukturerat dataformat**

**Kopplat krav:** F11  
**Status:** Genomfört

### Syfte

Verifiera att `Communication` skapar ett konsekvent JSON-format med samtliga mätvärden och giltighetsstatus.

Verifierat format:

```json
{
  "timestamp_ms": 1000,
  "air_inside_c": 22.4,
  "air_outside_c": 18.7,
  "water_c": 20.1,
  "humidity_inside_pct": 55.2,
  "valid": true
}
```

JSON-formatet används av MQTT-kommunikationen.

**Resultat:** Godkänd

---

**## T16 – Kommunikation till externt system**

**Kopplat krav:** F10  
**Status:** Genomfört på prototypnivå

### Syfte

Verifiera att projektets MQTT-format och topic kan tas emot av ett externt system.

### Genomförande

En lokal Mosquitto-broker startades i Docker.

En MQTT-subscriber lyssnade på:

```text
microhydros/measurement
```

Ett giltigt JSON-meddelande publicerades och togs emot av subscribern:

```text
microhydros/measurement {"timestamp_ms":1000,"air_inside_c":22.4,"air_outside_c":18.7,"water_c":20.1,"humidity_inside_pct":55.2,"valid":true}
```

**Resultat:** `PASSED`

### Begränsning

MQTT-flödet och den externa mottagningen är verifierade programvarumässigt. Den slutliga fysiska verifieringen där en riktig ESP32 ansluter via Wi-Fi och publicerar till brokern återstår som kompletterande hårdvarutest.

---

**## T17 – Komplett integrationstest / B20**

**Kopplade krav:** F1–F11, NF1  
**Status:** Genomfört – programvarubaserat integrationstest

### Syfte

Verifiera MicroHydros huvudflöde från simulerad datakälla till validering och vidare till den kommunikationslösning som används av systemet.

### Dataflöde

```text
Simulerade sensorer
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
JSON / Communication
        |
        v
MQTT
        |
        v
Externt system
```

### Deltest 1 – Komplett mätning

Vid en simulerad tidpunkt på `5000 ms` lästes en komplett `MeasurementData`.

Förväntade värden från den simulerade sensormodellen:

```text
timestampMs = 5000
airInsideC = 22.50
airOutsideC = 20.25
waterC = 19.10
humidityInsidePct = 55.50
valid = true efter Validator
```

Samtliga värden verifierades och mätningen godkändes av `Validator`.

**Resultat:** `PASSED`

### Deltest 2 – Flera mätcykler

Fem efterföljande mätcykler genomfördes.

För varje cykel verifierades att:

- timestamp uppdaterades,
- alla fyra mätvärden fanns,
- värdena låg inom beslutade D08-gränser,
- mätningen godkändes,
- en senare mätcykel hade en högre timestamp än föregående cykel.

PlatformIO-resultat:

```text
native-flow:test_data_flow [PASSED]
2 test cases: 2 succeeded
```

**Resultat:** `PASSED`

### Kommunikationsverifiering

Kommunikationsdelen har dessutom verifierats separat genom MQTT-testet i T16.

Det ger följande verifierade programvaruflöde:

```text
SensorManager
    -> MeasurementData
    -> Validator
    -> JSON
    -> MQTT
    -> extern subscriber
```

### Begränsning

Den kompletta kedjan har verifierats programvarumässigt i två testdelar. Ett fysiskt end-to-end-test med riktig ESP32 och Wi-Fi har ännu inte genomförts.

---

**## T18 – Stabilitetstest**

**Kopplat krav:** NF1  
**Status:** Ej genomfört

### Syfte

Verifiera att systemet kan köra under ett större antal mätcykler utan oväntat programavbrott.

Exakt antal mätcykler beslutas senare.

---

**# 10. Spårbarhet mellan krav och tester**

| Krav | Test |
|---|---|
| F1 – Lufttemperatur inne | TC-01, TC-04, TC-05, T17 |
| F2 – Lufttemperatur ute | TC-01, TC-06, TC-07, T17 |
| F3 – Vattentemperatur | TC-01, TC-08, TC-09, T17 |
| F4 – Luftfuktighet inne | TC-01, TC-02, TC-03, TC-10, TC-11, T17 |
| F5 – Återkommande mätningar | T12, T17 |
| F6 – Gemensam datastruktur | T13, T17 |
| F7 – Databehandling | T17 |
| F8 – Validering | TC-01–TC-11, T17 |
| F9 – Felhantering | TC-02, TC-04, TC-06, TC-08, TC-10, T14 |
| F10 – Kommunikation | T16, T17 |
| F11 – Strukturerat dataformat | T15, T17 |
| NF1 – Stabilitet | T12, T14, T17, T18 |

---

**# 11. Teststatus**

Nuvarande status:

| Område | Status |
|---|---|
| Native Validator-testmiljö | ✅ Klar |
| Validator automatiserade tester | ✅ 11/11 godkända |
| Native-flow integrationstestmiljö | ✅ Klar |
| B20 integrationstester | ✅ 2/2 godkända |
| D08-gränser implementerade | ✅ Klar |
| Återkommande mätningar | ✅ Verifierat med 5 cykler |
| Komplett MeasurementData | ✅ Verifierat |
| JSON/dataformat | ✅ Verifierat |
| MQTT-broker och extern subscriber | ✅ Verifierat med Docker/Mosquitto |
| ESP32 build efter B20 | ✅ SUCCESS |
| Kontrollerad felhantering över flera cykler | ⬜ Återstår som separat integrationstest |
| Fysisk ESP32 → Wi-Fi → MQTT-verifiering | ⬜ Återstår |
| Längre stabilitetstest | ⬜ Återstår |

---

**# 12. Slutsats hittills**

Projektets automatiserade Validator-testning fungerar och samtliga 11 Validator-testfall passerar.

B20 har kompletterat testningen med två programvarubaserade integrationstester. Dessa verifierar att `SensorManager`, `MeasurementData` och `Validator` fungerar tillsammans samt att flera mätcykler kan genomföras efter varandra.

MQTT-kommunikationen har dessutom verifierats med en lokal Mosquitto-broker i Docker, där ett giltigt JSON-meddelande publicerades på `microhydros/measurement` och togs emot av en extern subscriber.

Efter B20-testningen byggdes projektet åter för ESP32 med resultatet `SUCCESS`.

Det programvarubaserade huvudflödet är därmed verifierat:

```text
SensorManager
    -> MeasurementData
    -> Validator
    -> JSON
    -> MQTT
    -> externt system
```

Kvarvarande tester är framför allt kontrollerad felhantering över flera mätcykler, fysisk ESP32/Wi-Fi/MQTT-verifiering och ett längre stabilitetstest.
