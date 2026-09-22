# MicroHydros

Detta repository är en startmall för skolprojektet **MicroHydros**.
Målet med mallen är att ge gruppen en liten, stabil och begriplig grund som kan byggas vidare till en fungerande IoT-/embeddedprototyp.

## Projektmål

Prototypen ska som helhet kunna demonstrera att:

1. fyra efterfrågade mätpunkter kan läsas in,
2. mätningar görs återkommande,
3. mätdata behandlas av ett embedded-system,
4. mätdata kan skickas till ett externt system,
5. felaktiga/orimliga situationer hanteras,
6. lösningen är dokumenterad så att en annan utvecklare kan förstå den.

> DHT11 och DHT22 får inte användas.

## Nuvarande status i denna mall

Mallen innehåller en körbar ESP32-struktur där sensordata först **simuleras** och skickas som JSON-liknande text via seriell kommunikation.
Det gör att gruppen kan testa programstruktur, återkommande mätning, validering och kommunikationsformat innan fysisk hårdvara kopplas in.

Simulerade sensorer uppfyller **inte** den färdiga projektleveransen. De ska ersättas med gruppens valda och motiverade sensorer.

## Föreslagen teknik i startmallen

- ESP32
- C++ / Arduino framework
- PlatformIO
- Seriell kommunikation i första G-versionen
- Senare kan MQTT/HTTP/BLE läggas till om gruppen vill

Valen ovan är mallens utvecklingsstart och ska inte blandas ihop med projektets slutliga tekniska beslut. Alla slutliga val ska dokumenteras och motiveras av gruppen.

## Kom igång

1. Installera VS Code och PlatformIO.
2. Klona repositoryt.
3. Öppna projektmappen i VS Code.
4. Anslut en ESP32.
5. Bygg och ladda upp projektet.
6. Öppna Serial Monitor på `115200 baud`.

Exempel på utskrift:

```text
{"timestamp_ms":5000,"air_inside_c":22.4,"air_outside_c":20.1,"water_c":19.3,"humidity_inside_pct":55.0,"valid":true}
```

## Projektstruktur

```text
.
├── .github/
│   ├── ISSUE_TEMPLATE/
│   └── pull_request_template.md
├── docs/
│   ├── 01-projectplan.md
│   ├── 02-requirements.md
│   ├── 03-backlog.md
│   ├── 04-architecture.md
│   ├── 05-sensor-comparison.md
│   ├── 06-test-protocol.md
│   ├── 07-decision-log.md
│   └── 08-demo-checklist.md
├── include/
├── src/
├── .gitignore
├── CONTRIBUTING.md
├── platformio.ini
└── README.md
```

## Git-arbetssätt

- `main` ska alltid vara i ett fungerande skick.
- Varje uppgift görs på en separat branch.
- Exempel: `feature/water-temperature`, `feature/serial-output`, `docs/sensor-comparison`.
- Commits ska vara små och beskrivande.
- Ändringar förs in i `main` via Pull Request.
- Koppla gärna varje Pull Request till en Issue.

Se [CONTRIBUTING.md](CONTRIBUTING.md).

## Definition of Done för en uppgift

En uppgift räknas som klar när:

- koden bygger,
- funktionen är testad,
- relevant dokumentation är uppdaterad,
- inga kända fel döljs,
- en annan gruppmedlem kan förstå ändringen,
- Pull Request har granskats när det är rimligt.
