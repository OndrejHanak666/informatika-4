# **03. SSH Keys a Bezpečnost**

Zadávat heslo heslo při každém připojení je otravné. Zadávat složité heslo X7!mB9@qL je ještě otravnější. A mít na serveru povolené přihlašování heslem je bezpečnostní riziko (Brute-force útoky).

Řešením jsou **SSH klíče**.

## **Teorie: Asymetrická kryptografie**

Běžná hesla fungují na principu **symetrické kryptografie** (obě strany znají stejné tajemství). SSH klíče využívají **asymetrickou kryptografii**, která je založena na matematicky svázaném páru dvou odlišných klíčů:

1. **Veřejný klíč (Public Key):**  
   * Tento klíč můžete volně šířit. Dáváte ho serverům, kam se chcete připojovat.  
   * Slouží k **šifrování** zpráv pro vás nebo k **ověřování** vašich digitálních podpisů.  
   * Z veřejného klíče **nelze** spočítat klíč privátní.  
2. **Privátní klíč (Private Key):**  
   * Tento klíč musíte pečlivě chránit a nikdy ho nesmíte nikomu poslat.  
   * Slouží k **dešifrování** zpráv určených vám nebo k **digitálnímu podepisování**.

### **Jak probíhá přihlášení (SSH Handshake)?**

Proces ověření totožnosti probíhá tak, že server ověřuje, zda vlastníte privátní klíč, aniž byste ho museli posílat sítí.

1. **Klient:** "Ahoj, chci se přihlásit jako student a používám tento veřejný klíč."  
2. **Server:** Podívá se do souboru authorized_keys. Pokud tam klíč najde, vygeneruje náhodný řetězec (tzv. **Challenge**) a pošle ho klientovi.  
3. **Klient:** Vezme tento řetězec a **digitálně ho podepíše** svým **Privátním klíčem**. Výsledek pošle zpět serveru.  
4. **Server:** Vezme váš **Veřejný klíč** a ověří, zda podpis odpovídá původnímu řetězci. Pokud ano, znamená to, že musíte vlastnit privátní klíč, a server vás pustí dovnitř.

## **1. Generování páru klíčů (Hostitel)**

Tento krok děláte na svém **počítači (Windows/Mac)**, ne na serveru!

Otevřete terminál (PowerShell/Bash) a zadejte:

```shell
ssh-keygen -t ed25519 -C "vas-email@student.cz"
```

* `-t ed25519`: Moderní, bezpečný a rychlý algoritmus (lepší než staré RSA).  
* `-C`: Komentář pro identifikaci klíče (abyste poznali, komu patří).

Systém se zeptá, kam klíč uložit (nechte default Enter) a na Passphrase (pro výuku nechte prázdné Enter, v praxi zadejte heslo k odemčení klíče, což je další vrstva ochrany).

Vzniknou dva soubory (obvykle v `~/.ssh/`):

* `id_ed25519` (Váš **privátní** klíč. NIKDY nikomu neposílat!).  
* `id_ed25519.pub` (Váš **veřejný** klíč. Ten nahrajeme na server).

## **2. Nahrání veřejného klíče na server**

Musíme dostat obsah `id_ed25519.pub` do souboru `~/.ssh/authorized_keys` na serveru. Tím serveru říkáme: *"Tento veřejný klíč patří uživateli Student, pouštěj každého, kdo prokáže vlastnictví odpovídajícího privátního klíče."*

### **Varianta A: Automaticky (Linux/Mac/nový Windows)**

Pokud máte příkaz `ssh-copy-id` (nebo Windows s OpenSSH):

```shell
ssh-copy-id -p 2222 student@127.0.0.1
```

*Zadáte naposledy heslo a klíč se přenese.*

### **Varianta B: Ručně (Univerzální)**

1. Zobrazte si veřejný klíč na svém PC: `cat ~/.ssh/id_ed25519.pub` (nebo `type ...` na Windows).  
2. Zkopírujte ten řetězec (začíná `ssh-ed25519 ...`).  
3. Přihlašte se na server klasicky heslem.  
4. Na serveru: 
   ```bash
   mkdir -p ~/.ssh  
   echo "ZDE_VLOZTE_TEN_KOD_Z_KLICE" >> ~/.ssh/authorized_keys  
   chmod 600 ~/.ssh/authorized_keys  
   chmod 700 ~/.ssh
   ```

## **3. Test připojení**

Odhlaste se (`exit`) a zkuste se připojit znovu:

```shell
ssh -p 2222 student@127.0.0.1
```

Pokud vás to pustilo **bez hesla**, funguje to!

## **4. Hardening (Vypnutí hesel)**

Teď, když máme klíče, zakážeme hesla úplně. Tím zamezíme útokům hádačů hesel (botů, kteří zkouší admin/1234).

1. Na serveru editujte konfiguraci SSH daemona: 
   ```bash 
   sudo nano /etc/ssh/sshd_config
   ```

2. Najděte (Ctrl+W) řádek `PasswordAuthentication` a změňte ho na:  
   `PasswordAuthentication no`

3. Uložte (`Ctrl+O`, `Enter`) a ukončete (`Ctrl+X`).  
4. Restartujte službu:
   ```bash
   sudo systemctl restart ssh
   ```

*Pozor: Nyní se na server dostane jen ten, kdo má privátní klíč! Pokud ho ztratíte, jste ze serveru navždy zamčeni.*