/* Desarrolladores:
Guillermo Esquivel Ortiz
Scarlet Donaji
Emilio Gómez
Arnold Ponce  */

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "design.h"
#include "functions.h"

string query, salida, destino;
using namespace std; 

// ------------------------------ Clase vuelos ---------------------
class Vuelos {
  private:
  // Variables
  string idVuelo, destino, salida, duracion, precio;
  public:
  //Creacion de metodos
  string insertarVuelos();
  string mostrarVuelos();
  string mostrarVuelosD(string destino,string salida);
  string eliminarVuelos();
  string editarVuelos();
};

// ------------------------------ Métodos de clase ---------------------
// Método para ingresar los vuelos nuevos
string Vuelos::insertarVuelos(){
  cout << endl << endl <<"Ingrese los valores solicitados" << endl;
  cout << "Id del vuelo: ";
  cin >> idVuelo;
  cout << endl;
  cout << "Destino: ";
  cin >> destino;
  cout << endl;
  cout << "Salida: ";
  cin >> salida;
  cout << endl;
  cout << "Duración: ";
  cin >> duracion;
  cout << endl;
  cout << "Precio: ";
  cin >> precio;
  cout << endl;
  string query = "INSERT INTO vuelo(idV, destino, salida, duracion, precio) values ('"+ idVuelo + "','"+ destino +"','"+ salida +"','"+ duracion +"' ,'"+ precio +"' )";
  return query;
}
// Método para mostrar todos los vuelos 
string Vuelos::mostrarVuelos(){
  string query = "SELECT * FROM vuelo";
  return query;
}
// Método para mostrar los vuelos definidos
string Vuelos::mostrarVuelosD(string destino,string salida){
  string query = "SELECT * FROM vuelo WHERE (destino = '"+ destino +"' AND salida = '"+ salida +"');";
  return query;
}
// Método para eliminar los vuelos
string Vuelos::eliminarVuelos(){
  cout << "Ingresa los valores solicitados" << endl;
  cout << "Identificador: ";
  cin >> idVuelo;
  cout << endl;
  
  string query = "DELETE FROM vuelo WHERE idV == '"+ idVuelo +"";
  return query;
}
// Método para editar los vuelos
string Vuelos::editarVuelos(){
  int op;
  cout << "Ingresa el identificador para proceder a editar"<< endl;
  
  cout << "Identificador: ";
  cin >> idVuelo;
  cout << endl;
  cout << "¿Que aspecto deseas cambiar?" << endl;
  cout << "1: Destino" << endl << "2: Salida" << endl << "3: Duración de vuelo" << endl << "4: Precio" << endl << endl;
  cout << "Opcion: ";
  cin >> op;
  cout << endl;
  // --------------------- Caso erroneo en ingreso de datos   ---------------------
  while(op != 1 && op!= 2 && op != 3 && op!= 4){
    cout<<"Ingresa una opcion valida"<<endl;
    cout << "¿Que aspecto deseas cambiar?" << endl;
    cout << "1: Destino" << endl << "2: Salida" << endl <<"3:Duración de vuelo" << endl << "4: Precio" << endl;
    cout << "Opcion: ";
    cin >> op;
    cout << endl;
  }   
  if(op==1){
    // Editar el destino
    cout << "Nuevo destino: ";
    cin >> destino;
    cout << endl;
    string query = "UPDATE vuelo SET destino = '"+ destino +"WHERE idV = '"+ idVuelo +"';";
    return query;

  } else if (op==2){
    // Editar la salida
    cout << "Nueva salida: ";
    cin >> salida;
    cout << endl;
    string query = "UPDATE vuelo SET salida = '"+ salida +"WHERE idV = '"+ idVuelo +"';";
    return query;
  } else if (op==3){
    // Editar la duracion
    cout << "Nueva duración del vuelo: ";
    cin >> duracion;
    cout << endl;
    string query = "UPDATE vuelo SET duracion = '"+duracion+"WHERE idV = '"+ idVuelo +"';";
    return query;
  } else if (op==4){
    // Editar el precio
    cout << "Nuevo precio: ";
    cin >> precio;
    cout << endl;
    string query = "UPDATE vuelo SET precio = '"+ precio +"WHEREidV = '"+ idVuelo +"';";
    return query;
  } else{
    // --------------------- Caso erroneo en ingreso de datos   ---------------------
      cout << "Ingresa una opcion valida "<<endl;
      return 0; 
  }
}


// ---------------------------------- Main ---------------------

int main() {
  // ----------------------------- DB Connection ---------------------
  sqlite3* DB;
  int exit = 0;
  exit = sqlite3_open("vuelos.db",&DB);

  if(exit){
    cerr << "Error al abrir la DB" << sqlite3_errmsg(DB) << endl;   return(-1); 
  }
  // ----------------------- Inicializacion del objeto ---------------------
  Vuelos V1;
  //-------------------------Ciclo para repeticion del programa
  int repeat=0;
  int op, opC;
  string query, salida, destino;

  do{
    // ------------------------ Ingreso de la opcion inicial ---------------------
    op = intro();
    //cout << "Bienvenido a la version 6 de AirFly, ////ingresa una opción" << //endl;
    //cout << "1: Usuario" << endl;
    //cout << "2: Operador" << endl;
    //cout << "Opcion: "; 
    //cin>>op;
    //cout << endl;
  
    // --------------------- Caso erroneo en ingreso de datos   ---------------------
    while (op != 1 && op != 2 ){
      cout << "Tu opción no es valida" << endl;
      cout << "Ingresa una opción" << endl;
      cout << "1: Usuario" << endl;
      cout << "2: Operador" << endl;
      cout << "Opcion: "; 
      cin>>op;
      cout << endl;
    }
    // ---------------------------- Opciones para el usuario  -------------------------
    if(op == 1){
      string salida,destino;
      cout << "Por favor, ingresa los siguientes datos: " << endl;
      cout << "Puerto de salida (SIN): ";
      cin >> salida;
      cout << endl << "Destino(ZAC): ";
      cin >> destino;
      cout << endl;

      query = V1.mostrarVuelosD(destino,salida);
      cout << "-------------------- Próximos vuelos ----------------------------" << endl;
      sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
      cout << endl << "-----------------------------------------------------------------" << endl;
    } 
    // ---------------------------- Opciones para el operador -------------------------
    else {
      //------------------------ Pedimos un usuario y una contraseña ----------------
      string user,pass;
      cout<<"Escribe el usuario (admin): ";
      cin >>user;
      cout<<"Escribe la contraseña (admin): ";
      cin >>pass;
      if(user=="admin" && pass=="admin"){
        // -------------------------------- Solicitar el proceso a realizar -------------------------
        op = menuOp();
        //cout << endl << endl <<"Elige el proceso //que //quieres realizar" << //endl;
        //cout << "1: Mostrar vuelos" << endl;
        //cout << "2: Añadir vuelos" << endl;
        //cout << "3: Cancelar vuelos" << endl;
        //cout << "4: Editar vuelos" << endl;
        //cout << "Opción: ";
        //cin >> op;
        // --------------------- Caso erroneo en ingreso de datos   ---------------------
        while(op!=1 && op!=2 && op!=3 &&op!=4){
          cout<<"Ingresa una opcion valida";
          cout << "Elige el proceso que quieres realizar" << endl;
          cout << "1: Mostrar vuelos" << endl;
          cout << "2: Añadir vuelos" << endl;
          cout << "3: Cancelar vuelos" << endl;
          cout << "4: Editar vuelos" << endl;
          cin >> op;
        }
        // -------------------------------- Llamada de métodos --------------------------------
        switch(op){
          case 1:
            cout << endl << "------------- Selecciona una opcion -------------" << endl;
            cout << "1: Mostrar datos definidos" << endl;
            cout << "2: Mostrar todos los datos" << endl;
            cout << endl << "Opción: ";
            cin >> opC;
            cout << endl;
            if(opC == 1) {
              // ----------------------- Mostrar datos definidos
              cout << "Ingresa la ciudad de salida(SIN): ";
              cin >> salida;
              cout << endl << "Ingresa la ciudad de destino(ZAC):";
              cin >> destino;
              cout << endl; 
              query = V1.mostrarVuelosD(destino, salida);
            } else if(opC == 2){
              // ---------------------- Mostrar toda la información
              query = V1.mostrarVuelos(); // Se obtiene el sql query del método
            }
            cout << "---------------------- Próximos vuelos --------------------------" << endl;
            sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); // Lo ejecutamos en nuestra  db
            cout << "------------------------------------------------" << endl;
            break;
          case 2:
            // Opcion para insertar información
            query = V1.insertarVuelos(); // Se obtiene el sql query del método
            sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); // Lo ejecutamos en nuestra db
            cout << "Se insertaron los datos correctamente!" << endl;
            break;
          case 3:
            // Opcion para eliminar información
            query = V1.eliminarVuelos(); // Se obtiene el sql query del método
            sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); // Lo ejecutamos en nuestra db
            cout << "Se eliminaron los datos satisfactoriamente!" <<  endl;
            break;
          case 4:
            // Opcion para editar información
            query = V1.editarVuelos(); // Se obtiene el sql query del método
            sqlite3_exec(DB, query.c_str(), callback, NULL, NULL); // Lo ejecutamos en nuestra db
            cout << endl <<"********** Se editaron los datos satisfactoriamente! **********" <<  endl;
            break;
          default:
            cout << "Esta no es una opción" << endl;
            break;
          }  
        }else{
          // En caso de no tener los datos correctos 
          cout<<"Acceso denegado"<<endl;
          cout<<"Usuario o contraseña incorrectos"<<endl;
        }  
      }
    // -------------------------------- Condicion si se desea repetir ------------------------------  
    cout << "¿Quieres realizar algo más?" << endl << endl;
    cout << "1. Repetir programa " << endl << "2. Salir" << endl << endl;
    cout << "Ingresa una opcion: ";
    cin >> repeat;
    cout << endl;
    cout << "--------------------------------------------------------" << endl;
    if (repeat == 2) 
      cout << "*-*-*-*-*-*-*-*-* Nos vemos a la próxima! *-*-*-*-*-*-*-*-*" << endl;

    

  } while(repeat==1);    
  sqlite3_close(DB); // Cerramos la base de datos
} 
