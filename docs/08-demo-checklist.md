# Checklista inför demonstration – MicroHydros

## 1. Funktioner som ska kunna visas eller förklaras

- [x] Fyra mätpunkter finns i systemet:
  - lufttemperatur inne,
  - lufttemperatur ute,
  - vattentemperatur,
  - relativ luftfuktighet inne.

- [x] Samtliga fyra mätvärden lagras i samma `MeasurementData`.

- [x] Återkommande mätningar är implementerade.

- [x] Flera efterföljande mätcykler har verifierats genom integrationstest.

- [x] Mätvärden valideras av `Validator`.

- [x] Ett orimligt värde kan markeras med `valid = false`.

- [x] Ett ogiltigt värde stoppar inte nästa mätcykel.

- [x] Ogiltiga mätningar loggas med:
  `WARNING: Invalid measurement detected`

- [x] Mätdata formateras som JSON.

- [x] MQTT-kommunikation är implementerad i `Communication`.

- [x] MQTT publish/subscribe har verifierats med Mosquitto i Docker och extern subscriber.

- [ ] Fysisk ESP32 → Wi-Fi → MQTT har verifierats end-to-end.

Den sista punkten är en känd begränsning.

---

## 2. Dataflöde att kunna förklara

Gruppen ska kunna förklara följande huvudflöde:

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
valid = true / false
        |
        v
Communication
        |
        v
JSON
        |
        +----> Serial debug
        |
        v
Wi-Fi / MQTT
        |
        v
MQTT Broker
        |
        v
Extern subscriber
```

Viktigt att kunna förklara:

- `SensorManager` producerar mätvärden.
- `MeasurementData` håller ihop en komplett mätning.
- `Validator` ansvarar för rimlighetskontroll.
- `main.cpp` styr mätcykeln och loggar ogiltiga mätningar.
- `Communication` skapar JSON och hanterar Serial, Wi-Fi och MQTT.

---

## 3. Sensorval

Följande sensorval ska kunna motiveras:

- [x] SHT40 för lufttemperatur och relativ luftfuktighet inne.
- [x] En andra SHT40 för lufttemperatur ute.
- [x] DS18B20 i lämplig probe för vattentemperatur.
- [x] DHT11 och DHT22 används inte.

Vid demonstrationen ska det framgå att nuvarande implementation använder simulerade sensordata och att de valda fysiska sensorerna är referenslösningen för fortsatt fysisk implementation.

Sensorjämförelsen finns i:

`docs/05-sensor-comparison.md`

---

## 4. Tester att kunna visa

### Validator

Kommando:

```bash
pio test -e native
```

Verifierat resultat:

```text
11 test cases: 11 succeeded
```

Tester visar bland annat:

- giltiga värden,
- värden utanför gränserna,
- exakta gränsvärden.

---

### Integrationstest

Kommando:

```bash
pio test -e native-flow
```

Verifierat resultat:

```text
3 test cases: 3 succeeded
```

Integrationstesterna verifierar:

- komplett mätning,
- alla fyra mätvärden,
- flera efterföljande mätcykler,
- validering,
- att en ogiltig mätning inte blockerar nästa mätcykel.

---

### ESP32-build

Kommando:

```bash
pio run -e esp32dev
```

Verifierat resultat:

```text
SUCCESS
```

---

## 5. MQTT-verifiering

MQTT-topic:

```text
microhydros/measurement
```

MQTT-flödet har verifierats med:

- lokal Mosquitto-broker i Docker,
- MQTT publisher,
- extern MQTT subscriber.

Exempel på mottagen data:

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

- [x] JSON-format verifierat.
- [x] MQTT-topic verifierat.
- [x] Extern subscriber har tagit emot data.
- [ ] Fysisk ESP32 har ännu inte verifierats i hela MQTT-kedjan.

---

## 6. Viktiga tekniska beslut att kunna förklara

- [x] ESP32 + C++ + Arduino Framework + PlatformIO.
- [x] Simulering används för att undvika att utvecklingen blockeras av hårdvara.
- [x] Gemensam `MeasurementData`.
- [x] Separat `Validator`.
- [x] Tekniska rimlighetsgränser.
- [x] JSON som dataformat.
- [x] MQTT över Wi-Fi för extern IoT-kommunikation.
- [x] Serial behålls för lokal debug.
- [x] Secrets lagras inte i Git.
- [x] Separata branches och Pull Requests används.
- [x] Automatiserade native-tester används tillsammans med ESP32-build.

Besluten finns i:

`docs/07-decision-log.md`

---

## 7. Systemarkitektur

- [x] Arkitekturdiagram finns.
- [x] Dataflödet motsvarar implementationen.
- [x] MQTT-kommunikationen framgår.
- [x] Simulerad respektive fysisk datakälla beskrivs.
- [x] Kända begränsningar är dokumenterade.

Arkitekturen finns i:

`docs/04-architecture.md`

---

## 8. Kända begränsningar

Följande ska kunna förklaras öppet:

- sensordata är simulerade i nuvarande implementation,
- SHT40 och DS18B20 är ännu inte integrerade i det slutliga fysiska dataflödet,
- fysisk ESP32 → Wi-Fi → MQTT end-to-end-verifiering återstår,
- längre stabilitetstest återstår,
- ingen databas används för historisk lagring,
- ingen dashboard eller mobilapplikation ingår,
- MQTT-lösningen är en prototyplösning och saknar exempelvis TLS och autentisering.

---

## 9. Repository och dokumentation

- [x] README beskriver projektet.
- [x] README beskriver hur projektet byggs.
- [x] README beskriver hur tester körs.
- [x] README beskriver MQTT och lokal Mosquitto-testning.
- [x] Projektplan finns.
- [x] Kravspecifikation finns.
- [x] Backlog finns.
- [x] Arkitekturdokumentation finns.
- [x] Sensorjämförelse finns.
- [x] Testprotokoll finns.
- [x] Beslutslogg finns.
- [x] Git-historik finns.
- [x] Issues och Pull Requests visar utvecklingsarbetet.

---

## 10. Förslag på demonstrationsordning

1. Förklara kort projektets syfte.
2. Visa de fyra mätpunkterna.
3. Förklara `MeasurementData`.
4. Visa systemarkitekturen.
5. Förklara `SensorManager → MeasurementData → Validator → Communication`.
6. Visa Validator-testerna.
7. Visa integrationstestet.
8. Förklara kontrollerad felhantering.
9. Visa JSON-formatet.
10. Förklara MQTT-kommunikationen och Mosquitto-testet.
11. Visa ESP32-build med `SUCCESS`.
12. Förklara sensorvalen.
13. Förklara kända begränsningar.
14. Beskriv möjlig fortsatt utveckling.
