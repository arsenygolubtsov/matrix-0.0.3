[![Build Status](https://travis-ci.org/arsenygolubtsov/matrix-0.0.3.svg?branch=master)](https://travis-ci.org/arsenygolubtsov/matrix-0.0.3)

```
cmake -H. -B_builds -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON
cmake --build _builds
cmake --build _builds --target test -- ARGS=--verbose
_builds/example
```
