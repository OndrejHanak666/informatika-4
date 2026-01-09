# **Blok 3: Síťová komunikace a Deployment**

Máme aplikaci, která umí běžet ve více vláknech (Blok 2). Máme prostředí, kde ji můžeme spustit (Blok 1). Teď to musíme propojit.

V tomto bloku přeměníme naši "hluchou a slepou" konzolovou aplikaci na skutečný **Chatovací Server**, ke kterému se bude moci připojit kdokoli z lokální sítě (a později i z internetu).

## **1. Teoretické podklady pro studium (Definitivní přehled)**

Tato sekce detailně rozebírá principy síťové komunikace, od fyzických vrstev až po modely obsluhy tisíců klientů.

### **1.1 Hierarchie sítě: ISO/OSI vs. TCP/IP**

Síťová komunikace je složitá, proto ji dělíme do vrstev. Každá vrstva řeší jeden konkrétní problém a data z vyšší vrstvy "obalí" svou hlavičkou (**Zapouzdření/Encapsulation**).

1.  **Aplikační vrstva (L7 - Application):**
    *   **Účel:** Rozhraní pro uživatelské programy. Data zde mají význam (HTML stránka, JSON objekt, obrázek).
    *   **Protokoly:** HTTP (web), SMTP (mail), SSH (terminál), nebo váš vlastní protokol pro Chat (např. "Každá zpráva končí znakem `\n`").
2.  **Transportní vrstva (L4 - Transport):**
    *   **Účel:** Doručit data správné aplikaci na cílovém počítači.
    *   **Adresování:** **Port** (číslo 0-65535). Např. webserver naslouchá na portu 80, váš chat na 8080.
    *   **TCP (Transmission Control Protocol):** "Telefonní hovor". Naváže spojení, garantuje doručení a pořadí dat. Pomalé, ale spolehlivé.
    *   **UDP (User Datagram Protocol):** "Pohlednice". Pošlete data a nevíte, jestli dorazí. Rychlé, vhodné pro hry a streaming.
3.  **Síťová vrstva (L3 - Network):**
    *   **Účel:** Doručit paket z počítače A na počítač B  přes celý internet (**Routing**).
    *   **Adresování:** **IP Adresa** (např. `192.168.1.1` nebo `2001:db8::1`).
4.  **Linková vrstva (L2 - Data Link):**
    *   **Účel:** Poslat data po kabelu/Wi-Fi k nejbližšímu routeru (**Switching**).
    *   **Adresování:** **MAC Adresa** (fyzická adresa síťové karty).

### **1.2 Anatomie a životní cyklus Socketu**

**Socket** je "dveře" do sítě. Z pohledu programátora je to soubor (File Descriptor), do kterého zapisujeme (`send`) a ze kterého čteme (`recv`).

**Unikátnost spojení (Tuple):**
Každé TCP spojení je v operačním systému identifikováno pěticí hodnot. Pokud se jediná liší, jde o jiné spojení:
`{ Protokol (TCP), Zdrojová IP, Zdrojový Port, Cílová IP, Cílový Port }`

**Stavy TCP spojení (State Machine):**
1.  **LISTEN (Server):** Server zavolá `listen()` a pasivně čeká.
2.  **3-Way Handshake (Navázání):**
    *   *Klient:* Pošle paket **SYN** ("Chci se spojit").
    *   *Server:* Přijme SYN, pošle **SYN-ACK** ("Ok, souhlasím").
    *   *Klient:* Pošle **ACK** ("Potvrzuji spojení").
    *   *Výsledek:* Stav **ESTABLISHED**. Nyní tečou data.
3.  **Přenos dat:** Data se kouskují do paketů. Každý paket musí být druhou stranou potvrzen (ACK). Pokud potvrzení nepřijde, odesílá se znovu.
4.  **Ukončení (Teardown):**
    *   Jedna strana pošle **FIN**. Druhá potvrdí **ACK** a pošle vlastní **FIN**.
    *   **TIME_WAIT:** I po uzavření spojení si OS pamatuje "tady bylo spojení" ještě cca 60 sekund. Důvod: Kdyby se v síti toulal zpožděný paket ze starého spojení, nesmí ho OS omylem přiřadit novému spojení na stejném portu.

### **1.3 Endianita (Network Byte Order)**

Procesor a síťová karta se nemusí shodnout na tom, jak uložit číslo do paměti.

*   **Little-Endian (Intel/AMD, ARM):** Nejméně významný bajt (LSB) je na nejnižší adrese.
    *   Číslo 8080 (`0x1F90`) je v RAM uloženo jako: `[0x90, 0x1F]`.
*   **Big-Endian (Síťový standard):** Nejvýznamnější bajt (MSB) je první. Stejně jako píšeme čísla na papír.
    *   Číslo 8080 (`0x1F90`) musí po kabelu letět jako: `[0x1F, 0x90]`.

**Ponaučení:** Nikdy neposílejte `int` přímo přes `send()`. Vždy použijte konverzní funkce:
*   `htons(8080)` (Host To Network Short) -> přehodí bajty pro port.
*   `htonl(ip)` (Host To Network Long) -> přehodí bajty pro IP adresu.

### **1.4 Modely škálování: Problém C10k**

Jak napsat server, který obslouží 10 000 klientů současně?

1.  **Process-per-Client (Starý Apache):**
    *   Co klient, to nový proces (`fork`).
    *   *Problém:* Extrémní režie RAM a CPU. Neškáluje nad stovky klientů.
2.  **Thread-per-Client (Klasické vlákna):**
    *   Co klient, to vlákno (`pthread_create`, `std::thread`).
    *   *Problém:* Každé vlákno potřebuje vlastní Stack (cca 1–8 MB). Pro 10 000 klientů potřebujete desítky GB RAM jen na prázdné zásobníky! Navíc přepínání kontextu mezi 10k vlákny zabije CPU.
3.  **I/O Multiplexing (Event-Driven - NGINX, Node.js):**
    *   Jediné vlákno používá systémové volání **`epoll`** (Linux) nebo **`kqueue`** (BSD).
    *   Řekne OS: "Tady mám 10 000 socketů. Uspi mě a vzbuď mě, až na *kterémkoliv* z nich přijdou data."
    *   *Výhoda:* Nulová režie na "čekání". Spotřeba RAM je minimální. Zvládne statisíce spojení.
4.  **Asynchronní I/O (Async/Await):**
    *   Moderní jazykový konstrukt, který skrývá složitost `epoll`.
    *   V Pythonu (`asyncio`) nebo C++20 (`co_await`) píšete kód, který vypadá sekvenčně, ale na pozadí se "uspává" a uvolňuje vlákno pro jinou práci.

### **1.5 Studijní materiály (detaily a ukázky)**

*   **C++ (Nízkoúrovňové POSIX):**
    *   [Lekce 20: Síťová komunikace (Berkeley Sockets)](https://github.com/TomasRacil/informatika-2/tree/master/03-pokrocile-cpp/20-sitova-komunikace/)
*   **Python (Vysokoúrovňové a Async):**
    *   [Lekce 19: Klasické sockety](https://github.com/TomasRacil/informatika-2/tree/master/05-pokrocily-python/19-klasicke-sockety/)
    *   [Lekce 21: Síťová komunikace AsyncIO](https://github.com/TomasRacil/informatika-2/tree/master/05-pokrocily-python/21-sitova-komunikace-asyncio/)

## **2. Praktický Projekt A: TCP Chat Server**

Vaším úkolem je rozšířit server z minulého bloku. Místo simulovaných klientů teď budeme přijímat ty skutečné.

### **Zadání úlohy**

Upravte C++ kód tak, aby fungoval jako TCP Server naslouchající na portu **8080**.

**Logika serveru:**

1. **Start:** Server vytvoří socket a začne naslouchat na portu 8080.  
2. **Smyčka (Main Thread):**  
   * Čeká na připojení nového klienta funkcí `accept()` (toto je blokující operace).  
   * Jakmile se někdo připojí, server získá jeho socket (číslo).  
   * **Vytvoří nové vlákno** (viz Blok 2) a předá mu tento socket.  
3. **Vlákno klienta (Worker):**  
   * V nekonečné smyčce čte data ze socketu (`recv()`).  
   * Když přijdou data, pošle je všem ostatním připojeným klientům (**Broadcasting**).  
   * *Tip:* Budete potřebovat seznam všech aktivních socketů chráněný Mutexem!

### **Jak to otestovat?**

Nemusíte hned psát klienta. Použijte nástroj **Telnet** nebo **Netcat** (je v každém Linuxu/Macu, na Windows přes WSL nebo Putty).

**Příkaz v terminálu (simulace klienta):**

```shell
telnet localhost 8080  
# nebo  
nc localhost 8080
```

Cokoli napíšete, mělo by se objevit v ostatních terminálech připojených ke stejnému portu.

## **3. Praktický Projekt B: Deployment do Dockeru**

Mít server, který běží jen ve vašem VS Code, nestačí. V praxi se aplikace nasazují jako **Kontejnery**.

### **Zadání úlohy**

Vytvořte soubor `Dockerfile` v kořenu vašeho C++ projektu, který zabalí váš server do image.

**Požadavky na Dockerfile:**

1. **Base Image:** Použijte Linux s kompilátorem (např. `gcc:latest` nebo `ubuntu`).  
2. **Build:** Uvnitř kontejneru zkompilujte váš server (např. `g++ -o server main.cpp -pthread`).  
3. **Run:** Nastavte kontejner tak, aby po spuštění zapnul váš server.

Spuštění:  
Protože server naslouchá na portu uvnitř kontejneru, musíme tento port zpřístupnit zvenčí (Port Forwarding). 

```shell 
# 1. Sestavení image  
docker build -t muj-chat-server .

# 2. Spuštění (Port 8080 z kontejneru na 8080 vašeho PC)  
docker run -p 8080:8080 muj-chat-server
```

Pokud se vám podaří připojit přes `telnet localhost 8080` k běžícímu kontejneru, máte hotovo!

## **4. Řešení**

Vzorové řešení (C++ kód + Dockerfile) naleznete ve složce řešení.

* [**Řešení: TCP Server & Docker**](./reseni)
  * server.cpp: Kompletní implementace s vlákny a sockety.  
  * Dockerfile: Ukázka kompilace a spuštění v izolovaném prostředí.