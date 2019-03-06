# audio-synth


[![pipeline status](https://gitlab.insa-rennes.fr/hfief/audio-synth/badges/master/pipeline.svg)](https://gitlab.insa-rennes.fr/hfief/audio-synth/commits/master)

Synthétiseur audio en C (bibliothèque SDL2). Projet 3ème année EII INSA Rennes.

## Dépendances
Librairie SDL2:
```bash
$ sudo apt-get install libsdl2-dev
```

## Build
Executez le script :

```bash
$ ./build.sh
```

Le projet devrait compiler.

## Run
Compilez puis executez le script :

```bash
$ ./run.sh
```

Le projet devrait s'executer.


## Tests
Compilez puis executez le script :

```bash
$ ./test.sh
```

Le projet devrait executer les programme de test.

Utilisez l'option `-V` pour passer en mode verbose et voir le détail des tests :
```bash
$ ./test.sh -V
```

## Code coverage
Compilez puis executez le script :

```bash
$ ./coverage.sh
```
La couverture est accessible depuis doc/coverage/index.html

## Générer documentation HTML
Tapez la commande suivante.
```bash
$ doxygen doc/Doxyfile
```
La documentation est accessible depuis doc/doxygen/index.html

## Utiliser IDE : CLion
Ouvrez la racine du projet comme projet CLion, puis recharger Cmake en cliquant sur : "file/Reload Cmake Project".
Vous pouvez choisir dans le menu déroulant de la barre d'outil de compilation la cible entre "audio_synth" pour le projet et "audio_synth_test" pour les tests.
Vous pouvez maintenant compiler.
