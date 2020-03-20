# boost-shared-mem-child-python

This container will use a build container to create a runtime container that will read out a value from shared memory. It uses [Boost.python](https://www.boost.org/doc/libs/1_72_0/libs/python/doc/html/index.html), [Boost.Interprocess](https://www.boost.org/doc/libs/1_72_0/doc/html/interprocess.html) and is meant to be used in conjunction with [my boost-shared-mem test project](https://github.com/aidandj/boost-shared-mem)

## Architecture

* Uses a parent container based off of my other shared mem project
* Implements a Boost python module that reads from the shared memory.
* Exits if the shared value isn't correct.