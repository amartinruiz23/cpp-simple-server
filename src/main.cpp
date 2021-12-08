#include <unistd.h> // Para imprimir pid
#include "Server.hpp"
#include "utility.hpp"

volatile sig_atomic_t finish = 0;
volatile sig_atomic_t flush = 0;

void signal_handler(int signal) {
  if (signal == SIGTERM){
    finish = 1;
  } else if (signal == SIGUSR1){
    flush = 1;
    std::cout << "Done!" <<std::endl;
  }
}

int main(int argc, char const *argv[]) {

  const std::string CACHE_SIZE_OPTION = "-C";
  const std::string PORT_OPTION = "-p";

  std::string cache_str = get_cmd_option(argc, argv, CACHE_SIZE_OPTION);
  std::string port_str = get_cmd_option(argc, argv, PORT_OPTION);

  //std::cout <<"CACHE SIZE: "<<cache_str<< " IS NUMBER: "<<is_number(cache_str)<<std::endl;
  //std::cout <<"PORT NUMBER: "<<port_str<< " IS NUMBER: "<<is_number(port_str)<<std::endl;
  std::cout << "Meteologica server. PID: "<< getpid()<<std::endl;

  int port;
  int cache_size;

  if(is_number(port_str)){
    port = std::stoi(port_str);
    std::cout << "Port set to "<< port <<std::endl;
  } else {
    port = 9999;
    std::cout << "No valid port option found. By default, port set to "<<port<<std::endl;
  }

  if(is_number(cache_str)){
    cache_size = std::stoi(cache_str);
    std::cout << "Cache size set to "<< cache_size <<std::endl;
  } else {
    cache_size = 5;
    std::cout << "No valid cache size option found. By default, cache size set to "<<cache_size<<std::endl;
  }

  std::signal(SIGTERM, signal_handler);
  std::signal(SIGUSR1, signal_handler);

  //std::size_t size = 3;
  //Cache<std::string, int> c(size);
  //c.Put("Hello", 1);
  //c.Put("world", 2);
  //std::cout << c.Get("Hello") << c.Get("world") << std::endl;

  Server s(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, cache_size);
  
  return 0;
}

//HECHO: TODO: DEVOLVER HASH
//HECHO: TODO: AÑADIR CACHÉ AL SERVIDOR
//HECHO: TODO: OPERADOR STDOUT CACHE
//HECHO: TODO: MÉTODO PARA VACIAR LA CACHE (USAR CLEAR EN ESTRUCTURAS DE LA STD)
//HECHO: TODO: CLASE ABSTRACTA DE THREAD POOL
//HECHO: TODO: CLASE DE SERVER THREAD POOL
//HECHO: TODO: AÑADIR SERVER THREAD POOL A SERVER
//HECHO: TODO: ATENDER PETICIONES CONCURRENTES
//HECHO: TODO: PLANTEAR TRAER EL BUCLE A MAIN
//HECHO: TODO: GESTIÓN DE SEÑAL SIGUSR1
//HECHO: TODO: GESTIÓN DE SEÑAL SIGTERM
//HECHO: TODO: RECIBIR PUERTO Y TAMAÑO CACHE COMO ARGUMENTO AL EJECUTAR Y GESTIÓN DE ERROR DE ENTRADA
//HECHO: TODO: SACAR FUNCIONES DE UTILIDAD DEL ARCHIVO SERVER
// TODO: REFACTOR DE NOMBRES DE FUNCIONES
// TODO: REVISAR POR QUÉ HAY DOS CARACTERES EXTRA EN EL NÚMERO
// TODO: COMPROBAR QUÉ COSAS SE PUEDEN PONER COMO size_t
// TODO: CERRAR SERVIDOR
// TODO: REVISAR GESTIÓN DE ERRORES DE TODAS LAS CONEXIONES
// TODO: COMPROBAR PASOS A MÉTODOS CON CONST &
// TODO: DOXYGEN
// TODO: MAKEFILE
