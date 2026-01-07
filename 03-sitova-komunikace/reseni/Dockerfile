FROM gcc:latest

WORKDIR /app

COPY server.cpp .

# Kompilace serveru s podporou vláken
RUN g++ -o server server.cpp -pthread

# Otevření portu 8080 pro svět
EXPOSE 8080

# Spuštění serveru
CMD ["./server"]
