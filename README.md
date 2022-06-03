# My progress
Toutes les leçons que j'ai lues

## Level 1

### Install a compiler

### Use an IDE
- Rename Symbol -> F2 très pratique !
- Go to Definition -> F12
- Go to Symbol -> ctrl+shift+O
- Go to file -> ctrl+P
- Switch between .h and .cpp -> alt+O très pratique !
- Search for word in the whole project -> ctrl+shift+F

### Use Git
Faire des commit sous cette forme : 
```[Partie du code affectée] Add/Update/Fix/... détail du commit```

Faire des phrases dans le titre du commit, et pas commit du code qui marche pas

Ca rend le repository plus clair !

### Use a debugger
Ajouter des breakpoints pour debugger (cliquer à gauche de la ligne ou F9) -> très pratique !

### Use a formatting tool
Se fait tout seul au moment du ctrl+s

-> Trop bien pour avoir du joli code facile à lire

### Use static analysers
Clang-tidy et cppCheck

-> Trop bien pour repérer les erreurs de code

### Naming
Noms concis et descriptifs

Guidelines : 
- booléens sous forme de questions ou affirmation (isTeaFresh())
- éviter abbréviations
- utiliser variables et fonctions pour simplifier compréhension
- ajouter Out à la fin des variables que l'on modifie

### Stack vs Heap
Stack : int i=3 --> entier

Heap : int* i=3 --> pointeur d'entier

Préférer utiliser le stack

pas faire de new : utiliser std::unique_ptr ou std::shared_ptr
Utiliser le heap quand :
- objets de tailles variables
- gros objects
- polymorphisme

### Consistency in style
Garder les mêmes conventions tout au long d'un projet

-> pour ce projet : snake_case


## Level 2

### Make it work, then make it good
le plus important c'est que le code marche, après seulement on améliore

### Prefer free functions
Utiliser les free functions (qui prennent autant de paramètres que nécessaire) plutôt que des méthodes quand les méthodes utilisent que l'interface publique de la classe

### Design cohesive classes
- Utiliser les structs plutôt qu'une classe si on a pas d'invariants
- Respecter les principes de Single Responsibility
- Pas de méthodes privées
- Pas de méthodes publiques qui utilise que des membres publiques de la classe : dans ce cas ça doit être une free function

### Use structs to group data

### Write small functions
découper les longues fonctions en fonctions intermédiaires pour améliorer la lisibilité

### DRY: Don't repeat yourself
Avec boucles, fonctions, templates, structs ou classes

### Enums
- Utiliser enum class
- Utiliser using enum avant switch pour pas avoir à remettre le nom de l'enum à chaque fois dans les case du switch

### Split problems in small pieces
- faire des fonctions et classes simples et courtes
- diviser les tâches en plus petites tâches
- peut faire les tâches visuelles en premier pour voir plus facilement les résultats et bugs après

### Composition over Inheritance
- quand réutilisation du code : préférer fonctions ou composition
- faire du polymorphisme à la place de l'héritage : polymorphisme statique (templates) et dynamique (std::variant, std::function)
- utiliser héritage : quand classe mère est abstraite, ou CRTP


## Level 3

### std::vector
Utiliser std:vector comme container !

### Minimize dependencies
- ne passer que l'élément concerné dans une fonction, et pas tout le contexte (par exemple pour une caméra passer juste la matrice et pas la classe caméra entière) --> rend le code moins complexe et simplifie sa réécriture
- préférer les fonctions libres minimise aussi les dépendences

### Strong Types
- permet de rajouter des information à un type (par exemple donner un nom en plus à un int)
- clarifie l'utilisation des types et protège des accidents
- exemple : une classe point et vecteur -> ont toutes les deux des nombre x et y qui les représentent mais ce ne sont pas les même concepts

### Use libraries
lire la documentation des librairies !

### Range-based for loops
Exemple : ```for (auto& x : v) {
    // ...
}```
- --> montre mieux l'intention du code
- --> garantie aussi qu'on ne change pas l'index dans la boucle comme on pourrait le faire dans une boucle for

### Master your IDE
- aller voir et apprendre les raccourcis clavier pour gagner en rapidité
- sur Internet, ou sur vs code Keyboard Shortcuts (Ctrl+K Ctrl+S)

### std::optional
pour avoir des types qui peuvent être nuls, permet de l'indiquer explicitement

Exemple :  ```std::optional<int> oEmpty;```

### Single Source of Truth
- principe : ne stocker une information qu'une fois dans le code
- --> évite les problèmes au moment de la réécriture du code

### code reviews
- principe : demander des retours sur le code par une personne de l'équipe
- utile pour trouver les bugs, knowledge transfer, augmente responsibilité (devoir écrire une docummentation)

### Documentation
- mettre des commentaires au dessus des fonctions
- donner des exemples d'utilisation pour expliciter l'utilisation d'une fonction ou méthode
- Doxygen
- utiliser des readme interne pour les développeurs (dire pourquoi on a choisit cette solution plutôt qu'une autre...)

### Don't overfocus on performance
- préférer la maintenabilité et la lisibilité du code à sa performance (surtout quand la performance n'est pas requise)

### Git submodules
- ajouter un submodule à un projet depuis gitKraken (Submodules > plus, ajouter le lien du git)
- ```git clone --recursive https://github.com/url/to/the/repo``` pour cloner un projet qui utilise un submodule (ne pas le faire depuis gitKraken pour éviter les problèmes)

### assert
- pour faire des vérifications pendant le développement (assert est enlevé en release mode)
- assert est fait au moment du run
- static_assert est fait à la compilation

### auto
- Lorsque auto rend le code plus lisible, on peut l'utiliser
- --> évite les redondances dans le code

### Markdown
- simple, lisible, très utilisé
```
*italic text*

**bold text**

[Markdown Cheatsheet link](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)

 - A
 - bullet
 - point
 - list

 `inline code`
```

### Smart Pointers
utiliser `std::unique_ptr<MyClass> x = std::make_unique<MyClass>();` plutôt qu'un pointeur normal

### std::function
- type qui permet de passer une fonction en paramètre à d'autres fonctions
- exemple : `std::function<void()> my_function`

### Error Handling
avec des exceptions : `try { ... } catch { ... throw; }`

### Git Pull Requests
pour contribuer à un projet open source
- fork le projet
- faire une nouvelle branche et faire ses changments dedans
- faire une pull request et écrire un message sur ce que l'on a modifié

### Advanced Git features
- amend : fait un commit mais sans le push (bien pour revenir dessus plus tard s'il y a encore des bugs)
- rebase
- stash

### The Rule of 5
- règle : si on crée une special member function dans une classe, cela veut dire que l'on doit faire les 5 (destructor, copy constructor, copy assignment, move constructor, move assignment)
- Rule of 0 : la plupart des classes ne doivent pas avoir de special member functions explicitement défini, parce qu'elles ne le requiert pas

### State and Strategy
- state : le changement d'un state est géré par le state lui-même
vs 
- strategy : le changement vient de l'extérieur (dépend pas de la stratégie courante)

### std::variant
- exemple : `std::variant<int, float> my_variant` --> peut contenir un int OU un float 
- Le type du std::variant peut changer au court du temps entre les type qu'on lui a donné
- alternative à enum