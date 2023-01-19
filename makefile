.PHONY: build

main.o: main.cpp
	g++ -fdiagnostics-color=always -g -c main.cpp

procman.o: procman.cpp
	g++ -fdiagnostics-color=always -g -c procman.cpp

proc.o: proc.cpp
	g++ -fdiagnostics-color=always -g -c proc.cpp

hwman.o: hwman.cpp
	g++ -fdiagnostics-color=always -g -c hwman.cpp

mem.o: mem.cpp
	g++ -fdiagnostics-color=always -g -c mem.cpp

cpu.o: cpu.cpp
	g++ -fdiagnostics-color=always -g -c cpu.cpp

gpu.o: gpu.cpp
	g++ -fdiagnostics-color=always -g -c gpu.cpp

battery.o: battery.cpp
	g++ -fdiagnostics-color=always -g -c battery.cpp

build: main.o procman.o proc.o hwman.o mem.o cpu.o gpu.o battery.o
	g++ -fdiagnostics-color=always -g main.o procman.o proc.o hwman.o mem.o cpu.o gpu.o battery.o -o main
