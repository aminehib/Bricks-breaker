# Casse‑brique 

## Présentation

Ce dépôt rassemble le code produit entre les séances 1 à 5 du projet . L’objectif est de développer, pas à pas, un mini‑moteur 2D basé sur **SDL 2** pour réaliser deux jeux :

1. un **casse‑brique** classique (séances 3 → 5),
2. le jeu final **Snaketris** (séances 6 → 9, à venir) qui fusionne les mécaniques de *Snake* et *Tetris*.

Ce README récapitule l’avancement jusqu’à la séance 5, le découpage du code, les dépendances et la procédure de compilation.

---

## Dépendances

| Nom | Rôle | Version testée |
| --- | --- | --- |
| `SDL2` | Affichage, événements | ≥ 2.0.14 |
| `SDL2_image` | Chargement PNG | ≥ 2.0.5 |
| `SDL2_ttf` | Rendu de texte | ≥ 2.0.15 |
| `g++` | Compilation C++17 | ≥ 11 |

> **Astuce :** sous Debian/Ubuntu :
> ```bash
> sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
> ```

---

## Organisation des sources

```
.
├── Makefile          # compilation séparée (obj/ → bin/)
├── assets/           # images & polices
│   ├── ball.png
│   ├── tux.png
│   └── world.dat
└── src/
    ├── window.hpp|cpp   # wrapper SDL : fenêtre, textures, texte
    ├── world.hpp|cpp    # représentation de la grille de blocs
    ├── game.hpp|cpp     # logique du casse‑brique (S4‑S5)
    └── main.cpp         # point d’entrée (sélection d’un mode)
```

---

## Journal des séances

### Séance 1 : Premiers pas avec SDL
- Création de la structure `Window` (initialisation, fond, rectangles).
- Premier **Makefile** et affichage d’exemples : échiquier et pentominos.

### Séance 2 : Boucle événementielle & multimédia
- Gestion clavier, souris ; fermeture propre.
- Ajout d’images (`SDL_image`) et de texte (`SDL_ttf`).
- Animation d’une balle rebondissante avec vitesse variable.

### Séance 3 : Modélisation du monde
- Structure `World` → grille dynamique `Block`.
- Lecture/écriture sécurisée (`read`, `write`).
- Chargement depuis `world.dat`; affichage console pour debug.

### Séance 4 : Prototype graphique du casse‑brique
- Structure `Game` (monde + raquette + balle + couleurs).
- Affichage des blocs dans la fenêtre SDL.
- Contrôles : **← / →** (raquette), **Espace** (lancer/pause), **R** (reset), **Q** (quitter).

### Séance 5 : Règles de jeu & scoring
- Physiques de rebond (bords, raquette, briques).
- Destruction de briques `Type1`/`Type2` ; conditions **Win** / **GameOver**.
- Compteur de points affiché en HUD.

---

## Compilation & exécution

```bash
make              # construit tous les binaires dans ./bin
./bin/casse_brique   # lance la version graphique
./bin/world_test     # tests unitaires sur la structure World
```

Les chemins d’inclusion et de lien vers SDL sont générés automatiquement via :
```makefile
SDL_INC = $(shell sdl2-config --cflags)
SDL_LIB = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf
```

---

## Commandes clavier (jeu)

| Touche | Action |
| ------ | ------ |
| **← / →** | Déplacer la raquette |
| **Espace** | Lancer / Pause |
| **R** | Réinitialiser la partie |
| **Q** | Quitter |

---

## Roadmap (séances 6 → 9)

- Implémentation du *Snake* + fusion avec le plateau de tétrominos.
- Gestion des niveaux, persistance du score.
- Effets sonores via `SDL2_mixer`.
- Packaging cross‑platform (Windows/Mac/Linux).

---

## Auteurs

- **Mohammed Amine HIBAOUI** 

---

## Licence

Projet académique – usage pédagogique uniquement.

