# Vector

A _dynamic_ array modelled after C++'s `std::vector` and Python's `list`.

|    **Method**    	| **Worst** 	| **Average** 	|
|:----------------:	|:---------:	|:-----------:	|
|    `newVector`   	|   _O(1)_  	|    _O(1)_   	|
|   `freeVector`   	|   _O(n)_  	|    _O(n)_   	|
|   `cleanVector`  	|   _O(n)_  	|    _O(n)_   	|
|  `lPopVectorEl`  	|   _O(n)_  	|    _O(n)_   	|
|  `rPopVectorEl`  	|   _O(1)_  	|    _O(1)_   	|
|  `lPushVectorEl` 	|   _O(n)_  	|    _O(n)_   	|
|  `rPushVectorEl` 	|   _O(n)_  	|    _O(1)_   	|
|   `getVectorEl`  	|   _O(1)_  	|    _O(1)_   	|
|   `setVectorEl`  	|   _O(1)_  	|    _O(1)_   	|
| `deleteVectorEl` 	|   _O(k)_  	|    _O(k)_   	|
| `insertVectorEl` 	|   _O(n)_  	|    _O(k)_   	|
