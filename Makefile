echecs : obj/jeu.o obj/echiquier.o obj/piece.o
	g++ -o bin/echecs obj/jeu.o obj/echiquier.o obj/piece.o -g

obj/jeu.o : src/jeu.cc include/echiquier.h include/piece.h include/jeu.h
	g++ -o obj/jeu.o -c src/jeu.cc -g

obj/echiquier.o : src/echiquier.cc include/echiquier.h include/piece.h
	g++ -o obj/echiquier.o -c src/echiquier.cc -g

obj/piece.o : src/piece.cc include/piece.h
	g++ -o obj/piece.o -c src/piece.cc -g

docu : 
	rm -rf doc/*
	doxygen Doxyfile

clean : 
	rm -f bin/echecs
	rm -rf obj/*.o
	rm -rf doc/*