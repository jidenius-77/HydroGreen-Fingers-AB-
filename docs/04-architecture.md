# Systemarkitektur – MicroHydros

## 1. Grundarkitektur

MicroHydros byggs med en liten och modulär arkitektur där datainsamling,
databehandling, validering och kommunikation hålls separerade.

```text
+----------------------------------+       +--------------------------------+
| Sensorer / simulerade datakällor |       | Embedded-system                |
|                                  | ----> | ESP32 proof-of-concept         |
| - lufttemperatur inne            |       |                                |
| - lufttemperatur ute             |       | SensorManager                  |
| - vattentemperatur               |       |       |                        |
| - luftfuktighet inne             |       |       v                        |
+----------------------------------+       | MeasurementData                |
                                           |       |                        |
                                           |       v                        |
                                           | Validator                      |
                                           |       |                        |
                                           |       v                        |
                                           | Communication                  |
                                           +---------------+----------------+
                                                           |
                                                           |
                                        vald kommunikationslösning
                                        (seriell / MQTT / annat)
                                                           |
                                                           v
                                           +--------------------------------+
                                           | Externt system                 |
                                           | PC / gateway / broker / server |
                                           +--------------------------------+
```

---

## 2. Systemets huvuddelar

### SensorManager

`SensorManager` ansvarar för att hämta de fyra mätvärden som systemet behöver:

- lufttemperatur inne,
- lufttemperatur ute,
- vattentemperatur,
- relativ luftfuktighet inne.

Under den första utvecklingsfasen kan datan komma från simulerade
datakällor.

Om fysisk hårdvara används senare ska samma del kunna läsa värden från
riktiga sensorer.

---

### MeasurementData

`MeasurementData` är den gemensamma datastrukturen för en komplett
mätning.

Strukturen ska minst kunna representera:

- lufttemperatur inne,
- lufttemperatur ute,
- vattentemperatur,
- relativ luftfuktighet inne.

Den kan även innehålla exempelvis:

- tidpunkt,
- status,
- information om mätningen är giltig eller ogiltig.

---

### Validator

`Validator` ansvarar för att kontrollera om mätvärdena verkar rimliga.

Exempel på tydligt ogiltiga värden är:

- relativ luftfuktighet under 0 %,
- relativ luftfuktighet över 100 %.

De slutliga rimlighetsgränserna bestäms och dokumenteras senare i
projektet.

Ett ogiltigt värde ska kunna hanteras utan att hela systemet avslutas.

---

### Communication

`Communication` ansvarar för att formatera och kommunicera en komplett
mätning till ett externt system.

Som ett första proof-of-concept kan seriell kommunikation användas.

Projektgruppen ska senare utvärdera och motivera vilken
kommunikationslösning som används i slutprototypen.

Möjliga alternativ är exempelvis:

- seriell kommunikation,
- MQTT,
- HTTP/REST,
- Bluetooth/BLE,
- annan relevant lösning.

---

## 3. Dataflöde

Systemets grundläggande dataflöde är:

```text
Sensorer / simulerade värden
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

Processen genomförs enligt följande:

1. `SensorManager` läser eller tar emot de fyra mätvärdena.
2. Värdena sparas i en gemensam `MeasurementData`-struktur.
3. `Validator` kontrollerar om mätvärdena verkar rimliga.
4. Mätningen markeras som giltig eller ogiltig.
5. `Communication` formaterar mätningen.
6. Mätdata kommuniceras till ett externt system.
7. Processen upprepas efter projektets valda mätintervall.

---

## 4. Exempel på dataformat

En mätning kan exempelvis representeras som:

```json
{
  "air_inside_c": 22.4,
  "air_outside_c": 18.7,
  "water_c": 20.1,
  "humidity_inside_pct": 55.2,
  "valid": true
}
```

Det slutliga formatet kan förändras under projektet.

---

## 5. Designprincip

Arkitekturen är medvetet liten och modulär.

Projektgruppen prioriterar att först skapa en stabil och begriplig
grundlösning innan extra funktioner läggs till.

Genom att separera datainsamling, datastruktur, validering och
kommunikation blir det enklare att senare:

- byta sensorer,
- byta kommunikationslösning,
- lägga till fler mätpunkter,
- ansluta flera MicroHydros-enheter,
- lagra historiska mätvärden,
- ansluta systemet till en framtida molntjänst.

---

## 6. Beslut som återstår

Följande arkitekturbeslut är ännu inte slutligt fastställda:

- vilka sensorer som ska användas,
- om slutprototypen använder fysisk hårdvara, simulering eller en kombination,
- vilken kommunikationslösning som används i slutprototypen,
- vilket mätintervall som används,
- vilka slutliga valideringsgränser som används.

Besluten dokumenteras när de fattas under projektets utveckling.