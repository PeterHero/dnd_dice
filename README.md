# Struktura aplikace

## Třídy

Pro přehlednost a celkovou funkčnost jsem rozdělil kód do tříd, kde každá třída má svůj úkol.
Třídy jsou:

### Button

Zajišťuje vnitřní logiku tlačítka - přijímá vstup od uživatele.
Lze z něj získat, zda bylo tlačítko zmáčknuté (metoda isActive) či uvolněné (wasReleased).

### Timer

Timer zajišťuje měření času. Může vrátit aktuální naměřený čas. Taky má možnost nastavení periody po které časovač "vyprší" (metoda isUp).

### Random

Zajišťuje generaci náhodných čísel pomocí vestavěných metod arduina. Lze také nastavit seed pro generaci.

### Dice

Hlavní třída, která zajišťuje nastavení počtu hodů a typ kostky. Na základě toho vygeneruje náhodné číslo pomocí třídy Random (hodí x-krát zvolenou kostkou a sečte hody). Využívá taktéž třídu Timer na měření délky generace a tu předává jako seed pro Random. To zajišťuje uniformní distribuci.

### Display

Zajišťuje výstup aplikace. Získává data od třídy Dice. Má tři módy: normal, configuration a generation.
1. normal - zobrazuje vygenerované číslo
2. configuration - zobrazuje počet hodů, respektive typ kostky ve formátu '3d6'.
3. generating - zobrazuje animaci běhající číslice 8, jako symbol, že se generuje náhodné číslo

Vnitřně používá multiplex a  využívá třídu Timer.

## Rozhodování

V jedné situaci jsem řešil, jak budu strukturovat kód. Zamýšlel jsem se, zda Display přiřadím jako vnitřní hodnotu třídě Dice, která na něj bude zapisovat. Rozhodl jsem se proti tomu a to proto, abych oddělil zodpovědnost třídy Dice jen pro to co doopravdy má dělat - "házet kostkou" - a ne vypisovat. Rozhodnutí se mi vyplatilo, protože jsem při testování bral data z Dice a vypisoval je jak na display tak přes Serial. Takto je výstupní zařízení nezávislé na logice třídy Dice.

## Moje feature - melodie

Použil jsem bzučák na shieldu, abych hrál veselou melodii, pokud hráč hodí maximum a smutnou, pokud hráč hodí minimum. Bzučák má základně jen jeden tón, takže jsem musel střídat vypnutí a zapnutí, abych vytvořil tón jiné frekvence.
Feature se implementovala do programu snadno, jen se kontroluje, zda hráč hodil maximum respektive minimum. Jen pro usnadnění kódu melodie jsem použil delay, a proto se zobrazí hozená hodnota až po dohrání melodie (to ale nevadí, protože z melodie hráč ví, co hodil).
Protože je celý zbytek programu naprogramován bez delay, tak by se "paralelizace" melodie s displayem dala řešit bez přepsání zbytku programu. Jen by se upravil vnitřní kód třídy melodie, aby kontroloval pomocí timeru změnu.