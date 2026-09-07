# Samarbetsregler

## Brancher

Skapa alltid en branch från uppdaterad `main`.

Exempel:

```bash
git switch main
git pull
git switch -c feature/inside-climate-sensor
```

Rekommenderade prefix:

- `feature/` – ny funktion
- `fix/` – buggfix
- `docs/` – dokumentation
- `test/` – tester
- `refactor/` – omstrukturering utan ändrad funktion

## Commits

Skriv små, tydliga commits.

Bra exempel:

```text
Add measurement data structure
Add validation for humidity values
Document sensor comparison criteria
Fix serial output interval
```

Undvik commits som:

```text
fix
stuff
update
all changes
```

## Pull Requests

Innan merge:

- projektet ska bygga,
- ändringen ska vara testad,
- dokumentation ska vara uppdaterad vid behov,
- beskriv vad som ändrats och varför,
- be minst en annan gruppmedlem läsa ändringen när det är möjligt.

## Gruppens ansvar

Alla medlemmar ska delta i det tekniska arbetet och kunna förklara projektets övergripande lösning.
Använd Issues, commits och Pull Requests så att individuella bidrag går att följa.
