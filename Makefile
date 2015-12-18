all:
		clang++ vkparser.cpp -o vkparser -std=c++11 -lcurl -I /usr/include/jsoncpp/ -ljsoncpp `pkg-config --cflags --libs libnotifymm-1.0`
