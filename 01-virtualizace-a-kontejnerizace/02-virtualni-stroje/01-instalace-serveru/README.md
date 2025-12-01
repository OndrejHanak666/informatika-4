# **01. Instalace Serveru**

Tento návod vás provede kompletní instalací **Ubuntu Serveru** do prostředí **VirtualBox**. Počítáme s tím, že toto může být vaše první setkání s instalací serverového operačního systému.

Nebojte se chyb. Pokud se něco pokazí, prostě virtuální stroj smažete a začnete znovu. To je krása virtualizace.

## **1. Příprava a Stažení**

Než otevřete VirtualBox, musíte mít stažený tzv. **ISO obraz**. Je to digitální kopie instalačního disku.

1. Jděte na [ubuntu.com/download/server](https://ubuntu.com/download/server).  
2. Klikněte na **Download Ubuntu Server 24.04 LTS** (nebo novější).  
3. Soubor bude mít příponu `.iso` a velikost cca 3 GB.  
4. **Nikam ho nerozbalujte!** VirtualBox umí číst přímo `.iso` soubor.

## **2. Vytvoření virtuálního stroje (Hardware)**

Nejprve musíme "sestavit počítač" – tedy přidělit mu RAM, procesor a disk.

1. Spusťte **VirtualBox**.  
2. Klikněte na ikonu **New** (Nový) – modrá hvězdička.  
3. **Name and Operating System:**  
   * **Name:** `myserver` (nebo libovolné jméno bez mezer).  
   * **Folder:** Nechte výchozí.  
   * **ISO Image:** Klikněte na roletku -> *Other...* -> Najděte váš stažený `.iso` soubor.  
   * **Důležité:** Políčko **Proceed with Unattended Installation** nechte nezaškrknuté. Chceme si instalaci projít ručně, abychom viděli, co děláme.  
4. Klikněte na **Next**.  
5. **Hardware:**  
   * **Base Memory (RAM):** Nastavte alespoň **2048 MB** (2 GB). Pokud máte v PC 16 GB RAM a více, dejte klidně 4096 MB. Méně než 2 GB může způsobit pomalou instalaci.  
   * **Processors (CPU):** Nastavte **2 CPU**. S jedním jádrem bude instalace trvat věčnost.  
6. Klikněte na **Next**.  
7. **Virtual Hard disk:**  
   * Nechte vybrané "Create a Virtual Hard Disk Now".  
   * Velikost **25 GB** je pro server naprosto dostatečná (systém zabere cca 4 GB).  
8. Klikněte na **Next** a poté **Finish**.

V levém sloupci se objevil váš nový stroj `myserver`. Je ve stavu **Powered Off**.

## **3. Instalace systému (Software)**

Nyní stroj zapneme a provedeme instalaci.

### **První start a ovládání**

1. Klikněte na **Start** (zelená šipka).  
2. Otevře se nové okno. Po chvíli uvidíte menu "Try or Install Ubuntu Server". Stiskněte **Enter**.  
3. **Upozornění k ovládání:**  
   * V instalátoru **nefunguje myš**. Používejte **šipky** (nahoru/dolů) a **Enter** (potvrzení).  
   * Pro zaškrtávání políček `[ ]` / `[X]` používejte **Mezerník (Space)**.  
   * Pokud vaše myš bude uzamknutá v okně a nemůžete s ní vyjet ven, stiskněte **Pravý Ctrl** (nebo Left Command na Macu).

### **Průchod instalátorem**

1. **Language:** Vyberte **English**.  
   * *Proč ne čeština?* V IT světě se chyby řeší v angličtině. Hledat na Googlu "chyba segmentace" je peklo, hledat "segmentation fault" vám dá řešení hned.  
2. **Keyboard configuration:** Nechte English (US) nebo změňte na Czech. Potvrďte **Done**.  
3. **Choose type of install:** Nechte `Ubuntu Server`. (Verze "minimized" je fajn, ale chybí v ní některé nástroje, které budeme potřebovat).  
4. **Network connections:** Měli byste vidět `eth0` a IP adresu (např. `10.0.2.15`). To znamená, že VirtualBox (NAT) funguje. Dejte **Done**.  
5. **Configure proxy:** Nechte prázdné. **Done**.  
6. **Configure Ubuntu archive mirror:** Nechte výchozí adresu. **Done**.  
7. **Storage configuration (Dělení disku):**  
   * Ujistěte se, že je zaškrtnuto `[X] Use an entire disk`.  
   * Dejte **Done**.  
   * Objeví se souhrn rozdělení. Dejte **Done**.  
   * Vyskočí červené varování "Confirm destructive action". Zvolte **Continue**. (Nebojte, maže se jen ten virtuální disk 25 GB, ne váš skutečný disk v počítači).  
8. **Profile setup (Vytvoření uživatele):**  
   * **Your name:** `Student`  
   * **Your server's name:** `myserver` (toto uvidíte v příkazové řádce).  
   * **Pick a username:** `student` (malá písmena, bez mezer!).  
   * **Choose a password:** `heslo` (Zadejte 2x. Pro výuku stačí jednoduché).  
   * Dejte **Done**.  
9. **Upgrade to Ubuntu Pro:** Zvolte **Skip for now**. **Done**.  
10. **SSH Setup (KRITICKÉ!):**  
    * Najeďte na `[ ]` Install OpenSSH server.  
    * Stiskněte **Mezerník**, aby se objevilo `[X]`.  
    * Bez tohoto kroku se na server nepřipojíme z terminálu a VS Code!  
    * Dejte **Done**.  
11. **Featured Server Snaps:** Nic nezaškrtávejte. Dejte **Done**.

Nyní probíhá instalace. Může to trvat 5 až 20 minut podle rychlosti vašeho disku a internetu.

### **Restart**

Až se dole objeví text **Reboot Now**, zvolte ho a stiskněte Enter.

* Může se objevit hláška: `Please remove the installation medium, then press ENTER`.  
* VirtualBox většinou ISO "vysune" sám. Prostě stiskněte **Enter**.

## **4. První přihlášení**

Pokud vše dopadlo dobře, uvidíte černou obrazovku, kde běží spousta textu (logy startu). Nakonec se objeví:

```shell
myserver login:
```

1. Napište uživatelské jméno: `student` a stiskněte Enter.  
2. Napište heslo: `heslo` a stiskněte Enter.  
   * **POZOR:** Při psaní hesla se na obrazovce **NIC NEUKAZUJE** (ani hvězdičky). To je bezpečnostní vlastnost Linuxu.

Pokud vidíte text `student@myserver:~$`, jste připojení.

## **5. Ověření funkčnosti**

Zkuste zadat tento příkaz pro ověření, že běží SSH server:

```shell
systemctl status ssh
```

* Měli byste vidět zelené kolečko a text `inactive (dead)`.  
* Výpis opustíte stisknutím klávesy `q`.

Dále ověřte IP adresu:

```shell
ip a
```

Hledejte řádek začínající `inet 10.0.2.15...` (nebo podobně).

**Co dál?** Nyní server běží, ale je ve VirtualBox okně. V další lekci ([02. Síťování](../02-sitovani-port-forwarding) si nastavíme síť tak, abychom se k němu mohli připojit pohodlně z našeho hostitelského počítače.