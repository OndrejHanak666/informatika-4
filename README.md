# **Informatika 4**

 Tento kurz se zaměřuje na pokročilé koncepty vývoje softwaru, od infrastruktury až po síťovou komunikaci a mobilní aplikace.

## **Cíle předmětu**

V tomto semestru se posuneme od psaní jednoduchých konzolových aplikací k tvorbě komplexních systémů. Studenti se naučí:

* Jak připravit prostředí pro běh aplikací (Virtualizace a Docker) s využitím VS Code.  
* Jak vytvořit nativní mobilní aplikaci (Android).  
* Jak psát efektivní paralelní kód (Vlákna a Synchronizace).  
* Jak propojit aplikace přes síť (Sockety a Klient-Server).

## **Organizace výuky a Hodnocení**

Předmět je koncipován jako kombinace teoretické výuky, praktických cvičení a studentských prezentací.

### **1. Rozdělení do skupin**

Skupiny pro prezentace nejsou pevně dány na celý semestr. Studenti se mohou pro každou prezentaci organicky spojovat do týmů podle zájmu o dané téma.

* **Velikost týmu:** Jednotlivec nebo skupina **maximálně 3 studentů**.
* **Počet prezentací:** Pro každý ze 4 tematických bloků musí být pokryta témata celkem **4 prezentacemi**. 
* Celkem tedy proběhne **16 prezentací** v průběhu semestru.

### **2. Prezentace**

* **Čas:** Na začátku hodiny, nebo po domluvě i mimo výuku.  
* **Délka:** 15–20 minut.  
* **Obsah:** Teoretický úvod do problematiky + **praktická ukázka** (live coding nebo demo).  
* **Povinnost:** Každý student musí aktivně vystoupit (odprezentovat téma) **minimálně 2x** za semestr. Je možné (a vítané) prezentovat vícekrát.

### **3. Závěrečný test**

Na konci semestru proběhne komplexní test pokrývající všechny 4 bloky učiva. Termín bude upřesněn po domluvě.

### **Podmínky pro splnění předmětu**

Pro úspěšné absolvování této části předmětu a předání hodnocení je nutné splnit následující:

1. **Zůčastnit se alespoň 2 prezentací** (s praktickou ukázkou).  
2. **Napsat závěrečný test na min. 50 %.**

*Výsledné hodnocení (známka) je následně stanoveno v kooperaci s kolegy na základě těchto výstupů a výsledků z dalších částí předmětu.*

## **Obsah kurzu**

Materiály jsou rozděleny do tématických bloků. Každá složka obsahuje teoretický úvod a praktické ukázky kódu.

* [**00. Předpoklady a příprava prostředí**](./00-predpoklady-priprava-prostredi)
    * Instalace a konfigurace VS Code pro práci s kontejnery.  
    * Základy práce s verzovacím systémem Git (klonování, commit, push).  
    * Příprava nástrojů: Docker Desktop, VirtualBox, Android Studio.

* [**01. Virtualizace a Kontejnerizace**](./01-virtualizace-a-kontejnerizace)
    * Rozdíl mezi emulací, virtualizací a kontejnerizací.  
    * Práce s VirtualBoxem (instalace Linux serveru).  
    * Úvod do Dockeru (Image, Container, Dockerfile, Compose).  
    * Vývoj v kontejnerech pomocí VS Code (Dev Containers).
* [**02. Vlákna a Paralelní programování**](./02-vlakna-a-synchronizace)
    * Rozdíl mezi procesem a vláknem.  
    * Problémy sdílené paměti (Race Conditions).  
    * Synchronizace pomocí Mutexů a semaforů.
* [**03. Síťová komunikace**](./03-sitova-komunikace)
    * Úvod do TCP/IP a soketů.  
    * Implementace modelu Klient-Server.  
    * Tvorba vícevláknového chatovacího serveru.
* [**04. Mobilní vývoj (Android)**](./04-mobilni-vyvoj)
    * Vývoj v Android Studio (Kotlin/Java).  
    * Tvorba uživatelského rozhraní (XML Layouts).  
    * Logika aplikace a životní cyklus aktivit.

## **Požadovaný software**

Pro úspěšné absolvování předmětu je nutné mít nainstalované následující nástroje.

| Nástroj | Účel | Odkaz ke stažení |
| :---- | :---- | :---- |
| **VS Code** | Hlavní editor kódu (Docker, C++, Python) | [code.visualstudio.com](https://code.visualstudio.com/) |
| **Git** | Verzování kódu | [git-scm.com](https://git-scm.com/) |
| **VirtualBox** | Virtualizace OS | [virtualbox.org](https://www.virtualbox.org/) |
| **Docker Desktop** | Kontejnerizace | [docker.com](https://www.docker.com/products/docker-desktop) |
| **Android Studio** | Vývoj mobilních aplikací | [developer.android.com](https://developer.android.com/studio) |
| **Kompilátor C++/Python** | Pro bloky 3 a 4 | GCC/Clang nebo Python 3.x |

## **Harmonogram výuky**

| Hodina | Téma | Poznámka |
| :---- | :---- | :---- |
| 1. | Úvod, Emulace vs Virtualizace | Úvodní hodina. Teorie: Co je emulace (QEMU, herní emulátory) vs Virtualizace (Hypervizor 1. a 2. typu). |
| 2. | Praktická virtualizace (Linux) | VirtualBox/VMware. Instalace hostovaného OS (Linux Server). Sít'ování ve VM (NAT, Bridge). |
| 3. | Úvod do Kontejnerizace | Proč Docker? Rozdíl VM vs Kontejner. Instalace Dockeru. Příkazová řádka (run, ps, stop, exec). |
| 4. | Docker Images & Dockerfile | Jak se staví image. Vrstvy (Layers). Psaní vlastního Dockerfile pro jednoduchou aplikaci (Python/Node/C++). |
| 5. | Docker Compose & Data | Persistence dat (Volumes). Propojení více kontejnerů (např. Web Server + Databáze) pomocí docker-compose.yml. |
| 6. | Úvod do Androidu | Prostředí Android Studio. Struktura projektu. Spuštění emulátoru (AVD) – vazba na téma emulace. |
| 7. | Android - Tvorba UI (Layouts) | XML design. ConstraintLayout vs LinearLayout. Tvorba formuláře. |
| 8. | Android - Logika a Životní cyklus | Propojení kódu s UI. Activity Lifecycle (onCreate, onPause...). Jednoduchá aplikace (např. Kalkulačka). |
| 9. | Procesy vs Vlákna | Teorie operačních systémů. Paralelismus vs Concurrency. Spuštění vlákna v C++ (std::thread) nebo Pythonu. |
| 10. | Vlákna: Race Conditions | Demonstrace chyby při přístupu ke sdílené proměnné (počitadlo). Vysvětlení atomických operací. |
| 11. | Synchronizace (Mutexy) | Řešení souběhu. Mutex, Lock Guard, Semaphore. Rizika (Deadlock). |
| 12. | Pokročilá synchronizace | Úloha Producent-Konzument. Podmíněné proměnné (condition_variable). |
| 13. | Úvod do Socketů | Model Klient-Server. TCP vs UDP. IP adresy a porty. První připojení. |
| 14. | Implementace Serveru | Tvorba serveru, který naslouchá na portu a přijímá spojení. |
| 15. | Víceklientský Server | Syntéza: Spojení vláken a socketů. Server obsluhující každého klienta v novém vlákně. |
| 16. | Chatovací aplikace I. | Návrh protokolu pro chat. Implementace klienta. |
| 17. | Chatovací aplikace II. | Dokončení serveru, testování komunikace mezi studenty. |
| 18. | Rezerva / Projekty | Práce na závěrečných projektech nebo test. |
| 19. | Závěr a Zápočty | Prezentace, zápočty. | 