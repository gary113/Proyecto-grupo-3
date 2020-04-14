#include "utilitarios.h"

int elevar(unsigned long long x, unsigned long long y) {
	if (y == 0){
		return 1;
	}else if (y == 1){
		return x;
	}else{
		return x * elevar(x, y-1);
	}
}

int digitos (unsigned long long n, unsigned long long &dig) {
	if (n < 10){
	return dig+1;
	}else{
		dig++;
		return digitos(n/10, dig);
	}
}

int primeros(unsigned long long digitos, unsigned long long &numero) {
	return numero/elevar(10, digitos);
}

int ultimos(unsigned long long digitos, unsigned long long &numero) {
	return numero % elevar(10, digitos);
}

int maximo(unsigned long long u,unsigned long long v){
	if (u>=v){
		return u;
	}else{
	return v;
	}
}



