# libgroove

Music player backend library.

## Features

 * Uses [libav](http://www.libav.org/) for robust decoding and encoding.
   - [list of supported formats](http://www.libav.org/general.html#Supported-File-Formats-and-Codecs)
 * Add and remove entries on a playlist for gapless playback.
 * Supports idempotent pause, play, and seek.
 * Read and write metadata tags for every format.
 * [EBU R 128](http://tech.ebu.ch/loudness) loudness scanning for every format.
   - add files to a batch job and monitor progress
 * Loudness compensation using ReplayGain tags during playback.

## Dependencies

You will need these to compile libgroove. These are most likely in your
distribution's package manager.

 * [libbz2](http://www.bzip.org/)
 * [yasm](http://yasm.tortall.net/)
 * [cmake](http://www.cmake.org/)
 * [libsdl2-dev](http://www.libsdl.org/)

### Bundled Dependencies

These are bundled with libgroove. You don't need to do anything except
appreciate them.

Once libav makes a debian upstream release, we will no longer bundle these
dependencies and instead make our own debian upstream release.

 * [libav](http://libav.org)
 * [libebur128](https://github.com/jiixyj/libebur128)

## Installation

 1. Once you have the dependencies installed, you can use `make` to build
    libgroove.so. Using the `-jx` option where x is how many cores you have
    is recommended.
 2. Next install libgroove to your system with `make install`. You will need
    root privileges if you leave the `PREFIX` variable to its default, which
    is `/usr/local`.
 3. With libgroove installed in your system, you can compile the examples with
    `make examples`.
 4. Optionally you can install the examples to your system with
   `make install-examples`. These examples are:
    * `playlist` - play a series of songs with gapless playback
    * `metadata` - read or update song metadata
    * `replaygain` - recursively scan a set of directories, sort into albums,
      and then perform replaygain scanning using the EBU R 128 standard.

## Projects Using libgroove

Feel free to make a pull request adding yours to this list.

 * [TrenchBowl](https://github.com/superjoe30/TrenchBowl) - a simple Qt GUI
   on top of libgroove.
 * [node-groove](https://github.com/superjoe30/node-groove) -
   [Node.js](http://nodejs.org/) bindings to libgroove.
