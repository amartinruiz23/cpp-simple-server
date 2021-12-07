#include <unistd.h> // Para imprimir pid
#include "Server.hpp"


volatile sig_atomic_t finish = 0;
volatile sig_atomic_t flush = 0;

void signal_handler(int signal) {
  if (signal == SIGTERM){
    finish = 1;
    std::cout << "TERM SIGNAL HANDLED "<< finish <<std::endl;
  } else if (signal == SIGUSR1){
    flush = 1;
    std::cout << "SIGUSR1 SIGNAL HANDLED "<<flush<<std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::cout << "PID: "<< getpid()<<std::endl;
  std::signal(SIGTERM, signal_handler);
  std::signal(SIGUSR1, signal_handler);
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
//HECHO: TODO: CLASE ABSTRACTA DE THREAD POOL
//HECHO: TODO: CLASE DE SERVER THREAD POOL
//HECHO: TODO: AÑADIR SERVER THREAD POOL A SERVER
//HECHO: TODO: ATENDER PETICIONES CONCURRENTES
//HECHO TODO: PLANTEAR TRAER EL BUCLE A MAIN
//HECHO: TODO: GESTIÓN DE SEÑAL SIGUSR1
//HECHO: TODO: GESTIÓN DE SEÑAL SIGTERM
// TODO: CERRAR SERVIDOR
// TODO: RECIBIR PUERTO Y TAMAÑO CACHE COMO ARGUMENTO AL EJECUTAR Y GESTIÓN DE ERROR DE ENTRADA
// TODO: REVISAR GESTIÓN DE ERRORES DE TODAS LAS CONEXIONES
// TODO: REVISAR POR QUÉ HAY DOS CARACTERES EXTRA EN EL NÚMERO
// TODO: DOXYGEN
// TODO: MAKEFILE
// TODO: COMPROBAR PASOS A MÉTODOS CON CONST &
// TODO: SACAR FUNCIONES DE UTILIDAD DEL ARCHIVO SERVER
// TODO: COMPROBAR QUÉ COSAS SE PUEDEN PONER COMO size_t
