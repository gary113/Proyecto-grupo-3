#include "pantallas.hpp"

void pantallaPrincipal(){
	system("cls");
	string opcion;
	cout << "\n\t\t\t\tBodegas Delivery" << endl;
	cout << "\nQue tipo de usuario es?" << endl;
	cout << "1. Comprador" << endl;
	cout << "2. Repartidor" << endl;
	cout << "3. Tienda" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		pantallaComprador();
	}else if(opcion=="2"){
		pantallaRepartidor();
	}else if(opcion=="3"){
		pantallaTienda();
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		while(true){
			cout << "Ingrese una opcion valida: ";
			cin >> opcion;
			if(opcion=="1"){
				pantallaComprador();
			}else if(opcion=="2"){
				pantallaRepartidor();
			}else if(opcion=="3"){
				pantallaTienda();
			}else if(opcion=="0"){
				cerrarApp();
			}
		}
	}
}

