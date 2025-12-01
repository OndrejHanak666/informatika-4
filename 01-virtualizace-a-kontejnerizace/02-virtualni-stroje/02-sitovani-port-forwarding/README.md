# **02. Síťování a Port Forwarding**

Nejčastější frustrace začátečníků: *"Nainstaloval jsem server, ip a mi ukazuje IP adresu, ale z Windows se na ni nemůžu pingnout ani připojit."*

## **Teorie: Síťové režimy ve VirtualBoxu**

VirtualBox se chová jako virtuální router. Nabízí několik režimů zapojení:

### **1. NAT (Network Address Translation) - Výchozí**

* **Jak to funguje:** VM je schovaná za vaším PC. Má přístup ven (internet funguje), ale **zvenku se na ni nikdo nedostane** (ani váš hostitelský PC).  
* **Analogie:** VM je jako zařízení v domácí síti, váš PC je router.  
* **Výhoda:** Bezpečné, funguje vždy (škola, doma, kavárna).  
* **Nevýhoda:** Musíte ručně otevírat porty (Port Forwarding), abyste se p5ipojili.

### **2. Bridged Adapter (Most)**

* **Jak to funguje:** VM se připojí přímo do fyzické sítě (školní Wi-Fi/LAN). Dostane IP adresu od školního routeru, stejně jako váš notebook.  
* **Výhoda:** VM je vidět jako plnohodnotné zařízení v síti.  
* **Nevýhoda:**  
  * Může selhat, pokud je školní síť zabezpečená (MAC filtering).  
  * Při změně sítě (škola -> doma) se změní IP adresa serveru.

## **Praktická úloha: Nastavení Port Forwardingu (NAT)**

Použijeme režim **NAT**, protože je nejstabilnější pro notebooky, které přenášíte. Abychom se ale dostali dovnitř přes SSH, musíme udělat "díru" (přesměrování).

### **Cíl**

Chceme, aby platilo:

* `localhost:2222` (Váš PC) -> `vm-ip:22` (Linux Server SSH)  
* `localhost:8080` (Váš PC) -> `vm-ip:80` (Linux Server Web)

### **Postup**

1. Vypněte virtuální stroj (`poweroff`).  
2. Ve VirtualBoxu klikněte na **Settings** -> **Network**.  
3. Ujistěte se, že **Adapter 1** je **NAT**.  
4. Rozklikněte **Advanced** -> tlačítko **Port Forwarding**.  
5. Přidejte dvě pravidla (tlačítko Plus vpravo):

| Name | Protocol | Host IP | Host Port | Guest IP | Guest Port |
| :---- | :---- | :---- | :---- | :---- | :---- |
| SSH | TCP | 127.0.0.1 | **2222** | (nevyplňovat) | **22** |
| WEB | TCP | 127.0.0.1 | **8080** | (nevyplňovat) | **80** |

6. Potvrďte **OK**. Spusťte virtuální stroj.

### **Ověření**

Otevřete terminál ve svém hostitelském systému (PowerShell ve Windows / Terminál v macOS) a zkuste:

```shell
# Pozor: Připojujeme se na localhost a port 2222!  
ssh -p 2222 student@127.0.0.1
```

Pokud se vás zeptá na heslo a přihlásí vás, máte splněno.