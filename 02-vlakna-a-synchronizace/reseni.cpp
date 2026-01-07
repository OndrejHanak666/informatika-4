#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <random>

// Sdílené zdroje
std::vector<int> active_clients;
std::mutex clients_mutex;

// Funkce pro vlákno klienta
void worker(int id) {
    // Simulace práce (připojení)
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        active_clients.push_back(id);
        std::cout << "[Main] Připojen klient ID: " << id << std::endl;
    }

    // Simulace posílání zpráv
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + (rand() % 1000)));
        
        // Zámek pro bezpečný výpis na konzoli (std::cout není thread-safe pro atomický výpis řádku)
        // V praxi bychom měli mutex i pro logování, nebo použili thread-safe logger.
        // Zde spoléháme na to, že operátor << je částečně thread-safe, ale znaky se mohou míchat.
        // Pro názornost zamkneme i výpis.
        std::lock_guard<std::mutex> lock(clients_mutex); 
        std::cout << "[Client " << id << "] Posílá zprávu " << i + 1 << "/5" << std::endl;
    }

    // Odpojení
    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        std::cout << "[Main] Odpojen klient ID: " << id << std::endl;
        // Poznámka: Mazání z vektoru podle hodnoty by vyžadovalo iteraci,
        // pro jednoduchost zde jen oznámíme odpojení.
    }
}

int main() {
    std::cout << "[Main] Start serveru..." << std::endl;
    std::vector<std::thread> threads;

    // Simulace příchodu 5 klientů
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Spustíme nové vlákno pro klienta
        threads.emplace_back(worker, i);
    }

    // Čekáme, až všichni dokončí práci
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "[Main] Všichni klienti obslouženi. Konec." << std::endl;
    return 0;
}
