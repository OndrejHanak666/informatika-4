# **04. Snapshoty a Headless režim**

V této poslední části se naučíme server spravovat tak, jak se to dělá v praxi – efektivně a bez zbytečné grafiky.

## **Snapshoty (Snímky stavu)**

Představte si, že jdete editovat kritický konfigurační soubor. Pokud uděláte chybu, server nenaběhne. Ve světě fyzických serverů máte problém. Ve virtuálním světě máme **Snapshoty**.

### **Úkol: Vytvoření "Záchranného bodu"**

1. Před jakoukoli riskantní akcí (nebo teď hned) si udělejte snapshot.  
2. Můžete to udělat ve VirtualBox GUI (Machine -> Take Snapshot).  
3. Nebo přes příkazovou řádku (na hostitelském PC!):  
   Musíte být ve složce, kde je nainstalovaný VirtualBox, nebo ji mít v PATH. 

   ```shell
   # Seznam běžících VM  
   VBoxManage list runningvms

   # Vytvoření snapshotu  
   VBoxManage snapshot "Ubuntu-Server" take "Funkcni-SSH-Config" --description "Stav po nastaveni klicu a site"
   ```

Teď můžete server klidně rozbít (např. `sudo rm -rf --no-preserve-root /`). Pro obnovu stačí vypnout VM a vrátit se ke snapshotu.

## **Headless Mode**

Když spravujete server přes SSH, nepotřebujete, aby vám na liště svítilo okno VirtualBoxu s černou konzolí. Zbytečně to žere grafický výkon a paměť.

### **Jak spustit server na pozadí**

1. Vypněte server (pokud běží).  
2. Ve VirtualBoxu klikněte na šipku vedle tlačítka **Start** a vyberte **Headless Start**.  
3. Okno se neotevře, ale ikonka VM se zazelená (Running).

Nyní se připojte přes svůj terminál (`ssh -p 2222 ...`).

### **Ovládání přes terminál**

Pokud chcete server vypnout a nefunguje SSH (nebo ho chcete "vyrvat ze zásuvky"), použijte příkazy na hostitelském PC:

```shell
# Graceful shutdown (jako stisknutí tlačítka vypnout)  
VBoxManage controlvm "Ubuntu-Server" acpipowerbutton

# Hard shutdown (vytržení ze zásuvky)  
VBoxManage controlvm "Ubuntu-Server" poweroff
```

## **Závěrečný úkol sekce**

Abyste prokázali, že jste tuto sekci zvládli:

1. Spusťte VM v **Headless** režimu.  
2. Připojte se přes **SSH** pomocí klíče (bez hesla).  
3. Vytvořte na serveru soubor `dukaz.txt` s aktuálním datem.  
4. Udělejte screenshot vašeho terminálu, kde je vidět příkaz SSH a následně `ls -la` na serveru.