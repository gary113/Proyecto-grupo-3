#include "pantallas.hpp"

void pantallaRepartidor(){
	system("cls");
	string id,contra,opcion;
	cout << "\n\t\tBienvenido a la interfaz de Repartidores" << endl;
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Ingresar" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Regresar" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		ingresarRepartidor();
	}else if(opcion=="2"){
		registrarRepartidor();
	}else if(opcion=="3"){
		pantallaPrincipal();
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		cout << "Por favor elija una opcion valida" << endl;
		Sleep(2000);
		pantallaRepartidor();
	}
}


void ingresarRepartidor(){
	system("cls");
	string usuario;
	string contrasenia;
	cout << "\n\t\tBienvenido a la interfaz de identificacion de Repartidores" << endl;
	cout << "\nPor favor ingrese su nombre de usuario: ";
	cin >> usuario;
	string rutaArchivo="../archivos/repartidores/listaRepartidores.txt";
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		bool encontrado=false;
		string linea;
		string usuarioReal;
		while(!archivo.eof() && encontrado==false){ //Esto es para buscar si el usuario existe y guardar esa linea
			getline(archivo,linea);
			if(linea!=""){
				if(linea.find(usuario)<100){
					stringstream ss(linea);
					int i=0;
					while(i<4){
						getline(ss,usuarioReal,'|');
						i++;
					}
					encontrado=true;
				}
			}
		}
		archivo.close();
		if(encontrado==true){
			cout << "\nBienvenido " << usuarioReal << endl;
			cout << "\nPor favor ingrese su contrasenia: ";
			cin >> contrasenia;
			string contraReal;
			int i=0;
			stringstream ss(linea);
			while(i<6){
				getline(ss,contraReal,'|'); //Esto es para extraer la contraseña real de la lina de texto del archivo
				i++;
			}
			i=0;
			while(contrasenia!=contraReal && i<3){
				if(i==2){
					cout << "\nContrasenia incorrecta, le queda 1 intento: ";
				}else{
					cout << "\nContrasenia incorrecta, le quedan " << (3-i) << " intentos: ";
				}
				cin >> contrasenia;
				i++;
			}
			if(contrasenia!=contraReal && i==3){ //Para extraer el correo, el usuario y la contrasenia de la linea de texto del archivo, en caso de fallar 3 veces
				stringstream ss(linea);
				int j=0;
				string dato,usuario,correo,contrasenia;
				while(j<8){
					getline(ss,dato,'|');
					if(j==3){
						usuario=dato;
					}else if(j==4){
						correo=dato;
					}else if(j==5){
						contrasenia=dato;
					}
					j++;
				}
				cout << "\nFallo tres veces al ingresar la contrasenia, por favor revise su correo:\n" << endl;
				cout << correo << endl;
				cout << "\nEncontrara sus credenciales en el correo";
				string rutaArchivo1="../archivos/repartidores/recuperacion/"+correo+".txt";
				ofstream archivo1;
				archivo1.open(rutaArchivo1.c_str());
				if(archivo1.is_open()){
					archivo1 << "Saludos " << usuario << ", estos son sus datos para iniciar sesion:" << endl;
					archivo1 << "\nNombre de usuario: " << usuario << endl;
					archivo1 << "Contrasenia: " << contrasenia;
				}else{
					cout << "El archivo no pudo abrirse" << endl;
				}
				archivo1.close();
				Sleep(5000);
				exit(0);
			}else{
				repartidorLogeado(usuario);
			}
		}else{
			cout << "\nEl nombre de usuario no se encuentra registrado, por favor intente nuevamente" << endl;
			Sleep(3000);
			ingresarRepartidor();
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
}


void registrarRepartidor(){
	struct repartidor r;
	system("cls");
	cout << "\n\t\tBienvenido a la interfaz de registro de repartidores\n" << endl;
	cout << "Por favor, ingrese su nombre:" << endl;
	cin.ignore();
	getline(cin, r.nombre);
	bool encontrado=buscarPalabraRepartidor(r.nombre);
	if(encontrado==true){
		do{
			cout << "\nEse nombre de repartidor ya se encuentra registrado, por favor escriba otro:" << endl;
			getline(cin, r.nombre);
			encontrado=buscarPalabraRepartidor(r.nombre);
		}while(encontrado==true);
	}
	cout <<"\nPor favor, ingrese su numero telefonico o celular:" << endl;
	cin >> r.numero;
	cout <<"\nPor favor, ingrese su DNI:" << endl;
	cin >> r.dni;
	encontrado=buscarPalabraTienda(r.dni);
		if(encontrado==true){
			do{
				cout << "\nEse usuario ya se encuentra en uso, por favor elija otro:" << endl;
				cin >> r.dni;
				encontrado=buscarPalabraTienda(r.dni);
			}while(encontrado==true);
		}
	cout << "\nPor favor escriba el usuario que desea para ingresar a la aplicacion:" << endl;
	cin >> r.usuario;
	encontrado=buscarPalabraRepartidor(r.usuario);
		if(encontrado==true){
		do{
			cout << "\nEse usuario ya se encuentra en uso, por favor elija otro:" << endl;
			cin >> r.usuario;
			encontrado=buscarPalabraRepartidor(r.usuario);
		}while(encontrado==true);
	}
	cout << "\nPor favor escriba su correo electronico: " << endl;
	cin >> r.correo;
	encontrado=buscarPalabraRepartidor(r.correo);
	if(encontrado==true){
		do{
			cout << "\nEse correo ya se encuentra registrado, por favor escriba otro:" << endl;
			cin >> r.correo;
			encontrado=buscarPalabraRepartidor(r.correo);
		}while(encontrado==true);
	}
	r.crearContrasenia();
	r.puntuacion=0;
	r.numPuntuaciones=0;
	r.agregarRepartidor();
	r.crearArchivoConfirmacion();
	cout << "\nRepartidor registrado con exito" << endl;
	cout << "Recibira un correo de confirmacion";
	cout << "Sus datos seran revisados y se le notificara cuando su cuenta sea activada" << endl;
	Sleep(3000);
	exit(0);
}

void repartidorLogeado(string usuario){
	system("cls");
	struct repartidor repartidor=obtenerRepartidor(usuario);
	string opcion;
	cout << "\n\t\t\tInterfaz de Repartidores" << endl<<endl;
	cout << "Bienvenido " << repartidor.nombre << endl;
	if(repartidor.numPuntuaciones>0){
		cout << "Su puntuacion actual es: " << repartidor.puntuacion << " [1-10]"<< endl;
		cout << "De un total de: " << repartidor.numPuntuaciones << " puntuaciones" << endl;
	}
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Tomar un pedido" << endl;
	cout << "2. Finalizar pedido (pedido entregado)" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		tomarPedido(repartidor);
	}else if(opcion=="2"){
		finalizarPedido(repartidor);
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		while(true){
			cout << "\nIngrese una opcion valida: ";
			cin >> opcion;
			if(opcion=="1"){
				tomarPedido(repartidor);
			}else if(opcion=="2"){
				finalizarPedido(repartidor);
			}else if(opcion=="0"){
				cerrarApp();
			}
		}
	}
}

void tomarPedido(struct repartidor repartidor){
	system("cls");
	unsigned int opcionPedido=0;
	string opcion;
	vector <struct pedidoDisponible> pedidosDisponibles=obtenerPedidosDisponibles();
	imprimirPedidosDisponibles(pedidosDisponibles);
	cout << "\nIngrese el numero del pedido que desea tomar o digite 0 para volver: ";
	cin >> opcionPedido;
	if(opcionPedido>0 && opcionPedido<=pedidosDisponibles.size()){
		cout << "\nEsta seguro que desea tomar el pedido seleccionado? (S/N): ";
		cin >> opcion;
		if(opcion=="s" || opcion=="S"){
			BorrarPedidoTomar(pedidosDisponibles[opcionPedido-1].telefonoComprador,pedidosDisponibles[opcionPedido-1].horaPedido,repartidor);
			cout << "\nPedido tomado con exito" << endl;
			Sleep(2000);
			repartidorLogeado(repartidor.usuario);
		}else if(opcion=="n" || opcion=="N"){
			tomarPedido(repartidor);
		}else{
			while(true){
				cout << "\nPor favor elija una opcion valida: ";
				cin >> opcion;
				if(opcion=="s" || opcion=="S"){
					BorrarPedidoTomar(pedidosDisponibles[opcionPedido-1].telefonoComprador,pedidosDisponibles[opcionPedido-1].horaPedido,repartidor);
					cout << "\nPedido tomado con exito" << endl;
					Sleep(2000);
					repartidorLogeado(repartidor.usuario);
				}else if(opcion=="n" || opcion=="N"){
					tomarPedido(repartidor);
				}
			}
		}
	}else if(opcionPedido==0){
		repartidorLogeado(repartidor.usuario);
	}else{
		cout << "Por favor elija una opcion valida" << endl;
		Sleep(2000);
		tomarPedido(repartidor);
	}
}

void finalizarPedido(struct repartidor repartidor){
	system("cls");
	unsigned int opcionPedido=0;
	string opcion;
	vector <struct pedidoHistorial> pedidosTomados=obtenerPedidosTomados(repartidor);
	imprimirPedidosTomados(pedidosTomados);
	cout << "\nIngrese el numero del pedido que desea finalizar o digite 0 para volver: ";
	cin >> opcionPedido;
	if(opcionPedido>0 && opcionPedido<=pedidosTomados.size()){
		cout << "\nDesea finalizar el pedido seleccionado? (Ya fue entregado) (S/N): ";
		cin >> opcion;
		if(opcion=="s" || opcion=="S"){
			FinalizarPedidoHistorial(pedidosTomados[opcionPedido-1].telefonoComprador,pedidosTomados[opcionPedido-1].horaPedido);
			cout << "\nPedido finalizado con exito" << endl;
			Sleep(2000);
			repartidorLogeado(repartidor.usuario);
		}else if(opcion=="n" || opcion=="N"){
			finalizarPedido(repartidor);
		}else{
			while(true){
				cout << "\nPor favor elija una opcion valida";
				cin >> opcion;
				if(opcion=="s" || opcion=="S"){
					FinalizarPedidoHistorial(pedidosTomados[opcionPedido-1].telefonoComprador,pedidosTomados[opcionPedido-1].horaPedido);
					cout << "\nPedido finalizado con exito" << endl;
					Sleep(2000);
					repartidorLogeado(repartidor.usuario);
				}else if(opcion=="n" || opcion=="N"){
					finalizarPedido(repartidor);
				}
			}
		}
	}else if(opcionPedido==0){
		repartidorLogeado(repartidor.usuario);
	}else{
		cout << "\nPor favor ingrese una opcin valida" << endl;
		Sleep(2000);
		finalizarPedido(repartidor);
	}
}
