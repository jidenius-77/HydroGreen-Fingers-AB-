# Projektplan – MicroHydros

## 1. Sammanfattning av uppdraget

Gruppen ska utveckla en första fungerande IoT-/embeddedprototyp för MicroHydros. Systemet ska samla in miljödata från en mindre hydroponisk odlingsmiljö och demonstrera att mätdata kan lämna embedded-systemet.

## 2. Projektmål

- Mäta lufttemperatur inne i odlingsmiljön.
- Mäta lufttemperatur utanför odlingsmiljön.
- Mäta temperatur i vatten/näringslösning.
- Mäta relativ luftfuktighet inne i odlingsmiljön.
- Utföra mätningarna återkommande.
- Behandla mätdata i embedded-systemet.
- Kommunicera mätdata till ett externt system.
- Hantera minst några orimliga/felaktiga mätsituationer.
- Dokumentera arkitektur, komponentval, kommunikation och tester.

## 3. Avgränsningar

Följande ingår inte i första G-versionen om tid inte finns:

- kommersiell molnplattform,
- mobilapp,
- avancerat webbgränssnitt,
- maskininlärning,
- automatisk bevattningsreglering,
- automatisk belysningsstyrning,
- avancerade prediktionsalgoritmer.

## 4. Arbetsform

Vi använder en enkel Kanban-liknande process med GitHub Issues/Project Board:

- Backlog
- Ready
- In progress
- Review/Test
- Done

## 5. Arbetsfördelning

Fylls i av gruppen.

| Medlem | Huvudansvar | Tekniska uppgifter | Dokumentationsuppgifter |
|---|---|---|---|
| Namn 1 | TBD | TBD | TBD |
| Namn 2 | TBD | TBD | TBD |
| Namn 3 | TBD | TBD | TBD |

Alla ska delta i tekniskt arbete och förstå systemets helhet.

## 6. Övergripande tidsplan

### Vecka 1
Kravanalys, research, planering, sensorjämförelse och första proof-of-concept.

### Vecka 2
Sensorintegration, återkommande datainsamling och grundläggande arkitektur.

### Vecka 3
Kommunikation, felhantering, tester, stabilisering och dokumentation.

### Vecka 4
Sluttest, dokumentation, demonstration och individuell reflektion.

## 7. Projektrisker

| Risk | Sannolikhet | Konsekvens | Åtgärd |
|---|---|---|---|
| Sensor levererar instabila värden | Medel | Hög | Testa tidigt och jämför med referens |
| Sensor passar inte fuktig/våt miljö | Medel | Hög | Kontrollera kapsling och datablad före val |
| Hårdvara blir försenad | Medel | Hög | Beställ tidigt och behåll simulerad testväg |
| Kommunikationslösning blir instabil | Medel | Medel | Börja med seriell kommunikation, bygg vidare stegvis |
| Merge-konflikter | Medel | Medel | Små branches, små PR:er och ofta synkad main |
| För mycket extrafunktioner | Medel | Hög | Prioritera G-krav före all extra funktionalitet |
