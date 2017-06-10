# PG
The home of the PG game engine

For now PG is very bare bones and just the beginning of what I hope to become a solid choice for my 2D games, as well as games of others. Almost anything could change at this stage but I hope the core structure will be relatively stable.

More detail build instructions will follow, along with fixed up cmake and Windows projects.

To build:

- Clone and populate the submodules
- Place boost (http://www.boost.org/) in PG/thirdparty/boost/. At the time of writing the current version 1.64.0 works.
- Place SFML 2.4.2 (https://www.sfml-dev.org/) in PG/internal/sfml. You will need to bring the frameworks to the top level on macOS.
