
- Possibilité de faire un Kamblan en plus du Gand prévisionel

- Possibilité d'utiliser trello pour améliorer la coordination et synchronisation

- trie des métadonnée des fichier MIDI, suppression des paroles et autre infos inutiles.
Incription des notes et temps dans un tableau d'événements. Gestion par évenements autorise un grand nombre de polyphonie

- Synthèse audio et enveloppe OK. Les paramètres sont controlables

- Implémentation du MIDI avec le synthé en cours

- Coverage des test par ligne, on est pas à 100% car les if des mallocs pas testable par contre 100% des fonctions testées

- intégration continue > readme

- Open gl à éviter > sans rotation ou image par image

- effets et filtres sont prévu, temporisation et enveloppe

- Possibilité de récupérer de l'open source (chromnium par exemple) pour la retravailler

- SDL ne prend que le tableau d'évènement pour gérer la carte son, modèle très portable par ailleurs

- tri et ordonancement des fichiers MIDI passer plutot par la RAM car ne nécessite pas beaucoup de capa et plus rapide

- test Valgrind: SDL oublie beaucoup de mallocs, peut être séparer nos foctions de la SDL pour les tester
ou alors masquer la SDL par un flag de compil,

- Structure de donnée emboité avec les paramètre prêt à etre implémenté avec la vue
