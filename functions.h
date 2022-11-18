#include <iostream>

// Callback que realizará la muestra de datos
static int callback(void* data, int argc, char** argv, char** azColName) {
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] :"NULL");
  }
  cout << endl;
  return 0;
}
