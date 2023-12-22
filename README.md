# Simulator Prey Predator Graph

J'ai du simuler le système proies / prédateurs en me basant sur des règles
de mort / survie telles qu’elles se produisent (approximativement) dans la nature. L’objectif est
de suivre l’évolution de chaque population au cours du temps comme dans la version analytique
basées sur les équations de Lotka-Volterra et de vérifier qu’on obtient un comportement
similaire. Pour chaque individu on énoncera des règles (plus ou moins complexes et réalistes)
de naissance, reproduction, survie et mort (par prédation, faim, ou encore vieillesse).

Le rendu graphique:

![image](image/Wolf1.jpg)

L'evolution du graph correspondant:

![image](image/Wolf2.jpg)
![image](image/Wolf3.jpg)

# Subject

```
1. Un état d'équilibre de la population est observé quand aucune des deux populations en
présence n'évolue, c'est-à-dire quand les dérivées correspondantes sont nulles. Ecrivez
ce nouveau système d’équation et trouvez ses solutions.

2. En appliquant les coefficients alpha = 0.045, beta= 0.001, Yeta= 0.025 et Sigma= 0.0002 à une
population initiale de 120 proies et 40 prédateurs, écrivez les équations permettant de
calculer le nombre de proies et de prédateurs au temps t+1 en fonction du temps t.

3. Nous allons maintenant décrire les structures nécessaires à l’implémentation du modèle
proies / prédateurs en C/C++. Définissez une structure Ecosysteme qui dans sa version
initiale contiendra les champs suivants : nb_proies, nb_predateurs, ainsi que les 4
coefficients réels des équations de Lotka-Volterra notés alpha, beta, gamma et delta.

4. Écrivez une fonction evolution_ecosysteme qui simule l’évolution de chacune des
populations au cours du temps. Les résultats obtenus (nombre de proies et de prédateurs
à chaque instant) seront dans un premier temps stockés dans un tableau.

5. Après avoir défini les structures nécessaires à la modélisation du système proies /
prédateur et initialisé les paramètres avec les valeurs précédentes, modifiez la procédure
evolution_ecosysteme en faisant afficher à chaque pas de temps le nombre de proies
et de prédateurs sur un graphique. Vous utiliserez pour cela les fonctions Grapic :
 - plot_setSize (Plot &p, const int n)
qui définit le nombre de valeurs conservées (si n<0 une infinité, cas par défaut).
 - plot_add (Plot &p, float x, float y, int curve_n)
qui ajoute un point (x,y=f(x)) à la courbe numéro curve_n.
 - plot_draw (const Plot &p, int xmin, int ymin, int xmax, int
ymax, bool clearOrNot)
qui dessine la courbe dans le rectangle (xmin,ymin,xmax,ymax); et efface le
contenu du rectangle si clearOrNot est à true.

6. Définissez une structure Individu qui contiendra les champs type_individu (proie,
prédateur ou herbe), duree_vie et duree_jeune.

7. La représentation visuelle du système se fera au moyen d’une grille 2D dans laquelle
seront présent des individus (proie ou prédateur). Définissez la structure Ecosysteme
qui contiendra une grille 2D d’individus (ainsi que les paramètres de taille de la grille
dx et dy), le nombre de proies et de prédateurs et pour chaque population une image
(proie, prédateur et herbe).

8. Ecrivez la procédure evolution_ecosysteme qui prédit le devenir de chaque individu
en fonction de son environnement (voisinage) avec les deux règles suivantes.
 - Si deux proies sont dans des cases adjacentes, elles se reproduisent et donnent
donc naissance à un nouvel individu de type proie placé dans une case libre.
 - Si un prédateur a dans son voisinage une proie, il la mange, s’il a un autre
prédateur dans son voisinage il se reproduit uniquement s’il reste de la place
dans le voisinage.

9. Définissez les constantes DUREE_VIE_PROIE, DUREE_VIE_PREDATEUR,
MAX_JEUNE_PROIE, et MAX_JEUNE_PREDATEUR.

10. Définissez les structures Individu et Ecosysteme. Choisissez une image pour chaque
type d’individu (proie, prédateur et herbe) et enregistrez-les dans le dossier data. Ces
images doivent stockées dans la structure Ecosysteme.

11. Ecrivez la procédure init_ecosysteme qui initialisera le système avec des valeurs par
défaut (grille de taille 10 par 10, avec 40 proies et 10 prédateurs). Vous remplirez ici
toute la grille avec de l’herbe puis positionnerez aléatoirement vos proies et prédateurs.

12. Ecrivez la procédure draw_ecosysteme qui affiche le contenu de la grille avec les
images correspondantes dans une fenêtre Grapic.

13. Implémentez la version de base de la procédure evolution_ecosysteme et passez à
chaque itération le nombre de proies et de prédateurs à une courbe Plot de Grapic.

14. Affichez la courbe d’évolution des deux populations et comparez-la à la courbe
théorique obtenue grâce aux équations de Lotka-Volterra

```

# GrAPiC 

## Starting

Linux, Windows and Mac instruction :

http://licence-info.univ-lyon1.fr/grapic

## Introduction

GrAPiC is a small, easy-to-use framework to add graphical functionalities to your C/C++ code. 
Its main goal is to provide easy graphical functions to be used in introduction courses of algorithm and programming in C/C++. 
It is based on SDL2 but to use it you need to know only few very simples functions. 
The Grapic archive comes with the needed SDL part, you do not have to install SDL. Just unzip and enjoy ! 

## Starting

Compiling from the github (which is not the standard way).

* On Linux you need to install:
- g++
- doxygen
- zip
- lib-sdl2-dev lib-sdl2 sd2_image... sdl2_ttf...

1. sudo apt install g++ premake4 zip doxygen libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev
2. make premake
3. make
(4. script/make_linux_test.sh): to test the archive doc/download/grapic-linux.tgz
(5. script/make_web.sh): to create the zip files in doc/download or to sync everything to the webpage (need passwd).


* On windows
0. Install CB 20
1. run premake-cb20.bat to generate the projects files    or     run premake-lifami.bat to generate lifami projects 
2. open build/windows-cb20/grapic.workspace

## Best way to make a projet in windows

(windows): 
 - Open build/windows-cb20/grapic.workspace in CodeBlocks
 - In the left part (Management) of the logiciel, double clic in the projet of yours choice (it's those in /apps)
 - Finally clic in the green arrow in the top of the screen

![OpenFolder](image/OpenFolder.jpg)
![OpenFile](image/OpenFile.jpg)

## Put your new project in GraPic

Add your directory with your cpp files in "apps" and add the path in "premake4".

