#include "Server.hpp"

int main(int argc, char const *argv[]) {

  std::size_t size = 3;
  //Cache<std::string, int> c(size);
  //c.Put("Hello", 1);
  //c.Put("world", 2);
  //std::cout << c.Get("Hello") << c.Get("world") << std::endl;

  std::cout << "Meteologica server" << std::endl;
  Server sss(AF_INET, SOCK_STREAM, 0, 9999, INADDR_ANY, 10, size);
  std::cout << "Success" << std::endl;

  return 0;
}

//HECHO: TODO: DEVOLVER HASH
//HECHO: TODO: AÑADIR CACHÉ AL SERVIDOR
//HECHO: TODO: OPERADOR STDOUT CACHE
//HECHO: TODO: MÉTODO PARA VACIAR LA CACHE (USAR CLEAR EN ESTRUCTURAS DE LA STD)
// TODO: CLASE ABSTRACTA DE THREAD POOL
// TODO: CLASE DE SERVER THREAD POOL
// TODO: AÑADIR SERVER THREAD POOL A SERVER
// TODO: ATENDER PETICIONES CONCURRENTES
// TODO: REVISAR GESTIÓN DE ERRORES DE TODAS LAS CONEXIONES
// TODO: RECIBIR PUERTO Y TAMAÑO CACHE COMO ARGUMENTO AL EJECUTAR Y GESTIÓN DE ERROR DE ENTRADA
// TODO: PLANTEAR TRAER EL BUCLE A MAIN
// TODO: GESTIÓN DE SEÑAL SIGUSR1
// TODO: GESTIÓN DE SEÑAL SIGTERM
// TODO: REVISAR POR QUÉ HAY DOS CARACTERES EXTRA EN EL NÚMERO
// TODO: CERRAR SERVIDOR
// TODO: DOXYGEN
// TODO: MAKEFILE
// TODO: COMPROBAR PASOS A MÉTODOS CON CONST &
// TODO: SACAR FUNCIONES DE UTILIDAD DEL ARCHIVO SERVER
// TODO: COMPROBAR QUÉ COSAS SE PUEDEN PONER COMO size_t
