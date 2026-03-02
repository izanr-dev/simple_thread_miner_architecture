CC = gcc
CFLAGS = -Wall -g -pthread
OBJ = main.o miner.o log.o pow.o

MINER: $(OBJ)
	@$(CC) $(CFLAGS) -o MINER $(OBJ)
	@echo "building the executable..."

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o MINER *.log
	@echo "cleaning the project and log files..."

# --- COMANDOS DE PRUEBA ---

run: MINER
	@echo "\nstarting test... (Target: 0, Rondas: 5, Hilos: 3)"
	./MINER 0 5 3

runv: MINER
	@echo "\nstarting test with valgrind... (Target: 0, Rondas: 5, Hilos: 3)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./MINER 0 5 3

run-heavy: MINER
	@echo "\nstartig heavy test... (Target: 1234, Rondas: 10, Hilos: 8)"
	./MINER 1234 10 8

runv-heavy: MINER
	@echo "\nstarting heavy test with valgrind... (Target: 1234, Rondas: 10, Hilos: 8)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./MINER 1234 10 8