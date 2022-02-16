# My progress
Les leçons que j'ai lues

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
- Respecter les principe de Single Responsibility
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