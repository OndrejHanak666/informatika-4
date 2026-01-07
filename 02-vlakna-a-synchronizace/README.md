# **Blok 2: Vlákna a Paralelizace**

V tomto bloku se zaměříme na to, jak naučit naše programy dělat více věcí současně. To je naprosto klíčové pro náš **Chatovací Server**, který musí umět obsloužit desítky uživatelů najednou, aniž by se zasekl.

## **1. Teoretické podklady pro studium (Definitivní přehled)**

Tato sekce obsahuje vyčerpávající rozbor témat pro pochopení paralelního programování, správy paměti a interakce s hardwarem.

### **1.1 Hierarchie: Proces vs. Vlákno**

Pro pochopení paralelizace musíme začít u toho, jak operační systém (OS) spravuje běžící programy.

*   **Proces (Process):**
    *   **Definice:** Proces je "kontejner" pro běžící aplikaci. Z pohledu OS je to jednotka vlastnící zdroje (paměť, otevřené soubory, socket connecty).
    *   **Izolace paměti (Virtual Address Space):** Každý proces má iluzi, že vlastní celou paměť RAM (např. adresy `0x0000` až `0xFFFF`). Ve skutečnosti OS pomocí **MMU (Memory Management Unit)** mapuje tyto virtuální adresy na fyzické adresy v RAM (stránkování). Pokud proces sáhne mimo svůj přidělený prostor, CPU vyvolá výjimku a OS proces ukončí (**Segmentation Fault**).
    *   **Struktura paměti procesu:**
        *   **Code Segment:** Strojový kód (instrukce), obvykle Read-Only.
        *   **Data Segment:** Globální a statické proměnné.
        *   **Heap (Halda):** Dynamicky alokovaná paměť (`new`, `malloc`), sdílená pro celý proces.
        *   **Stack (Zásobník):** Lokální proměnné a návratové adresy funkcí.
    *   **Režie:** Vytvoření procesu je "drahé" (trvá milisekundy), protože OS musí vytvořit nové stránkovací tabulky a kernelové struktury.

*   **Vlákno (Thread):**
    *   **Definice:** Vlákno je "lehká" jednotka vykonávání kódu *uvnitř* procesu.
    *   **Sdílení:** Vlákna v jednom procesu **sdílejí Code, Data a Heap**. Pokud jedno vlákno změní globální proměnnou, druhé to okamžitě vidí.
    *   **Privátní data:** Každé vlákno má vlastní **Stack** (aby mohlo volat funkce nezávisle) a sadu **Registrů** (aby CPU vědělo, kde ve vykonávání vlákno skončilo).
    *   **Výhoda:** Vytváření a přepínání vláken je řádově rychlejší než u procesů.

### **1.2 Interakce s hardwarem a OS**

Jak se tisíce vláken vejdou na procesor s 8 jádry?

*   **OS Scheduler (Plánovač):**
    *   Komponenta jádra (Kernel), která rozhoduje, *kdo* poběží a *jak dlouho*.
    *   **Time Slicing (Časová kvanta):** Každé vlákno dostane příděl času (např. 10 ms). Pokud neskončí, OS ho násilně přeruší (**Preempce**) a pustí jiné vlákno.
    *   **Stavy vlákna:**
        1.  **Running:** Aktuálně běží na fyzickém jádře CPU.
        2.  **Ready:** Připraveno běžet, ale čeká ve frontě na volné jádro.
        3.  **Blocked/Waiting:** Čeká na externí událost (disk, síť, zámek) a nespotřebovává CPU.

*   **Context Switch (Přepnutí kontextu):**
    *   Okamžik, kdy OS vymění běžící vlákno A za vlákno B.
    *   **Cena:** OS musí uložit registry vlákna A do RAM a načíst registry vlákna B.
    *   **Thread vs Process switch:** Přepnutí mezi vlákny téhož procesu je rychlé. Přepnutí mezi procesy je pomalé, protože se musí "vypláchnout" TLB cache (mapování paměti), což zpomalí následný přístup k RAM.

*   **Cache Coherency (Sdílení cache):**
    *   Každé jádro má vlastní super-rychlou paměť (**L1/L2 Cache**).
    *   Pokud vlákno A na jádře 1 změní data, která má v cache i vlákno B na jádře 2, musí se cache synchronizovat. To je velmi pomalé. Proto se snažíme vlákna "vázat" k jádrům (**Processor Affinity**).

### **1.3 Problémy souběhu a synchronizace**

Paralelní programování přináší nové typy chyb, které se špatně ladí, protože nejsou deterministické (objevují se náhodně).

1.  **Race Condition (Souběh):**
    *   Nastane, když více vláken přistupuje k paměti a alespoň jedno zapisuje, bez synchronizace.
    *   *Příklad:* `i++` není jedna instrukce, ale tři: (1) Načti `i` do registru, (2) Přičti 1, (3) Ulož zpět. Pokud se vlákna přepnou mezi krokem 1 a 3, data se ztratí.
2.  **Deadlock (Uváznutí):**
    *   Vlákno A drží Zámek 1 a čeká na Zámek 2. Vlákno B drží Zámek 2 a čeká na Zámek 1. Nikdy se nedočkají.
    *   *Coffmanovy podmínky:* Aby nastal deadlock, musí platit: (1) Mutual Exclusion, (2) Hold and Wait, (3) No Preemption (zámek nelze sebrat), (4) Circular Wait.
3.  **Livelock:**
    *   Vlákna nejsou zablokovaná, ale neustále "uhýbají" jedno druhému a neudělají žádnou užitečnou práci (jako dva lidé na chodníku).
4.  **Starvation (Hladovění):**
    *   Vlákno s nízkou prioritou se nikdy nedostane k CPU, protože stále přicházejí vlákna s vyšší prioritou.

### **1.4 IPC (Inter-Process Communication)**

Jelikož procesy nevidí do své paměti, pro výměnu dat musíme použít služby OS:

*   **Shared Memory (Sdílená paměť):** OS mapuje stejný kus fyzické RAM do adresního prostoru dvou procesů. Je to nejrychlejší metoda (žádné kopírování), ale vyžaduje složitou synchronizaci (Mutexy ve sdílené paměti).
*   **Pipes (Roury):** Standardní Unixový mechanismus (`|`). Jednosměrný tok bytů z procesu A do procesu B.
*   **Sockets (Sockety):** Umožňují komunikaci i mezi procesy na různých počítačích. (Viz Blok 3).
*   **Signals (Signály):** Jednoduché notifikace (např. SIGINT při Ctrl+C). Nenesou data, jen informaci "něco se stalo".

### **1.5 Asynchronní programování a Event Loop**

Jak obsloužit 10 000 spojení, když nemůžeme mít 10 000 vláken (došla by RAM)?

*   **Blokující vs. Neblokující I/O:**
    *   **Blokující:** Volání `read()` zastaví vlákno, dokud nepřijdou data.
    *   **Neblokující:** Volání `read()` se vrátí okamžitě. Buď jsou data, nebo vrátí chybu `EAGAIN` ("zkus to později").
*   **Event Loop (Smyčka událostí):**
    *   Jádro asynchronní aplikace. Používá systémová volání (**epoll** na Linuxu, **kqueue** na macOS, **IOCP** na Windows), která umí uspat vlákno a probudit ho, až když se *na některém* z tisíce socketů něco stane.
*   **Korutiny (Coroutines):**
    *   Umožňují psát asynchronní kód, který vypadá jako sekvenční (`await`).
    *   **Stackless (C++20, JS, C#):** Korutina nemá vlastní stack, její stav je uložen v malém objektu na haldě. Extrémně úsporné na paměť.
    *   **Stackful (Go, Java fibers):** Každá "korutina" má malý dynamický stack.

### **1.6 Studijní materiály (detaily a ukázky)**

*   **C++:** 
    *   [Vlákna a Mutexy](../03-pokrocile-cpp/18-vlakna-a-paralelni-programovani/)
    *   [Sdílená paměť a IPC](../03-pokrocile-cpp/19-sdilena-pamet/)
    *   [Asynchronní C++ (Async/Future/Korutiny)](../03-pokrocile-cpp/21-asynchronni-programovani/)
*   **Python:**
    *   [Threading a GIL](../05-pokrocily-python/16-vlakna/)
    *   [Multiprocessing](../05-pokrocily-python/17-multiprocessing/)
    *   [AsyncIO Základy](../05-pokrocily-python/20-uvod-asyncio/)

## **2. Praktický Projekt: Chatovací Server**

Cílem tohoto bloku je vytvořit **kostru serveru**, který dokáže běžet ve více vláknech. Zatím nemusíme řešit složitý síťový protokol (to doladíme v dalším bloku), ale musíme vyřešit **architekturu a bezpečnost dat**.

### **Zadání úlohy**

Vytvořte konzolovou aplikaci (v C++), která simuluje chování serveru.

**Požadavky:**

1. **Hlavní vlákno (Listener):**  
   * Simuluje přijímání nových klientů.  
   * V nekonečné smyčce "čeká" (např. sleep) a generuje nové uživatele.  
2. **Vlákna klientů (Workers):**  
   * Pro každého připojeného uživatele vytvořte **nové vlákno**.  
   * Toto vlákno bude simulovat aktivitu uživatele (např. každou sekundu napíše zprávu "Ahoj, já jsem klient ID: 5").  
3. **Sdílená paměť (Kritická sekce):**  
   * Server si musí udržovat globální seznam všech připojených uživatelů (`std::vector`).  
   * **Problém:** Co se stane, když se jeden uživatel připojuje (zápis do vectoru) a druhý se zrovna odpojuje (mazání z vectoru)?  
   * **Úkol:** Zabezpečte tento seznam pomocí **Mutexu**, aby nedošlo k pádu aplikace (Race Condition).

### **Očekávaný výstup**

Program by měl vypisovat log, kde se míchají zprávy od různých vláken, ale nesmí spadnout na chybu paměti ("Segmentation Fault").

```
[Main] Server běží...  
[Main] Připojen klient ID: 1  
[Client 1] Posílá zprávu...  
[Main] Připojen klient ID: 2  
[Client 2] Posílá zprávu...  
[Client 1] Posílá zprávu...  
...
```

## **3. Řešení**

Vzorové řešení v jazyce C++ naleznete v přiložených souborech.

* [**Řešení: Multi-threaded Server**](./reseni.cpp)
  * Obsahuje ukázku použití std::thread pro obsluhu klientů.
  * Ukazuje správné uzamčení sdílených dat pomocí `std::mutex`.