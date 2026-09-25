# MicroHydros

MicroHydros är en IoT-/embeddedprototyp utvecklad för **HydroGreen Fingers AB**.

Syftet är att samla in, behandla, validera och kommunicera miljödata från en hydroponisk odlingsmiljö.

Prototypen hanterar fyra mätpunkter:

- lufttemperatur inne,
- lufttemperatur ute,
- vattentemperatur,
- relativ luftfuktighet inne.

Systemet är utvecklat med fokus på en liten, modulär och testbar arkitektur som senare kan byggas vidare med fysisk sensorhårdvara och lagring av historiska mätvärden.

---

## Funktioner

Nuvarande prototyp innehåller:

- fyra simulerade mätvärden,
- återkommande mätcykler,
- gemensam `MeasurementData`-struktur,
- validering av tekniskt rimliga mätvärden,
- kontrollerad hantering av ogiltiga mätningar,
- JSON-format för mätdata,
- Serial-output för lokal debug,
- Wi-Fi- och MQTT-kommunikation,
- återanslutningsförsök vid kommunikationsproblem,
- automatiserade Unity-tester,
- integrationstest av systemets dataflöde.

---

## Systemarkitektur

Systemets huvudsakliga dataflöde är:

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

Mer detaljerad information finns i:

```text
docs/04-architecture.md
```

---

## Teknik

Projektet använder:

- ESP32
- C++
- Arduino Framework
- PlatformIO
- Visual Studio Code
- MQTT
- Wi-Fi
- Unity Test Framework
- Docker och Mosquitto för MQTT-verifiering

MQTT-bibliotek:

```text
256dpi/MQTT
```

---

## Sensorer

Den nuvarande programvarubaserade prototypen använder simulerade sensordata.

För fysisk implementation har projektet valt följande referenssensorer:

- **SHT40** – lufttemperatur och relativ luftfuktighet inne
- **SHT40** – lufttemperatur ute
- **DS18B20** – vattentemperatur

DHT11 och DHT22 används inte.

Sensorjämförelse och motivering finns i:

```text
docs/05-sensor-comparison.md
```

---

## MeasurementData

En komplett mätning representeras av:

```cpp
struct MeasurementData {
    unsigned long timestampMs = 0;
    float airInsideC = 0.0f;
    float airOutsideC = 0.0f;
    float waterC = 0.0f;
    float humidityInsidePct = 0.0f;
    bool valid = false;
};
```

Samma struktur används genom systemets dataflöde.

---

## Validering

`Validator` kontrollerar samtliga fyra mätvärden.

Tekniska rimlighetsgränser:

| Mätvärde | Minimum | Maximum |
|---|---:|---:|
| Lufttemperatur inne | -10 °C | 60 °C |
| Lufttemperatur ute | -30 °C | 60 °C |
| Vattentemperatur | 0 °C | 50 °C |
| Relativ luftfuktighet inne | 0 % | 100 % |

Gränserna används för att identifiera tekniskt orimliga värden och ska inte tolkas som optimala odlingsförhållanden.

Om en mätning är ogiltig:

1. sätts `valid = false`,
2. en varning loggas,
3. mätningen kan fortfarande behandlas,
4. programmet fortsätter,
5. nästa mätcykel genomförs normalt.

---

## Mätintervall

Under utveckling används:

```cpp
constexpr unsigned long MEASUREMENT_INTERVAL_MS = 5000;
```

Det innebär en ny mätning var femte sekund.

Projektets normala målintervall är **60 sekunder**.

Det kortare intervallet används för att utveckling och testning ska gå snabbare.

---

## JSON-format

Mätdata konverteras till JSON innan den kommuniceras.

Exempel:

```json
{
  "timestamp_ms": 1000,
  "air_inside_c": 22.40,
  "air_outside_c": 18.70,
  "water_c": 20.10,
  "humidity_inside_pct": 55.20,
  "valid": true
}
```

---

## MQTT

Extern kommunikation sker via MQTT över Wi-Fi.

Nuvarande topic:

```text
microhydros/measurement
```

Serial används parallellt för lokal felsökning.

MQTT-flödet har verifierats med en lokal Mosquitto-broker i Docker och en extern subscriber.

---

## Wi-Fi-konfiguration

Riktiga Wi-Fi-uppgifter ska aldrig commitas till Git.

Projektet använder:

```text
include/secrets.h
```

för lokal konfiguration.

Filen ignoreras av Git.

Skapa den utifrån:

```text
include/secrets.example.h
```

Exempel:

```cpp
#pragma once

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
```

Byt exempelvärdena mot egna uppgifter lokalt.

---

## Kom igång

### 1. Klona repositoryt

```bash
git clone https://github.com/jidenius-77/HydroGreen-Fingers-AB-.git
```

Gå sedan till projektmappen.

### 2. Installera utvecklingsmiljö

Installera:

- Visual Studio Code
- PlatformIO

### 3. Skapa secrets.h

Kopiera:

```text
include/secrets.example.h
```

till:

```text
include/secrets.h
```

och lägg in lokal Wi-Fi-konfiguration.

### 4. Bygg projektet

```bash
pio run -e esp32dev
```

Alternativt kan projektet byggas genom PlatformIO-tillägget i Visual Studio Code.

### 5. Ladda upp till ESP32

Med en kompatibel ESP32 ansluten:

```bash
pio run -e esp32dev -t upload
```

### 6. Serial Monitor

Serial använder:

```text
115200 baud
```

Exempel på output:

```text
{"timestamp_ms":5000,"air_inside_c":22.50,"air_outside_c":20.25,"water_c":19.10,"humidity_inside_pct":55.50,"valid":true}
```

---

## Tester

Projektet använder Unity för automatiserade tester.

### Validator

Kör:

```bash
pio test -e native
```

Senast verifierat resultat:

```text
11 test cases: 11 succeeded
```

Tester omfattar bland annat:

- giltiga värden,
- värden under minimum,
- värden över maximum,
- exakta gränsvärden.

---

### Integrationstest

Kör:

```bash
pio test -e native-flow
```

Senast verifierat resultat:

```text
3 test cases: 3 succeeded
```

Integrationstesterna verifierar bland annat:

- komplett `MeasurementData`,
- samtliga fyra mätvärden,
- flera efterföljande mätcykler,
- validering,
- att en ogiltig mätning inte blockerar nästa mätcykel.

---

### ESP32-build

Projektet har även verifierats genom:

```bash
pio run -e esp32dev
```

med resultat:

```text
SUCCESS
```

Mer detaljerade testresultat finns i:

```text
docs/06-test-protocol.md
```

---

## Lokal MQTT-testning med Docker

En lokal Mosquitto-broker kan startas med Docker.

Konfiguration finns i:

```text
docker/mosquitto.conf
```

Exempel:

```powershell
docker run --name microhydros-mqtt -p 1883:1883 -v "${PWD}\docker\mosquitto.conf:/mosquitto/config/mosquitto.conf" eclipse-mosquitto
```

Starta en subscriber:

```powershell
docker exec -it microhydros-mqtt mosquitto_sub -h localhost -t microhydros/measurement -v
```

Detta kan användas för att verifiera MQTT-kommunikationen oberoende av övriga delar av systemet.

---

## Projektstruktur

```text
.
├── .github/
│   ├── ISSUE_TEMPLATE/
│   └── pull_request_template.md
│
├── docker/
│   └── mosquitto.conf
│
├── docs/
│   ├── 01-projectplan.md
│   ├── 02-requirements.md
│   ├── 03-backlog.md
│   ├── 04-architecture.md
│   ├── 05-sensor-comparison.md
│   ├── 06-test-protocol.md
│   ├── 07-decision-log.md
│   └── 08-demo-checklist.md
│
├── include/
│   ├── communication.h
│   ├── measurement_data.h
│   ├── sensor_manager.h
│   ├── validator.h
│   └── secrets.example.h
│
├── src/
│   ├── communication.cpp
│   ├── main.cpp
│   ├── sensor_manager.cpp
│   └── validator.cpp
│
├── test/
│   ├── stubs/
│   ├── test_data_flow/
│   └── test_validator/
│
├── .gitignore
├── CONTRIBUTING.md
├── platformio.ini
└── README.md
```

---

## Dokumentation

Projektets tekniska dokumentation finns i `docs/`.

| Dokument | Innehåll |
|---|---|
| `01-projectplan.md` | Projektplan och arbetssätt |
| `02-requirements.md` | Funktionella och icke-funktionella krav |
| `03-backlog.md` | Backlog och projektstatus |
| `04-architecture.md` | Systemarkitektur och dataflöde |
| `05-sensor-comparison.md` | Sensorjämförelse och sensorval |
| `06-test-protocol.md` | Testfall och testresultat |
| `07-decision-log.md` | Tekniska och organisatoriska beslut |
| `08-demo-checklist.md` | Checklista inför demonstration |

---

## Git-arbetssätt

Projektet använder ett branch- och Pull Request-baserat arbetsflöde.

Grundprincip:

```text
main
  |
  +-- feature/...
  +-- test/...
  +-- docs/...
```

- `main` ska hållas stabil.
- Nya uppgifter utvecklas på separata branches.
- Commits ska vara små och beskrivande.
- Pull Requests används för att integrera större ändringar.
- GitHub Issues används där det är relevant för spårbarhet.

Mer information finns i:

```text
CONTRIBUTING.md
```

---

## Kända begränsningar

Den nuvarande prototypen har följande begränsningar:

- sensordata är simulerade,
- de valda fysiska sensorerna är ännu inte integrerade i slutflödet,
- fysisk ESP32 → Wi-Fi → MQTT end-to-end-verifiering återstår,
- längre stabilitetstest återstår,
- ingen databas används för historisk lagring,
- ingen dashboard eller mobilapplikation ingår,
- MQTT-lösningen är en prototyplösning och saknar produktionsfunktioner som TLS och autentisering.

---

## Möjlig vidareutveckling

Projektet kan senare kompletteras med:

- fysisk integration av SHT40 och DS18B20,
- historisk datalagring,
- databas,
- dashboard,
- notifieringar,
- TLS och autentiserad MQTT,
- unika MQTT-topics per enhet,
- fler sensorer,
- längre stabilitetstester.

---

## Definition of Done

En uppgift räknas som klar när:

- implementationen fungerar,
- projektet bygger,
- relevanta tester passerar,
- dokumentationen är uppdaterad,
- kända begränsningar dokumenteras,
- ändringen är spårbar i Git,
- en annan utvecklare kan förstå lösningen.