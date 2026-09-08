# Projektplan – MicroHydros

## Projektinformation

**Projekt:** MicroHydros  
**Kurs:** Projekt 1 – IoT- och embeddedutveckling  
**Omfattning:** 20 YH-poäng  
**Projektperiod:** 31 augusti – 25 september 2026  
**Arbetsform:** Projekt i team  

### Gruppmedlemmar

- Lucas
- Gayathri
- Simon
- Desmond

---

## 1. Bakgrund

HydroGreen Fingers AB är ett fiktivt företag som arbetar med småskaliga hydroponiska odlingssystem.

Företagets produktkoncept MicroHydros är tänkt att vara en kompakt hydroponisk odlingsenhet som kan användas i miljöer där traditionell odling inte är möjlig och där tillgången till naturligt solljus kan vara begränsad.

Eftersom odlingen använder bland annat artificiell belysning, elektronik och vatten kan temperatur och luftfuktighet förändras över tid. Företaget behöver därför ett system som kan samla in information om odlingsmiljön återkommande.

I ett tidigare utvecklingsprojekt användes bland annat sensorerna DHT11 och DHT22. Företaget upplevde problem med mätkvalitet, stabilitet och hur väl sensorerna passade miljön. DHT11 och DHT22 får därför inte användas i den nya prototypen.

Projektgruppen har fått i uppdrag att utveckla en första teknisk prototyp som demonstrerar hur relevanta miljödata kan samlas in, behandlas och kommuniceras till ett externt system.

---

## 2. Syfte

Syftet med projektet är att utveckla en fungerande IoT-/embeddedprototyp för MicroHydros som kan samla in och behandla relevanta miljödata från en mindre hydroponisk odlingsmiljö.

Projektet ska också demonstrera hur mätdata kan struktureras och kommuniceras från embedded-systemet till ett externt system.

Syftet är inte att utveckla en färdig kommersiell produkt, utan att ta fram en stabil och begriplig teknisk grund som kan testas, utvärderas och vidareutvecklas.

---

## 3. Projektmål

När projektet är färdigt ska prototypen kunna:

1. hantera mätvärden för lufttemperatur inne i odlingsmiljön,
2. hantera mätvärden för lufttemperatur utanför odlingsmiljön,
3. hantera mätvärden för temperatur i vatten eller näringslösning,
4. hantera mätvärden för relativ luftfuktighet inne i odlingsmiljön,
5. genomföra mätningar återkommande så att en serie mätvärden kan skapas över tid,
6. behandla mätdata i ett embedded-system,
7. identifiera och hantera vissa felaktiga eller orimliga mätvärden,
8. strukturera mätdata på ett tydligt sätt,
9. kommunicera mätdata till någon form av externt system,
10. dokumentera lösningen så att en annan utvecklare kan förstå systemets huvudsakliga uppbyggnad.

Projektet ska prioritera stabilitet, tydlighet och välmotiverade tekniska val framför extra funktionalitet.

---

## 4. Avgränsningar

Projektet omfattar en första teknisk prototyp och inte en färdig kommersiell produkt.

Följande funktioner är inte obligatoriska i projektets grundversion:

- färdig kommersiell molnplattform,
- mobilapplikation,
- avancerat webbgränssnitt,
- maskininlärning,
- automatisk bevattningsreglering,
- automatisk styrning av belysning,
- avancerade prediktionsalgoritmer,
- färdig fysisk produktdesign.

Extra funktionalitet utvecklas endast om projektets grundläggande krav först är uppfyllda och fungerar stabilt.

---

## 5. Kravspecifikation

Projektets fullständiga och testbara kravspecifikation finns i:

`docs/02-requirements.md`

De viktigaste funktionella grundkraven är att systemet ska kunna:

- hantera lufttemperatur inne i odlingsmiljön,
- hantera lufttemperatur utanför odlingsmiljön,
- hantera temperatur i vatten eller näringslösning,
- hantera relativ luftfuktighet inne i odlingsmiljön,
- genomföra mätningar återkommande,
- representera mätdata i en gemensam datastruktur,
- behandla och validera mätdata,
- hantera vissa felaktiga eller orimliga situationer,
- kommunicera mätdata till ett externt system.

Viktiga icke-funktionella krav omfattar:

- stabilitet,
- läsbar och modulär kod,
- versionshantering med Git,
- spårbar utveckling,
- dokumentation,
- möjlighet till framtida vidareutveckling.

Kravspecifikationen uppdateras vid behov när tekniska beslut fattas under projektets gång.

---

## 6. Teknisk lösning

### 6.1 Embedded-plattform och utvecklingsmiljö

Projektets nuvarande proof-of-concept använder:

- ESP32 som målplattform,
- C++,
- Arduino Framework,
- PlatformIO,
- Visual Studio Code.

Detta är projektgruppens nuvarande utvecklingsmiljö och ska utvärderas som en del av projektet.

### Beslut som behöver bekräftas

Det behöver bekräftas med läraren hur den slutliga prototypen ska demonstreras, exempelvis med fysisk hårdvara, simulering eller en kombination.

Under den tidiga utvecklingsfasen kan simulerade mätvärden användas för att testa programstruktur, databehandling, validering och kommunikationsformat.

Programstrukturen ska utformas så att datakällan senare kan bytas utan att övriga delar av systemet behöver byggas om.

---

### 6.2 Sensorer

DHT11 och DHT22 får inte användas.

Projektgruppen ska undersöka möjliga sensoralternativ innan slutligt sensorval görs.

Sensorerna ska jämföras utifrån relevanta egenskaper, exempelvis:

- noggrannhet,
- upplösning,
- mätområde,
- responstid,
- kommunikationsgränssnitt,
- kostnad,
- tillgänglighet,
- strömförbrukning,
- lämplighet för den aktuella miljön.

Sensorval och motivering dokumenteras separat i:

`docs/05-sensor-comparison.md`

---

### 6.3 Mjukvarustruktur

Programmet delas upp i flera delar med tydliga ansvarsområden.

#### Sensorhantering

Ansvarar för att ta fram de fyra mätvärden som systemet behöver. Under den första utvecklingsfasen kan värden simuleras.

#### Measurement Data

Representerar en komplett mätning och kan exempelvis innehålla:

- temperatur inne,
- temperatur ute,
- vattentemperatur,
- luftfuktighet,
- tidpunkt,
- status för mätningen.

#### Validering

Kontrollerar om mottagna mätvärden ligger inom definierade rimlighetsgränser.

#### Kommunikation

Ansvarar för att formatera och överföra mätdata till ett externt system.

#### Main

Ansvarar för programmets huvudsakliga flöde och återkommande mätcykel.

---

## 7. Kommunikation

Projektet ska demonstrera att mätdata kan lämna embedded-systemet.

Möjliga kommunikationslösningar som ska kunna övervägas är exempelvis:

- MQTT,
- HTTP/REST,
- Bluetooth/BLE,
- seriell kommunikation till en gateway,
- annan relevant kommunikationslösning.

Som ett första proof-of-concept används seriell och strukturerad utdata för att tidigt verifiera dataflödet från embedded-systemet.

Projektgruppen ska därefter utvärdera och motivera vilken kommunikationslösning som används i den slutliga prototypen.

Ett möjligt dataformat är:

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

## 8. Systemarkitektur

Den planerade grundarkitekturen är:

```text
Sensorer / simulerade datakällor
              |
              v
        Sensor Manager
              |
              v
       Measurement Data
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

Dataflödet är:

1. Mätvärden samlas in eller simuleras.
2. Värdena lagras i en gemensam datastruktur.
3. Värdena valideras.
4. Mätningen markeras som giltig eller ogiltig.
5. Informationen formateras.
6. Informationen kommuniceras vidare till ett externt system.
7. Processen upprepas vid nästa mätintervall.

Den modulära strukturen ska göra det möjligt att byta datakälla eller kommunikationslösning utan att hela programmet behöver ändras.

Ett mer detaljerat arkitekturdiagram dokumenteras i:

`docs/04-architecture.md`

---

## 9. Projektorganisation

Projektet genomförs gemensamt av:

- Lucas
- Gayathri
- Simon
- Desmond

Alla gruppmedlemmar ska delta i den tekniska utvecklingsprocessen och kunna förstå projektets övergripande lösning.

Arbetsuppgifter fördelas genom projektets backlog och GitHub Issues.

### Arbetsfördelning

| Gruppmedlem | Huvudområde | Övrigt ansvar |
|----------|-----|-----|
| Lucas    | TBD | TBD |
| Gayathri | TBD | TBD |
| Simon    | TBD | TBD |
| Desmond  | TBD | TBD |

Rollerna kan förändras under projektets gång. Ingen gruppmedlem ska enbart arbeta med dokumentation.

---

## 10. Agilt arbetssätt

Gruppen använder ett enkelt agilt arbetssätt med en gemensam prioriterad backlog.

GitHub Issues används för att beskriva arbetsuppgifter och projektets status följs exempelvis genom:

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

Gruppen följer regelbundet upp:

- vad som är färdigt,
- vad som pågår,
- vilka problem eller blockerare som finns,
- vilka uppgifter som ska prioriteras härnäst,
- hur arbetet är fördelat.

Backloggen hålls uppdaterad under projektperioden.

---

## 11. Versionshantering

Git och GitHub används för versionshantering.

`main` används som projektets stabila branch.

Nya funktioner, tester och dokumentationsändringar görs i separata branches.

Exempel:

```text
feature/data-validation
feature/communication
feature/sensor-simulation
docs/sensor-research
test/measurement-validation
fix/invalid-measurement
```

När en arbetsuppgift är klar skapas en Pull Request till `main`.

Commits ska vara små och tydligt beskriva vad som förändrats.

Exempel:

```text
Add measurement validation
Add simulated humidity measurement
Document sensor comparison
Fix invalid water temperature handling
```

När det är möjligt granskas en Pull Request av minst en annan gruppmedlem innan merge.

---

## 12. Prioriterad backlog

Den detaljerade backloggen finns i:

`docs/03-backlog.md`

### P0 – Måste fungera

1. Färdigställa projektplan och kravspecifikation.
2. Sätta upp gemensamt GitHub-repository och arbetssätt.
3. Undersöka och jämföra lämpliga sensorer.
4. Bestämma och motivera sensorval.
5. Hantera fyra efterfrågade mätpunkter.
6. Genomföra mätningar återkommande.
7. Samla mätvärden i en gemensam datastruktur.
8. Implementera validering och felhantering.
9. Kommunicera mätdata till ett externt system.
10. Genomföra och dokumentera tester.
11. Dokumentera arkitektur och tekniska beslut.
12. Färdigställa README och demonstrationsunderlag.

### P1 – Förbättringar när P0 fungerar

- förbättrad felhantering,
- längre stabilitetstest,
- förbättrad loggning,
- MQTT eller annan utökad kommunikationslösning,
- lagring av historiska mätvärden.

### P2 – Endast om tid finns

- dashboard,
- notifieringar,
- automatisk styrning,
- mer avancerad analys.

---

## 13. Tidsplan

Projektperioden är fyra veckor.

### Vecka 1 – Kravanalys, research och planering

Fokus:

- analysera kundunderlaget,
- identifiera och prioritera krav,
- skapa projektplan,
- skapa och prioritera backlog,
- påbörja sensorresearch,
- sätta upp GitHub-repository,
- testa grundläggande proof-of-concept.

Förväntat resultat:

- första version av projektplan,
- kravspecifikation,
- prioriterad backlog,
- första tekniska proof-of-concept.

### Vecka 2 – Grundläggande implementation och integration

Fokus:

- utveckla sensor- eller simuleringslösning,
- implementera de fyra mätpunkterna,
- skapa gemensam datastruktur,
- implementera återkommande mätningar,
- påbörja validering och felhantering.

Förväntat resultat:

- fungerande datainsamling eller simulering,
- fyra mätpunkter,
- grundläggande systemarkitektur.

### Vecka 3 – Kommunikation, testning och förbättring

Fokus:

- färdigställa kommunikationslösning,
- integrera systemets delar,
- testa felaktiga och orimliga värden,
- genomföra stabilitetstester,
- dokumentera resultat.

Förväntat resultat:

- fungerande kommunikationslösning,
- integrerad prototyp,
- dokumenterade tester och kända begränsningar.

### Vecka 4 – Färdigställande och överlämning

Fokus:

- sluttest,
- korrigering av fel,
- README,
- teknisk dokumentation,
- arkitekturdiagram,
- demonstration,
- muntlig överlämning,
- individuell reflektionsrapport.

Förväntat resultat:

- komplett repository,
- fungerande prototyp,
- färdig teknisk dokumentation,
- testdokumentation,
- genomförbar demonstration.

---

## 14. Riskanalys

| Risk | Sannolikhet | Konsekvens | Åtgärd |
|---|---|---|---|
| Kraven misstolkas | Medel | Hög | Kontrollera lösningen löpande mot projektbeskrivningen och kundunderlaget |
| Projektet blir för omfattande | Medel | Hög | Prioritera grundkraven före extra funktionalitet |
| Sensorval tar längre tid än planerat | Medel | Medel | Begränsa jämförelsen till relevanta alternativ och dokumentera beslut |
| Sensor ger felaktiga eller orimliga värden | Medel | Medel | Implementera validering och felhantering |
| Kommunikationslösningen fungerar inte stabilt | Medel | Hög | Börja med ett enkelt proof-of-concept och bygg vidare stegvis |
| Merge-konflikter i Git | Medel | Medel | Arbeta i separata branches, göra små commits och synka `main` regelbundet |
| Arbetsfördelningen blir ojämn | Medel | Hög | Använd GitHub Issues, Pull Requests och regelbundna avstämningar |
| Projektet tar längre tid än planerat | Medel | Hög | Prioritera kärnfunktionalitet och flytta extrafunktioner till P1/P2 |
| Kravet på fysisk hårdvara eller simulering är oklart | Medel | Medel | Bekräfta demonstrationsformen med läraren innan slutlig implementation låses |

---

## 15. Budget och resurser

### Programvara

Projektet använder i första hand kostnadsfria utvecklingsverktyg:

- Visual Studio Code,
- PlatformIO,
- Git,
- GitHub,
- C++,
- Arduino Framework.

### Hårdvara

Eventuellt behov av fysisk hårdvara bestäms efter att projektgruppen har bekräftat hur prototypen ska demonstreras och vilka tekniska val som görs.

Eventuella komponenter, antal och kostnader dokumenteras när sensor- och hårdvaruval är beslutade.

---

## 16. Testplan

Testningen ska visa att projektets viktigaste krav fungerar och att lösningen producerar rimliga resultat.

Detaljerade testresultat dokumenteras i:

`docs/06-test-protocol.md`

### 16.1 Komponenttest

Systemets delar testas separat.

Exempel:

- kan varje mätpunkt producera ett värde?
- kan Validator identifiera ett orimligt temperaturvärde?
- kan Validator identifiera ett orimligt luftfuktighetsvärde?
- kan Communication skapa korrekt strukturerad utdata?

### 16.2 Integrationstest

Flera delar testas tillsammans.

Exempel:

```text
Sensor Manager
      |
      v
Measurement Data
      |
      v
Validator
      |
      v
Communication
```

Testet ska kontrollera att samma mätdata kan röra sig genom hela kedjan.

### 16.3 Systemtest

Hela prototypen körs under flera mätcykler.

Systemtestet ska kontrollera att:

1. fyra mätvärden produceras,
2. mätningarna sker återkommande,
3. värdena behandlas och valideras,
4. felaktiga situationer hanteras på ett kontrollerat sätt,
5. mätdata kommuniceras till ett externt system,
6. systemet fortsätter fungera över flera mätcykler.

För varje dokumenterat test ska det framgå:

- vad som testades,
- hur testet genomfördes,
- förväntat resultat,
- faktiskt resultat,
- om testet blev godkänt eller inte.

---

## 17. Informationssäkerhet

Den första prototypen är främst inriktad på miljödata och hanterar inte personuppgifter som en central del av lösningen.

Om nätverkskommunikation införs ska lösenord, API-nycklar och andra hemligheter inte lagras direkt i ett publikt Git-repository.

Om MQTT, Wi-Fi, HTTP eller en molntjänst används ska gruppen även ta ställning till exempelvis autentisering och hur kommunikationen skyddas.

---

## 18. Energiförbrukning

Kundunderlaget anger inte batteridrift som ett krav för den första prototypen.

Energiförbrukning är därför inte ett primärt krav i grundversionen, men kan diskuteras som en framtida designfråga.

Om en framtida version ska vara batteridriven behöver exempelvis följande analyseras:

- hur ofta sensorer läses,
- hur ofta data skickas,
- mikrokontrollerns strömförbrukning,
- eventuell användning av sleep mode eller deep sleep.

---

## 19. Tillförlitlighet

Prototypen ska kunna hantera fel på ett kontrollerat sätt.

Exempel på situationer som ska analyseras eller testas:

- orimliga mätvärden,
- saknade eller ogiltiga mätvärden,
- kommunikationsproblem,
- fel i en enskild mätcykel.

Ett enskilt felaktigt mätvärde ska inte automatiskt göra att hela programmet avslutas.

---

## 20. Skalbarhet och framtida utveckling

MicroHydros är tänkt att i framtiden kunna bestå av flera odlingsenheter som ansluts till en gemensam digital tjänst.

Prototypens struktur ska därför så långt som möjligt separera:

- datainsamling,
- databehandling,
- validering,
- kommunikation.

Detta ska göra det enklare att i framtiden:

- lägga till eller byta sensorer,
- byta kommunikationsmetod,
- ansluta flera MicroHydros-enheter,
- lagra historiska mätvärden,
- skapa notifieringar,
- ansluta systemet till en server, broker eller molntjänst.

---

## 21. Dokumentation

Projektet dokumenteras löpande.

Repositoryt ska minst innehålla:

- `README.md`,
- projektplan,
- kravspecifikation,
- prioriterad backlog,
- arkitekturbeskrivning och arkitekturdiagram,
- sensorjämförelse och motivering,
- testdokumentation,
- teknisk beslutslogg,
- källkod.

Git-historiken, Issues och Pull Requests används också för att dokumentera projektets utveckling och gruppmedlemmarnas bidrag.

---

## 22. Definition of Done

En arbetsuppgift betraktas som färdig när:

1. implementationen eller dokumentationen är klar,
2. ändringen är testad eller granskad,
3. relevant dokumentation är uppdaterad,
4. ändringen har commitats med ett tydligt commit-meddelande,
5. Pull Request har skapats när det är relevant,
6. inga kända problem döljs,
7. ändringen kan integreras i projektets stabila version.

---

## 23. Checklista för projektets grundkrav

Innan projektet betraktas som färdigt ska gruppen kunna visa att:

- [ ] fyra efterfrågade mätpunkter kan hanteras,
- [ ] mätningar genomförs återkommande,
- [ ] mätdata behandlas av ett embedded-system,
- [ ] mätdata kan kommuniceras till ett externt system,
- [ ] systemet kan hantera någon form av felaktig eller orimlig situation,
- [ ] sensorvalen är undersökta och motiverade,
- [ ] lösningen är dokumenterad så att en annan utvecklare kan förstå huvudstrukturen,
- [ ] ett arkitekturdiagram finns,
- [ ] projektets viktigaste funktioner har testats och dokumenterats,
- [ ] Git-repositoryt visar projektets utveckling och gruppmedlemmarnas bidrag,
- [ ] gruppen kan förklara centrala tekniska beslut,
- [ ] kända begränsningar och möjliga nästa steg är dokumenterade.
