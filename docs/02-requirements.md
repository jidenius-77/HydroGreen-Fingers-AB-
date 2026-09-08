# Kravspecifikation – MicroHydros

## 1. Syfte

Detta dokument beskriver de tekniska krav som MicroHydros-prototypen ska uppfylla.

Kraven baseras på kundunderlaget, projektbeskrivningen och projektgruppens tolkning av uppdraget.

Kravspecifikationen används som grund för:

- implementation,
- prioritering,
- testning,
- dokumentation,
- demonstration,
- tekniska beslut.

Kraven kan uppdateras under projektets gång om gruppen fattar nya tekniska beslut eller om krav behöver förtydligas.

---

## 2. Prioritering

Kraven prioriteras enligt följande:

- **P0 – Måste fungera:** krävs för projektets grundprototyp.
- **P1 – Bör fungera:** förbättrar lösningen men prioriteras efter P0.
- **P2 – Kan utvecklas:** extra funktionalitet om tid finns.

Projektgruppen ska prioritera en liten och stabil lösning framför extra funktionalitet.

---

## 3. Funktionella krav

Funktionella krav beskriver vad systemet ska kunna göra.

### F1 – Lufttemperatur inne

**Beskrivning:**  
Systemet ska kunna läsa in eller ta emot ett mätvärde som representerar lufttemperaturen inne i odlingsmiljön.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när ett värde för lufttemperatur inne finns med i en komplett mätning och kan behandlas av systemet.

---

### F2 – Lufttemperatur ute

**Beskrivning:**  
Systemet ska kunna läsa in eller ta emot ett mätvärde som representerar lufttemperaturen utanför odlingsmiljön.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när ett värde för lufttemperatur ute finns med i en komplett mätning och kan behandlas av systemet.

---

### F3 – Vattentemperatur

**Beskrivning:**  
Systemet ska kunna läsa in eller ta emot ett mätvärde som representerar temperaturen i vatten eller näringslösning.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när ett värde för vattentemperatur finns med i en komplett mätning och kan behandlas av systemet.

---

### F4 – Luftfuktighet inne

**Beskrivning:**  
Systemet ska kunna läsa in eller ta emot ett värde som representerar relativ luftfuktighet inne i odlingsmiljön.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när ett värde för relativ luftfuktighet inne finns med i en komplett mätning och kan behandlas av systemet.

---

### F5 – Återkommande mätningar

**Beskrivning:**  
Systemet ska genomföra nya mätningar återkommande över tid.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när systemet kan producera flera efterföljande mätningar utan att programmet behöver startas om mellan mätningarna.

Det exakta mätintervallet bestäms senare av projektgruppen och ska motiveras.

---

### F6 – Gemensam datastruktur

**Beskrivning:**  
De fyra efterfrågade mätvärdena ska representeras tillsammans i en gemensam datastruktur.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när en komplett mätning minst innehåller:

- lufttemperatur inne,
- lufttemperatur ute,
- vattentemperatur,
- relativ luftfuktighet inne.

Mätningen kan även innehålla exempelvis:

- tidpunkt,
- status,
- information om mätningen är giltig eller ogiltig.

---

### F7 – Databehandling

**Beskrivning:**  
Mätdata ska behandlas av embedded-systemet innan informationen kommuniceras vidare.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när insamlade mätvärden går genom systemets databehandling innan de skickas till kommunikationsdelen.

---

### F8 – Validering av mätvärden

**Beskrivning:**  
Systemet ska kunna identifiera vissa felaktiga eller orimliga mätvärden.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när minst ett medvetet orimligt testvärde kan identifieras som ogiltigt.

Exempel på tydligt orimliga värden:

- relativ luftfuktighet under 0 %,
- relativ luftfuktighet över 100 %.

Slutliga rimlighetsgränser ska bestämmas och dokumenteras av projektgruppen.

---

### F9 – Kontrollerad felhantering

**Beskrivning:**  
Ett felaktigt eller orimligt mätvärde ska hanteras på ett kontrollerat sätt.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när systemet kan identifiera ett felaktigt testvärde utan att hela programmet avslutas.

Systemet ska kunna fortsätta till en senare mätcykel efter felet.

---

### F10 – Kommunikation till externt system

**Beskrivning:**  
Systemet ska kunna kommunicera mätdata från embedded-systemet till ett externt system.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när en komplett mätning kan lämna embedded-systemet genom den kommunikationslösning som projektgruppen valt.

Den slutliga kommunikationslösningen ska undersökas och motiveras.

Möjliga alternativ är exempelvis:

- MQTT,
- HTTP/REST,
- Bluetooth/BLE,
- seriell kommunikation till en gateway,
- annan relevant lösning.

---

### F11 – Strukturerad kommunikationsdata

**Beskrivning:**  
Mätdata som kommuniceras ska ha ett tydligt och konsekvent format.

**Prioritet:** P0

**Verifiering:**  
Kravet är uppfyllt när en komplett mätning kan representeras i ett strukturerat format.

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

Det slutliga dataformatet kan förändras under projektet.

---

## 4. Icke-funktionella krav

Icke-funktionella krav beskriver egenskaper hos systemet och hur lösningen ska vara utformad.

### NF1 – Stabilitet

**Beskrivning:**  
Systemet ska kunna genomföra flera mätcykler utan att krascha vid normal användning.

**Prioritet:** P0

**Verifiering:**  
Systemet körs under ett bestämt antal mätcykler och ska genomföra dessa utan oväntat programavbrott.

Det exakta antalet mätcykler för stabilitetstestet bestäms i testplanen.

---

### NF2 – Läsbar kod

**Beskrivning:**  
Källkoden ska vara strukturerad och begriplig för en annan utvecklare.

**Prioritet:** P0

**Verifiering:**  
Kodens huvudsakliga delar och ansvar ska kunna förklaras av gruppen och beskrivas i projektets tekniska dokumentation.

---

### NF3 – Modulär struktur

**Beskrivning:**  
Programmets huvudsakliga ansvarsområden ska så långt som möjligt vara separerade.

Exempel:

- datainsamling,
- datastruktur,
- validering,
- kommunikation,
- huvudflöde.

**Prioritet:** P0

**Verifiering:**  
Projektets kod och arkitektur visar tydligt separerade delar med olika ansvarsområden.

---

### NF4 – Versionshantering

**Beskrivning:**  
All programkod ska versionshanteras med Git.

**Prioritet:** P0

**Verifiering:**  
Gruppens GitHub-repository innehåller projektets kod och versionshistorik.

---

### NF5 – Spårbar utveckling

**Beskrivning:**  
Projektets utveckling och gruppmedlemmarnas bidrag ska i rimlig grad kunna följas genom GitHub.

**Prioritet:** P0

**Verifiering:**  
Repositoryt innehåller relevanta:

- commits,
- branches,
- GitHub Issues,
- Pull Requests.

---

### NF6 – Dokumentation

**Beskrivning:**  
Systemet ska dokumenteras så att en annan utvecklare kan förstå lösningens huvudsakliga uppbyggnad.

**Prioritet:** P0

**Verifiering:**  
Repositoryt innehåller relevant:

- README,
- projektplan,
- kravspecifikation,
- arkitekturbeskrivning,
- sensorval,
- testdokumentation.

---

### NF7 – Utbyggbarhet

**Beskrivning:**  
Systemets struktur ska göra det möjligt att senare byta eller lägga till sensorer och kommunikationslösningar utan att hela programmet behöver skrivas om.

**Prioritet:** P1

**Verifiering:**  
Arkitekturen separerar datainsamling från exempelvis validering och kommunikation.

---

### NF8 – Säker hantering av hemligheter

**Beskrivning:**  
Om projektet använder Wi-Fi, MQTT, API-nycklar eller andra inloggningsuppgifter får dessa inte lagras direkt i ett publikt Git-repository.

**Prioritet:** P1

**Verifiering:**  
Publik källkod ska inte innehålla riktiga lösenord, tokens eller API-nycklar.

---

## 5. Tekniska begränsningar

### R1 – DHT11 och DHT22

DHT11 och DHT22 får inte användas i prototypen.

Projektgruppen ska istället undersöka och motivera andra sensoralternativ.

---

### R2 – Sensorval ska motiveras

Valda sensorer ska bedömas utifrån relevanta tekniska egenskaper.

Exempel på faktorer:

- noggrannhet,
- upplösning,
- mätområde,
- responstid,
- kommunikationsgränssnitt,
- kostnad,
- tillgänglighet,
- strömförbrukning,
- lämplighet för miljön.

Sensorjämförelsen dokumenteras i:

`docs/05-sensor-comparison.md`

---

## 6. Beslut som återstår

Följande frågor är ännu inte slutligt beslutade och ska undersökas under projektet:

- vilka sensorer som ska användas,
- om fysisk hårdvara, simulering eller en kombination ska användas,
- vilken kommunikationslösning som ska användas i slutprototypen,
- hur ofta mätningar ska genomföras,
- vilka exakta gränsvärden som ska användas vid validering,
- hur långt stabilitetstestet ska vara.

När ett beslut fattas ska relevant krav uppdateras och beslutet dokumenteras.

---

## 7. Spårbarhet mellan krav och tester

Varje viktigt P0-krav ska senare kopplas till minst ett testfall.

Den första preliminära kopplingen är:

| Krav | Test | Syfte |
|---|---|---|
| F1 | T1 | Kontrollera lufttemperatur inne |
| F2 | T2 | Kontrollera lufttemperatur ute |
| F3 | T3 | Kontrollera vattentemperatur |
| F4 | T4 | Kontrollera luftfuktighet inne |
| F5 | T5 | Kontrollera återkommande mätningar |
| F6 | T6 | Kontrollera komplett datastruktur |
| F7 | T7 | Kontrollera databehandling |
| F8 | T8 | Kontrollera orimligt mätvärde |
| F9 | T9 | Kontrollera felhantering |
| F10 | T10 | Kontrollera extern kommunikation |
| F11 | T11 | Kontrollera strukturerat dataformat |
| NF1 | T12 | Kontrollera stabilitet över flera mätcykler |

Den slutliga testkopplingen uppdateras när `docs/06-test-protocol.md` färdigställs.