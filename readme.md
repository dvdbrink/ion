## ion
[![Build Status](https://travis-ci.org/dvdbrink/ion.svg)](https://travis-ci.org/dvdbrink/ion)
Experimental C++14 game development framework. Not suitable for production quality software in any way whatsoever.

### Modules
* ion-ecs
* ion-gfx (todo)
* ion-gfx-d3d11 (todo)
* ion-gfx-gl
* ion-log
* ion-math
* ion-sfx (todo)
* ion-sfx-al
* ion-wnd

### Tested compilers
| OS      | Compiler    | Works |
| ------- |:-----------:| -----:|
| Linux   | Clang 3.7.0 | Yes   |
| Linux   | GCC 5.2.0   | Yes   |
| Windows | Clang 3.7.0 | No    |
| Windows | GCC 5.2.0   | Yes   |
| Windows | MSVC 14.0   | Yes   |

### Naming conventions
```c++
struct Economy
{
	bool has_crashed = false;
};

void crash_economy(Economy& economy)
{
	economy.has_crashed = true;
}

int main()
{
	Economy economy;
	crash_economy(economy);
	return economy.has_crashed;
}
```

### Third party libraries

[OpenAL Soft](http://kcat.strangesoft.net/openal.html), an LGPL-licensed, cross-platform, software implementation of the OpenAL 3D audio API.

[Sean Barrett's](https://github.com/nothings/stb) public domain image loading, ogg vorbis decoding and truetype rasterization libraries.