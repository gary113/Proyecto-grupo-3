#include "utilitarios.hpp"

void cambiarEstadoPuntuacionHistorialPedidos(struct pedidoHistorial pedido){ //para mencionar que ya se puntuo el repartidor en el historial de pedidos
	pedido.estadoPuntuacion="sipuntuado";
	vector <string> vectorArchivoHistorialPedidos=obtenerVectorArchivo("../archivos/pedidos/historialPedidos.txt");
	for(unsigned int i=0;i<vectorArchivoHistorialPedidos.size();i++){
		if(vectorArchivoHistorialPedidos[i].find(pedido.telefonoComprador)<50 && vectorArchivoHistorialPedidos[i].find(pedido.horaPedido)<100){
			vectorArchivoHistorialPedidos[i]=pedido.crearLinea();
			break;
		}
	}
	ofstream archivo("../archivos/pedidos/historialPedidos.txt",ios::trunc);
	for(unsigned int i=0;i<vectorArchivoHistorialPedidos.size();i++){
		archivo << vectorArchivoHistorialPedidos[i] << endl;
	}
	archivo.close();
}

void modificarRepartidor(struct repartidor repartidor){ //para cambiarle la puntuacion al repartidor
	vector <string> vectorArchivoRepartidores=obtenerVectorArchivo("../archivos/repartidores/listaRepartidores.txt");
	for(unsigned int i=0;i<vectorArchivoRepartidores.size();i++){
		if(vectorArchivoRepartidores[i].find(ias(repartidor.numero))<100){
			vectorArchivoRepartidores[i]=repartidor.crearLinea();
			break;
		}
	}
	ofstream archivo("../archivos/repartidores/listaRepartidores.txt",ios::trunc);
	if(archivo.is_open()){
		for(unsigned int i=0;i<vectorArchivoRepartidores.size();i++){
			archivo << vectorArchivoRepartidores[i] << endl;
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
}

vector <struct pedidoHistorial> obtenerVectorEstructuraPedidos(vector <string> vectorArchivoHistorialPedidos){
	vector <struct pedidoHistorial> vectorHistorialPedidos;
	for(unsigned int i=0;i<vectorArchivoHistorialPedidos.size();i++){
		struct pedidoHistorial pedido;
		vector <string> datos=separarDatos(vectorArchivoHistorialPedidos[i]);
		pedido.inicializarConVector(datos);
		vectorHistorialPedidos.push_back(pedido);
	}
	return vectorHistorialPedidos;
}

vector <string> obtenerVectorArchivo(string rutaArchivo){ //Sin el espacio en blanco al final del archivo
	vector <string> vectorArchivo;
	string linea;
	ifstream archivo(rutaArchivo.c_str());
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
	return vectorArchivo;
}

void FinalizarPedidoHistorial(string telefonoComprador,string horaPedido){ //Modifica el historial para poner hora y fecha de entrega
	vector <string> vectorArchivoHistorialPedidos=obtenerVectorArchivo("../archivos/pedidos/historialPedidos.txt");
	vector <struct pedidoHistorial> vectorHistorialPedidos=obtenerVectorEstructuraPedidos(vectorArchivoHistorialPedidos);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		if(vectorHistorialPedidos[i].telefonoComprador==telefonoComprador && vectorHistorialPedidos[i].horaPedido==horaPedido){
			vectorHistorialPedidos[i].fechaEntrega=obtenerFecha();
			vectorHistorialPedidos[i].horaEntrega=obtenerHora();
			vectorHistorialPedidos[i].estadoPedido="entregado";
			break;
		}
	}
	ofstream archivoHistorial("../archivos/pedidos/historialPedidos.txt",ios::trunc);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		archivoHistorial << vectorHistorialPedidos[i].crearLinea() << endl;
	}
	archivoHistorial.close();
}

void BorrarPedidoTomar(string telefonoComprador,string horaPedido,struct repartidor repartidor){ //Borra el pedido de pedidos disponibles y modifica el historial
	vector <string> vectorArchivoPedidos=obtenerVectorArchivo("../archivos/pedidos/pedidosDisponibles.txt");
	for(unsigned int i=0;i<vectorArchivoPedidos.size();i++){
		if(vectorArchivoPedidos[i].find(telefonoComprador)<500 && vectorArchivoPedidos[i].find(horaPedido)<50){
			vectorArchivoPedidos.erase(vectorArchivoPedidos.begin()+i);
			break;
		}
	}
	ofstream archivoPedidos("../archivos/pedidos/pedidosDisponibles.txt",ios::trunc);
	if(archivoPedidos.is_open()){
		for(unsigned int i=0;i<vectorArchivoPedidos.size();i++){
			archivoPedidos << vectorArchivoPedidos[i] << endl;
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivoPedidos.close();

	vector <string> vectorArchivoHistorialPedidos=obtenerVectorArchivo("../archivos/pedidos/historialPedidos.txt");
	vector <struct pedidoHistorial> vectorHistorialPedidos=obtenerVectorEstructuraPedidos(vectorArchivoHistorialPedidos);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		if(vectorHistorialPedidos[i].telefonoComprador==telefonoComprador && vectorHistorialPedidos[i].horaPedido==horaPedido){
			vectorHistorialPedidos[i].repartidor=repartidor.nombre;
			vectorHistorialPedidos[i].telefonoRepartidor=ias(repartidor.numero);
			vectorHistorialPedidos[i].estadoPedido="tomado";
			break;
		}
	}
	ofstream archivoHistorial("../archivos/pedidos/historialPedidos.txt",ios::trunc);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		archivoHistorial << vectorHistorialPedidos[i].crearLinea() << endl;
	}
	archivoHistorial.close();
}

void CancelarPedido(string telefonoComprador,string horaPedido){ //Borra el pedido de pedidos disponibles y modifica el historial
	vector <string> vectorArchivoPedidos=obtenerVectorArchivo("../archivos/pedidos/pedidosDisponibles.txt");
	for(unsigned int i=0;i<vectorArchivoPedidos.size();i++){
		if(vectorArchivoPedidos[i].find(telefonoComprador)<500 && vectorArchivoPedidos[i].find(horaPedido)<50){
			vectorArchivoPedidos.erase(vectorArchivoPedidos.begin()+i);
			break;
		}
	}
	ofstream archivoPedidos("../archivos/pedidos/pedidosDisponibles.txt",ios::trunc);
	if(archivoPedidos.is_open()){
		for(unsigned int i=0;i<vectorArchivoPedidos.size();i++){
			archivoPedidos << vectorArchivoPedidos[i] << endl;
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivoPedidos.close();

	vector <string> vectorArchivoHistorialPedidos=obtenerVectorArchivo("../archivos/pedidos/historialPedidos.txt");
	vector <struct pedidoHistorial> vectorHistorialPedidos=obtenerVectorEstructuraPedidos(vectorArchivoHistorialPedidos);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		if(vectorHistorialPedidos[i].telefonoComprador==telefonoComprador && vectorHistorialPedidos[i].horaPedido==horaPedido){
			vectorHistorialPedidos[i].estadoPedido="cancelado";
			break;
		}
	}
	ofstream archivoHistorial("../archivos/pedidos/historialPedidos.txt",ios::trunc);
	for(unsigned int i=0;i<vectorHistorialPedidos.size();i++){
		archivoHistorial << vectorHistorialPedidos[i].crearLinea() << endl;
	}
	archivoHistorial.close();
}

void imprimirPedidosFinalizados(vector <struct pedidoHistorial> pedidos){ //sirve para el comprador
	if(pedidos.size()==0){
		cout << "\nNo tiene ningun pedido finalizado sin puntuar" << endl;
	}else{
		cout << "\nPedidos finalizados:\n" << endl;
		for(unsigned int i=0;i<pedidos.size();i++){
			cout << "--> Pedido numero " << (i+1) << ":" << endl;
			cout << "* Nombre de producto: " << pedidos[i].nombreProducto << endl;
			cout << "* Cantidad: " << pedidos[i].cantidad << endl;
			cout << "* Monto a pagado: S/." << pedidos[i].montoTotal << endl;
			cout << "* Nombre de la tienda: " << pedidos[i].nombreTienda << endl;
			cout << "* Fecha del pedido: " << pedidos[i].fechaPedido << endl;
			cout << "* Hora del pedido: " << pedidos[i].horaPedido << endl;
			cout << "* Fecha de entrega: " << pedidos[i].fechaEntrega << endl;
			cout << "* Hora de entrega: " << pedidos[i].horaEntrega << endl;
			cout << "* Nombre del repartidor: " << pedidos[i].repartidor << endl;
			cout << endl;
		}
	}
}

void imprimirPedidosPendientes(vector <struct pedidoHistorial> pedidos){ //sirve para el comprador
	if(pedidos.size()==0){
		cout << "\nNo tiene ningun pedido pendiente" << endl;
	}else{
		cout << "\nPedidos pendientes:\n" << endl;
		for(unsigned int i=0;i<pedidos.size();i++){
			if(pedidos[i].estadoPedido=="disponible"){
				cout << "--> Pedido numero " << (i+1) << ":" << endl;
				cout << "* Nombre de producto: " << pedidos[i].nombreProducto << endl;
				cout << "* Cantidad: " << pedidos[i].cantidad << endl;
				cout << "* Monto a pagar: S/." << pedidos[i].montoTotal << endl;
				cout << "* Nombre de la tienda: " << pedidos[i].nombreTienda << endl;
				cout << "* Fecha del pedido: " << pedidos[i].fechaPedido << endl;
				cout << "* Hora del pedido: " << pedidos[i].horaPedido << endl;
				cout << endl;
			}else if(pedidos[i].estadoPedido=="tomado"){
				cout << "--> Pedido numero " << (i+1) << ":" << endl;
				cout << "* Nombre de producto: " << pedidos[i].nombreProducto << endl;
				cout << "* Cantidad: " << pedidos[i].cantidad << endl;
				cout << "* Monto a pagar: S/." << pedidos[i].montoTotal << endl;
				cout << "* Nombre de la tienda: " << pedidos[i].nombreTienda << endl;
				cout << "* Fecha del pedido: " << pedidos[i].fechaPedido << endl;
				cout << "* Hora del pedido: " << pedidos[i].horaPedido << endl;
				cout << "* Nombre del repartidor: " << pedidos[i].repartidor << endl;
				cout << "* Telefono del repartidor: " << pedidos[i].telefonoRepartidor << endl;
				cout << endl;
			}
		}
	}
}

void imprimirFacturas(vector <struct pedidoHistorial> pedidos){ //sirve para el comprador
	if(pedidos.size()==0){
		cout << "\nNo tiene ninguna factura" << endl;
	}else{
		struct comprador comprador=obtenerComprador(pedidos[0].telefonoComprador);
		cout << "\nSus facturas son las siguientes:\n" << endl;
		for(unsigned int i=0;i<pedidos.size();i++){
			cout << "--> Factura numero " << (i+1) << ":" << endl;
			cout << "* Nombre de la tienda: " << pedidos[i].nombreTienda << endl;
			cout << "* Nombre: " << comprador.nombre << endl;
			cout << "* Nombre de producto: " << pedidos[i].nombreProducto << endl;
			cout << "* Cantidad: " << pedidos[i].cantidad << endl;
			cout << "* Precio unitario: " << (pedidos[i].montoTotal-4)/pedidos[i].cantidad << endl;
			cout << "* Monto total: S/." << pedidos[i].montoTotal << endl;
			cout << "* Fecha: " << pedidos[i].fechaPedido << endl;
			cout << endl;
		}
	}
}

vector <struct pedidoHistorial> obtenerFacturas(struct comprador comprador){
	vector <struct pedidoHistorial> respuesta;
	string linea;
	ifstream archivo("../archivos/pedidos/historialPedidos.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(ias(comprador.numero))<200 && linea.find("entregado")<300){
				struct pedidoHistorial pedido;
				vector <string> datos=separarDatos(linea);
				pedido.inicializarConVector(datos);
				respuesta.push_back(pedido);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return respuesta;
}

vector <struct pedidoHistorial> obtenerPedidosFinalizados(struct comprador comprador){
	vector <struct pedidoHistorial> respuesta;
	string linea;
	ifstream archivo("../archivos/pedidos/historialPedidos.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(ias(comprador.numero))<200 && linea.find("entregado")<300 && linea.find("nopuntuado")<300){
				struct pedidoHistorial pedido;
				vector <string> datos=separarDatos(linea);
				pedido.inicializarConVector(datos);
				respuesta.push_back(pedido);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return respuesta;
}

void imprimirPedidosDisponibles(vector <struct pedidoDisponible> pedidosDisponibles){ //sirve para el repartidor
	if(pedidosDisponibles.size()==0){
		cout << "\nNo existe ningun pedido disponible en este momento" << endl;
	}else{
		cout << "\nPedidos disponibles:\n" << endl;
		for(unsigned int i=0;i<pedidosDisponibles.size();i++){
			cout << "--> Pedido numero " << (i+1) << ":" << endl;
			cout << "* Nombre de producto: " << pedidosDisponibles[i].nombreProducto << endl;
			cout << "* Cantidad: " << pedidosDisponibles[i].cantidad << endl;
			cout << "* Monto del pedido: S/." << pedidosDisponibles[i].montoTotal << endl;
			cout << "* El comprador pagara con: S/." << pedidosDisponibles[i].pagaCon << endl;
			cout << "* Nombre de la tienda: " << pedidosDisponibles[i].nombreTienda << endl;
			cout << "* Direccion de la tienda: " << pedidosDisponibles[i].direccionTienda << endl;
			cout << "* Nombre del comprador: " << pedidosDisponibles[i].nombreComprador << endl;
			cout << "* Direccion del comprador: " << pedidosDisponibles[i].direccionComprador << endl;
			cout << "* Coordenadas del comprador: " << "(" << pedidosDisponibles[i].coordX << "," << pedidosDisponibles[i].coordY << ")" << endl;
			cout << "* Telefono del comprador: " << pedidosDisponibles[i].telefonoComprador << endl;
			cout << "* Fecha del pedido: " << pedidosDisponibles[i].fechaPedido << endl;
			cout << "* Hora del pedido: " << pedidosDisponibles[i].horaPedido << endl;
			cout << endl;
		}
	}
}

vector <struct pedidoDisponible> obtenerPedidosDisponibles(){
	vector <struct pedidoDisponible> respuesta;
	string linea;
	ifstream archivo("../archivos/pedidos/pedidosDisponibles.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!=""){
				struct pedidoDisponible pedido;
				vector <string> datos=separarDatos(linea);
				pedido.inicializarConVector(datos);
				respuesta.push_back(pedido);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return respuesta;
}

void imprimirPedidosTomados(vector <struct pedidoHistorial> pedidosTomados){
	if(pedidosTomados.size()==0){
		cout << "\nNo tienes ningun pedido en curso" << endl;
	}else{
		cout << "\nPedidos tomados:\n" << endl;
		for(unsigned int i=0;i<pedidosTomados.size();i++){
			cout << "--> Pedido numero " << (i+1) << ":" << endl;
			cout << "* Nombre de producto: " << pedidosTomados[i].nombreProducto << endl;
			cout << "* Cantidad: " << pedidosTomados[i].cantidad << endl;
			cout << "* Monto del pedido: S/." << pedidosTomados[i].montoTotal << endl;
			cout << "* Nombre de la tienda: " << pedidosTomados[i].nombreTienda << endl;
			cout << "* Telefono del comprador: " << pedidosTomados[i].telefonoComprador << endl;
			cout << "* Fecha del pedido: " << pedidosTomados[i].fechaPedido << endl;
			cout << "* Hora del pedido: " << pedidosTomados[i].horaPedido << endl;
			cout << endl;
		}
	}
}

vector <struct pedidoHistorial> obtenerPedidosTomados(struct repartidor repartidor){
	vector <struct pedidoHistorial> respuesta;
	string linea;
	ifstream archivo("../archivos/pedidos/historialPedidos.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!="" && linea.find(ias(repartidor.numero))<300 && linea.find("tomado")<300){
				struct pedidoHistorial pedido;
				vector <string> datos=separarDatos(linea);
				pedido.inicializarConVector(datos);
				respuesta.push_back(pedido);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return respuesta;
}

vector <struct pedidoHistorial> obtenerPedidosPendientes(struct comprador comprador){
	vector <struct pedidoHistorial> respuesta;
	string linea;
	ifstream archivo("../archivos/pedidos/historialPedidos.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(ias(comprador.numero))<200 && (linea.find("disponible")<300 || linea.find("tomado")<300)){
				struct pedidoHistorial pedido;
				vector <string> datos=separarDatos(linea);
				pedido.inicializarConVector(datos);
				respuesta.push_back(pedido);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return respuesta;
}

string obtenerHora(){
	time_t tiempo = time(NULL);
	struct tm *tlocal = localtime(&tiempo);
	stringstream ss;
	ss << tlocal->tm_hour << ':' << tlocal->tm_min << ':' << tlocal->tm_sec;
	return ss.str();
}

string obtenerFecha(){
	time_t tiempo = time(NULL);
	struct tm *tlocal = localtime(&tiempo);
	stringstream ss;
	ss << tlocal->tm_mday << '/' << tlocal->tm_mon+1 << '/' << tlocal->tm_year+1900;
	return ss.str();
}

void agregarHistorial(string producto,int cantidad,float precioTotal,struct tienda tienda,struct comprador comprador){
	vector <string> pedido;
	ofstream archivo("../archivos/pedidos/historialPedidos.txt",ios::app);
	pedido.push_back(producto);
	pedido.push_back(ias(cantidad));
	pedido.push_back(fas(precioTotal));
	pedido.push_back(tienda.nombre);
	pedido.push_back(ias(comprador.numero));
	pedido.push_back(obtenerFecha());
	pedido.push_back(obtenerHora());
	pedido.push_back("");
	pedido.push_back("");
	pedido.push_back("");
	pedido.push_back("");
	pedido.push_back("nopuntuado");
	pedido.push_back("disponible");
	for(unsigned int i=0;i<pedido.size();i++){
		if(i==(pedido.size()-1)){
			archivo << pedido[i];
		}else{
			archivo << pedido[i] << '|';
		}
	}
	archivo << endl;
	archivo.close();
}

void generarPedido(string producto,int cantidad,float precioTotal,float pagaCon,bool casa,int coordx,int coordy,struct tienda tienda,struct comprador comprador){
	vector <string> pedido;
	ofstream archivo("../archivos/pedidos/pedidosDisponibles.txt",ios::app);
	pedido.push_back(producto);
	pedido.push_back(obtenerHora());
	pedido.push_back(obtenerFecha());
	pedido.push_back(tienda.nombre);
	pedido.push_back(tienda.direccion);
	pedido.push_back(ias(cantidad));
	pedido.push_back(fas(precioTotal));
	pedido.push_back(fas(pagaCon));
	pedido.push_back(comprador.nombre);
	if(casa==true){
		pedido.push_back(comprador.direccion);
		pedido.push_back(ias(coordx));
		pedido.push_back(ias(coordy));
	}else{
		pedido.push_back("Revisar coordenadas");
		pedido.push_back(ias(coordx));
		pedido.push_back(ias(coordy));
	}
	pedido.push_back(ias(comprador.numero));
	for(unsigned int i=0;i<pedido.size();i++){
		if(i==(pedido.size()-1)){
			archivo << pedido[i];
		}else{
			archivo << pedido[i] << '|';
		}
	}
	archivo << endl;
	archivo.close();
}

float buscarPrecio(string producto,string usuarioTienda){
	float precio=0;
	ifstream archivo("../archivos/productos/listaProductosPorTiendas.txt");
	string linea;
	if(archivo.is_open()){
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(producto)<100 && linea.find(usuarioTienda)<100){
				vector <string> datos=separarDatos(linea);
				precio=saf(datos[3]);
				break;
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
	return precio;
}

struct repartidor obtenerRepartidor(string datoRepartidor){
	struct repartidor repartidor;
	ifstream archivo("../archivos/repartidores/listaRepartidores.txt");
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(datoRepartidor)<500){
				vector <string> datosRepartidor=separarDatos(linea);
				repartidor.inicializarConVector(datosRepartidor);
				break;
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return repartidor;
}

struct comprador obtenerComprador(string numero){
	struct comprador comprador;
	ifstream archivo("../archivos/compradores/listaCompradores.txt");
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(numero)<100){
				vector <string> datosComprador=separarDatos(linea);
				comprador.inicializarConVector(datosComprador);
				break;
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return comprador;
}

struct tienda obtenerTienda(string usuario){
	struct tienda tienda;
	ifstream archivo("../archivos/tiendas/listaTiendas.txt");
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(usuario)<100){
				vector <string> datosTienda=separarDatos(linea);
				tienda.inicializarConVector(datosTienda);
				break;
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return tienda;
}

void imprimirProductos(vector <string> productos){
	for(unsigned int i=0;i<productos.size();i++){
		cout << (i+1) << ". " << productos[i] << endl;
	}
}

vector <string> separarDatos(string linea){
	vector<string> datos;
	string aux="";
	for(unsigned int i=0;i<linea.size();i++){
		if(linea[i]=='|'){
			datos.push_back(aux);
			aux="";
		}else{
			aux+=linea[i];
		}
	}
	datos.push_back(aux);
	return datos;
}

vector <string> obtenerProductos(string categoria){
	vector <string> resultado;
	int ubicacion=sai(categoria);
	string linea;
	ifstream archivo("../archivos/productos/listaProductosPorCategorias.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		int i=1;
		while(!archivo.eof()){
			if(i==ubicacion){
				getline(archivo,linea,'|');
				getline(archivo,linea);
				resultado=separarDatos(linea);
			}
			getline(archivo,linea);
			i++;
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	return resultado;
}

void imprimirCategoriasProductos(){
	ifstream archivo("../archivos/productos/listaProductosPorCategorias.txt");
	string linea;
	if(archivo.is_open()){
		getline(archivo,linea);
		int i=1;
		while(!archivo.eof()){
			getline(archivo,linea,'|');
			if(linea!=""){
				cout << i << ". " << linea << endl;
				getline(archivo,linea);
			}
			i++;
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
}

void cerrarApp(){
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\t\tGracias por usar nuestra aplicacion" << endl;
	Sleep(2000);
	exit(0);
}

bool buscarPalabraTienda(string dato){ //Esta funcion sirve para buscar si el dato ingresado se encuentra en el archivo de tiendas
	string rutaArchivo="../archivos/tiendas/listaTiendas.txt"; // cuando se corre el ejecutable
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!=""){ //Esto es para evitar leer el espacio en blanco al final del archivo
				if(linea.find(dato)<400){
					archivo.close();
					return true;
				}
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return false;
}

bool buscarPalabraRepartidor(string dato){ //Esta funcion sirve para buscar si el dato ingresado se encuentra en el archivo de repartidores
	string rutaArchivo="../archivos/repartidores/listaRepartidores.txt"; // cuando se corre el ejecutable
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!=""){ //Esto es para evitar leer el espacio en blanco al final del archivo
				if(linea.find(dato)<400){
					archivo.close();
					return true;
				}
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return false;
}

bool buscarPalabraComprador(string dato){ //Esta funcion sirve para buscar si el dato ingresado se encuentra en el archivo de compradores
	string rutaArchivo="../archivos/compradores/listaCompradores.txt"; // cuando se corre el ejecutable
	ifstream archivo;
	archivo.open(rutaArchivo.c_str());
	if(archivo.is_open()){
		string linea;
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea!=""){ //Esto es para evitar leer el espacio en blanco al final del archivo
				if(linea.find(dato)<400){
					archivo.close();
					return true;
				}
			}
		}
	}else{
		cout << "El archivo no pudo abrirse" << endl;
	}
	archivo.close();
	return false;
}

unsigned long long saull(string texto){
	unsigned long long n;
	stringstream ss;
	ss << texto;
	ss >> n;
	return n;
}

int sai(string texto){
	int n;
	stringstream ss;
	ss << texto;
	ss >> n;
	return n;
}

float saf(string texto){
	float n;
	stringstream ss;
	ss << texto;
	ss >> n;
	return n;
}

string ias(unsigned long long n){
	stringstream ss;
	ss << n;
	return ss.str();
}

string ias(int n){
	stringstream ss;
	ss << n;
	return ss.str();
}

string fas(float n){
	stringstream ss;
	ss << n;
	return ss.str();
}

int elevar(unsigned long long x, unsigned long long y){
	if (y == 0){
		return 1;
	}else if (y == 1){
		return x;
	}else{
		return x * elevar(x, y-1);
	}
}

int primeros(unsigned long long digitos, unsigned long long &numero){
	return numero/elevar(10, digitos);
}

int ultimos(unsigned long long digitos, unsigned long long &numero){
	return numero % elevar(10, digitos);
}

int maximo(unsigned long long u,unsigned long long v){
	if (u>=v){
		return u;
	}else{
	return v;
	}
}

int digitos (unsigned long long n, unsigned long long &dig){
	if (n < 10){
	return dig+1;
	}else{
		dig++;
		return digitos(n/10, dig);
	}
}

unsigned long long karatsuba (unsigned long long &u, unsigned long long &v){
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

vector < pair <struct tienda,float> > buscarTiendas(string producto,int coordx,int coordy){
	vector <struct tienda> tiendas;
	vector <float> distancias;
	vector < pair <struct tienda,float> > respuesta;
	string linea;
	ifstream archivo("../archivos/productos/listaProductosPorTiendas.txt");
	if(archivo.is_open()){
		getline(archivo,linea);
		while(!archivo.eof()){
			getline(archivo,linea);
			if(linea.find(producto)<100){
				vector <string> datos=separarDatos(linea);
				struct tienda tienda=obtenerTienda(datos[1]);
				tiendas.push_back(tienda);
			}
		}
	}else{
		cout << "No se pudo abrir el archivo" << endl;
	}
	archivo.close();
 	for(unsigned int i=0;i<tiendas.size();i++){
		distancias.push_back(sqrt(pow(tiendas[i].coordX-coordx,2)+pow(tiendas[i].coordY-coordy,2)));
	}
 	float auxDistancia;
 	struct tienda auxTienda;
	for(unsigned int i=0;i<tiendas.size()-1;i++){
		for(unsigned int j=i+1;j<tiendas.size();j++){
			if(distancias[i]>distancias[j]){
			auxDistancia=distancias[i];
			distancias[i]=distancias[j];
			distancias[j]=auxDistancia;
			auxTienda=tiendas[i];
			tiendas[i]=tiendas[j];
			tiendas[j]=auxTienda;
			}
		}
	}
	for(unsigned int i=0;i<tiendas.size();i++){
		respuesta.push_back(make_pair(tiendas[i],distancias[i]));
	}
	return respuesta;
}
