# PG
PG Engine is a cross platform, open source 2D game engine.

For now PG is very bare bones and just the beginning of what I hope to become a solid choice for my 2D games, as well as games of others. Almost anything could change at this stage but I hope the core structure will be relatively stable.

# Build Instructions

More detailed build instructions / automation of build will follow, along with fixed up cmake and Windows projects.

- Clone and populate the submodules
- Place boost (http://www.boost.org/) in PG/thirdparty/boost/. At the time of writing the current version 1.64.0 works.
- On macOS and Windows, place SFML 2.4.2 (https://www.sfml-dev.org/) in PG/internal/sfml. You will need to bring the frameworks to the top level on macOS. For Linux install SFML using your distribution's package manager.

Project files for Xcode and Visual Studio can be found for the three projects (PG itself, the test app and the unit tests). For Linux cmake files are provided. For best results use these in a "build" subdirectory. One day the Xcode and VS project files may be generated from the cmake projects.
