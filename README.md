# audio-synth

Synthétiseur audio en C (bibliothèque SDL2). Projet 3ème année EII INSA Rennes.

## Dépendances
Librairie SDL2:
```bash
$ sudo apt-get install libsdl2-dev
```

## Auto build & Run
Executer le script :

```bash
$ ./run.sh
```

Le projet devrait compiler et s'executer.


## Manual building


```bash
$ rm -rf build/manual && mkdir build/manual
$ cd build/manual
$ cmake ../..
$ make && make install
$ cd ../..

# Run the binary:
$ bin/audio_synth

# Run the tests:
$ bin/audio_synth_test
```

## Tests
Executer le script :

```bash
$ ./test.sh
```

Le projet devrait compiler et executer les programme de test.

Utilisez l'option `-V` pour passer en mode verbose et voir le détail des tests :
```bash
$ ./test.sh -V
```
## Générer documentation HTML
Tapez la commande "doxygen" depuis le dossier doc.
```bash
$ cd doc
$ doxygen
```
La documentation est accessible depuis doc/HTML/index.html

## Utiliser IDE : CLion
Ouvrez la racine du projet comme projet CLion, puis recharger Cmake en cliquant sur : "file/Reload Cmake Project".
Vous pouvez choisir dans le menu déroulant de la barre d'outil de compilation la cible entre "audio_synth" pour le projet et "audio_synth_test" pour les tests.
Vous pouvez maintenant compiler.
