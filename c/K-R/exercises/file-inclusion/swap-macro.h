#ifndef SWAP_MACRO_H
#define SWAP_MACRO_H

#define swap(t, x, y) do { 	\
	t _temp; 		\
	_temp = (x); 		\
	(x) = (y); 		\
	(y) = _temp; 		\
} while (0);

#endif
