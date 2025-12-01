# **01. Docker CLI: Základy a Sítě**

Command line utility dockeru (CLI) je váš hlavní nástroj pro komunikaci s Docker Enginem. V této lekci se naučíme spouštět kontejnery, spravovat je a propojovat.

## **1. Životní cyklus kontejneru**

### **Hello World**

Nejprve ověříme, že vše funguje.

```shell
docker run hello-world
```

Tento příkaz stáhl image z Docker Hubu, vytvořil kontejner, spustil ho (vypsal text) a ukončil se.

### **Interaktivní režim (Alpine Linux)**

Chceme se dostat "dovnitř" kontejneru. Použijeme alpine – extrémně malou distribuci Linuxu (cca 5 MB).

```shell
docker run --name muj-alpine -it alpine:latest /bin/sh
```

* `-i` (interactive): Udržuje STDIN otevřený.  
* `-t` (tty): Přidělí virtuální terminál.  
* `--name`: Pojmenuje kontejner (jinak dostane náhodné jméno).

Nyní jste uvnitř. Zkuste `ls`, `whoami` nebo `cat /etc/os-release`. Pro ukončení napište `exit`.

## **2. Běh na pozadí a Porty (PostgreSQL)**

Databáze a webové servery chceme spouštět na pozadí (**Detached mode**).

```shell
docker run --name mojedb -e POSTGRES_PASSWORD=tajneheslo -d postgres
```

* `-e`: Nastavení environment proměnné (konfigurace kontejneru).  
* `-d`: Detached mode (běží na pozadí).

Zkontrolujte, že běží:

```shell
docker ps
```

## **3. Networking: Propojení dvou kontejnerů**

Toto je klíčový úkol. Chceme propojit databázi (**PostgreSQL**) s grafickým správcem (**pgAdmin**), aniž bychom museli cokoli instalovat do Windows/macOS.

### **Krok A: Vytvoření sítě**

Kontejnery se navzájem nevidí, pokud nejsou ve stejné síti.

```shell
docker network create my-net
```

### **Krok B: Spuštění databáze v síti**

Nyní musíme dostat naši databázi do sítě `my-net`. Máme dvě možnosti:

**Varianta 1: Smazat a vytvořit znovu (Doporučeno)**
Abychom měli pořádek v názvech (a fungoval nám přesně návod v Kroku D), starou databázi smažeme a vytvoříme novou s názvem `db-server`.

```shell
docker rm -f mojedb

docker run --name db-server   
  --network my-net   
  -e POSTGRES_USER=student   
  -e POSTGRES_PASSWORD=heslo   
  -d postgres
```

**Varianta 2: Připojit stávající kontejner** Pokud byste měli v kontejneru mojedb důležitá data a nechtěli ho mazat, můžete ho připojit do sítě za chodu:

```shell
docker network connect my-net mojedb
```
*(Pozor: Pokud zvolíte tuto možnost, váš kontejner se stále jmenuje `mojedb`. V Kroku D tedy musíte jako Host name zadat mojedb místo `db-server`.)*

### **Krok C: Spuštění pgAdmin v síti**

pgAdmin je webové rozhraní pro správu DB. Musíme mu vystavit port ven, abychom ho viděli v prohlížeči.

```shell
docker run --name db-admin   
  --network my-net   
  -p 8080:80   
  -e PGADMIN_DEFAULT_EMAIL=admin@skola.cz   
  -e PGADMIN_DEFAULT_PASSWORD=admin   
  -d dpage/pgadmin4
```

* `-p 8080:80`: To, co je uvnitř kontejneru na portu 80, bude na mém PC na portu 8080.

### **Krok D: Připojení**

1. Otevřete prohlížeč na `http://localhost:8080`.  
2. Přihlašte se (email: `admin@skola.cz`, heslo: `admin`).  
3. Klikněte na **Add New Server**.  
   * **Host name/address:** `db-server` (V Docker síti se kontejnery vidí pod svými názvy. Pokud jste použili Variantu 2, zadejte `mojedb`)  
   * **Username:** `student`  
   * **Password:** `heslo`  
4. Pokud se připojíte, výborně. Propojili jste dva izolované systémy.

## **Úklid**

Po dokončení práce po sobě ukliďte:

```shell
docker rm -f db-server db-admin  
docker network rm my-net
```