# **03. Docker Compose: Orchestrace**

Doposud jsme spouštěli kontejnery ručně pomocí `docker run`. To je fajn pro jeden kontejner, ale co když jich potřebujeme pět? A co když musí startovat ve správném pořadí?

**Docker Compose** je nástroj pro definování a spouštění více kontejnerových aplikací. Celou konfiguraci zapíšeme do jednoho souboru `docker-compose.yml`.

## **Teorie: Infrastruktura jako Kód (IaC)**

Místo psaní dlouhých příkazů do terminálu (které si nikdo nepamatuje) popíšeme "cílový stav" systému.

* **Services (Služby):** Jednotlivé kontejnery (např. `databaze`, `backend`).  
* **Networks (Sítě):** Jak se kontejnery vidí.  
* **Volumes (Svazky):** Kam se ukládají data (aby přežila smazání kontejneru).

## **Základní příkazy**

Všechny příkazy se spouští ve složce, kde leží `docker-compose.yml`.

| Příkaz | Popis |
| :---- | :---- |
| `docker compose up` | Spustí všechny služby (vypisuje logy do terminálu). |
| `docker compose up -d` | Spustí služby na pozadí (Detached). |
| `docker compose down` | Zastaví a **smaže** kontejnery i sítě. |
| `docker compose stop` | Jen zastaví kontejnery (nemže). |
| `docker compose logs -f` | Sleduje výpis logů (jako `tail -f`). |
| `docker compose build` | Sestaví obrazy (pokud používáte `build:` místo `image:`). |

## **Praktický úkol 1: Databáze a Administrace**

V adresáři `01-db-admin` naleznete jednoduchý příklad, jak propojit databázi **PostgreSQL** s grafickým rozhraním **pgAdmin**.

1. Přejděte do adresáře: `cd 01-db-admin`  
2. Prohlédněte si soubor `docker-compose.yml`.  
3. Spusťte stack: `docker compose up -d` 
4. Otevřete prohlížeč na `http://localhost:8080` - *může chvíli trvat než naběhne pgAdmin* (Email: `admin@admin.com`, Heslo: `root`).  
5. Zkuste se připojit k serveru (Hostname: `database`, Databáze: `skola_db`, Uživatel: `student`, Heslo: `heslo`, ).

## **Praktický úkol 2: Full-Stack Aplikace**

V adresáři `02-full-stack` je simulace reálného vývoje. Máme tam:

* **Frontend:** React aplikace (formulář pro přidání úkolu).
* **Backend:** Python Flask API  (přijímá data a ukládá je do DB). 
* **Databáze:** PostgreSQL  (uchovává úkoly i po restartu).

Vše se musí sestavit a propojit.

1. Přejděte do adresáře: `cd ../02-full-stack` 
2. Spusťte sestavení a start: 
   ```shell
   docker compose up -d --build
   ```
   * *Přepínač `--build` je důležitý, protože musíme sestavit naše vlastní Dockerfiles.*  
3. Ověřte Frontend na `http://localhost:3000`
4. Zkuste přidat úkol (např. "Naučit se Docker").
5. **Test persistence:**
    * Vypněte kontejnery: `docker compose stop`
    * Znovu je zapněte: `docker compose up -d`
    * Obnovte stránku. Úkol tam stále bude. To je díky `volumes`.