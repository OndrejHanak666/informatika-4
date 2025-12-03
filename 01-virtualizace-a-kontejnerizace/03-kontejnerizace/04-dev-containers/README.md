# **04. Dev Containers: Vývoj přímo v Dockeru**

Zatím jsme Docker používali k **běhu** hotových aplikací. Ale co **vývoj**?

Představte si scénář:

* **Backend tým** potřebuje Python 3.9, PostgreSQL a specifické C++ knihovny.  
* **Frontend tým** potřebuje Node.js 18 (protože na 20 to padá) a jinou sadu nástrojů.

Pokud si toto všechno nainstalujete do svého Windows/Macu, vznikne "konfliktní peklo". Řešením jsou **Dev Containers**.

## **Jak to funguje?**

VS Code se rozdělí na dvě části:

1. **Klient (UI):** Běží na vašem fyzickém počítači. Vidíte okna, menu, barvy.  
2. **Server (Terminal, Debugger, Language Server):** Běží **uvnitř** Docker kontejneru.

Vy píšete kód ve Windows, ale kód se ukládá a spouští v Linuxu uvnitř kontejneru.

## **Obsah lekce**

Tato sekce jsme rozdělena na dvě části:

* [**01. Základy (Jeden skript)**](./01-zaklady)
    * Nejjednodušší možná ukázka.  
    * Otevřeme Python prostředí, aniž bychom měli Python nainstalovaný v PC.

* [**02. Pokročilý Full-Stack (Backend + Frontend)**](./02-full-stack-dev)
    * Simulace reálného scénáře full-stack developera.  
    * Budeme mít **dva různé kontejnery**:  
        1. **Backend:** Automaticky nastartuje Python i databázi PostgreSQL.  
        2. **Frontend:** Izolované prostředí pro Node.js.  
    * Ukážeme si, jak pracovat ve dvou oknech VS Code zároveň.

## **Prerekvizity**

Musíte mít nainstalované rozšíření **Dev Containers** ve VS Code.

## **Úkoly**

Jakmile si projdete výše uvedené materiály vraťte se sem splňte následující úkoly.

### 1. Úkol: Extensions

Otevřít VS Code v kontejneru je fajn, ale pokud tam nemáte potřebné doplňky, práce drhne.

  * **Zadání:**
    1.  Otevřete projekt `01-zaklady` v Dev Containeru.
    2.  Otevřete soubor `.devcontainer/devcontainer.json`.
    3.  Do sekce `extensions` přidejte rozšíření pro kontrolu pravopisu **Code Spell Checker** (ID: `streetsidesoftware.code-spell-checker`) nebo třeba **Emojisense** (`bierner.emojisense`).
    4.  **Aplikace:** Změna se neprojeví hned. Musíte provést **Rebuild Container** (přes F1 -> `Dev Containers: Rebuild Container`).
    5.  **Výsledek:** Po znovunačtení okna by mělo být rozšíření nainstalováno a aktivní (viditelné v panelu Extensions).

---

### 2. Úkol: postCreateCommand

Využijeme toho, že po vytvoření kontejneru můžeme spustit libovolný příkaz a vytvoříme pozdrav pro uživatele.

  * **Zadání:**
    1.  V `devcontainer.json` najděte vlastnost `"postCreateCommand"`. (Pokud je zakomentovaná, odkomentujte ji).
    2.  Změňte ji tak, aby vypsala uvítací hlášku do souboru:
        `"postCreateCommand": "echo 'Vítejte v Python kontejneru!'`
    3.  Proveďte **Rebuild**.
    4.  **Výsledek:** V build logu se objeví `'Vítejte v Python kontejneru!'`.

---

### 3. Úkol: Automatizace závislostí

V Python projektu (např. v lekci `02-full-stack`) často potřebujeme doinstalovat knihovny ze souboru `requirements.txt`. Dělat to ručně `pip install ...` po každém restartu není ideální.

  * **Zadání:**
    1.  Vytvořte ve složce `01-zaklady` soubor `requirements.txt` a napište do něj: `colorama`.
    2.  Upravte `devcontainer.json` tak, aby se tento soubor automaticky nainstaloval při vytvoření kontejneru.
    3.  Příkaz bude vypadat nějak takto: `"pip install -r requirements.txt"`.
    4.  **Rebuild** a test: Otevřete terminál a spusťte `pip show colorama`. Pokud vypíše informace o balíčku, máte hotovo.

-----

### 4. Úkol: Dev Container Features

*Tento úkol vyžaduje, abyste se podívali na web `containers.dev` nebo hledali "Dev Container Features".*

Máte Python kontejner. Co když ale v tom samém projektu potřebujete i **Node.js** (např. pro kompilaci frontendových assetů), ale nechce se vám psát složitý Dockerfile a instalovat Node ručně přes `apt-get`?

Microsoft vytvořil tzv. **Features** – způsob, jak do kontejneru přidat další jazyky a nástroje.

  * **Zadání:**

    1.  Do vašeho čistě Pythonního `devcontainer.json` (v `01-zaklady`) přidejte sekci `"features"`.
    2.  Nakonfigurujte ji tak, aby do kontejneru doinstalovala **Node.js** (verze "lts" nebo "latest").
    3.  **Cíl:** Po Rebuildu musíte být schopni v terminálu napsat:
          * `python --version` (funguje, je to základ image)
          * `node --version` (funguje, přidali jste ho přes Features)

    *Nápověda: Sekce v JSONu bude vypadat zhruba takto:*

    ```json
    "features": {
        "ghcr.io/devcontainers/features/node:1": {}
    }
    ```