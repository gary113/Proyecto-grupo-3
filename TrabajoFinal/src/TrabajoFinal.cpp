#include<iostream>
#include<string.h>
#include<climits>
#include<vector>
#include<math.h>
#include<utility>
#include<algorithm>

#include "algoritmos/algoritmos.h"
using namespace std;

int main (){
	int tiempo[15],seguridad[15];
	int o=0,a=0,b=0;
	unsigned long long n,k,r;
	char id,aux,nombre;
	cout<<"Ingrese un numero (maximo 1000000): ";
	cin>>n;
	r=contra(n);
	cout<<"\n\n Tu contrasenia es: "<<r;
	cout<<"\n Ingrese contrasenia: "<<endl;cin>>k;
	if(k!=r){
	cout<<"CONTRASENIA INCORRECTA"; return 0;}
	else{
		cout<<"tenemos las siguiente opciones a elegir en delivery "<<endl;
		cout<<"1. Bebidas"<<endl;
		cout<<"2. Hambuergeza"<<endl;
		cout<<"3. Pizzas"<<endl;
		cout<<"4. Helados"<<endl;
		cout<<"5. Pollo a la brasa"<<endl;
		cout<<"eliga su opcion: ";
		cin>>o;
		cout<<endl;
		cout<<"\nNuestros puntos de encuentros disponibles  son : "<<endl<<endl;
		cout<<"Tottus de chorrillos"<<"(2,4)"<<endl;
		cout<<"plaza norte"<<"(4,2)"<<endl;
		cout<<"Plaza lima sur"<<"(7,1)"<<endl;
		cout<<"Mall aventura plaza"<<"(3,7)"<<endl;
		cout<<"Real plaza"<<"(6,5)"<<endl;
		cout<<"Galaxy plaza"<<"(8,3)"<<endl;
		cout<<"Metro UNI"<<" (10,2)"<<endl;
		cout<<"Jiron de la union"<<"(5,9)"<<endl;
		cout<<"Aeropuerto"<<"(9,9)"<<endl;
		cout<<"Universidad Nacional de Ingenieria"<<"(11,6)"<<endl;
		cout<<"Galaxy plaza de Miraflores"<<"(13,4)"<<endl<<endl;

		cout<<"Ingresar su ubicacion"<<endl;
		cin>>a;
		cin>>b;
		cout<<"Los tres puntos de encuentros mas cercanos son: "<<endl<<endl;
		vector< pair<int,int> > puntos(11);
    	vector<double> angulos(11,0.0);
		puntos[0].first=2;
        puntos[0].second=4;
        puntos[1].first=4;
        puntos[1].second=2;
        puntos[2].first=7;
        puntos[2].second=1;
        puntos[3].first=3;
        puntos[3].second=7;
        puntos[4].first=6;
        puntos[4].second=5;
        puntos[5].first=8;
        puntos[5].second=3;
        puntos[6].first=10;
        puntos[6].second=2;
        puntos[7].first=5;
        puntos[7].second=9;
        puntos[8].first=9;
        puntos[8].second=9;
        puntos[9].first=11;
        puntos[9].second=6;
        puntos[10].first=13;
        puntos[10].second=4;

    int men = 0;
    for(int i = 0 ; i < 11 ; i++)
    {
        if(puntos[i].second < puntos[men].second)
            men = i;
        else if(puntos[i].second == puntos[men].second)
            if(puntos[i].first < puntos[men].first)
               men = i;
    }
    for(int i = 0 ; i < 11 ; i++)
        if(i != men)
            angulos[i] = acos((puntos[i].first-puntos[men].first)/sqrt(pow(puntos[i].first-puntos[men].first,2)+pow(puntos[i].second-puntos[men].second,2)));

    ordenar(puntos,angulos);
    envolvente(puntos,angulos);


    funcion_Distan(puntos,a,b);

    	tiempo[0]=4;seguridad[0]=9;
       	tiempo[1]=6;seguridad[1]=5;
		tiempo[2]=7;seguridad[2]=1;
		tiempo[3]=4;seguridad[3]=9;
       	tiempo[4]=6;seguridad[4]=5;
		tiempo[5]=7;seguridad[5]=1;
		tiempo[6]=4;seguridad[6]=9;
       	tiempo[7]=6;seguridad[7]=5;
		tiempo[8]=7;seguridad[8]=1;
    	tiempo[9]=6;seguridad[9]=5;
		tiempo[10]=7;seguridad[10]=1;

	cout<<"el punto ("<<puntos[0].first<<","<<puntos[0].second<<")"<<" tiene "<<seguridad[0]<<" estrellas de seguridad y "<<tiempo[0]<<" estrellas en tiempo de llegada"<<endl;
	cout<<"el punto ("<<puntos[1].first<<","<<puntos[1].second<<")"<<" tiene "<<seguridad[1]<<" estrellas de seguridad y "<<tiempo[1]<<" estrellas en tiempo de llegada"<<endl;
	cout<<"el punto ("<<puntos[2].first<<","<<puntos[2].second<<")"<<" tiene "<<seguridad[2]<<" estrellas de seguridad y "<<tiempo[2]<<" estrellas en tiempo de llegada"<<endl;
	cout<<endl;
	int i,j,aux,min,n=3;
	char opcion;


	for(i=0;i<n;i++){
		min = i;
		for(j=i+1;j<n;j++){
			if(tiempo[j] < tiempo[min]){
				min = j;
			}
		}
		aux = tiempo[i];
		tiempo[i] = tiempo[min];
		tiempo[min] = aux;
	}
	cout<<" El orden de merito en Tiempo es  :"<<endl<<endl;
	for(i=2;i>=0;i--){

		cout<<"El punto "<<"("<<puntos[i].first<<","<<puntos[i].second<<")"<<" tiene "<<tiempo[i]<<" estrellas en tiempo de llegada"<<endl;
	}
	cout<<endl<<endl;

	for(i=0;i<n;i++){
		min = i;
		for(j=i+1;j<n;j++){
			if(seguridad[j] < seguridad[min]){
				min = j;
			}
		}
		aux = seguridad[i];
		seguridad[i] = seguridad[min];
		seguridad[min] = aux;
	}
	cout<<" El orden de merito en seguridad es :"<<endl<<endl;
	for(i=2;i>=0;i--){

		cout<<"El punto "<<"("<<puntos[i].first<<","<<puntos[i].second<<")"<<" tiene "<<seguridad[i]<<" estrellas calidad de seguridad"<<endl;
	}

	cout<<endl;
	cout<<"Con la informacion brindada invitamos a que pueda elegir por el punto de encuentro que le parezca mas optimo"<<endl;
	cout<<"1_ "<<"("<<puntos[0].first<<","<<puntos[0].second<<")"<<endl;
	cout<<"2_ "<<"("<<puntos[1].first<<","<<puntos[1].second<<")"<<endl;
	cout<<"3_ "<<"("<<puntos[2].first<<","<<puntos[2].second<<")"<<endl;
	cout<<"Opcion : ";

	cin>>opcion;

	if(o==1){
	cout<<"Las Bebidas estan en camino al local "<<opcion;}
	else if(o==2){
	cout<<"Las Hamburgezas esta en camino al local "<<opcion;}
	else if(o==3){
	cout<<"Las Pizzas esta en camino al local "<<opcion;}
	else if(o==4){
	cout<<"Los Helado esta en camino al local "<<opcion;}
	else if(o==5){
	cout<<"El pollo a la brasa esta en camino al local "<<opcion;}
}
return 0;
}
