all: graCPP.e graPY.e

graCPP.e : gra.cpp gralib.hpp
	g++ -O3 -static -std=c++11 gra.cpp -o graCPP.e

graPY.e : gra.py
	echo "#!/usr/bin/env python3" > graPY.e
	cat gra.py >> graPY.e
	chmod +x graPY.e

mrproper: clean

clean:
	rm -f graCPP.e
	rm -f graPY.e
