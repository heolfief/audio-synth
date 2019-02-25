# audio-synth

Synthétiseur audio en C (bibliothèque SDL2). Projet 3ème année EII INSA Rennes.


## Auto build & Run
Executer le script :

```bash
$ ./run.sh
```

Le projet devrait compiler et s'executer.


## Manual building :


```bash
$ rm -rf build/manual && mkdir build/manual
$ cd build/manual
$ cmake ../..
$ make && make install
$ cd ../..

# Run the tests:
$ bin/audio_synth_tests

# Run the binary:
$ bin/audio_synth
```

## Tests
Tapez la commande suivante pour executer les tests :

```bash
$ ctest
```
Utilisez l'option `-V` pour passer en mode verbose et voir le détail des tests.
