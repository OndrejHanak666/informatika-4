# **01. Emulace: Když hardware lže**

*Tato sekce vysvětluje princip emulace a obsahuje praktickou ukázku vlastního emulátoru v Pythonu.*

## **Co je to emulace?**

Emulace je proces, kdy jeden počítačový systém (hostitel) se chová jako jiný systém (host). Emulátor musí **překládat instrukce procesoru** v reálném čase.

### **Příklad: Instrukční sady**

* Váš notebook má pravděpodobně procesor architektury **x86_64** (Intel/AMD).  
* Váš telefon má procesor architektury **ARM** (Qualcomm, MediaTek, Apple Silicon).

Pokud chcete spustit aplikaci z telefonu na notebooku, emulátor musí vzít instrukci ARM (např. "sečti registr A a B") a přeložit ji na instrukci x86 ("sečti registr EAX a EBX").

Výhoda: Můžete spustit software pro úplně jiný hardware (např. hru ze staré konzole na PC).  
Nevýhoda: Je to extrémně náročné na výkon (tzv. overhead). Každá instrukce se musí dekódovat a simulovat.

## **Kde se s tím potkáte?**

1. **Android Studio:** Pokud máte Intel procesor a stáhnete si "ARM Image" pro telefon, bude to velmi pomalé (emulace).  
2. **Rosetta 2 (Apple):** Umožňuje spouštět x86 aplikace na nových Macích s ARM čipy.  
3. **QEMU:** Univerzální emulátor pro Linux.  
4. **Herní emulátory:** GameBoy, PlayStation, atd.

## **Praktická ukázka: Vlastní CPU v Pythonu**

Abychom si dokázali, že emulátor je jen "program, který čte jiný program", napsali jsme jednoduchý emulátor fiktivního procesoru.

### **Náš fiktivní hardware**

* **Registry:** Máme dva registry A a B (malé paměťové buňky přímo v procesoru).  
* **Instrukční sada:** Náš procesor umí jen 5 příkazů (Instrukcí):

| Opcode (Kód) | Název | Popis | Příklad v kódu |
| :---- | :---- | :---- | :---- |
| `0x01` | `LOAD_A` | Načte číslo do registru A. | `[0x01, 10]` -> A = 10 |
| `0x02` | `LOAD_B` | Načte číslo do registru B. | `[0x02, 20]` -> B = 20 |
| `0x03` | `ADD` | Sečte A + B a výsledek uloží do A. | `[0x03]` -> A = A + B |
| `0x04` | `PRINT` | Vypíše aktuální hodnotu registru A. | `[0x04]` -> print(A) |
| `0xFF` | `HALT` | Zastaví procesor (konec programu). | `[0xFF]` |

### **Jak to funguje?**

Soubor `simple_cpu.py` obsahuje smyčku `while`, která:

1. **Načte** (Fetch) instrukci z paměti.  
2. **Dekóduje** (Decode) o jaké číslo jde (např. vidí `1`, ví že je to `LOAD_A`).  
3. **Vykoná** (Execute) příslušnou Python funkci.

### **Úkol**

1. Stáhněte si soubor [`simple_cpu.py`](./simple_cpu.py).  
2. Spusťte ho v terminálu: python `simple_cpu.py`.  
3. Podívejte se do kódu a zkuste změnit "program" (pole `rom`) tak, aby procesor spočítal a vypsal výsledek `50 + 50`.