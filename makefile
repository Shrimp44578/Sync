compile:
	icx ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c -o ./bin/Sync
run:
	icx ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c -o ./bin/Sync
	./bin/Sync
clean:
	rm ./bin/Sync
gcc-run:
	gcc ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c -o ./bin/Sync
	./bin/Sync
gcc-compile:
	gcc ./src/Sync.c ./src/PrintFunctions.c ./src/SyncNetwork.c -o ./bin/Sync