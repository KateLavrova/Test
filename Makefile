main: 
	rm -f out/*
	g++ -c -o out/logger src/logger.cpp -std=c++17  
	g++ -fPIC -shared src/logger.cpp -Iinclude -o out/liblogger.so
	g++ src/logger_tests.cpp src/logger.cpp -o out/logger_tests  -std=c++17
	./out/logger_tests
	g++ src/main.cpp -o out/main -I ./include -L ./out  -llogger -v  -std=c++17
	./out/main
lib:
	rm -f out/*
	g++ -c -o out/logger src/logger.cpp -std=c++17  
	g++ -fPIC -shared src/logger.cpp -Iinclude -o out/liblogger.so
exe:
	g++ src/main.cpp -o out/main -I ./include -L ./out  -llogger -v  -std=c++17
	./out/main
test:
	g++ src/logger_tests.cpp src/logger.cpp -o out/logger_tests  -std=c++17
	./out/logger_tests
clean:
	rm -f out/*