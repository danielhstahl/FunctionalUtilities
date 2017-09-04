| [Linux][lin-link] | [Windows][win-link] | [Codecov][cov-link] |
| :---------------: | :-----------------: | :-------------------: |
| ![lin-badge]      | ![win-badge]        | ![cov-badge]          |

[lin-badge]: https://travis-ci.org/phillyfan1138/FunctionalUtilities.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/phillyfan1138/FunctionalUtilities "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/4xusch0q6s830d3n?svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/phillyfan1138/functionalutilities "AppVeyor build status"
[cov-badge]: https://codecov.io/gh/phillyfan1138/FunctionalUtilities/branch/master/graph/badge.svg
[cov-link]:  https://codecov.io/gh/phillyfan1138/FunctionalUtilities

## This library may become outdated with C++17's parallel STL containers!

See [this description of c++17](http://www.modernescpp.com/index.php/c-17-new-algorithm-of-the-standard-template-library).

## Functional Utilities
These utilities run in the futilities namespace and are header only.  To run the unit tests, `make` and `./test`



## API definitions

When there is a "copy" in the title of the function, a new array (with potentially different signature) is returned.  This is useful for "purer" functional programming since it retains two arrays but is less efficient.  Note that it is also useful if you want to transform the type of the array; eg from a vector of doubles to a vector of complex<double>'s.
 