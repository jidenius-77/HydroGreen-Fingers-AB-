# Backlog – MicroHydros

## 1. Syfte

Detta dokument innehåller projektets prioriterade backlog.

Backloggen används för att:

- bryta ner projektets krav i konkreta arbetsuppgifter,
- prioritera vad som ska göras först,
- fördela arbete mellan gruppmedlemmarna,
- skapa GitHub Issues,
- följa projektets utveckling,
- koppla implementation och testning till kravspecifikationen.

Backloggen ska hållas uppdaterad under hela projektperioden.

---

## 2. Prioritering

Arbetsuppgifterna prioriteras enligt följande:

- **P0 – Måste göras:** krävs för projektets grundprototyp.
- **P1 – Bör göras:** förbättrar kvalitet, stabilitet eller dokumentation efter att P0 fungerar.
- **P2 – Kan göras:** extra funktionalitet om tid finns.

Projektgruppen ska prioritera en liten, stabil och välmotiverad lösning framför många halvfärdiga funktioner.

---

## 3. Status

Varje backlog-item kan ha någon av följande statusar:

- **Backlog** – identifierad men ännu inte planerad.
- **To Do** – redo att påbörjas.
- **In Progress** – arbete pågår.
- **Review / Test** – implementationen är klar och väntar på granskning eller test.
- **Done** – uppgiften uppfyller projektets Definition of Done.

Exempel på arbetsflöde:

```text
Backlog
   |
   v
To Do
   |
   v
In Progress
   |
   v
Review / Test
   |
   v
Done
```

---

# 4. P0 – Grundkrav

## B01 – Färdigställ projektplan

**Kopplade krav:** NF6  
**Prioritet:** P0  
**Status:** Done  
**Ansvarig:** Lucas

**Beskrivning:**  
Färdigställ och strukturera projektplanen så att den beskriver projektets bakgrund, syfte, mål, avgränsningar, tekniska lösning, organisation, tidsplan, risker och teststrategi.

**Klart när:**

- `docs/01-projectplan.md` finns i repositoryt,
- gruppmedlemmarna är angivna,
- projektplanen är läsbar på GitHub,
- dokumentet kan uppdateras när nya beslut fattas.

---

## B02 – Färdigställ kravspecifikation

**Kopplade krav:** F1–F11, NF1–NF8, R1–R2  
**Prioritet:** P0  
**Status:** Done  
**Ansvarig:** Lucas

**Beskrivning:**  
Dokumentera projektets funktionella och icke-funktionella krav och definiera hur viktiga krav ska kunna verifieras.

**Klart när:**

- `docs/02-requirements.md` finns,
- varje viktigt krav har ett unikt ID,
- P0-kraven går att koppla till framtida testfall,
- tekniska begränsningar och öppna beslut är dokumenterade.

---

## B03 – Sätta upp gemensamt GitHub-arbetssätt

**Kopplade krav:** NF4, NF5  
**Prioritet:** P0  
**Status:** -
**Ansvarig:** -

**Beskrivning:**  
Säkerställ att gruppen använder ett gemensamt arbetssätt med branches, commits, Issues och Pull Requests.

**Klart när:**

- alla fyra gruppmedlemmar har tillgång till repositoryt,
- `main` används som stabil branch,
- nya uppgifter görs i separata branches,
- minst en GitHub Issue har skapats från backloggen,
- gruppen vet hur Pull Requests ska användas.

**Exempel på branches:**

```text
feature/measurement-data
feature/sensor-simulation
feature/data-validation
feature/communication
docs/sensor-research
test/system-flow
```

---

## B04 – Bekräfta demonstrationsform med läraren

**Kopplade krav:** beslut som återstår i kravspecifikationen  
**Prioritet:** P0  
**Status:** Done  
**Ansvarig:** Lucas

**Beskrivning:**  
Bekräfta om projektet ska demonstreras med fysisk hårdvara, simulering eller en kombination.

**Klart när:**

- gruppen har fått ett tydligt besked,
- beslutet dokumenteras i `docs/07-decision-log.md`,
- projektplan, krav och arkitektur uppdateras vid behov.

---

## B05 – Undersök sensorer för lufttemperatur och luftfuktighet

**Kopplade krav:** F1, F2, F4, R1, R2  
**Prioritet:** P0  
**Status:** On going / Done
**Ansvarig:** Grupp tillsammans

**Beskrivning:**  
Undersök lämpliga sensorer för temperatur och relativ luftfuktighet.

DHT11 och DHT22 får inte användas.

Sensoralternativ ska jämföras utifrån relevanta egenskaper, exempelvis:

- noggrannhet,
- upplösning,
- mätområde,
- responstid,
- kommunikationsgränssnitt,
- kostnad,
- tillgänglighet,
- strömförbrukning,
- lämplighet för miljön.

**Klart när:**

- minst två relevanta alternativ har jämförts,
- fördelar och nackdelar är dokumenterade,
- ett rekommenderat alternativ har föreslagits och motiverats,
- resultatet finns i `docs/05-sensor-comparison.md`.

---

## B06 – Undersök sensor för vattentemperatur

**Kopplade krav:** F3, R2  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Grupp tillsammans

**Beskrivning:**  
Undersök lämpliga lösningar för att mäta temperaturen i vatten eller näringslösning.

**Klart när:**

- minst två relevanta alternativ har jämförts,
- miljölämplighet och integrationsmöjligheter har analyserats,
- ett rekommenderat alternativ har föreslagits och motiverats,
- resultatet finns i `docs/05-sensor-comparison.md`.

---

## B07 – Besluta om sensorval

**Kopplade krav:** F1, F2, F3, F4, R1, R2  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Gruppen

**Beroende av:** B05, B06

**Beskrivning:**  
Välj vilka sensorer eller simulerade sensormodeller som ska användas i prototypen.

**Klart när:**

- gruppen har valt en lösning för samtliga fyra mätpunkter,
- valet är tekniskt motiverat,
- beslutet finns i `docs/07-decision-log.md`,
- sensorjämförelsen är uppdaterad.

---

## B08 – Skapa gemensam MeasurementData-struktur

**Kopplade krav:** F6, F7, NF3  
**Prioritet:** P0  
**Status:** Done  
**Ansvarig:** Lucas

**Beskrivning:**  
Skapa den gemensamma datastruktur som representerar en komplett mätning.

Strukturen ska minst innehålla:

- lufttemperatur inne,
- lufttemperatur ute,
- vattentemperatur,
- relativ luftfuktighet inne.

Den kan även innehålla exempelvis:

- tidpunkt,
- giltighetsstatus.

**Klart när:**

- strukturen finns i koden,
- alla fyra mätvärden kan lagras samtidigt,
- strukturen kan användas av både Validator och Communication,
- koden bygger utan fel.

**Resultat:** 
`MeasurementData` verifierad, förbättrad med säkra standardvärden och mergad via PR #2.

---

## B09 – Implementera datakälla för lufttemperatur inne

**Kopplade krav:** F1  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Lucas

**Beskrivning:**  
Implementera eller simulera ett mätvärde för lufttemperaturen inne i odlingsmiljön.

**Klart när:**

- ett temperaturvärde kan produceras,
- värdet sparas i `MeasurementData`,
- värdet kan skickas vidare till validering.

**Resultat:**  
Simulerad datakälla implementerad i `SensorManager`.  
Värdet sparas i `MeasurementData.airInsideC` och skickas vidare till `Validator`.  
Funktionen verifierades i B20-integrationstestet.

---

## B10 – Implementera datakälla för lufttemperatur ute

**Kopplade krav:** F2  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Lucas

**Beskrivning:**  
Implementera eller simulera ett mätvärde för lufttemperaturen utanför odlingsmiljön.

**Klart när:**

- ett temperaturvärde kan produceras,
- värdet sparas i `MeasurementData`,
- värdet kan skickas vidare till validering.

**Resultat:**  
Simulerad datakälla implementerad i `SensorManager`.  
Värdet sparas i `MeasurementData.airOutsideC` och skickas vidare till `Validator`.  
Verifierad i B20-integrationstestet.

---

## B11 – Implementera datakälla för vattentemperatur

**Kopplade krav:** F3  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Lucas

**Beskrivning:**  
Implementera eller simulera ett mätvärde för temperaturen i vatten eller näringslösning.

**Klart när:**

- ett temperaturvärde kan produceras,
- värdet sparas i `MeasurementData`,
- värdet kan skickas vidare till validering.

**Resultat:**  
Simulerad datakälla implementerad i `SensorManager`.  
Värdet sparas i `MeasurementData.waterC` och skickas vidare till `Validator`.  
Verifierad i B20-integrationstestet.

---

## B12 – Implementera datakälla för luftfuktighet inne

**Kopplade krav:** F4  
**Prioritet:** P0  
**Status:** DONE
**Ansvarig:** Lucas

**Beskrivning:**  
Implementera eller simulera ett mätvärde för relativ luftfuktighet inne i odlingsmiljön.

**Klart när:**

- ett luftfuktighetsvärde kan produceras,
- värdet sparas i `MeasurementData`,
- värdet kan skickas vidare till validering.

**Resultat:**  
Simulerad datakälla implementerad i `SensorManager`.  
Värdet sparas i `MeasurementData.humidityInsidePct` och skickas vidare till `Validator`.  
Verifierad i B20-integrationstestet.

---

## B13 – Implementera återkommande mätcykel

**Kopplade krav:** F5, NF1  
**Prioritet:** P0  
**Status:** DONE  
**Ansvarig:** Lucas

**Beskrivning:**  
Systemet ska kunna skapa nya mätningar återkommande utan att behöva startas om.

**Klart när:**

- flera mätningar kan genomföras efter varandra,
- alla fyra mätvärden uppdateras i varje mätcykel,
- programmet fortsätter köra mellan mätningarna,
- valt mätintervall är dokumenterat och motiverat.

**Resultat:**  
Återkommande mätcykel är implementerad i `main.cpp`.

Under utveckling används ett mätintervall på 5 sekunder.  
Systemet uppdaterar samtliga fyra mätvärden i varje cykel och fortsätter köra mellan mätningarna.

B20-integrationstestet verifierade fem efterföljande mätcykler med uppdaterad timestamp och giltiga mätvärden.

---

## B14 – Definiera rimlighetsgränser

**Kopplade krav:** F8  
**Prioritet:** P0  
**Status:** Done
**Ansvarig:** Simon

**Beskrivning:**  
Bestäm vilka värden systemet ska betrakta som tydligt felaktiga eller orimliga i prototypen.

Exempel:

- relativ luftfuktighet under 0 %,
- relativ luftfuktighet över 100 %.

**Klart när:**

- rimlighetsgränser för relevanta mätpunkter är dokumenterade,
- gruppen kan motivera gränserna,
- Validator kan använda gränserna.

---

## B15 – Implementera Validator

**Kopplade krav:** F8, F9, NF1  
**Prioritet:** P0  
**Status:** Done
**Ansvarig:** Simon / Lucas

**Beroende av:** B08, B14

**Beskrivning:**  
Implementera validering av mätvärden.

**Klart när:**

- minst ett korrekt mätvärde godkänns,
- minst ett medvetet orimligt värde markeras som ogiltigt,
- en komplett mätning får en tydlig giltighetsstatus,
- programmet kraschar inte vid ogiltiga testvärden.

---

## B16 – Implementera kontrollerad felhantering

**Kopplade krav:** F9, NF1  
**Prioritet:** P0  
**Status:** in progress 
**Ansvarig:** Lucas

**Beskrivning:**  
Säkerställ att felaktiga mätvärden inte avslutar hela programmet.

**Klart när:**

- systemet kan upptäcka ett ogiltigt värde,
- felet hanteras eller loggas på ett begripligt sätt,
- nästa mätcykel kan genomföras efter felet.

**Resultat:**  

Ogiltiga mätvärden identifieras av `Validator` och får `valid = false`.

`main.cpp` loggar:

```text
WARNING: Invalid measurement detected

---

## B17 – Utvärdera kommunikationslösning

**Kopplade krav:** F10, F11  
**Prioritet:** P0  
**Status:** To Do  
**Ansvarig:** TBD

**Beskrivning:**  
Jämför möjliga sätt att kommunicera mätdata till ett externt system.

Alternativ kan exempelvis vara:

- seriell kommunikation,
- MQTT,
- HTTP/REST,
- Bluetooth/BLE.

**Klart när:**

- minst två relevanta alternativ har diskuterats,
- gruppen har valt en lösning för slutprototypen,
- valet är motiverat,
- beslutet dokumenteras i `docs/07-decision-log.md`.

---

## B18 – Implementera strukturerat dataformat

**Kopplade krav:** F11  
**Prioritet:** P0  
**Status:** Done
**Ansvarig:** Lucas

**Beskrivning:**  
Formatera en komplett mätning i ett tydligt och konsekvent format.

Ett möjligt format är JSON:

```json
{
  "air_inside_c": 22.4,
  "air_outside_c": 18.7,
  "water_c": 20.1,
  "humidity_inside_pct": 55.2,
  "valid": true
}
```

**Klart när:**

- alla fyra mätvärden finns i output,
- formatet är konsekvent mellan mätcykler,
- giltighetsstatus kan representeras,
- output kan användas av kommunikationsdelen.

**Resultat:**

Strukturerad JSON-formatering implementerad genom
`Communication::toJson()`. Alla fyra mätvärden,
timestamp och giltighetsstatus inkluderas. Funktionen kan
återanvändas av framtida kommunikationslösningar.
Implementation verifierad med lyckad ESP32-build och mergad via PR #6.

---

## B19 – Implementera kommunikation till externt system

**Kopplade krav:** F10, F11  
**Prioritet:** P0  
**Status:** DONE 
**Ansvarig:** Lucas

**Beroende av:** B17, B18

**Beskrivning:**  
Implementera vald kommunikationslösning så att mätdata kan lämna embedded-systemet.

**Klart när:**

- en komplett mätning lämnar embedded-systemet,
- ett externt system kan ta emot eller läsa mätningen,
- gruppen kan demonstrera dataflödet,
- kommunikationslösningen är dokumenterad.

**Resultat:**  
Wi-Fi- och MQTT-kommunikation har implementerats i `Communication`.

Mätdata formateras som JSON och publiceras på topic
`microhydros/measurement`.

ESP32-projektet bygger utan fel och befintliga Validator-tester
passerar 11/11.

MQTT-flödet har verifierats med en lokal Mosquitto-broker i Docker,
där giltig JSON publicerades och togs emot av en extern subscriber.

---

## B20 – Testa komplett dataflöde

**Kopplade krav:** F1–F11, NF1  
**Prioritet:** P0  
**Status:** DONE 
**Ansvarig:** Lucas

**Beroende av:** B08–B19

**Beskrivning:**  
Genomför ett integrationstest av hela grundflödet.

```text
Datakälla
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

**Klart när:**

- alla fyra mätvärden ingår,
- värdena behandlas och valideras,
- mätningen formateras,
- mätningen kommuniceras vidare,
- flera mätcykler kan genomföras.

**Resultat:**  
Komplett programvarubaserat integrationstest genomfört.

- `SensorManager → MeasurementData → Validator` verifierat med `native-flow`.
- 2/2 integrationstester godkända.
- Fem återkommande mätcykler verifierade.
- Alla fyra mätvärden producerades och validerades.
- JSON-format och MQTT-topic verifierade.
- MQTT publish/subscribe verifierat med lokal Mosquitto-broker i Docker och extern subscriber.
- Befintliga Validator-tester passerar 11/11.
- ESP32-projektet bygger med `SUCCESS`.
- Resultaten är dokumenterade i `docs/06-test-protocol.md`.

---

## B21 – Skapa testprotokoll

**Kopplade krav:** F1–F11, NF1  
**Prioritet:** P0  
**Status:** Done
**Ansvarig:** Simon / Lucas

**Beskrivning:**  
Dokumentera hur systemets viktigaste krav testas.

För varje test ska följande finnas:

- test-ID,
- kopplat krav,
- vad som testas,
- hur testet genomförs,
- förväntat resultat,
- faktiskt resultat,
- godkänt eller underkänt.

**Klart när:**

- `docs/06-test-protocol.md` är uppdaterad,
- viktiga P0-krav har minst ett testfall,
- testresultaten kan kopplas tillbaka till `docs/02-requirements.md`.

---

## B22 – Uppdatera systemarkitektur

**Kopplade krav:** NF3, NF6, NF7  
**Prioritet:** P0  
**Status:** DONE 
**Ansvarig:** Lucas

**Beskrivning:**  
Håll arkitekturdokumentet uppdaterat när tekniska beslut fattas.

**Klart när:**

- `docs/04-architecture.md` beskriver slutprototypens huvuddelar,
- dataflödet är korrekt,
- valt kommunikationssätt framgår,
- fysisk hårdvara/simulering är korrekt beskrivet,
- arkitekturdiagrammet motsvarar implementationen.

**Resultat:**

`docs/04-architecture.md` har uppdaterats för att motsvara den slutliga prototypens implementation.

Dokumentet beskriver:

- aktuell modulär arkitektur,
- simulerade datakällor och valda fysiska sensorer,
- `SensorManager`, `MeasurementData`, `Validator` och `Communication`,
- validering och kontrollerad felhantering,
- JSON-format,
- Wi-Fi och MQTT,
- Serial-debug,
- återkommande mätcykler,
- integrationstest och kända begränsningar.

Arkitekturdiagrammet och dataflödet motsvarar den nuvarande implementationen.

---

## B23 – Dokumentera tekniska beslut

**Kopplade krav:** NF6  
**Prioritet:** P0  
**Status:** To Do  
**Ansvarig:** Gruppen

**Beskrivning:**  
Dokumentera större tekniska beslut löpande.

Exempel:

- sensorval,
- kommunikationslösning,
- mätintervall,
- valideringsgränser,
- fysisk hårdvara eller simulering.

**Klart när:**

- varje viktigt beslut har datum,
- alternativ som övervägts framgår,
- vald lösning framgår,
- en kort motivering finns i `docs/07-decision-log.md`.

---

## B24 – Färdigställ README

**Kopplade krav:** NF6  
**Prioritet:** P0  
**Status:** Backlog  
**Ansvarig:** TBD

**Beskrivning:**  
Uppdatera projektets README så att en annan utvecklare kan förstå projektets syfte och hur systemet används.

**Klart när README minst beskriver:**

- projektets syfte,
- projektets huvudfunktioner,
- hur projektet byggs eller startas,
- nödvändiga beroenden,
- grundläggande användning,
- länk eller hänvisning till teknisk dokumentation.

---

## B25 – Förbered demonstration och överlämning

**Kopplade krav:** samtliga P0-krav  
**Prioritet:** P0  
**Status:** Backlog  
**Ansvarig:** Gruppen

**Beskrivning:**  
Förbered projektets slutliga demonstration.

**Demonstrationen ska kunna visa:**

- de fyra mätpunkterna,
- återkommande mätningar,
- databehandling,
- validering eller felhantering,
- kommunikation till externt system,
- systemarkitektur,
- viktiga tekniska val,
- kända begränsningar.

**Klart när:**

- `docs/08-demo-checklist.md` är uppdaterad,
- gruppen har genomfört minst en intern testdemonstration,
- alla gruppmedlemmar kan förklara systemets huvudflöde.

---

# 5. P1 – Kvalitetsförbättringar

P1-arbete påbörjas först när P0-funktionerna fungerar.

## B26 – Längre stabilitetstest

**Kopplade krav:** NF1  
**Prioritet:** P1  
**Status:** Backlog  
**Ansvarig:** TBD

Kör systemet under en längre period eller ett större antal mätcykler och dokumentera resultatet.

---

## B27 – Förbättrad loggning

**Kopplade krav:** F9, NF1  
**Prioritet:** P1  
**Status:** Backlog  
**Ansvarig:** TBD

Lägg till tydligare loggning för exempelvis:

- mätcykler,
- felaktiga värden,
- kommunikationsfel,
- systemstatus.

---

## B28 – Utökad kommunikation

**Kopplade krav:** F10, NF7  
**Prioritet:** P1  
**Status:** Backlog  
**Ansvarig:** TBD

Om grundkommunikationen är enkel, exempelvis seriell kommunikation, kan gruppen utvärdera att komplettera med exempelvis MQTT.

---

## B29 – Lagring av historiska mätdata

**Kopplade krav:** framtida utveckling  
**Prioritet:** P1  
**Status:** Backlog  
**Ansvarig:** TBD

Undersök eller implementera enkel lagring av mätvärden över tid.

---

# 6. P2 – Extra funktionalitet

P2 genomförs endast om P0 är färdigt och gruppen har tillräckligt med tid.

## B30 – Enkel visualisering

**Prioritet:** P2  
**Status:** Backlog

Visa mätvärden i exempelvis ett enkelt webbgränssnitt eller dashboard.

---

## B31 – Notifieringar

**Prioritet:** P2  
**Status:** Backlog

Undersök hur framtida system skulle kunna varna vid exempelvis onormal temperatur.

---

## B32 – Flera MicroHydros-enheter

**Prioritet:** P2  
**Status:** Backlog

Undersök hur flera enheter skulle kunna identifieras och skicka data till samma externa tjänst.

---

## B33 – Automatisk styrning

**Prioritet:** P2  
**Status:** Backlog

Undersök framtida styrning av exempelvis belysning eller bevattning.

Detta är inte ett krav för grundprototypen.

---

# 7. Rekommenderade första GitHub Issues

Följande backlog-items är lämpliga att skapa som gruppens första GitHub Issues:

1. **B03 – Sätta upp gemensamt GitHub-arbetssätt**
2. **B04 – Bekräfta demonstrationsform med läraren**
3. **B05 – Undersök sensorer för lufttemperatur och luftfuktighet**
4. **B06 – Undersök sensor för vattentemperatur**
5. **B08 – Skapa gemensam MeasurementData-struktur**
6. **B17 – Utvärdera kommunikationslösning**
7. **B23 – Dokumentera tekniska beslut**

Varje GitHub Issue bör innehålla:

- backlog-ID,
- beskrivning,
- kopplade krav,
- acceptance criteria / "Klart när",
- ansvarig person,
- eventuell branch.

---

# 8. Arbetsfördelning

Gruppen består av:

- Lucas
- Gayathri
- Simon
- Desmond

Arbetsuppgifter tilldelas löpande genom GitHub Issues.

Alla gruppmedlemmar ska delta i det tekniska utvecklingsarbetet och kunna förstå projektets övergripande lösning.

Ingen person ska enbart arbeta med dokumentation.

En person kan ha huvudansvar för en uppgift, men gruppen ska använda code review, tester och gemensamma avstämningar för att sprida kunskap om systemet.

---

# 9. Definition of Ready

En uppgift är redo att flyttas till **To Do** när:

- syftet med uppgiften är tydligt,
- kopplade krav är identifierade när det är relevant,
- det finns tydliga kriterier för när uppgiften är klar,
- nödvändiga tidigare beslut eller beroenden är hanterade,
- en gruppmedlem kan påbörja arbetet utan att behöva gissa vad som ska göras.

---

# 10. Definition of Done

En backlog-uppgift betraktas som **Done** när:

1. implementationen eller dokumentationen är färdig,
2. kriterierna under **Klart när** är uppfyllda,
3. arbetet är testat eller granskat,
4. relevant dokumentation är uppdaterad,
5. ändringen är commitad med ett tydligt commit-meddelande,
6. Pull Request har skapats när det är relevant,
7. eventuella kända begränsningar är dokumenterade,
8. ändringen kan integreras i projektets stabila version.

---

# 11. Underhåll av backloggen

Backloggen är ett levande dokument och ska uppdateras under projektet.

Gruppen bör regelbundet:

- ändra status på pågående uppgifter,
- tilldela ansvariga personer,
- lägga till nya uppgifter när behov upptäcks,
- flytta mindre viktiga funktioner till P1 eller P2 vid tidsbrist,
- dokumentera blockerare,
- kontrollera att P0 fortfarande prioriteras,
- kontrollera att avslutade uppgifter kan kopplas till projektets krav och testning.

GitHub Issues används för det dagliga arbetet. `docs/03-backlog.md` används som den övergripande och dokumenterade bilden av projektets backlog.
