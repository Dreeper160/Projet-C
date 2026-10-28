# Bomberman C (MLV) - Plan d'attaque du trinôme

L2 Informatique, UJM · Prog Impérative II

PS: le Template a été géneré par Claude, (c’est un bon) j’ai fait que le remplir.

## Objectifs et Jalons

L'objectif : sortir un Bomberman jouable, robuste et sans code magique. Chacun doit pouvoir expliquer l'intégralité de l'architecture, la note de soutenance étant individuelle.

* **Code freeze** : Fuh Idk, mais on se garde une marge de sécurité confortable avant le rendu.

* **Rendu Moodle strict** : Dépôt de l'archive `Nosnoms.tar.gz`.

**Approche** : Développement itératif. On garde une build toujours fonctionnelle ( "ça compile chez moi" doit devenir "ça compile sur les PC de la fac")(ne jamais push sur main, ça marche pas de facon) . Les phases sont divisées en 3 lots pour répartir la charge, et on fait tourner les rôles pour que tout le monde mette les mains dans chaque module.

## Principes d'ingénierie et Workflow

* **Conception d'abord** : On valide ensemble les `.h` (structures, prototypes) avant d'écrire l'implémentation. La structure `Jeu` est critique (elle gère l'état et la sauvegarde), on la fige en groupe.

* **Git & PR** : Une feature = une branche. Pull request obligatoire, relue et validée par un autre membre. Le reviewer doit comprendre le code ; en cas de doute, on bloque la PR avec des questions.

* **Granularité** : Des PR courtes. Une PR de 500 lignes ne se review pas correctement, elle se contemple avec désespoir.

* **Sync** : Deux points de 15 minutes par semaine (statut, bloqueurs, modifs d'interfaces).

* **Tests matériel** : Compilation `make` propre et exécution sur les machines de la fac régulièrement (vérification des inputs prolongés et de la stabilité des FPS).

* **Definition of Done** : Un lot est terminé s'il compile sans warning (`-Wall -Wextra`), est mergé après review, et est compris par le reste de l'équipe.

* **Entraide** : Si un membre bloque, on débug ensemble, on ne contourne pas son module.

## Phase 0 - Fondations

*~~Lot 1 (Membre A) : Setup et structures du plateau~~

  * Initialisation du repo Git partagé, `.gitignore` (binaires, `.o`).

  * Headers du plateau et des entités : types de cases, `Plateau`, `Joueur`.

* **Lot 2 (Membre B) : Structures des mécaniques**

  * Headers des bombes et explosions : `Bombe`, `Explosion`, rayon, timers.

  * Définition des conventions de nommage et de l'architecture des modules.

* **Lot 3 (Ulrich) : Build et boucle principale**

  * Makefile strict (`-Wall -Wextra`, `-lMLV`, flag POSIX pour `clock_gettime`).

  * Définition de l'état global (`struct Jeu`).

  * Boucle de jeu de base (limite de FPS, un seul `MLV_actualise_window()`).

**Critère de validation** : MLV tourne chez nous trois, `make` est clean, la fenêtre s'ouvre.

## Phase 1 - Core Gameplay

* **Lot 1 (Membre A) : Moteur de déplacement**

  * Chargement d'un niveau 1 statique (fichier ou constante).

  * Déplacement du joueur sur la grille avec cooldown.

  * Gestion des collisions contre les murs (un joueur qui traverse un mur est un bug, pas une feature).

* **Lot 2 (Membre B) : Logique des explosifs**

  * Pose de bombe (vérification de case valide).

  * Minuteur strict basé sur `clock_gettime` (indépendant du framerate).

  * Rayon d'explosion (4 directions, arrêt sur murs durs, destruction murs cassables) et kill du joueur.

* **Lot 3 (Membre C) : Rendu et I/O**

  * Moteur de rendu (plateau, entités, FX d'explosions).

  * Input clavier (Flèches/ZQSD, pose bombe, gestion des touches maintenues).

  * Conditions de victoire/défaite.

**Critère de validation** : Le niveau 1 est jouable de A à Z. Code croisé et compris.

## Phase 2 - UI, Sauvegarde et State

*Rotation des rôles pour toucher à de nouveaux domaines.*

* **Lot 1 (Membre B) : Système de sauvegarde**

  * Format texte clair (facile à parser et à débugger).

  * 4 slots gérant l'état complet (plateau, entités, niveau actuel).

  * Gestion des I/O (fichiers manquants ou corrompus = pas de crash, on gère les pointeurs NULL avec dignité).

* **Lot 2 (Membre C) : Interfaces**

  * Menus (Main, Pause) et transitions d'états.

  * Gestion propre des inputs de l'UI (clics et touches).

* **Lot 3 (Membre A) : Logique de scoring**

  * Algorithme de score (points par destruction, bonus temps/niveau).

  * Persistance du Top 10 sur disque, tri et affichage.

  * Sécurité sur l'I/O du fichier de scores.

**Critère de validation** : Cycle complet fonctionnel (Lancer > Jouer > Pause > Save > Quit > Load). Persistance vérifiée.

## Phase 3 - Génération procédurale

* **Lot 1 (Membre C) : Générateur de grille**

  * Piliers fixes, distribution aléatoire des murs destructibles.

  * Garantie algorithmique d'une zone de spawn sécurisée.

* **Lot 2 (Membre A) : Validation topologique**

  * Algorithme de parcours (type BFS) depuis le spawn pour certifier que tous les murs cassables sont atteignables.

  * Tests automatisés (ex: 1000 seeds générées sans map invalide).

* **Lot 3 (Membre B) : Boucle de progression**

  * Mécanique de passage au niveau suivant, scaling de la difficulté (densité des murs).

  * Intégration de la progression à l'état de sauvegarde et au score.

**Critère de validation** : 10 niveaux générés et enchaînés sans crash ni blocage topologique.

## Phase 4 - Features additionnelles

*Proposition à valider : Power-ups et Time Attack.*

* **Lot 1 (Membre C) : Drops et Power-ups**

  * Apparition RNG de bonus à la destruction des murs.

  * Types de mods : portée, max bombes, vitesse.

* **Lot 2 (Membre A) : Implémentation des mods**

  * Intégration des modificateurs de stats dans les modules core (joueur, bombes).

  * Sérialisation des stats dans la sauvegarde.

* **Lot 3 (Membre B) : Système de chronométrage**

  * Chronomètre temps réel (horloge système).

  * Enregistrement des meilleurs temps, UI de fin.

  * HUD en jeu (temps, niveau, buffs actifs) et documentation Doxygen si le temps le permet.

**Critère de validation** : Features stables et documentées dans le README.

## Phase 5 - QA, Build final et Soutenance

* **Lot 1 (Membre A) : Documentation et Package**

  * Rédaction du README (build, archi data, règles de score).

  * Création de l'archive propre (sources, headers, Makefile, assets. Pas de dossier `.git`, on évite l'archive de 50 Mo).

* **Lot 2 (Membre B) : Audit de robustesse**

  * Tests aux limites (inputs erronés, corruption de fichiers de save).

  * Audit mémoire : Valgrind est notre berger, nous ne manquerons de rien. Chasse aux fuites et aux warnings.

* **Lot 3 (Membre C) : Déploiement cible**

  * Test blanc sur machine TP UJM : extraction, build silencieux, run complet.

  * Préparation des questions techniques.

*On prévoit une soutenance blanche : chacun explique un module qu'il n'a pas codé pour valider la compréhension.*

## Décisions techniques à figer ensemble

* Attribution des rôles (A, B, C) selon les profils de chacun.

* Dates clés : Code freeze et répétition de la soutenance.

* Moteur physique : déplacement case par case strict (recommandé) ou interpolation en pixels.

* Constantes d'équilibrage : taille de map (ex: 15x13), durée de la bombe (2s), rayon initial.

* Format de sauvegarde (texte recommandé).

* Validation des 2 features additionnelles.

* Stack de gestion de projet (GitHub Issues, Trello, etc.).