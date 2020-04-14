#include "algoritmos.h"

unsigned long long karatsuba (unsigned long long &u, unsigned long long &v) {
	unsigned long long dig1=0, dig2=0;

	unsigned long long numDigitos = maximo(digitos(u, dig1), digitos(v, dig2));

	if (numDigitos <= 1){
		return u*v;
	}

	numDigitos = (numDigitos / 2) + (numDigitos % 2);

	unsigned long long w = primeros(numDigitos, u);
	unsigned long long x = ultimos(numDigitos, u);
	unsigned long long y = primeros(numDigitos, v);
	unsigned long long z = ultimos(numDigitos, v);

	unsigned long long p=karatsuba(w, y);
	unsigned long long q=karatsuba(x, z);
	unsigned long long wMasx = w + x;
	unsigned long long zMasy = z + y;

	unsigned long long r=karatsuba(wMasx, zMasy);

	return elevar(10, 2*numDigitos)*p+elevar(10, numDigitos)*(r-p-q)+q;
}

unsigned long long contra(unsigned long long n){
	unsigned long long arreglo[100000];
	unsigned long long j=2,k,cont=0, c=0;
	bool primo[n+1];

	for(unsigned long long i=2;i<=n;i++){
		primo[i]=true;	//supongamos que todos los numeros son primos
	}

	while(j*j<=n){					//menor multiplo
		k=j;
		while(j*k<=n){				//multiplo k*j en el intervalo
			if(primo[j*k]) primo[j*k]=false;	// multiplo no es primo
			k++;
		}
		j++;
		if(primo[j]==false) j++;
	}
	k=2;
	while(k<=n){
		if(primo[k]) {
			arreglo[cont]=k;
			cont++;

		}
		k++;
	}
	c=karatsuba(arreglo[cont-1],arreglo[cont-2]);
	return c;
}
	//cout<<"\n"<<cont; //cantidad de primos encontrados


void ordenar( vector< pair<int,int> > &p, vector<double> &a)
{


    double temp;
    pair<int,int> t;
    for(unsigned int i = 0 ; i < a.size() ;i++)
    {
        for(unsigned int j = 0 ; j < a.size() ;j++)
        {
            if(a[i]<a[j])
            {
                temp = a[i]; t = p[i];
                a[i] = a[j]; p[i] = p[j];
                a[j] = temp; p[j] = t;
            }
        }
    }
}
void envolvente(vector< pair<int,int> > &p, vector<double> &a)
{
    for(unsigned int i = 1 ; i < p.size() ; i++)
    {
        if(((p[i].first-p[i-1].first)*(p[i+1].second-p[i].second)-(p[i].second-p[i-1].second)*(p[i+1].first-p[i].first)) < 0)
        {
            p.erase(p.begin()+i);
            a.erase(a.begin()+i);
            i--;
        }
    }
}
void funcion_Distan(vector< pair<int,int> > &puntos,int a, int b){
	float aux;
	int tam=puntos.size();
	float arreglo[100];
	vector< pair<int,int> > pun(1);
 	for(int i=0;i<tam;i++){
		arreglo[i]=sqrt(pow(puntos[i].first-a,2)+pow(puntos[i].second-b,2));
	}
	for(int i=0;i<tam;i++){
		for(int j=i+1;j<tam;j++){
			if(arreglo[i]>arreglo[j]){
			aux=arreglo[i];
			arreglo[i]=arreglo[j];
			arreglo[j]=aux;
			pun[1]=puntos[i];
			puntos[i]=puntos[j];
			puntos[j]=pun[1];
			}
		}
	}
	//cout<<"los 3 puntos mas cercanos con dichas distaciias son "<<endl;
	cout<<"El punto "<<"("<<puntos[0].first<<","<<puntos[0].second<<")"<<" con distancia: "<<arreglo[0]<<endl;
	cout<<"El punto "<<"("<<puntos[1].first<<","<<puntos[1].second<<")"<<" con distancia: "<<arreglo[1]<<endl;
	cout<<"El punto "<<"("<<puntos[2].first<<","<<puntos[2].second<<")"<<" con distancia: "<<arreglo[2]<<endl<<endl;
}

