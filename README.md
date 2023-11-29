Ce projet vise à réaliser une interface de jeu d'échecs en C++.
Pour compiler : make echecs. Pour lancer le jeu, exécuter ./bin/echecs
Pour générer la documentation : make docu.

Les tests comprennent 4 niveaux : le premier teste les fonctions basiques (saisie et affichage, prises, obstacles), le deuxième teste la détection de l'échec, le troisième teste les roques, la prise en passant et la promotion, et le dernier teste le mat et le pat.
Pour lancer les tests : aller dans test, puis bash test-level.sh numéro_niveau nom_executable(/bin/echecs).