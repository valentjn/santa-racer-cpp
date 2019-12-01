Santa Racer
===========

Santa Racer is an open-source clone of “Nikolaus Express 2000,” a Christmas-themed advergame/screensaver by German advertising agency Anders und Seim Neue Medien AG. The goal is to steer Santa's sleigh over the roofs of a snowy village and to drop presents into chimneys to score points.

The source code has been written entirely from scratch, so it does not infringe any copyright.

This repository is pretty useless without the image/sound assets, which may be extracted from the original game by reverse engineering. While this is a somewhat gray area, distributing the assets would definitely be illegal, which is why they are missing here. Sorry!

The best option would be if someone could recreate the assets from scratch.

Requirements
------------

* CMake 3.13+
* SDL 1.2
* SDL_image 1.2
* SDL_mixer 1.2

How to Compile and Run
----------------------

```bash
cmake -B build
cmake --build build -j
build/santa-racer
```
