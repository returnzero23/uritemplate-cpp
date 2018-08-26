URI Template C++
================

This is a C++ implementation of [RFC6570](http://tools.ietf.org/html/rfc6570) - URI Template, and can expand templates up to and including Level 4 in that specification.

Usage
------------

```cpp
#include "uritemplate.hpp"

using UriTemplate = uritemplatecpp::UriTemplate;

int main(){
	UriTemplate uri("{hello}");
	uri.set("hello","world");
	assert(uri.build() == "world");
	return 0;
}
```

License
-------
Copyright (c) 2018 ReturnZer0

MIT License, see http://mit-license.org/

