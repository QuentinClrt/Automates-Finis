
# Projet d'Automates

Un projet consistant à programmer des outils afin d'appliquer des algorithmes sur des automates.

Les algorithmes implémentés lors de ce projet sont les suivants :
 - [x] Création d'AFD
 - [x] Création d'AFN
 - [x] Reconnaissance de mots
 - [x] Minimisation
 - [x] Déterminisation (qui reste à compléter car l'architecture de l'automate n'est pas adaptée à l'algorithme pensé)
 - [ ] Epsilon-transitions


## Compilation

Afin de compiler le projet écrit en C++, il faut se placer dans le dossier src et compiler le tout à l'aide du Makefile disponible (utilise le compilateur g++). Les commandes suivantes compilent et vident les fichiers de sortie .o :

```
cd ./src
make
make clean
```


## Usage

Pour lancer l'application :

```bash
./lanceur [0-3] [AUTOMATE1.txt AUTOMATE2.txt ...]
```


Une aide décrivant les modes et leur usage est disponible ainsi :

```
./lanceur help
```


**4 modes** sont ainsi disponibles :


**0** : lecture d'une liste de mots par un automate (déterministe ou non)

Exemple :

```
./lanceur 0 afd1.txt mots1.txt sortie1.txt
```

**1** : minimisation d'un automate

Exemple :

```
./lanceur 1 afd2.txt afd2_minimized.txt
```

**2** : déterminisation d'un automate

Exemple :

```
./lanceur 2 afn2.txt afd2.txt
```

**3** : suppression des e-transitions

Exemple :

```
En développement.
```


## Author

COLLART Quentin


## Version

Project version : 1.0

G++ version : (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008
Copyright (C) 2019 Free Software Foundation, Inc.

