# **Blok 2: Vlákna a Paralelizace**

V tomto bloku se zaměříme na to, jak naučit naše programy dělat více věcí současně. To je naprosto klíčové pro náš **Chatovací Server**, který musí umět obsloužit desítky uživatelů najednou, aniž by se zasekl.

## **1. Teoretické podklady**

Teorie k vláknům, procesům a synchronizaci je pokryta v externích materiálech. Předtím, než začnete programovat server, nastudujte si následující:

### **C++ (Backend)**

* **[Odkaz na materiály C++ Vlákna](https://github.com/TomasRacil/informatika-2/tree/master/03-pokrocile-cpp/18-vlakna-a-paralelni-programovani)**  
* *Klíčová slova:* `std::thread`, `join`, `detach`, `std::mutex`, `std::lock_guard`, Race Condition.

### **Python (Prototypování/Skripty)**

* **[Odkaz na materiály Python Threading]** *(Bude doplněno)*  
* *Klíčová slova:* `threading`, `GIL` (Global Interpreter Lock).

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