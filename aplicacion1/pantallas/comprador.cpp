#include "pantallas.hpp"

void pantallaComprador(){
	system("cls");
	cout << "\n\t\tBienvenido a la interfaz de compradores" << endl;
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Ingresar" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Regresar" << endl;
	cout << "0. Salir" << endl;
	string opcion;
	cout << "\nIngrese una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		ingresarComprador();
	}else if(opcion=="2"){
		registrarComprador();
	}else if(opcion=="3"){
		pantallaPrincipal();
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		cout << "\nPor favor ingrese una opcion valida";
		Sleep(2000);
		pantallaComprador();
	}
}


void ingresarComprador(){
	system("cls");
	string linea,dato,contrasenia,nombre,contraReal,numero,pregunta,respuestaReal,respuesta;
	cout << "\n\t\tBienvenido a la interfaz de identificacion de compradores" << endl;
	cout << "\nPor favor digite su numero telefonico: ";
	cin >> numero;
	string rutaArchivo="../archivos/compradores/listaCompradores.txt";
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		bool encontrado=false;
		while(!archivo.eof() && encontrado==false){ //Esto es para buscar si el usuario existe y guardar esa linea
			getline(archivo,linea);
			if(linea!=""){
				if(linea.find(numero)<100){
					stringstream ss(linea);
					getline(ss,nombre,'|');
					encontrado=true;
				}
			}
		}
		archivo.close();
		if(encontrado==true){
			cout << "\nBienvenido " << nombre << endl;
			cout << "\nPor favor ingrese su contrasenia: ";
			cin >> contrasenia;
			int i=0;
			char separador;
			stringstream ss(linea);
			while(i<9){
				if(i==8){
					separador='\n';
				}else{
					separador='|';
				}
				getline(ss,contraReal,separador); //Esto es para extraer la contrase๑a real de la lina de texto del archivo
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
			if(contrasenia!=contraReal && i==3){
				stringstream ss(linea);
				int j=0;
				while(j<9){
					if(j==8){
						separador='\n';
					}else{
						separador='|';
					}
					getline(ss,dato,separador);
					if(j==1){
						numero=dato;
					}else if(j==6){
						pregunta=dato;
					}else if(j==7){
						respuestaReal=dato;
					}
					j++;
				}
				cout << "\nFallo tres veces al ingresar la contrasenia, por favor responda su pregunta secreta:\n" << endl;
				cout << pregunta << endl;
				cin.ignore();
				getline(cin,respuesta);
				if(respuesta!=respuestaReal){
					cout << "\nLa respueta a la pregunta secreta es incorrecta, por favor intentelo nuevamente";
					Sleep(3000);
					ingresarComprador();
				}else{
					compradorLogeado(numero);
				}
			}else{
				compradorLogeado(numero);
			}
		}else{
			cout << "\nEl numero telefonico no se encuentra registrado, por favor intente nuevamente" << endl;
			Sleep(3000);
			ingresarComprador();
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
}

void registrarComprador(){
	string preguntas[6]={"Que tipo de emascotas me gustan?","Como se llamaba mi primera mascota?","Como se llama mi mejor amigo?","Cual es mi curso favorito?","Cual es mi cancion favorita?","Donde nacio mi madre?"};
	struct comprador c;
	system("cls");
	cout << "\n\t\tBienvenido a la interfaz de registro de compradores" << endl;
	cout << "\nPor favor escriba su nombre:" << endl;
	cin.ignore();
	getline(cin, c.nombre);
	cout << "\nPor favor digite su numero telefonico o celular:" << endl;
	cin >> c.numero;
	bool encontrado=buscarPalabraComprador(ias(c.numero));
	if(encontrado==true){
		do{
			cout << "\nEse numero ya se encuentra registrado, por favor escriba otro:" << endl;
			cin >> c.numero;
			encontrado=buscarPalabraComprador(ias(c.numero));
		}while(encontrado==true);
	}
	cout << "\nPor favor escriba su correo electronico:" << endl;
	cin >> c.correo;
	encontrado=buscarPalabraComprador(c.correo);
	if(encontrado==true){
		do{
			cout << "\nEse correo ya se encuentra registrado, por favor escriba otro:" << endl;
			cin >> c.correo;
			encontrado=buscarPalabraComprador(c.correo);
		}while(encontrado==true);
	}
	cout << "\nPor favor escriba la direccion de su casa:" << endl;
	cin.ignore();
	getline(cin, c.direccion);
	cout << "\nDigite las coordenadas X Y de su casa (separadas con espacio):" << endl;
	cin >> c.coordX >> c.coordY;
	cout << "\nPor favor elija una pregunta secreta para reestablecer su contrasenia:\n" << endl;
	for(int i=0;i<6;i++){
		cout << (i+1) << ". " << preguntas[i] << endl;
	}
	string opcion;
	cout << "\nElija el numero de la pregunta: ";
	cin >> opcion;
	if(opcion=="1"){
		c.preguntaSecreta=preguntas[0];
	}else if(opcion=="2"){
		c.preguntaSecreta=preguntas[1];
	}else if(opcion=="3"){
		c.preguntaSecreta=preguntas[2];
	}else if(opcion=="4"){
		c.preguntaSecreta=preguntas[3];
	}else if(opcion=="5"){
		c.preguntaSecreta=preguntas[4];
	}else if(opcion=="6"){
		c.preguntaSecreta=preguntas[5];
	}else{
		while(true){
			cout << "\nPor favor elija una opcion valida :";
			cin >> opcion;
			if(opcion=="1"){
				c.preguntaSecreta=preguntas[0];
				break;
			}else if(opcion=="2"){
				c.preguntaSecreta=preguntas[1];
				break;
			}else if(opcion=="3"){
				c.preguntaSecreta=preguntas[2];
				break;
			}else if(opcion=="4"){
				c.preguntaSecreta=preguntas[3];
				break;
			}else if(opcion=="5"){
				c.preguntaSecreta=preguntas[4];
				break;
			}else if(opcion=="6"){
				c.preguntaSecreta=preguntas[5];
				break;
			}
		}
	}
	cout << "\nEscriba su respuesta secreta:" << endl;
	cin.ignore();
	getline(cin,c.respuestaSecreta);
	c.crearContrasenia();
	c.agregarComprador();
	c.crearArchivoConfirmacion();
	cout << "\nComprador registrado con exito" << endl;
	cout << "Recibira un correo de confirmacion";
	Sleep(5000);
	exit(0);
}


void compradorLogeado(string numero){
	system("cls");
	string opcion;
	struct comprador comprador=obtenerComprador(numero);
	cout << "\nBienvenido " << comprador.nombre << endl;
	cout << "\nOpciones disponibles" << endl;
	cout << "1. Ver estado de pedido" << endl;
	cout << "2. Comprar" << endl;
	cout << "3. Ver facturas" << endl;
	cout << "0. Salir" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		estadoPedido(comprador);
	}else if(opcion=="2"){
		compradorComprar(comprador);
	}else if(opcion=="3"){
		verFacturas(comprador);
	}else if(opcion=="0"){
		cerrarApp();
	}else{
		cout << "\nPor favor elija una opcion valida" << endl;
		Sleep(2000);
		compradorLogeado(numero);
	}
}

void verFacturas(struct comprador comprador){
	system("cls");
	string opcion;
	vector <struct pedidoHistorial> facturas=obtenerFacturas(comprador);
	imprimirFacturas(facturas);
	cout << "\nPresione 0 para volver: ";
	cin >> opcion;
	if(opcion=="0"){
		compradorLogeado(ias(comprador.numero));
	}else{
		while(true){
			cout << "\nPor favor ingrese una opcion valida:";
			cin >> opcion;
			if(opcion=="0"){
				compradorLogeado(ias(comprador.numero));
			}
		}
	}

}

void compradorComprar(struct comprador comprador){
	system("cls");
	string opcion,opcionDireccion;
	int coordx,coordy,cantidad;
	bool casa;
	cout<<"\nCategorias disponibles\n"<<endl;
	imprimirCategoriasProductos();
	cout << "\nPor favor elija una categoria o presione 0 para salir: ";
	cin>>opcion;
	if(opcion=="1" || opcion=="2" || opcion=="3"){
		if(opcion=="1" || opcion=="2" || opcion=="3"){
			cout<<"\nProductos disponibles en la categoria seleccionada:"<<endl;
			vector <string> productos=obtenerProductos(opcion);
			imprimirProductos(productos);
			cout << "\nPor favor elija el producto que desea comprar: ";
			cin>>opcion;
			string producto=productos[sai(opcion)-1];
			cout << "\nA donde desea que sea enviado el producto?" << endl;
			cout << "1. A mi domicilio" << endl;
			cout << "2. Mi ubicacion actual" << endl;
			cout << "\nPor favor elija una opcion: ";
			cin >> opcionDireccion;
			cout << "\nอออออออออออออออออออออออออออออออออออออออออออออออออออออ" << endl;
			if(opcionDireccion=="1"){
				coordx=comprador.coordX;
				coordy=comprador.coordY;
				casa=true;
			}else if(opcionDireccion=="2"){
				cout << "\nPor favor digite las coordenadas de su ubicacion separadas por espacio: ";
				cin >> coordx >> coordy;
				casa=false;
			}else{
				while(true){
					cout << "\n\nPor favor elija una opcion valida: ";
					cin >> opcionDireccion;
					if(opcionDireccion=="1"){
						coordx=comprador.coordX;
						coordy=comprador.coordY;
						casa=true;
						break;
					}else if(opcion=="2"){
						cout << "\nPor favor digite las coordenadas de su ubicacion separadas por espacio: ";
						cin >> coordx >> coordy;
						casa=false;
						break;
					}
				}
			}
			cout << "\nLas tres bodegas mas cercanas que venden " << producto << " son:" << endl;
			vector < pair <struct tienda,float> > tiendas=buscarTiendas(producto,coordx,coordy);
			for(unsigned int i=0;(i<3 && i<tiendas.size());i++){
				cout << (i+1) << ". Nombre: " << tiendas[i].first.nombre << endl;
				cout << "Distancia: " << tiendas[i].second << endl;
				cout << "Precio unitario: S/." << buscarPrecio(producto,tiendas[i].first.usuario) << endl << endl;
			}
			cout << "\nPor favor elija una tienda: ";
			string opcionTienda;
			cin >> opcionTienda;
			if(opcionTienda=="1" || opcionTienda=="2" || opcionTienda=="3"){
				cout << "\nPor favor digite la cantidad de unidades del producto: ";
				cin >> cantidad;
				int opcionEntero=sai(opcionTienda)-1;
				float precioTotal=(buscarPrecio(producto,tiendas[opcionEntero].first.usuario)*cantidad)+4;
				cout << "\nEl monto total a pagar por este pedido seria S/." << precioTotal << " (incluye tarifa por delivery de S/.4)" << endl;
				cout << "\nCon cuanto desea pagar?: S/.";
				float pagaCon;
				cin >> pagaCon;
				cout << "\nDigite 1 para confirmar el pedido o 0 para cancelar: ";
				cin >> opcion;
				if(opcion=="1"){
					generarPedido(producto,cantidad,precioTotal,pagaCon,casa,coordx,coordy,tiendas[sai(opcionTienda)-1].first,comprador);
					agregarHistorial(producto,cantidad,precioTotal,tiendas[sai(opcionTienda)-1].first,comprador);
					cout << "\nHa realizado su pedido con exito" << endl;
					cout << "\nPuede consultar el estado de su pedido en la opcion Ver estado de pedido" << endl;
					cout << "\nDesea realizar otro pedido? (S/N): ";
					cin >> opcion;
					if(opcion=="s" || "S"){
						compradorComprar(comprador);
					}else if(opcion=="n" || "N"){
						compradorLogeado(ias(comprador.numero));
					}else{
						while(true){
							cout << "\nPor favor elija una opcion valida";
							cin >> opcion;
							if(opcion=="s" || "S"){
								compradorComprar(comprador);
							}else if(opcion=="n" || "N"){
								compradorLogeado(ias(comprador.numero));
							}
						}
					}
				}else if(opcion=="0"){
					compradorComprar(comprador);
				}else{
					while(true){
						cout << "\nPor favor elija una opcion valida: ";
						cin >> opcion;
						if(opcion=="1"){
							generarPedido(producto,cantidad,precioTotal,pagaCon,casa,coordx,coordy,tiendas[sai(opcionTienda)-1].first,comprador);
							agregarHistorial(producto,cantidad,precioTotal,tiendas[sai(opcionTienda)-1].first,comprador);
							cout << "\nHa realizado su pedido con exito" << endl;
							cout << "\nPuede consultar el estado de su pedido en la opcion Ver estado de pedido" << endl;
							cout << "\nDesea realizar otro pedido? (S/N): ";
							cin >> opcion;
							if(opcion=="s" || "S"){
								compradorComprar(comprador);
							}else if(opcion=="n" || "N"){
								compradorLogeado(ias(comprador.numero));
							}else{
								while(true){
									cout << "Por favor elija una opcion valida";
									cin >> opcion;
									if(opcion=="s" || "S"){
										compradorComprar(comprador);
									}else if(opcion=="n" || "N"){
										compradorLogeado(ias(comprador.numero));
									}
								}
							}
						}else if(opcion=="0"){
							compradorComprar(comprador);
						}
					}
				}
			}else{
				while(true){
					cout << "\nPor favor elija una opcion valida: ";
					cin >> opcion;
				}
			}
		}else{
			cout << "Por favor elija una opcion valida" << endl;
			Sleep(2000);
			compradorComprar(comprador);
		}
	}else if(opcion=="0"){
		compradorLogeado(ias(comprador.numero));
	}else{
		cout << "Por favor elija una opcion valida" << endl;
		Sleep(2000);
		compradorComprar(comprador);
	}
}

void estadoPedido(struct comprador comprador){
	system("cls");
	string opcion;
	cout << "\nBienvenido " << comprador.nombre << endl;
	cout << "\nQue desea hacer?" << endl;
	cout << "1. Ver pedidos pendientes" << endl;
	cout << "2. Puntuar un repartidor" << endl;
	cout << "0. Regresar" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		verPedidosPendientes(comprador);
	}else if(opcion=="2"){
		verPedidosFinalizados(comprador);
	}else if(opcion=="0"){
			compradorLogeado(ias(comprador.numero));
	}else{
		cout << "\nPor favor elija una opcion valida" << endl;
		Sleep(2000);
		estadoPedido(comprador);
	}
}

void verPedidosPendientes(struct comprador comprador){
	system("cls");
	string opcion;
	unsigned int opcionPedido;
	vector <struct pedidoHistorial> pedidosPendientes=obtenerPedidosPendientes(comprador);
	imprimirPedidosPendientes(pedidosPendientes);
	cout << "Opciones disponibles: " << endl;
	cout << "1. Cancelar un pedido" << endl;
	cout << "0. Regresar" << endl;
	cout << "\nPor favor elija una opcion: ";
	cin >> opcion;
	if(opcion=="1"){
		cout << "\nPor favor elija el pedido que quiere cancelar: ";
		cin >> opcionPedido;
		if(opcionPedido<=pedidosPendientes.size() && pedidosPendientes[opcionPedido-1].estadoPedido=="disponible"){
			cout << "\nEsta seguro que desea cancelar el pedido seleccionado? (S/N): ";
			cin >> opcion;
			if(opcion=="s" || opcion=="S"){
				CancelarPedido(pedidosPendientes[opcionPedido-1].telefonoComprador,pedidosPendientes[opcionPedido-1].horaPedido);
				cout << "\nPedido borrado con exito" << endl;
				Sleep(2000);
				compradorLogeado(ias(comprador.numero));
			}else if(opcion=="n" || opcion=="N"){
				estadoPedido(comprador);
			}else{
				while(true){
					cout << "\nPor favor elija una opcion valida" << endl;
					cin >> opcion;
					if(opcion=="s" || opcion=="S"){
						CancelarPedido(pedidosPendientes[opcionPedido-1].telefonoComprador,pedidosPendientes[opcionPedido-1].horaPedido);
						cout << "\nPedido borrado con exito" << endl;
						Sleep(2000);
						compradorLogeado(ias(comprador.numero));
					}else if(opcion=="n" || opcion=="N"){
						estadoPedido(comprador);
					}
				}
			}
		}else{
			cout << "Por favor elija una opcion valida" << endl;
			Sleep(2000);
			verPedidosPendientes(comprador);
		}
	}else if(opcion=="0"){
		estadoPedido(comprador);
	}else{
		cout << "\nPor favor elija una opcion valida" << endl;
		Sleep(2000);
		verPedidosPendientes(comprador);
	}
}

void verPedidosFinalizados(struct comprador comprador){
	system("cls");
	unsigned int opcionPedido;
	vector <struct pedidoHistorial> pedidosFinalizados=obtenerPedidosFinalizados(comprador);
	imprimirPedidosFinalizados(pedidosFinalizados);
	cout << "\nElija el pedido con el repartidor que quiere puntuar o digite 0 para regresar: ";
	cin >> opcionPedido;
	if(opcionPedido==0){
		estadoPedido(comprador);
	}else if(opcionPedido<=pedidosFinalizados.size() && opcionPedido>0){
		float puntuacion;
		cout << "\nPor favor digite una puntuacion del 1 al 10 o digite 0 para volver: ";
		cin >> puntuacion;
		if(puntuacion>0 && puntuacion<=10){
			struct repartidor repartidor=obtenerRepartidor(pedidosFinalizados[opcionPedido-1].telefonoRepartidor);
			repartidor.ingresarPuntuacion(puntuacion);
			modificarRepartidor(repartidor);
			cambiarEstadoPuntuacionHistorialPedidos(pedidosFinalizados[opcionPedido-1]);
			cout << "La puntuacion fue registrada con exito" << endl;
			Sleep(2000);
			estadoPedido(comprador);
		}else if(puntuacion==0){
			estadoPedido(comprador);
		}else{
			cout << "Por favor ingrese una puntuacion valida";
			Sleep(2000);
			verPedidosFinalizados(comprador);
		}
	}else{
		cout << "Por favor elija una opcion valida" << endl;
		Sleep(2000);
		verPedidosFinalizados(comprador);
	}
}
