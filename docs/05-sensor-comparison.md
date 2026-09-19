# Sensorjämförelse – MicroHydros

## 1. Syfte

Detta dokument jämför möjliga sensorer för MicroHydros-prototypens fyra mätpunkter:

- lufttemperatur inne i odlingsmiljön,
- lufttemperatur utanför odlingsmiljön,
- temperatur i vatten eller näringslösning,
- relativ luftfuktighet inne i odlingsmiljön.

Syftet är att projektgruppen ska kunna göra och motivera ett rimligt sensorval utifrån projektets behov.

DHT11 och DHT22 får inte användas.

---

## 2. Bedömningskriterier

Sensorerna jämförs främst utifrån:

- noggrannhet,
- mätområde,
- upplösning,
- responstid,
- kommunikationsgränssnitt,
- strömförbrukning,
- integrationskomplexitet,
- kostnad och tillgänglighet,
- lämplighet för den aktuella miljön.

Alla kriterier behöver inte väga lika tungt.

För MicroHydros bedömer gruppen att följande är särskilt viktiga:

1. **Tillförlitlighet och rimlig noggrannhet**  
   Systemet ska kunna producera stabila och trovärdiga mätvärden.

2. **Lämplighet för fuktig miljö**  
   Sensorn inne i odlingsmiljön kommer att arbeta i en miljö där luftfuktigheten kan vara relativt hög.

3. **Enkel integration**  
   Prototypen ska hållas liten och stabil. Ett digitalt gränssnitt som I²C eller 1-Wire förenklar integrationen.

4. **Tillgänglighet och kostnad**  
   Prototypen behöver inte använda den dyraste sensorn, men komponenten bör vara rimlig att få tag på och använda.

5. **Möjlighet till framtida vidareutveckling**  
   Valet bör fungera även om prototypen senare byggs ut med fler funktioner eller fler MicroHydros-enheter.

---

# 3. Lufttemperatur och luftfuktighet

För mätning inne i odlingsmiljön behövs både temperatur och relativ luftfuktighet.

En kombinerad temperatur- och luftfuktighetssensor är därför lämplig.

## 3.1 Alternativ 1 – Sensirion SHT40

SHT40 är en digital temperatur- och luftfuktighetssensor med I²C-gränssnitt.

### Viktiga egenskaper

| Egenskap | SHT40 |
|---|---|
| Luftfuktighet | 0–100 %RH |
| Typisk RH-noggrannhet | ±1,8 %RH |
| Typisk temperaturnoggrannhet | ±0,2 °C |
| Temperaturspann | -40 till +125 °C |
| RH-responstid | cirka 4 s |
| Temperaturresponstid | cirka 2 s |
| Kommunikation | I²C |
| Matningsspänning | 1,08–3,6 V |
| Genomsnittlig strömförbrukning | cirka 0,4 µA |

### Fördelar

- god noggrannhet för både temperatur och luftfuktighet,
- digitalt I²C-gränssnitt,
- låg strömförbrukning,
- litet och modernt sensorchip,
- lämpligt för integration med ESP32,
- finns i varianter med skyddande membran eller skydd.

### Nackdelar

- själva sensorkapseln behöver monteras på lämpligt breakout-kort eller kretskort,
- kondens och direkt vattenkontakt måste fortfarande undvikas,
- kan vara något dyrare än enklare alternativ.

### Miljövariant

Sensirion har även SHT40-varianter med PTFE-membran eller skydd, exempelvis SHT40-AD1F.

En sådan variant är intressant för MicroHydros eftersom membranet ger extra skydd mot partiklar och mer krävande miljöer.

---

## 3.2 Alternativ 2 – Sensirion SHT31

SHT31 är en äldre men väl etablerad digital temperatur- och luftfuktighetssensor.

### Viktiga egenskaper

| Egenskap | SHT31 |
|---|---|
| Luftfuktighet | 0–100 %RH |
| Typisk RH-noggrannhet | ±2 %RH |
| Typisk temperaturnoggrannhet | cirka ±0,2 °C |
| Temperaturspann | -40 till +125 °C |
| RH-responstid | cirka 8 s |
| Temperaturresponstid | över 2 s |
| Kommunikation | I²C |
| Matningsspänning | cirka 2,15/2,4–5,5 V beroende på variant |
| Genomsnittlig strömförbrukning | cirka 1,7 µA för digital variant |

### Fördelar

- god noggrannhet,
- beprövad sensorfamilj,
- I²C-gränssnitt,
- relativt enkel att integrera,
- finns i variant med skyddande cover.

### Nackdelar

- något långsammare responstid än SHT40,
- högre genomsnittlig strömförbrukning än SHT40,
- äldre generation än SHT4x-serien.

---

## 3.3 Alternativ 3 – Bosch BME280

BME280 mäter temperatur, luftfuktighet och lufttryck.

Tryckmätningen behövs inte för MicroHydros, men sensorn är vanlig i IoT-projekt.

### Viktiga egenskaper

| Egenskap | BME280 |
|---|---|
| Luftfuktighet | 0–100 %RH |
| RH-noggrannhet | cirka ±3 %RH |
| Temperaturområde | -40 till +85 °C |
| Temperaturnoggrannhet | cirka ±0,5 °C vid 25 °C |
| RH-responstid | cirka 1 s |
| Kommunikation | I²C eller SPI |
| Matningsspänning | 1,71–3,6 V |
| Strömförbrukning | cirka 1,8 µA vid 1 Hz för temperatur + luftfuktighet |

### Fördelar

- mäter tre storheter i samma sensor,
- stöd för både I²C och SPI,
- vanligt förekommande och lätt att hitta på breakout-kort,
- låg strömförbrukning,
- snabb luftfuktighetsrespons.

### Nackdelar

- lufttryck behövs inte i projektet,
- sämre specificerad luftfuktighetsnoggrannhet än SHT40 och SHT31,
- temperaturmätningen kan påverkas av hur sensorn monteras nära värmealstrande elektronik.

---

# 4. Jämförelse – lufttemperatur och luftfuktighet

| Egenskap | SHT40 | SHT31 | BME280 |
|---|---:|---:|---:|
| RH-noggrannhet | ±1,8 %RH | ±2 %RH | ±3 %RH |
| Temp.-noggrannhet | ±0,2 °C typ. | ±0,2 °C typ. | ±0,5 °C vid 25 °C |
| RH-responstid | ca 4 s | ca 8 s | ca 1 s |
| Kommunikation | I²C | I²C | I²C / SPI |
| Strömförbrukning | mycket låg | låg | låg |
| Fukt-/miljöskydd som variant | Ja | Ja | Inte huvudfördel |
| Integrationssvårighet | Låg | Låg | Låg |
| Extra mätning | Nej | Nej | Lufttryck |
| Bedömd lämplighet för MicroHydros | **Mycket hög** | Hög | Medel–hög |

---

## 4.1 Preliminär bedömning för luftmätning

**SHT40 bedöms preliminärt som det starkaste alternativet** för MicroHydros.

Motivering:

- bättre specificerad luftfuktighetsnoggrannhet än BME280,
- ungefär samma goda temperaturnoggrannhet som SHT31,
- lägre strömförbrukning än SHT31,
- snabbare luftfuktighetsrespons än SHT31,
- enkelt I²C-gränssnitt,
- finns i varianter med extra skydd för mer krävande miljö.

För lufttemperaturen utanför odlingsmiljön skulle en andra SHT40 kunna användas.

Det innebär att samma sensorfamilj och samma programbibliotek kan användas för både inne- och utemätning, vilket minskar integrationskomplexiteten.

Ett alternativ är att använda en enklare separat temperatursensor utanför, men det skulle introducera ytterligare en sensortyp och mer kod utan att det är nödvändigt för grundprototypen.

---

# 5. Vattentemperatur

Sensorn för vattentemperatur har andra krav än luftsensorerna.

Den viktigaste skillnaden är att själva mätpunkten behöver kunna användas i eller mot vatten/näringslösning.

---

## 5.1 Alternativ 1 – DS18B20

DS18B20 är en digital temperatursensor med 1-Wire-gränssnitt.

### Viktiga egenskaper

| Egenskap | DS18B20 |
|---|---|
| Temperaturområde | -55 till +125 °C |
| Noggrannhet | ±0,5 °C mellan -10 och +85 °C |
| Upplösning | programmerbar 9–12 bit |
| Kommunikation | 1-Wire |
| Externa komponenter | mycket få |
| Flera sensorer på samma buss | Ja |

### Fördelar

- enkel digital temperaturmätning,
- endast en dataledning behövs för 1-Wire,
- tillräcklig noggrannhet för en enkel hydroponisk prototyp,
- vanligt förekommande i temperaturprojekt,
- finns ofta som färdig inkapslad temperaturprob.

### Nackdelar

- sensorn i sig är inte automatiskt vattentät,
- en vattentät prob är en separat inkapsling och dess kvalitet beror på tillverkaren,
- lägre noggrannhet än exempelvis TMP117,
- 1-Wire kräver annan programhantering än I²C-sensorerna.

### Viktigt om "vattentät DS18B20"

När projektet beskriver en vattentät DS18B20 bör gruppen skilja på:

1. själva DS18B20-sensorchipet,
2. en färdig probe där sensorn har kapslats i exempelvis metall och tätats.

Databladets mätprestanda gäller själva sensorn. Täthet och material i en färdig probe måste bedömas utifrån den specifika produkten.

---

## 5.2 Alternativ 2 – Texas Instruments TMP117

TMP117 är en högprecisions digital temperatursensor.

### Viktiga egenskaper

| Egenskap | TMP117 |
|---|---|
| Temperaturområde | -55 till +150 °C |
| Noggrannhet | upp till ±0,1 °C mellan -20 och +50 °C |
| Upplösning | 16 bit, cirka 0,0078 °C per steg |
| Kommunikation | I²C / SMBus |
| Strömförbrukning | cirka 3,5 µA vid 1 Hz |
| Inbyggd EEPROM | Ja |

### Fördelar

- mycket hög noggrannhet,
- mycket hög upplösning,
- I²C passar bra tillsammans med exempelvis SHT40,
- låg strömförbrukning,
- väl specificerad temperaturmätning.

### Nackdelar

- sensorn är inte i sig avsedd som färdig vattentät probe,
- kräver en genomtänkt kapsling för användning i vatten,
- högre precision än vad grundprototypen sannolikt behöver,
- mer mekaniskt arbete kan krävas för en fysisk implementation.

---

## 5.3 Alternativ 3 – PT100 / PT1000

PT100 och PT1000 är resistiva platinasensorer som ofta används för noggrann temperaturmätning.

### Fördelar

- mycket stabil och välkänd mätprincip,
- hög noggrannhet är möjlig,
- finns som prober lämpade för vätskor,
- lämplig för industriella och mer avancerade lösningar.

### Nackdelar

- kräver extra elektronik eller mätinterface,
- mer komplex implementation än DS18B20,
- högre kostnad och fler komponenter,
- onödigt avancerad för en liten första prototyp om kraven inte motiverar det.

Exakt noggrannhet och mätområde beror på vald RTD-klass, probe och interface.

---

# 6. Jämförelse – vattentemperatur

| Egenskap | DS18B20 + lämplig probe | TMP117 + egen kapsling | PT100/PT1000 |
|---|---|---|---|
| Noggrannhet | God | Mycket hög | Hög–mycket hög |
| Digitalt gränssnitt | 1-Wire | I²C | Kräver interface |
| Integrationssvårighet | **Låg** | Medel | Hög |
| Vätskeprobe tillgänglig | **Vanlig** | Kräver lösning | Vanlig |
| Kostnadsnivå | Låg | Medel | Medel–hög |
| Lämplighet för enkel prototyp | **Mycket hög** | Hög | Medel |
| Framtida precision | Medel | **Mycket hög** | **Mycket hög** |

---

## 6.1 Preliminär bedömning för vattentemperatur

**DS18B20 i en verifierad och lämplig probe bedöms preliminärt som det enklaste valet för grundprototypen.**

Motivering:

- tillräcklig noggrannhet för att demonstrera systemets funktion,
- låg integrationskomplexitet,
- digital kommunikation,
- färdiga probe-lösningar är vanliga,
- mycket mindre mekanisk och elektronisk komplexitet än PT100/PT1000.

TMP117 är tekniskt mer exakt och är ett intressant alternativ om gruppen vill prioritera mätnoggrannhet och kan lösa kapslingen på ett bra sätt.

---

# 7. Preliminärt sensorförslag för MicroHydros

Följande är ett **preliminärt förslag** och inte ett slutligt gruppbeslut:

| Mätpunkt | Preliminär sensor |
|---|---|
| Lufttemperatur inne | SHT40 / SHT40 med skyddande membran |
| Luftfuktighet inne | Samma SHT40 |
| Lufttemperatur ute | En andra SHT40 |
| Vattentemperatur | DS18B20 i lämplig vattentät probe |

Detta ger en relativt liten lösning med två sensortyper:

```text
SHT40 #1
  ├─ lufttemperatur inne
  └─ luftfuktighet inne

SHT40 #2
  └─ lufttemperatur ute

DS18B20-probe
  └─ vattentemperatur
```

### Fördel med denna kombination

- endast två sensorfamiljer behöver integreras,
- tre av fyra mätvärden kan lösas med samma SHT40-familj,
- vattenmätningen kan hållas separat,
- programstrukturen blir tydlig,
- lösningen kan senare bytas ut utan att Validator eller Communication behöver skrivas om.

---

# 8. Om projektet genomförs med simulering

Om läraren bekräftar att projektet genomförs helt eller delvis med simulerade sensorer kan samma tekniska sensorval fortfarande användas som projektets **referensdesign**.

Programmet kan då simulera beteendet från:

- SHT40 för lufttemperatur och luftfuktighet,
- DS18B20 för vattentemperatur.

Det innebär att projektgruppen fortfarande kan:

- motivera realistiska komponentval,
- strukturera koden som om riktiga sensorer används,
- testa validering och felhantering,
- byta den simulerade datakällan mot riktig sensorläsning i en framtida version.

---

# 9. Risker och begränsningar

## Kondens och hög luftfuktighet

En luftfuktighetssensor bör inte utsättas för direkt vattenkontakt.

Vid en fysisk implementation behöver placering och eventuellt skydd analyseras.

En SHT40-variant med membran kan minska vissa miljörisker men ersätter inte en korrekt mekanisk design.

---

## Vattentät probe

En DS18B20 är inte automatiskt vattentät bara för att sensorchipet används.

En fysisk probe måste vara korrekt kapslad och lämpad för den aktuella vätskan.

---

## Självuppvärmning och placering

Temperatursensorer kan påverkas av värme från exempelvis:

- mikrokontroller,
- spänningsregulator,
- belysning,
- annan elektronik.

Sensorernas placering måste därför beaktas vid en fysisk prototyp.

---

## Noggrannhet i hela systemet

Databladets noggrannhet beskriver sensorns specificerade prestanda under givna förhållanden.

Den faktiska systemnoggrannheten kan även påverkas av:

- montering,
- kapsling,
- luftflöde,
- värmekällor,
- kondens,
- kvaliteten på en färdig probe.

---

# 10. Beslut som återstår

Projektgruppen behöver fortfarande besluta:

- om SHT40 ska väljas framför SHT31/BME280,
- om en skyddad SHT40-variant ska användas inne i odlingsmiljön,
- om samma sensortyp ska användas både inne och ute,
- om DS18B20 ska användas för vatten eller om högre precision motiverar TMP117/PT100,
- vilka exakta komponentmodeller eller breakout-kort som används,
- hur sensorernas placering ska lösas,
- om implementationen blir fysisk, simulerad eller en kombination.

Slutliga beslut dokumenteras i:

`docs/07-decision-log.md`

---

# 11. Preliminär rekommendation

Projektgruppens preliminära huvudspår kan vara:

**Luft inne:** SHT40, gärna variant med skyddande membran om fysisk implementation används.  
**Luft ute:** SHT40.  
**Vatten:** DS18B20 i lämplig probe.

Valet motiveras främst av:

- tillräcklig eller god mätnoggrannhet,
- enkel digital integration,
- få olika sensorfamiljer,
- låg komplexitet för en första prototyp,
- möjlighet att senare byta komponenter tack vare den modulära arkitekturen.

Detta är inte ett slutligt beslut förrän gruppen har granskat jämförelsen och dokumenterat sitt val i beslutsloggen.

---

# 12. Källor för tekniska specifikationer

Tekniska specifikationer i denna jämförelse har kontrollerats mot tillverkarnas dokumentation:

- Sensirion – SHT40 / SHT4x
  - https://sensirion.com/products/catalog/SHT40
- Sensirion – SHT40-AD1F
  - https://sensirion.com/products/catalog/SHT40-AD1F
- Sensirion – SHT31
  - https://sensirion.com/products/catalog/SHT31-DIS-B
- Bosch Sensortec – BME280
  - https://www.bosch-sensortec.com/en/products/environmental-sensors/humidity-sensors-bme280
- Analog Devices – DS18B20
  - https://www.analog.com/en/products/ds18b20.html
- Texas Instruments – TMP117
  - https://www.ti.com/product/TMP117

Priser och tillgänglighet varierar mellan återförsäljare och bör kontrolleras separat om de blir viktiga för slutligt komponentval.

