# audio-synth

[Initially posted on school's GitLab. Therefore, contributors and Continuous Integration may not be shown properly]


[![pipeline status](https://gitlab.insa-rennes.fr/hfief/audio-synth/badges/master/pipeline.svg)](https://gitlab.insa-rennes.fr/hfief/audio-synth/commits/master)    [![coverage report](https://gitlab.insa-rennes.fr/hfief/audio-synth/badges/master/coverage.svg)](https://gitlab.insa-rennes.fr/hfief/audio-synth/commits/master)


Audio synthesizer coded in C (SDL2 lib). This is a 3y degree school project at INSA Rennes, France.

## Dependencies
You will need the SDL2 library, the SDL2-image and SDL2-tff libraries, the sndfile library and the libxml2 library for the programm to work.
```bash
$ sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsndfile1-dev libxml2-dev
```

## Build
Execute the following script:

```bash
$ ./build.sh
```

Project should compile.

## Run
Compile then run this script:

```bash
$ ./run.sh
```

Project should run.


## Tests
Compile then run this script:

```bash
$ ./test.sh
```

Project should run the tests.

Use the option `-V` to use verbose mode and lookat detailed test report:
```bash
$ ./test.sh -V
```

## Code coverage
Compile then run this script:

```bash
$ ./coverage.sh
```
Code coverage is accessible from doc/coverage/index.html

## Generate HTML code documentation
Run the following command:
```bash
$ doxygen doc/Doxyfile
```
Documentation is accessible from doc/doxygen/index.html

## Use CLion IDE
- Open project root as CLion project.
- Reload Cmake by clicking on "file/Reload Cmake Project".
- Chose build target in the drop down menu of the upper toolbar between "audio_synth" for the project and "audio_synth_test" for the tests. The others targets are for auto memory leak testing
- You can now build and run the project.

___

LICENSING

Licence for this project is available in the LICENSE file.

DSP part of filters in this project are taken from https://github.com/voidqk/sndfilter,
and are designed by Sean Connelly (@voidqk) who used the chromium code source. His work is licensed under MIT license.

SDL_Button library is licensed under the MIT License and is from author : Tim Smith (tim14smith@gmail.com).  Source : https://github.com/tim14smith/SDL_Button

Tiny file dialogs library is licensed with zlib licence. Copyright (c) 2014 - 2018 Guillaume Vareille http://ysengrin.com . Source : http://tinyfiledialogs.sourceforge.net
