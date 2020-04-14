#ifndef UTILITARIOS_HPP_
#define UTILITARIOS_HPP_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
using namespace std;

//FUNCIONES **************************************************************************************

bool buscarPalabraRepartidor(string dato);
bool buscarPalabraTienda(string dato);
bool buscarPalabraComprador(string dato);
unsigned long long saull(string texto);
int sai(string texto);
float saf(string texto);
string ias(unsigned long long n);
string ias(int n);
string fas(float n);
int elevar(unsigned long long x, unsigned long long y);
int primeros(unsigned long long digitos, unsigned long long &numero);
int ultimos(unsigned long long digitos, unsigned long long &numero);
int maximo(unsigned long long u,unsigned long long v);
int digitos (unsigned long long n, unsigned long long &dig);
unsigned long long karatsuba (unsigned long long &u, unsigned long long &v);
unsigned long long contra(unsigned long long n);
vector < pair <struct tienda,float> > buscarTiendas(string producto,int coordx,int coordy);
void cerrarApp();
void imprimirCategoriasProductos();
vector <string> obtenerProductos(string categoria);
vector <string> separarDatos(string linea);
void imprimirProductos(vector <string> productos);
struct repartidor obtenerRepartidor(string datoRepartidor);
struct comprador obtenerComprador(string numero);
struct tienda obtenerTienda(string usuario);
float buscarPrecio(string producto,string usuarioTienda);
void generarPedido(string producto,int cantidad,float precioTotal,float pagaCon,bool casa,int coordx,int coordy,struct tienda tienda,struct comprador comprador);
void agregarHistorial(string producto,int cantidad,float precioTotal,struct tienda tienda,struct comprador comprador);
string obtenerFecha();
string obtenerHora();
vector <struct pedidoHistorial> obtenerPedidosPendientes(struct comprador comprador);
void imprimirPedidosPendientes(vector <struct pedidoHistorial> pedidos);
void CancelarPedido(string telefonoComprador,string horaPedido);
vector <string> obtenerVectorArchivo(string rutaArchivo);
vector <struct pedidoHistorial> obtenerVectorEstructuraPedidos(vector <string> vectorArchivoHistorialPedidos);
void imprimirPedidosFinalizados(vector <struct pedidoHistorial> pedidos);
vector <struct pedidoHistorial> obtenerPedidosFinalizados(struct comprador comprador);
void modificarRepartidor(struct repartidor repartidor);
void cambiarEstadoPuntuacionHistorialPedidos(struct pedidoHistorial pedido);
vector <struct pedidoDisponible> obtenerPedidosDisponibles();
void imprimirPedidosDisponibles(vector <struct pedidoDisponible> pedidosDisponibles);
void BorrarPedidoTomar(string telefonoComprador,string horaPedido,struct repartidor repartidor);
vector <struct pedidoHistorial> obtenerPedidosTomados(struct repartidor repartidor);
void imprimirPedidosTomados(vector <struct pedidoHistorial> pedidosTomados);
void FinalizarPedidoHistorial(string telefonoComprador,string horaPedido);
vector <struct pedidoHistorial> obtenerFacturas(struct comprador comprador);
void imprimirFacturas(vector <struct pedidoHistorial> pedidos);

//ESTRUCTURAS ************************************************************************************

struct pedidoHistorial{
	string nombreProducto;
	int cantidad;
	float montoTotal;
	string nombreTienda;
	string telefonoComprador;
	string fechaPedido;
	string horaPedido;
	string fechaEntrega;
	string horaEntrega;
	string repartidor;
	string telefonoRepartidor;
	string estadoPuntuacion;
	string estadoPedido;

	void inicializarConVector(vector <string> datos){
		nombreProducto=datos[0];
		cantidad=sai(datos[1]);
		montoTotal=saf(datos[2]);
		nombreTienda=datos[3];
		telefonoComprador=datos[4];
		fechaPedido=datos[5];
		horaPedido=datos[6];
		fechaEntrega=datos[7];
		horaEntrega=datos[8];
		repartidor=datos[9];
		telefonoRepartidor=datos[10];
		estadoPuntuacion=datos[11];
		estadoPedido=datos[12];
	}

	string crearLinea(){
		string linea;
		return linea=nombreProducto+'|'+ias(cantidad)+'|'+fas(montoTotal)+'|'+nombreTienda+'|'+telefonoComprador+'|'+fechaPedido+'|'+horaPedido+'|'+fechaEntrega+'|'+horaEntrega+'|'+repartidor+'|'+telefonoRepartidor+'|'+estadoPuntuacion+'|'+estadoPedido;
	}
};

struct pedidoDisponible{
	string nombreProducto;
	string horaPedido;
	string fechaPedido;
	string nombreTienda;
	string direccionTienda;
	int cantidad;
	float montoTotal;
	float pagaCon;
	string nombreComprador;
	string direccionComprador;
	int coordX;
	int coordY;
	string telefonoComprador;

	void inicializarConVector(vector <string> datos){
		nombreProducto=datos[0];
		horaPedido=datos[1];
		fechaPedido=datos[2];
		nombreTienda=datos[3];
		direccionTienda=datos[4];
		cantidad=sai(datos[5]);
		montoTotal=saf(datos[6]);
		pagaCon=saf(datos[7]);
		nombreComprador=datos[8];
		direccionComprador=datos[9];
		coordX=sai(datos[10]);
		coordY=sai(datos[11]);
		telefonoComprador=datos[12];
	}

	string crearLinea(){
		string linea;
		return linea=nombreProducto+'|'+horaPedido+'|'+fechaPedido+'|'+nombreTienda+'|'+direccionTienda+'|'+ias(cantidad)+'|'+fas(montoTotal)+'|'+fas(pagaCon)+'|'+nombreComprador+'|'+direccionComprador+'|'+ias(coordX)+'|'+ias(coordY)+'|'+telefonoComprador;
	}
};

struct producto{
	string categoria;
	string tienda;
	string nombre;
	float precio;

	void inicializar(string opcion,string usuario,string nombreProducto){
		if(opcion=="1"){
			categoria="Viveres";
		}else if(opcion=="2"){
			categoria="Higiene personal";
		}else if(opcion=="3"){
			categoria="Limpieza del hogar";
		}
		tienda=usuario;
		nombre=nombreProducto;
	}

	string crearLinea(){
		string linea;
		return linea=categoria+'|'+tienda+'|'+nombre+'|'+fas(precio);
	}

	void agregarProducto(){
		string linea=crearLinea();
		string rutaArchivo="../archivos/productos/listaProductosPorTiendas.txt"; //Cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::app);
		if(archivo.is_open()){
			archivo << linea << endl;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}
};

struct comprador{
	string nombre;
	unsigned long long numero;
	string correo;
	string direccion;
	int coordX;
	int coordY;
	string preguntaSecreta;
	string respuestaSecreta;
	int contrasenia;

	void inicializarConVector(vector<string> datos){
		nombre = datos[0];
		numero = saull(datos[1]);
		correo = datos[2];
		direccion = datos[3];
		coordX = sai(datos[4]);
		coordY = sai(datos[5]);
		preguntaSecreta=datos[6];
		respuestaSecreta=datos[7];
		contrasenia=sai(datos[8]);
	}

	void crearContrasenia(){
		unsigned long long valor=numero%10000;
		contrasenia=contra(valor);
	}

	string crearLinea(){
		string linea;
		return linea=nombre+'|'+ias(numero)+'|'+correo+'|'+direccion+'|'+ias(coordX)+'|'+ias(coordY)+'|'+preguntaSecreta+'|'+respuestaSecreta+'|'+ias(contrasenia);
	}

	void agregarComprador(){
		string linea=crearLinea();
		string rutaArchivo="../archivos/compradores/listaCompradores.txt"; //Cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::app);
		if(archivo.is_open()){
			archivo << linea << endl;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}

	void crearArchivoConfirmacion(){
		string rutaArchivo="../archivos/compradores/confirmacion/"+correo+".txt"; //cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::trunc);
		if(archivo.is_open()){
			archivo << "Sus datos son los siguientes:\n" << endl;
			archivo << "Nombre: " << nombre << endl;
			archivo << "Numero de telefono: " << numero << endl;
			archivo << "Correo electronico: " << correo << endl;
			archivo << "Direccion: " << direccion << endl;
			archivo << "Coordenadas XY (separadas por espacio): " << coordX << " " << coordY << endl;
			archivo << "Pregunta secreta: " << preguntaSecreta << endl;
			archivo << "Respuesta secreta: " << respuestaSecreta << endl;
			archivo << "Contrasenia: " << contrasenia;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}
};

struct repartidor{
	string nombre;
	unsigned long long numero;
	string dni;
	string usuario;
	string correo;
	unsigned long long contrasenia;
	float puntuacion;
	int numPuntuaciones;

	void inicializarConVector(vector<string> datos){
		nombre = datos[0];
		numero = saull(datos[1]);
		dni = datos[2];
		usuario = datos[3];
		correo = datos[4];
		contrasenia = saull(datos[5]);
		puntuacion=saf(datos[6]);
		numPuntuaciones=sai(datos[7]);
	}

	void ingresarPuntuacion(float punt){
		float total=puntuacion*numPuntuaciones;
		numPuntuaciones++;
		puntuacion=(total+punt)/numPuntuaciones;
	}

	void crearContrasenia(){
		unsigned long long valor=numero%10000;
		contrasenia=contra(valor);
	}

	string crearLinea(){
		string linea;
		return linea=nombre+'|'+ias(numero)+'|'+dni+'|'+usuario+'|'+correo+'|'+ ias(contrasenia)+'|'+fas(puntuacion)+'|'+ias(numPuntuaciones);
	}

	void agregarRepartidor(){
		string linea=crearLinea();
		//string rutaArchivo="archivos/repartidores/listaRepartidores"; //Cuando se corre en eclipse
		string rutaArchivo="../archivos/repartidores/listaRepartidores.txt"; //Cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::app);
		if(archivo.is_open()){
			archivo << linea << endl;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}

	void crearArchivoConfirmacion(){
		//string rutaArchivo="archivos/repartidores/confirmacion/"+correo+".txt"; //cuando se corre en el eclipse
		string rutaArchivo="../archivos/repartidores/confirmacion/"+correo+".txt"; //cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::trunc);
		if(archivo.is_open()){
			archivo << "Sus datos son los siguientes:\n" << endl;
			archivo << "Nombre del repartidor: " << nombre << endl;
			archivo << "Numero de telefono: " << numero << endl;
			archivo << "DNI: " << dni << endl;
			archivo << "Usuario: " << usuario << endl;
			archivo << "Contrasenia: " << contrasenia<<endl;
			archivo << "Puntacion: "<< puntuacion<<endl;
			archivo << "Numero de puntuaciones: "<< numPuntuaciones<<endl;

		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}
};

struct tienda{
	string nombre;
	unsigned long long numero;
	string usuario;
	string correo;
	string direccion;
	int coordX;
	int coordY;
	unsigned long long contrasenia;

	void inicializarConVector(vector<string> datos){
		nombre = datos[0];
		numero = saull(datos[1]);
		usuario = datos[2];
		correo = datos[3];
		direccion = datos[4];
		coordX = sai(datos[5]);
		coordY = sai(datos[6]);
		contrasenia=sai(datos[7]);
	}

	string crearLinea(){
		string linea;
		return linea=nombre+'|'+ias(numero)+'|'+usuario+'|'+correo+'|'+direccion+'|'+ias(coordX)+'|'+ias(coordY)+'|'+ias(contrasenia);
	}

	void ingresarDatos(int i,string dato){
		switch (i){
		case 0: nombre=dato;
		break;
		case 1: numero=saull(dato);
		break;
		case 2: usuario=dato;
		break;
		case 3: correo=dato;
		break;
		case 4: direccion=dato;
		break;
		case 5:	coordX=sai(dato);
		break;
		case 6: coordY=sai(dato);
		break;
		case 7: contrasenia=saull(dato);
		break;
		}
	}

	void crearContrasenia(){
		unsigned long long valor=numero%1000;
		contrasenia=contra(valor);
	}

	void agregarTienda(){
		string linea=crearLinea();
		//string rutaArchivo="archivos/tiendas/listaTiendas.txt"; //Cuando se corre en eclipse
		string rutaArchivo="../archivos/tiendas/listaTiendas.txt"; //Cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::app);
		if(archivo.is_open()){
			archivo << linea << endl;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}

	void crearArchivoConfirmacion(){
		//string rutaArchivo="archivos/confirmacion/"+correo+".txt"; //cuando se corre en el eclipse
		string rutaArchivo="../archivos/tiendas/confirmacion/"+correo+".txt"; //cuando se corre el ejecutable
		ofstream archivo;
		archivo.open(rutaArchivo.c_str(),ios::trunc);
		if(archivo.is_open()){
			archivo << "Sus datos son los siguientes:\n" << endl;
			archivo << "Nombre de la tienda: " << nombre << endl;
			archivo << "Numero de telefono: " << numero << endl;
			archivo << "Usuario: " << usuario << endl;
			archivo << "Correo electronico de contacto: " << correo << endl;
			archivo << "Direccion de la tienda: " << direccion << endl;
			archivo << "Coordenadas XY (separadas por espacio): " << coordX << " " << coordY << endl;
			archivo << "Contrasenia: " << contrasenia;
		}else{
			cout << "El archivo no pudo abrirse" << endl;
		}
		archivo.close();
	}
};

#endif
