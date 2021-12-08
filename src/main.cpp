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

  std::cout << "Meteologica server. PID: "<< getpid()<<std::endl;

  int port;
  int cache_size;

  bool valid_parameters = true;

  if(is_number(port_str)){
    port = std::stoi(port_str);
    std::cout << "Port set to "<< port <<std::endl;
  } else {
    std::cout << "No valid port option found. Please use -p <port number> "<<std::endl;
    valid_parameters = false;
  }

  if(is_number(cache_str)){
    cache_size = std::stoi(cache_str);
    std::cout << "Cache size set to "<< cache_size <<std::endl;
  } else {
    std::cout << "No valid cache size option found. Please use -C <cache size> "<<std::endl;
    valid_parameters = false;
  }

  if (valid_parameters){
    std::signal(SIGTERM, signal_handler);
    std::signal(SIGUSR1, signal_handler);

    Server s(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, cache_size);
  }
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
//HECHO: TODO: REVISAR POR QUÉ HAY DOS CARACTERES EXTRA EN EL NÚMERO
//HECHO: TODO: CERRAR SERVIDOR
//HECHO: TODO: REFACTOR DE NOMBRES DE FUNCIONES
//HECHO: TODO: REVISAR GESTIÓN DE ERRORES DE TODAS LAS CONEXIONES
//HECHO: TODO: COMPROBAR PASOS A MÉTODOS CON CONST &
//HECHO: TODO: BORRAR COMENTARIOS INNECESARIOS
// TODO: DOXYGEN
// TODO: MAKEFILE
