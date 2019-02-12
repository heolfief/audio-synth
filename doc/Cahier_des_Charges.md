# Specs


- **MIDI**
    - Enregistrement de ce qui à été joué vers fichier MIDI
    - Notes jouables au clavier, puis iterfaçage clavier MIDI
    - Lecture de fichiers MIDI

- **Enregistrement du son en WAVE**


- **Polyphonique: 10 notes à la foix max**
    - Laisser un overhead pour l'amplitude du son. Prévoir un limiteur hardcodé pour sécuriser les amplitudes trop fortes (overflows)

- **3x VCO par note:**
  - waveform : sinus, carré, rampe
  - detune de +- 12notes par VCO
  - Amplitude
  - Rapport cyclique variable


- **Enveloppe sonore (ADSR)**
  - Attack
  - Decay
  - Sustain
  - Release
  - Indépendant pour les 3 VCO


- **Filtres :**
Chaine d'effets fixe. Effets indépendaments activables. Actif sur les 3 voix d'un coup. Paramétriques
  - distortion (utilisateur : possibilité de changer l'algo de compression, voir d'en écrire un mathématiquement)
  - compresseur
  - delay
  - passe bas
  - passe haut
  - LFO (oscillateur basse frequence comme modulant): modulation d'amplitude, passe bas, flanger


- **Presets :**
  - Possibilité de sauvegarder les réglages actuels et de les charger
  
- **Interface**
  - paramétrisation par bouton tournant, ou jauge
  - valeur numérique disponible directement ou en fichier txt
  - bouton master pour un réglage unique


- **BONUS**
    - Convertir le projet en VST pour intégration dans un DAW