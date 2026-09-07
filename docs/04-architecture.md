# Systemarkitektur

## Första G-arkitektur

```text
+----------------------+       +------------------------+
| Fysiska sensorer     |       | Embedded-system ESP32  |
|                      | ----> |                        |
| - temp inne          |       | SensorManager          |
| - temp ute           |       | Validator              |
| - vattentemp         |       | MeasurementData        |
| - luftfuktighet inne |       | Communication          |
+----------------------+       +-----------+------------+
                                            |
                                            | seriell / senare MQTT
                                            v
                                +------------------------+
                                | Externt system         |
                                | PC / gateway / broker  |
                                +------------------------+
```

## Dataflöde

1. SensorManager läser sensorerna.
2. Värden sparas i en gemensam `MeasurementData`-struktur.
3. Validator kontrollerar om värdena verkar rimliga.
4. Communication formaterar och skickar mätningen.
5. Processen upprepas med ett definierat mätintervall.

## Viktigt

Denna arkitektur är medvetet liten. Den ska först göras stabil och begriplig innan extra funktioner läggs till.
