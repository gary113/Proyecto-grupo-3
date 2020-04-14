#include "pantallas.hpp"

void registrarComprador(){
	system("cls");
	string preguntas[6]={"1. ¿Que tipo de mascotas le gustan?","2. ¿Como se llamo su primera mascota?","3. ¿Como se llama su mejor amigo?","4. ¿Cual es su curso favorito?","5. ¿Cual es su cancion favorita?","6. ¿Donde nacio su madre?"};
	string num,nombre,pregunta,respuesta;
	cout << "Bienvenido al proceso de registro de compradores\n" << endl;
	cout << "Por favor, ingrese su numero telefonico o celular" << endl;
	cin >> num;
	cout << "\nPor favor, ingrese su nombre" << endl;
	cin >> nombre;
	cout << "\nPor favor, elija una pregunta secreta" << endl;
	for(int i=0;i<6;i++){
		cout << preguntas[i] << endl;
	}
	cin >> pregunta;
	cout << "\nPor favor digite su respuesta secreta" << endl;
	cin >> respuesta;
	cout << "\nAhora se encuentra registrado, presione enter para cerrar la aplicacion" << endl;
	getch();
}

void registrarRepartidor(){
	system("cls");
	string num,nombre,dni,direccion;
	cout << "Bienvenido al proceso de registro de repartidores\n" << endl;
	cout << "Por favor, ingrese su DNI:" << endl;
	cin >> dni;
	cout << "\nPor favor, ingrese su nombre:" << endl;
	cin >> nombre;
	cout <<"\nPor favor, ingrese su numero telefonico o celular:" << endl;
	cin >> num;
	cout << "\nPor favor, ingrese su direccion:" << endl;
	cin >> direccion;
	cout << "\nSus datos seran revisados y se le notificara cuando su cuenta sea activada, presione enter para cerrar la aplicacion." << endl;
	getch();
	exit(0);
}

void RepartidorNoRegistrado(){
	system("cls");
	string opcion;
	cout << "Su nombre de usuario no se encuentra registrado, elija una opcion:" << endl;
	cout << "1. Registrarse" << endl;
	cout << "2. Regresar" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion;
	if(opcion=="1"){
		registrarRepartidor();
	}if(opcion=="2"){
		pantallaRepartidor();
	}else if(opcion=="3"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
		exit(0);
	}else{
		RepartidorNoRegistrado();
	}
}

void pantallaComprador(){
	system("cls");
	string id,contra,pregunta,respuesta,opcion;
	int i=0;
	cout << "Bienvenido a la interfaz de compradores\n" << endl;
	cout << "¿Que desea hacer?" << endl;
	cout << "1. Ingresar" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Regresar" << endl;
	cout << "4. Salir\n" << endl;
	cout << "Ingrese una opcion del 1 al 4: ";
	cin >> opcion;
	if(opcion=="1"){
		system("cls");
		cout << "\nPor favor digite su numero telefonico o celular" << endl;
		cin >> id;
		if(id=="987654321"){
			while(i<3){
				if(i==0){
					cout << "\nPor favor digite su contrasenia" << endl;
					cin >> contra;
					if(contra=="123456"){
						break;
					}
				}else{
					if((3-i)==2){
						cout << "\nPor favor intente nuevamente, le quedan " << 3-i << " intentos" << endl;
						cin >> contra;
						if(contra=="123456"){
							break;
						}
					}else{
						cout << "\nPor favor intente nuevamente, le queda " << 3-i << " intento" << endl;
						cin >> contra;
						if(contra=="123456"){
							break;
						}
					}
				}
				i++;
			}
			if(i<3){
				pantallaCompradorLog(id);
			}else{
				system("cls");
				cout << "Por favor responda su pregunta secreta\n" << endl;
				cout << "¿Que tipo de mascotas le gustan?" << endl;
				cin >> respuesta;
				if(respuesta=="Gatos"){
					pantallaCompradorLog(id);
				}else{
					system("cls");
					cout << "Respuesta secreta incorrecta\n" << endl;
					cout << "Eliga una opcion\n" << endl;
					cout << "1. Registrarse" << endl;
					cout << "2. Regresar" << endl;
					cout << "3. Salir" << endl;
					cin >> opcion;
					if(opcion=="1"){
						registrarComprador();
					}else if(opcion=="2"){
						pantallaComprador();
					}else if(opcion=="3"){
						system("cls");
						cout << "Gracias por usar nuestra aplicacion :)" << endl;
						getch();
					}
				}
			}
		}else{
			cout << "Su numero NO se encuentra registrado\n" << endl;
			cout << "Eliga una opcion\n" << endl;
			cout << "1. Registrarse" << endl;
			cout << "2. Regresar" << endl;
			cout << "3. Salir" << endl;
			cin >> opcion;
			if(opcion=="1"){
				registrarComprador();
			}else if(opcion=="2"){
				pantallaComprador();
			}else if(opcion=="3"){
				system("cls");
				cout << "Gracias por usar nuestra aplicacion :)" << endl;
				getch();
			}

		}
	}else if(opcion=="2"){
		system("cls");
		registrarComprador();
	}else if(opcion=="3"){
		system("cls");
		pantallaPrincipal();
	}else if(opcion=="4"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
	}else{
		pantallaComprador();
	}
}

void pantallaRepartidorLog(string id){
	system("cls");
	string opcion1,opcion2;
	cout << "Repartidor identificado con exito\n" << endl;
	cout << "Elija una opcion" << endl;
	cout << "1. Tomar un pedido" << endl;
	cout << "2. Finalizar pedido" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion1;
	if(opcion1=="1"){
		system("cls");
		cout << "Pedidos disponibles:\n" << endl;
		cout << "1. Pasta dental de la tienda 5,9 hacia 6,6" << endl;
		cout << "\nDigite el numero de pedido a tomar o digite 999 para regresar al menu" << endl;
		cin >> opcion2;
		if(opcion2=="1"){
			cout << "Pedido tomado, presione enter para cerrar la aplicacion" << endl;
			getch();
		}else{
			pantallaRepartidorLog(id);
		}
	}else if(opcion1=="2"){
		system("cls");
		cout << "Pedidos tomados:\n" << endl;
		cout << "1. Pasta dental de la tienda 5,9 hacia 6,6" << endl;
		cout << "\nDigite el numero de pedido a finalizar o digite 999 para regresar al menu" << endl;
		cin >> opcion2;
		if(opcion2=="1"){
			cout << "Pedido finalizado, presione enter para cerrar la aplicacion" << endl;
			getch();
		}else{
			pantallaRepartidorLog(id);
		}
	}else if(opcion1=="3"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
	}else{
		pantallaRepartidorLog(id);
	}
}

void pantallaRepartidor(){
	system("cls");
	string id,contra,opcion;
	int i=0;
	cout << "Bienvenido a la interfaz de Repartidores\n" << endl;
	cout << "¿Que desea hacer?" << endl;
	cout << "1. Ingresar" << endl;
	cout << "2. Registrarse" << endl;
	cout << "3. Regresar" << endl;
	cout << "4. Salir" << endl;
	cin >> opcion;
	if(opcion=="1"){
		system("cls");
		cout << "Por favor ingrese su nombre de usuario" << endl;
		cin >> id;
		if(id=="miguel"){
			while(i<3){
				if(i==0){
					cout << "\nPor favor digite su contrasenia" << endl;
					cin >> contra;
					if(contra=="123456"){
						break;
					}
				}else{
					if((3-i)==2){
						cout << "\nPor favor intente nuevamente, le quedan " << 3-i << " intentos" << endl;
						cin >> contra;
						if(contra=="123456"){
							break;
						}
					}else{
						cout << "\nPor favor intente nuevamente, le queda " << 3-i << " intento" << endl;
						cin >> contra;
						if(contra=="123456"){
							break;
						}
					}
				}
				i++;
			}
			if(i<3){
				pantallaRepartidorLog(id);
			}else{
				cout << "\nPor favor, contactese con el administrador para recuperar su cuenta, presione enter para cerrar la aplicacion" << endl;
				getch();
			}
		}else{
			RepartidorNoRegistrado();
		}
	}else if(opcion=="2"){
		registrarRepartidor();
	}else if(opcion=="3"){
		pantallaPrincipal();
	}else if(opcion=="4"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
	}else{
		pantallaRepartidor();
	}
}

void estadoEntrega(string id){
	system("cls");
	string opcion;
	cout << "Sus pedidos:\n" << endl;
	cout << "1. Pasta dental de la tienda 5,9 hacia 6,6 sera entregado por el repartidor miguel" << endl;
	cout << "\nElija una opcion:" << endl;
	cout << "1.Contactar con el repartidor" << endl;
	cout << "2.Regresar al menu" << endl;
	cin >> opcion;
	if(opcion=="1"){
		system("cls");
		cout << "Numero de celular del repartidor: 987654123" << endl;
		cout << "Presione enter para salir" << endl;
		getch();
	}else if(opcion=="2"){
		pantallaCompradorLog(id);
	}else{
		estadoEntrega(id);
	}
}

void pantallaCompradorLog(string id){
	system("cls");
	string opcion1,opcion2,opcion3,opcion4,coord1,coord2;
	cout << "Usuario identificado con exito\n" << endl;
	cout << "Elija una opcion" << endl;
	cout << "1. Ver estado de pedido" << endl;
	cout << "2. Comprar" << endl;
	cout << "3. Salir" << endl;
	cin >> opcion1;
	if(opcion1=="1"){
		estadoEntrega(id);
	}else if(opcion1=="2"){
		system("cls");
		cout << "Elija el tipo de producto que desea pedir" << endl;
		cout << "1. Viveres" << endl;
		cout << "2. Higiene personal" << endl;
		cout << "3. Limpieza del hogar" << endl;
		cin >> opcion2;
		system("cls");
		cout << "Elija el producto que desea pedir\n" << endl;
		cout << "1. Pasta dental" << endl;
		cout << "2. Desodorante" << endl;
		cout << "3. Shampoo" << endl;
		cout << "4. Jabon" << endl;
		cout << "5. Papel higienico" << endl;
		cin >> opcion3;
		system("cls");
		cout << "Los puntos de venta disponibles son:\n" << endl;
		cout << "- (7,1) Tienda 1" << endl;
		cout << "- (3,7) Tienda 2" << endl;
		cout << "- (6,5) Tienda 3" << endl;
		cout << "- (8,3) Tienda 4" << endl;
		cout << "- (10,2) Tienda 5" << endl;
		cout << "- (5,9) Tienda 6" << endl;
		cout << "- (9,9) Tienda 7" << endl;
		cout << "\nPor favor digite su ubicacion (coordenadas)" << endl;
		cin >> coord1 >> coord2;
		system("cls");
		cout << "Su ubicacion es: " << coord1+","+coord2 << endl;
		cout << "\nA continuacion se muestran las tiendas ordenadas con respecto a sus caracteristicas\n" << endl;
		cout << "Las tres tiendas mas cercanas son:\n" << endl;
		cout << "- La tienda 6 (5,9) con distancia: 3.16228" << endl;
		cout << "- La tienda 2 (3,7) con distancia: 3.16228" << endl;
		cout << "- La tienda 7 (9,9) con distancia: 4.24264" << endl;
		cout << "\nEl tiempo de entrega aproximado para cada tienda es:\n" << endl;
		cout << "- Para la tienda 6 (5,9): 5 minutos" << endl;
		cout << "- Para la tienda 2 (3,7): 5 minutos" << endl;
		cout << "- Para la tienda 7 (9,9): 7 minutos" << endl;
		cout << "\nLa calificacion para cada tienda es (1-10 puntos):\n" << endl;
		cout << "- Para la tienda 2 (3,7): 8 puntos" << endl;
		cout << "- Para la tienda 7 (9,9): 5 puntos" << endl;
		cout << "- Para la tienda 6 (5,9): 2 puntos" << endl;

		cout << "\nCon la informacion brindada, por favor elija una tienda" << endl;
		cin >> opcion4;
		cout << "Su producto esta en camino, presione enter para salir" << endl;
		getch();
	}else if(opcion1=="3"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
	}else{
		pantallaCompradorLog(id);
	}
}

void pantallaPrincipal(){
	system("cls");
	string opcion;
	cout << "***** Bienvenido a bodegas delivery *****\n" << endl;
	cout << "Por favor elija una opcion" << endl;
	cout << "1. Comprador" << endl;
	cout << "2. Repartidor" << endl;
	cout << "3. Salir\n" << endl;
	cin >> opcion;
	if(opcion=="1"){
		pantallaComprador();
	}else if(opcion=="2"){
		pantallaRepartidor();
	}else if(opcion=="3"){
		system("cls");
		cout << "Gracias por usar nuestra aplicacion :)" << endl;
		getch();
	}else{
		pantallaPrincipal();
	}
}
