#include "pantallas.hpp"

void pantallaTienda(){
	system("cls");
	string opcion;
	cout << "\n\t\t\tBienvenido a la interfaz de tiendas" << endl;
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Ingresar" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Regresar" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		ingresarTienda();
	}else if(opcion=="2"){
		registrarTienda();
	}else if(opcion=="3"){
		pantallaPrincipal();
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		cout << "\nPor favor ingrese una opcion valida";
		Sleep(3000);
		pantallaTienda();
	}
}

void registrarTienda(){
	struct tienda t;
	system("cls");
	cout << "\n\t\tBienvenido a la interfaz de registro de tiendas" << endl;
	cout << "\nPor favor escriba el nombre de su tienda:" << endl;
	cin.ignore();
	getline(cin, t.nombre);
	bool encontrado=buscarPalabraTienda(t.nombre);
	if(encontrado==true){
		do{
			cout << "\nEse nombre de tienda ya se encuentra registrado, por favor escriba otro:" << endl;
			getline(cin, t.nombre);
			encontrado=buscarPalabraTienda(t.nombre);
		}while(encontrado==true);
	}
	cout << "\nPor favor digite el numero telefonico o celular de contacto de su tienda:" << endl;
	cin >> t.numero;
	cout << "\nEscriba el usuario que desea para ingresar a la aplicacion:" << endl;
	cin >> t.usuario;
	encontrado=buscarPalabraTienda(t.usuario);
	if(encontrado==true){
		do{
			cout << "\nEse usuario ya se encuentra en uso, por favor elija otro:" << endl;
			cin >> t.usuario;
			encontrado=buscarPalabraTienda(t.usuario);
		}while(encontrado==true);
	}
	cout << "\nPor favor escriba el correo electronico de contacto de su tienda:" << endl;
	cin >> t.correo;
	encontrado=buscarPalabraTienda(t.correo);
	if(encontrado==true){
		do{
			cout << "\nEse correo ya se encuentra registrado, por favor escriba otro:" << endl;
			cin >> t.correo;
			encontrado=buscarPalabraTienda(t.correo);
		}while(encontrado==true);
	}
	cout << "\nPor favor escriba la direccion de su tienda:" << endl;
	cin.ignore();
	getline(cin, t.direccion);
	cout << "\nDigite las coordenadas X Y de su tienda (separadas con espacio):" << endl;
	cin >> t.coordX >> t.coordY;
	t.crearContrasenia();
	t.agregarTienda();
	t.crearArchivoConfirmacion();
	cout << "\nTienda registrada con exito" << endl;
	cout << "Recibira un correo de confirmacion";
	Sleep(5000);
	exit(0);
}

void ingresarTienda(){
	system("cls");
	string usuario;
	string contrasenia;
	cout << "\n\t\tBienvenido a la interfaz de identificacion de tiendas" << endl;
	cout << "\nPor favor ingrese su nombre de usuario: ";
	cin >> usuario;
	string rutaArchivo="../archivos/tiendas/listaTiendas.txt";
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
					while(i<3){
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
			char separador;
			while(i<8){
				if(i==7){
					separador='\n';
				}else{
					separador='|';
				}
				getline(ss,contraReal,separador); //Esto es para extraer la contraseña real de la lina de texto del archivo
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
					if(j==7){
						separador='\n';
					}else{
						separador='|';
					}
					getline(ss,dato,separador);
					if(j==2){
						usuario=dato;
					}else if(j==3){
						correo=dato;
					}else if(j==7){
						contrasenia=dato;
					}
					j++;
				}
				cout << "\nFallo tres veces al ingresar la contrasenia, por favor revise su correo:\n" << endl;
				cout << correo << endl;
				cout << "\nEncontrara sus credenciales en el correo enviado";
				string rutaArchivo1="../archivos/tiendas/recuperacion/"+correo+".txt";
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
				tiendaLogeado(usuario);
			}
		}else{
			cout << "\nEl nombre de usuario no se encuentra registrado, por favor intente nuevamente" << endl;
			Sleep(3000);
			ingresarTienda();
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
}

void tiendaLogeado(string usuario){
	system("cls");
	string opcion;
	cout << "\t\t\tInterfaz de usuarios" << endl;
	cout << "\nBienvenido, " << usuario << endl;
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Ingresar producto" << endl;
	cout << "2. Editar informacion" << endl;
	cout << "3. Eliminar cuenta" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		ingresarProducto(usuario);
	}else if(opcion=="2"){
		editarTienda(usuario);
	}else if(opcion=="3"){
		eliminarTienda(usuario);
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		while(true){
			cout << "\nPor favor ingrese una opcion valida: ";
			cin >> opcion;
			if(opcion=="1"){
				ingresarProducto(usuario);
			}else if(opcion=="2"){
				editarTienda(usuario);
			}else if(opcion=="3"){
				eliminarTienda(usuario);
			}else if(opcion=="0"){
				cerrarApp();
			}
		}
	}
}

void ingresarProducto(string usuario){
	system("cls");
	vector <string> productos;
	struct producto p;
	string opcion;
	cout << "\n\t\tBienvenido "<<usuario<< " al ingreso de productos" << endl<<endl;
	cout<<"Categorias disponibles:"<<endl;
	imprimirCategoriasProductos();
	cout<<"\nElija la categoria del producto que desea agregar: ";
	cin>>opcion;
	if(opcion=="1" || opcion=="2" || opcion=="3"){
		cout << "\nProductos en la categoria seleccionada:" << endl;
		productos=obtenerProductos(opcion);
		imprimirProductos(productos);
		cout << "\nPor favor elija un producto: ";
		string prod;
		cin >> prod;
		if(saull(prod)>=1 && saull(prod)<=productos.size()){
			p.inicializar(opcion,usuario,productos[sai(prod)-1]);
			cout << "\nPor favor ingrese el precio del producto en soles: S/.";
			cin >> p.precio;
		}else{
			while(true){
				cout << "\nPor favor elija una opcion valida: ";
				cin >> prod;
				if(saull(prod)>=1 && saull(prod)<=productos.size()){
					p.inicializar(opcion,usuario,productos[sai(prod)-1]);
					cout << "\nPor favor ingrese el precio del producto en soles: S/.";
					cin >> p.precio;
					break;
				}
			}
		}
	}else{
		cout << "\nPor favor elija una opcion valida";
		Sleep(2000);
		ingresarProducto(usuario);
	}
	p.agregarProducto();
	cout << "\nProducto ingresado con exito" << endl;
	Sleep(3000);
	tiendaLogeado(usuario);
}

void editarTienda(string usuario){
	system("cls");
	string linea;
	vector <string> vectorArchivo;
	string rutaArchivo="../archivos/tiendas/listaTiendas.txt";
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!=""){
				vectorArchivo.push_back(linea); //Creando un vector con todas las lineas del archivo
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	int posicion=0;
	for(unsigned int i=0;i<vectorArchivo.size();i++){ //Para encontrar la posicion donde se encuentra el usuario
		if(vectorArchivo[i].find(usuario)<100){
			posicion=i;
			break;
		}
	}
	linea=vectorArchivo[posicion]; //Para obtener la linea donde se encuentra el usuario y guardarla en una estructura
	struct tienda t;
	stringstream ss(linea);
	char separador;
	string dato;
	for(int i=0;i<8;i++){
		if(i==7){
			separador='\n';
		}else{
			separador='|';
		}
		getline(ss,dato,separador);
		t.ingresarDatos(i,dato);
	}
	string opcion;
	cout << "\nQue desea editar?" << endl;
	cout << "\n1. Nombre de la tienda" << endl;
	cout << "2. Numero telefonico de contacto" << endl;
	cout << "3. Correo electronico de contacto" << endl;
	cout << "4. Direccion de la tienda" << endl;
	cout << "5. Coordenadas" << endl;
	cout << "6. Contrasenia" << endl;
	cout << "\nElija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		cout << "\nNombre actual: " << t.nombre << endl;
		cout << "Escriba el nuevo nombre de la tienda: ";
		cin.ignore();
		getline(cin,dato);
		bool encontrado=buscarPalabraTienda(dato);
		if(encontrado==false){
			t.nombre=dato;
		}else{
			do{
				cout << "\nEse nombre de tienda ya se encuentra registrado, por favor escriba otro: ";
				getline(cin,dato);
				encontrado=buscarPalabraTienda(dato);
			}while(encontrado==true);
			t.nombre=dato;
		}
	}else if(opcion=="2"){
		cout << "\nNumero telefonico actual: " << t.numero << endl;
		cout << "Digite el nuevo numero telefonico: ";
		cin.ignore();
		getline(cin,dato);
		t.numero=saull(dato);
	}else if(opcion=="3"){
		cout << "\nEl correo electronico actual es: " << t.correo << endl;
		cout << "Escriba el nuevo correo electronico: ";
		cin.ignore();
		getline(cin,dato);
		bool encontrado=buscarPalabraTienda(dato);
		if(encontrado==false){
			t.correo=dato;
		}else{
			do{
				cout << "\nEse correo ya se encuentra registrado, por favor escriba otro: ";
				getline(cin,dato);
				encontrado=buscarPalabraTienda(dato);
			}while(encontrado==true);
			t.correo=dato;
		}
	}else if(opcion=="4"){
		cout << "\nDireccion actual: " << t.direccion << endl;
		cout << "Escriba la nueva direccion: ";
		cin.ignore();
		getline(cin,dato);
		t.direccion=dato;
	}else if(opcion=="5"){
		string x,y;
		cout << "\nLas coordenadas actuales son: " << t.coordX << " " << t.coordY << endl;
		cout << "Digite las nuevas coordenadas (separadas por espacio): ";
		cin >> x >> y;
		t.coordX=sai(x);
		t.coordY=sai(y);
	}else if(opcion=="6"){
		cout << "\nLa contrasenia actual es: " << t.contrasenia << endl;
		cout << "Digite la nueva contrasenia (numerica): ";
		cin.ignore();
		getline(cin,dato);
		t.contrasenia=saull(dato);
	}else{
		cout << "\nPor favor, elija una opcion valida" << endl;
		Sleep(2000);
		editarTienda(usuario);
	}
	linea=t.crearLinea();
	vectorArchivo[posicion]=linea; //Para sobreescribir la linea modificada en el vector
	string rutaArchivo1="../archivos/tiendas/listaTiendas.txt";
	ofstream archivo1;
	archivo1.open(rutaArchivo1.c_str(),ios::trunc); //Para escribir el archivo con la linea cambiada
	for(unsigned long long i=0;i<vectorArchivo.size();i++){
		archivo1 << vectorArchivo[i] << endl;
	}
	archivo1.close();
	cout << "\nCambio realizado con exito, por favor revise su correo con los nuevos datos" << endl;
	t.crearArchivoConfirmacion();
	cout << "\nDesea realizar algun otro cambio (S/N)?: ";
	cin >> opcion;
	if(opcion=="S" || opcion=="s"){
		editarTienda(t.usuario);
	}else if(opcion=="N" || opcion=="n"){
		cerrarApp();
	}else{
		while(true){
			cout << "\nPor favor elija una opcion valida: ";
			cin >> opcion;
			if(opcion=="S" || opcion=="s"){
				editarTienda(t.usuario);
			}else if(opcion=="N" || opcion=="n"){
				cerrarApp();
			}
		}
	}
}

void eliminarTienda(string usuario){
	string opcion;
	cout << "\nEsta seguro que quiere eliminar su tienda de nuestra base de datos? (S/N): ";
	cin >> opcion;
	if(opcion=="S" || opcion=="s"){
		string linea;
		vector <string> vectorArchivo;
		string rutaArchivo="../archivos/tiendas/listaTiendas.txt";
		ifstream archivo;
		archivo.open(rutaArchivo.c_str()); //Creando un vector con todas las lineas del archivo
		if(archivo.is_open()){
			while(!archivo.eof()){
				getline(archivo,linea);
				if(linea!=""){
					vectorArchivo.push_back(linea);
				}
			}
		}else{
			cout << "No se pudo abrir el archivo" << endl;
		}
		archivo.close();
		int posicion=0;
		for(unsigned int i=0;i<vectorArchivo.size();i++){ //Para encontrar la linea donde se encuentra el usuario
			if(vectorArchivo[i].find(usuario)<100){
				posicion=i;
				break;
			}
		}
		linea=vectorArchivo[posicion];
		int i=0;
		string correo;
		stringstream ss(linea);
		while(i<4){
			getline(ss,correo,'|'); //Para tener el correo al cual le enviaremos el mensaje de confirmacion
			i++;
		}
		vectorArchivo.erase(vectorArchivo.begin()+posicion); //Borrando la linea del vector
		string rutaArchivo1="../archivos/tiendas/listaTiendas.txt";
		ofstream archivo1;
		archivo1.open(rutaArchivo1.c_str(),ios::trunc); //Escribiendo el nuevo archivo sin la linea
		for(unsigned long long i=0;i<vectorArchivo.size();i++){
			archivo1 << vectorArchivo[i] << endl;
		}
		archivo1.close();
		string rutaArchivo2="../archivos/tiendas/confirmacion/"+correo+".txt";
		ofstream archivo2;
		archivo2.open(rutaArchivo2.c_str(),ios::trunc); //Escribiendo el correo de confirmacion
		archivo2 << "Su tienda fue borrada exitosamente de nuestra base de datos" << endl;
		archivo2 << "Esperamos volverlo a ver pronto";
		archivo2.close();
		cout << "\nSu tienda fue borrada exitosamente de nuestra base de datos" << endl;
		cout << "Recibira un correo de confirmacion";
		Sleep(5000);
		exit(0);
	}else if(opcion=="N" || opcion=="n"){
		tiendaLogeado(usuario);
	}else{
		cout << "\nElija una opcion valida" << endl;
		Sleep(2000);
		eliminarTienda(usuario);
	}
}


