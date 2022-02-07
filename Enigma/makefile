enigma: main.o enigma.o plugboard.o reflector.o rotor.o
	g++ -g main.o enigma.o plugboard.o reflector.o rotor.o -o enigma
main.o: main.cpp errors.h enigma.h plugboard.h reflector.h rotor.h
	g++ -Wall -g -c main.cpp
enigma.o: enigma.cpp errors.h enigma.h
	g++ -Wall -g -c enigma.cpp
plugboard.o: plugboard.cpp errors.h enigma.h plugboard.h
	g++ -Wall -g -c plugboard.cpp
reflector.o: reflector.cpp errors.h enigma.h reflector.h
	g++ -Wall -g -c reflector.cpp
rotor.o: rotor.cpp errors.h enigma.h rotor.h
	g++ -Wall -g -c rotor.cpp
clean:
	rm -f *.o enigma
