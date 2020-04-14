#ifndef PANTALLAS_HPP_
#define PANTALLAS_HPP_

#include "../utilitarios/utilitarios.hpp"

void pantallaComprador();
void ingresarComprador();
void registrarComprador();
void compradorLogeado(string numero);
void compradorComprar(struct comprador comprador);
void estadoPedido(struct comprador comprador);
void registrarRepartidor();
void ingresarRepartidor();
void repartidorLogeado(string usuario);
void pantallaRepartidor();
void pantallaPrincipal();
void pantallaTienda();
void registrarTienda();
void ingresarTienda();
void tiendaLogeado(string usuario);
void ingresarProducto(string usuario);
void editarTienda(string usuario);
void eliminarTienda(string usuario);
void cerrarApp();
void verPedidosPendientes(struct comprador comprador);
void verPedidosFinalizados(struct comprador comprador);
void tomarPedido(struct repartidor repartidor);
void finalizarPedido(struct repartidor repartidor);
void verFacturas(struct comprador comprador);

#endif
