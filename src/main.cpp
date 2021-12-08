#include <unistd.h>
#include "Server.hpp"
#include "utility.hpp"

volatile sig_atomic_t finish = 0; // Variable for SIGTERM signal
volatile sig_atomic_t flush = 0; // Variable for SIGUSR1 signal

void signal_handler(int signal) {
  if (signal == SIGTERM){ // If the signal is SIGTERM
    finish = 1; // Makes finish variable 1 to mark that the program must end
  } else if (signal == SIGUSR1){ // If the signal is SIGUSR1
    flush = 1; // Makes flush variable 1 to mark that the cache must be emptied
    std::cout << "Done!" <<std::endl;
  }
}

int main(int argc, char const *argv[]) {

  //
  const std::string CACHE_SIZE_OPTION = "-C"; // Cache size option string
  const std::string PORT_OPTION = "-p"; // Port number opcion string

  std::string cache_str = get_cmd_option(argc, argv, CACHE_SIZE_OPTION); // Obtain cache size from the arguments
  std::string port_str = get_cmd_option(argc, argv, PORT_OPTION); // Obtain port number from the arguments

  std::cout << "Meteologica server. PID: "<< getpid()<<std::endl;

  int port;
  int cache_size;

  bool valid_parameters = true;

  if(is_number(port_str)){ // If the port number given is a number
    port = std::stoi(port_str); // Make the port number the argument obtained
    std::cout << "Port set to "<< port <<std::endl;
  } else { // If it is not, end program with an error
    std::cout << "No valid port option found. Please use -p <port number> "<<std::endl;
    valid_parameters = false;
  }

  if(is_number(cache_str)){ // If the cache size is a number
    cache_size = std::stoi(cache_str); // Make the cache size the argument obtained
    std::cout << "Cache size set to "<< cache_size <<std::endl;
  } else { // If it is not, end program with an error
    std::cout << "No valid cache size option found. Please use -C <cache size> "<<std::endl;
    valid_parameters = false;
  }

  if (valid_parameters){ // If parameters are right
    std::signal(SIGTERM, signal_handler); // Handle SIGTERM
    std::signal(SIGUSR1, signal_handler); // Handle SIGUSR1

    Server s(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 10, cache_size); // Create server object
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
//HECHO: TODO: MAKEFILE
// TODO: DOXYGEN
