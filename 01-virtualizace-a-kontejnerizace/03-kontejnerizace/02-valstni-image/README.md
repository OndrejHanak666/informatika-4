# **02. Dockerfile: Stavíme vlastní aplikace**

Doposud jsme používali hotové obrazy od cizích lidí (např. `postgres` nebo `nginx`). Nyní se naučíme zabalit vlastní aplikaci tak, aby šla spustit kdekoli. K tomu slouží soubor s názvem `Dockerfile`.

## **Teorie: Vrstvení obrazů (Layers)**

Docker image není jeden velký soubor, ale skládá se z vrstev (jako cibule). Každý příkaz v Dockerfile vytvoří novou vrstvu.

1. **Base Image:** Např. `python:3.9` (obsahuje OS a Python).  
2. **Dependencies:** Vrstva s nainstalovanými knihovnami (`pip install`).  
3. **App Code:** Vrstva s vaším kódem.

Proč je to důležité?  
Když změníte jen jeden řádek ve svém kódu, Docker nemusí stahovat znovu Python ani instalovat knihovny. Přebuduje jen tu poslední, nejtenčí vrstvu. To šetří čas i místo na disku.

## **Praktický úkol 1: Python Flask Aplikace**

V adresáři `muj-flask` máte připravenou jednoduchou webovou aplikaci. Otevřete si soubor `muj-flask/Dockerfile` a přečtěte si komentáře, abyste pochopili, co se děje.

### **Postup sestavení a spuštění**

1. Otevřete terminál a přejděte do složky s aplikací: 
   ```shell 
   cd muj-flask
   ```

2. **Build (Sestavení):** Vytvoříme image z našeho `Dockerfile`. 
   ```shell
   docker build -t moje-flask-app:v1 .
   ```

   * `-t`: Tag (název) obrazu.  
   * `.`: Tečka na konci je důležitá! Říká: "Hledej Dockerfile v aktuální složce".  
3. **Run (Spuštění):** Spustíme kontejner z našeho nového image.
   ```shell  
   docker run -p 5000:5000 moje-flask-app:v1
   ```

4. Ověření: Otevřete v prohlížeči
`http://localhost:5000`.

## **Praktický úkol 2: Node.js Aplikace**

V adresáři moje-node-app je ukázka v jiném jazyce (JavaScript), aby bylo vidět, že princip Dockerfile je univerzální.

### **Postup**

1. Přejděte do složky: 
   ```shell 
   cd ../moje-node-app
   ```

2. **Build:** 
   ```shell 
   docker build -t moje-node-app:v1 .
   ```

3. **Run:**  
   ```shell
   docker run -p 3000:3000 moje-node-app:v1
   ```

4. Ověření: Otevřete v prohlížeči `http://localhost:3000`.

## **3. Sdílení se světem (Docker Hub)**

Stejně jako dáváme zdrojový kód na GitHub, dáváme sestavené obrazy do tzv. **Container Registry**. Nejznámějším a výchozím registrem je **Docker Hub**.

### **Co je to Docker Hub?**

Je to veřejná knihovna obrazů. Když napíšete `FROM python`, Docker se podívá právě sem. Vy zde můžete mít vlastní repozitáře (veřejné zdarma, soukromé většinou placené).

### **Pravidla pojmenování**

Aby Docker věděl, komu image patří, musíte dodržet jmennou konvenci:  
`uzivatel/nazev-image:verze`

* **uzivatel:** Vaše jméno na Docker Hubu.  
* **nazev-image:** Jméno aplikace.  
* **verze (tag):** Např. v1, latest, 1.0.2.

### **Postup nahrání (Push)**

1. **Registrace:** Vytvořte si účet na [hub.docker.com](https://hub.docker.com/).  
2. **Přihlášení v terminálu:**
   ```shell  
   docker login
   ```

   *Zadejte své uživatelské jméno a heslo (nebo Access Token).*
 
3. **Přejmenování (Tagging)**: Náš lokální image `moje-node-app:v1` musíme "přetaggovat", aby obsahoval vaše jméno.  
   *(Nahraďte `vas_login` vaším skutečným loginem na Docker Hubu.)*
   ```shell
   docker tag moje-node-app:v1 vas_login/moje-node-app:v1
   ```

4. **Odeslání (Push)**: Nyní image odešleme do cloudu.
   ```shell  
   docker push vas_login/moje-node-app:v1
   ```

5. **Ověření:** Nyní můžete jít na jiný počítač (nebo poprosit spolužáka) a spustit:
   ```shell 
   docker run -p 3000:3000 vas_login/moje-node-app:v1
   ```
   Docker si image stáhne z internetu a spustí ho. Funguje to kdekoli na světě.