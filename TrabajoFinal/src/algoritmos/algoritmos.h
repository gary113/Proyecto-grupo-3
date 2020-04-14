
#include<iostream>
#include<string.h>
#include<climits>
#include<vector>
#include<math.h>
#include<utility>
#include<algorithm>

#include "../utilitarios/utilitarios.h"
using namespace std;
#ifndef ALGORITMOS_ALGORITMOS_HPP_
#define ALGORITMOS_ALGORITMOS_HPP_

unsigned long long karatsuba (unsigned long long &u, unsigned long long &v);
unsigned long long contra(unsigned long long n);
void ordenar( vector< pair<int,int> > &p, vector<double> &a);
void envolvente(vector< pair<int,int> > &p, vector<double> &a);
void funcion_Distan(vector< pair<int,int> > &puntos,int a, int b);




#endif /* ALGORITMOS_ALGORITMOS_HPP_ */
