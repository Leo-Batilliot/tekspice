# NanoBonus - Visual Circuit Simulator

## Introduction
**NanoBonus** est une version graphique interactive du simulateur de circuits logiques **NanoTekSpice**, développée avec **SFML** (Simple and Fast Multimedia Library) en **C++**.

Cette interface visuelle permet de construire, visualiser et simuler des circuits logiques en temps réel avec une interface intuitive drag-and-drop.

## Compilation et Lancement

### Dépendances
Assurez-vous que les dépendances suivantes sont installées :
- cmake
- g++
- make
- git

SFML sera téléchargée automatiquement lors de la compilation.

### Compilation
```bash
cd bonus/
cmake -S . -B build
cmake --build build
```

### Lancement
```bash
./build/NanoBonus
```

## Interface et Fonctionnalités

### Vue Générale
L'application présente une **grille de travail** centrale où vous pouvez placer et connecter les composants, avec une **toolbar** en bas pour sélectionner rapidement les composants à ajouter.

### Composants Disponibles

#### Entrées/Sorties
- **Input** : Entrée utilisateur (valeur modifiable en cliquant)
- **Output** : Sortie pour afficher les résultats
- **True** : Entrée constamment à 1 (vrai)
- **False** : Entrée constamment à 0 (faux)

#### Portes Logiques
- **And** : Porte ET (tous les signaux sont 1)
- **Or** : Porte OU (au moins un signal est 1)
- **Not** : Inverseur (inverse le signal)

### Interaction Utilisateur

#### Navigation à la Souris
- **Clic gauche sur un composant de la toolbar** : Fait apparaître ce composant au centre de l'écran
- **Clic gauche maintenu depuis un pin** : Démarre une connexion entre deux pins
- **Clic droit maintenu** : Déplacer la caméra dans l'espace

#### Contrôles au Clavier

- **↑↓←→ / ZQSD** : Déplacer la caméra dans l'espace
- **Suppr / Backspace** : Supprimer un composant/lien. 
- **Escape** Quitter l'application

#### Interaction Visuelle
- **Déplacer les composants** : Glisser-déposer un composant sur la grille
- **Créer des connexions** : Cliquer sur un pin de sortie et rester appuyer jusqu'à un pin d'entrée
- **Supprimer des connexions** : viser la connexion/composant et appuyer sur Suppr ou Backspace
- **Modifier les valeurs d'entrée** : Cliquer sur un pin d'entrée pour inverser sa valeur

## Configuration Visuelle

Le fichier [Config.hpp](src/Config.hpp) centralise tous les paramètres visuels et de contrôle. Vous pouvez personnaliser :

### Fenêtre
```cpp
#define WINDOW_WIDTH 1280       // Largeur de la fenêtre
#define WINDOW_HEIGHT 720       // Hauteur de la fenêtre
#define WINDOW_NAME "NanoBonus" // Titre de la fenêtre
#define WINDOW_FPS 60           // FPS Maximums de la fenêtre
```

### Caméra
```cpp
#define CAMERA_ZOOM_IN_FACTOR 0.9f      // Facteur de zoom avant
#define CAMERA_ZOOM_OUT_FACTOR 1.1f     // Facteur de zoom arrière
#define CAMERA_KEYBOARD_SPEED 10.0f     // Vitesse de déplacement
```

### Touches de Contrôle
```cpp
// Touches mentionnées dans la sections "Contrôles au Clavier"
#define CAMERA_KEY_UP sf::Keyboard::Key::Up
#define CAMERA_KEY_DOWN sf::Keyboard::Key::Down
#define CAMERA_KEY_LEFT sf::Keyboard::Key::Left
#define CAMERA_KEY_RIGHT sf::Keyboard::Key::Right
#define CAMERA_KEY_UP_ALT sf::Keyboard::Key::Z
#define CAMERA_KEY_DOWN_ALT sf::Keyboard::Key::S
#define CAMERA_KEY_LEFT_ALT sf::Keyboard::Key::Q
#define CAMERA_KEY_RIGHT_ALT sf::Keyboard::Key::D

#define KEY_DELETE_PRIMARY sf::Keyboard::Key::Delete
#define KEY_DELETE_SECONDARY sf::Keyboard::Key::Backspace
#define KEY_QUIT sf::Keyboard::Key::Escape
```

### Apparence Générale
```cpp
#define GRID_SIZE 20                            // Taille de la grille du fond
#define GRID_COLOR sf::Color(0, 0, 0)           // Couleur de la grille du fond
#define BACKGROUND_COLOR sf::Color(15, 15, 35)  // Couleur principale du fond
```

### Composants
```cpp
#define MIN_COMPONENT_HEIGHT 40.0f        // Hauteur minimale
#define COMPONENT_HEIGHT_PER_PIN 20.0f    // Hauteur rajouté par pin au dessus de 1
#define MIN_COMPONENT_WIDTH 70.0f         // Largeur minimale
#define COMPONENT_FILL_COLOR sf::Color(50, 50, 50)        // Remplissage
#define COMPONENT_OUTLINE_COLOR sf::Color(255, 255, 255)  // Couleur du Contour
#define COMPONENT_OUTLINE_THICKNESS 2.0f                // Épaisseur du contour
```

### Épingles (Pins)
```cpp
#define PINS_RADIUS 5.0f                            // Rayon des pins
#define INPUT_COLOR_ON sf::Color(50, 150, 50)       // Couleur d'un Pin d'entrée ON (vert)
#define INPUT_COLOR_OFF sf::Color(150, 50, 50)      // Couleur d'un Pin d'entrée OFF (rouge)
#define OUTPUT_PIN_ON sf::Color(50, 150, 50)        // Couleur d'un Pin de sortie ON
#define OUTPUT_PIN_UNDEFINED sf::Color(150, 50, 50) // Valeur indéfinie
```

### Connexions
```cpp
#define LINK_ON_COLOR sf::Color(0, 255, 0)      // Connexion active (vert)
#define LINK_OFF_COLOR sf::Color(50, 50, 50)    // Connexion inactive
#define LINK_PENDING_COLOR sf::Color(100, 100, 100) // Connexion en cours
```

### Toolbar
```cpp
#define TOOLBAR_COLOR sf::Color(30, 30, 30) // couleur de la toolbar
#define TOOLBAR_SCREEN_SIZE 1.0f / 6.0f  // Taille de la barre (Occupe 1/6 de l'écran)
#define TOOLBAR_COMPONENTS_PADDING_RATIO 1.0f / 10.0f // Espace entre les composants dans la toolbar
```

## Ajouter un Nouveau Composant

Pour ajouter un nouveau composant au bonus, suivez ces étapes :

### 1. Créer la classe du composant

Créez un fichier `src/Components/MyComponent.hpp` :
```cpp
#pragma once
#include "../Core/Component.hpp"

class MyComponent : public Component {
public:
    MyComponent(sf::Vector2f position, sf::Font& font);
    ~MyComponent() override = default;

    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    // Vos membres privés
};
```

Et implémentez `src/Components/MyComponent.cpp`.

### 2. Enregistrer le composant dans main.cpp

Ajoutez l'include dans [main.cpp](src/main.cpp) :
```cpp
#include "Components/MyComponent.hpp"
```

Puis enregistrez-le dans la section du clic sur la toolbar :
```cpp
if (type == "MyComponent") 
    world.addComponent(std::make_unique<MyComponent>(spawn, font));
```

### 3. Ajouter un bouton dans la toolbar

Modifiez la [Toolbar](src/Core/Toolbar.cpp) pour inclure votre nouveau composant dans la liste disponible.

### 4. Ajouter votre fichier au cmake

N'oubliez pas d'ajouter votre nouveau fichier dans le `CMakeLists.txt` :
```
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Core/Component.cpp
    src/Core/Circuit.cpp
    src/Core/Camera.cpp
    src/Core/Toolbar.cpp
    src/Components/AndGate.cpp
    src/Components/OrGate.cpp
    src/Components/NotGate.cpp
    src/Components/Input.cpp
    src/Components/Output.cpp
    src/Components/TrueInput.cpp
    src/Components/FalseInput.cpp
    src/Components/MyComponent.cpp  # <-- Ajoutez votre composant ici
)
```

## Architecture Interne

### Structure des Fichiers
```
bonus/
├── src/
│   ├── main.cpp                 # Point d'entrée principal
│   ├── Config.hpp               # Configuration globale
│   ├── Components/              # Composants logiques
│   │   ├── Input.hpp/cpp
│   │   ├── Output.hpp/cpp
│   │   ├── AndGate.hpp/cpp
│   │   ├── OrGate.hpp/cpp
│   │   ├── NotGate.hpp/cpp
│   │   ├── TrueInput.hpp/cpp
│   │   └── FalseInput.hpp/cpp
│   └── Core/                    # Système principal
│       ├── Component.hpp/cpp    # Classe de base pour les composants
│       ├── Circuit.hpp/cpp      # Gestion du circuit
│       ├── Camera.hpp/cpp       # Système de caméra
│       └── Toolbar.hpp/cpp      # Interface toolbar
├── assets/
│   └── Inter.ttf                # Police utilisée
└── CMakeLists.txt               # Configuration build
```

### Hiérarchie des Classes
- **Component** : Classe abstraite de base pour tous les composants
  - **Input/Output** : Entrées et sorties utilisateur
  - **AndGate/OrGate/NotGate** : Portes logiques
  - **TrueInput/FalseInput** : Entrées constantes

## Voir Aussi

Documentation technique complète : [docs/README.md](../docs/README.md)
Simulateur en ligne de commande : [README.md](../README.md)
