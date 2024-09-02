#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define MAX 50

using namespace std;

// Declaración de estructuras
struct fecha {
    int anio, mes, dia;
};

struct usuario {
    char nombre[MAX];
    char apellido[MAX];
    char cedula[11]; // Se requiere una cadena de 10 dígitos más el carácter nulo '\0'
    char numero_casa[MAX];
    char placa[MAX];
    char correo[MAX];
    char motivo_visita[MAX];
    char celular[MAX];
    fecha hora_entrada;
    fecha hora_salida;
};

// Prototipo de funciones
void ingreso();
void leer(int i);
void mostrar();
void buscar();
void menu();
void cambiarColor(int fondo, int texto);
void caratula();
void guardarArchivo();
void cargarArchivo();
void abrirArchivo();
fecha obtenerFechaActual();

// Variables globales
usuario grupo[MAX];
int num_usuario = 0;
const char* arch_in = "C:/Users/acer/Documents/TEXTO/RESIDENTES ARMENIA II.txt";
const char* arch_out = "C:/Users/acer/Documents/TEXTO/RESIDENTES ARMENIA II.txt";

int main() {
    caratula();
    cargarArchivo();  // Cargar datos de archivo al inicio
    menu();
    guardarArchivo();  // Guardar datos al salir
    return 0;
}

void menu() {
    int opcion;
    cambiarColor(1, 15);
    do {
        system("cls");
        cout << "\n--- MENU ---" << endl;
        cout << "1. MOSTRAR LISTA DE USUARIOS" << endl;
        cout << "2. ANIADIR NUMERO DE USUARIOS" << endl;
        cout << "3. BUSCAR USUARIO POR NOMBRE Y APELLIDO" << endl;
        cout << "4. GUARDAR USUARIOS EN ARCHIVO" << endl;
        cout << "5. ABRIR ARCHIVO DE USUARIOS" << endl;
        cout << "6. SALIR" << endl;
        cout << "DEME SU OPCION: ";
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer

        switch(opcion) {
            case 1:
                if (num_usuario == 0) {
                    cambiarColor(1, 14);
                    cout << "No hay usuarios ingresados aun." << endl;
                } else {
                    mostrar();
                }
                break;
            case 2:
                ingreso();
                break;
            case 3:
                buscar();
                break;
            case 4:
                guardarArchivo();
                cout << "Datos de usuarios guardados exitosamente en el archivo." << endl;
                break;
            case 5:
                abrirArchivo();
                break;
            case 6:
                cambiarColor(1, 14);
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cambiarColor(1, 12);
                cout << "Ingrese una opcion correcta" << endl;
        }
        if (opcion != 6) {
            cambiarColor(1, 15);
            cout << "\nPresione una tecla para continuar...";
            getch();
        }

    } while(opcion != 6);
}

void ingreso() {
    cambiarColor(1, 0);
    int nuevos;
    cout << "Ingrese el numero de usuarios a aniadir: "<< endl;
    cin >> nuevos;
    cin.ignore();  // Limpiar el buffer

    for (int i = num_usuario; i < num_usuario + nuevos && i < MAX; ++i) {
        cout << "Ingrese datos del usuario " << i + 1 << endl;
        leer(i);
    }
    num_usuario += nuevos;
    if (num_usuario > MAX) {
        num_usuario = MAX;
        cambiarColor(1, 14);
        cout << "Se ha alcanzado el numero maximo de usuarios." << endl;
    }
}

void leer(int i) {
    cambiarColor(1, 15);
    cout << "Ingrese nombre: "<< endl;
    cin.getline(grupo[i].nombre, MAX);

    cout << "Ingrese apellido: "<< endl;
    cin.getline(grupo[i].apellido, MAX);

    // Validar cédula
    bool cedulaValida;
     do {
        cedulaValida = true;
        cout << "Ingrese cedula de identidad (10 digitos): " << endl;
        cin.getline(grupo[i].cedula, 11);

        // Verificar si la cédula tiene exactamente 10 dígitos
        if (strlen(grupo[i].cedula) != 10) {
            cedulaValida = false;
            cambiarColor(1, 12);  // Color rojo para mensaje de error
            cout << "Cedula invalida, debe ingresar exactamente 10 dgitos." << endl;
            cambiarColor(1, 15);  // Restaurar color normal
        } else {
            // Verificar que todos los caracteres sean dígitos
            for (int j = 0; j < 10; ++j) {
                if (!isdigit(grupo[i].cedula[j])) {
                    cedulaValida = false;
                    cambiarColor(1, 12);  // Color rojo para mensaje de error
                    cout << "Cédula inválida, debe ingresar solo dígitos." << endl;
                    cambiarColor(1, 15);  // Restaurar color normal
                    break;
                }
            }
        }
    } while (!cedulaValida);

    cout << "Ingrese numero de casa: "<< endl;
    cin.getline(grupo[i].numero_casa, MAX);

    cout << "Ingrese placa vehicular (dejar vacio si no tiene): "<< endl;
    cin.getline(grupo[i].placa, MAX);

    cout << "Ingrese correo: "<< endl;
    cin.getline(grupo[i].correo, MAX);

    cout << "Ingrese motivo de visita (dejar vacio si no es visitante): "<< endl;
    cin.getline(grupo[i].motivo_visita, MAX);

    cout << "Ingrese numero de celular: "<< endl;
    cin.getline(grupo[i].celular, MAX);

    // Registrar hora de entrada automáticamente
    fecha actual = obtenerFechaActual();
    grupo[i].hora_entrada = actual;

    // Inicializar hora de salida
    grupo[i].hora_salida.anio = 0;
    grupo[i].hora_salida.mes = 0;
    grupo[i].hora_salida.dia = 0;

    cin.ignore();  // Limpiar el buffer
}

void mostrar() {
    cambiarColor(1, 15);
    for (int i = 0; i < num_usuario; ++i) {
        cout << "\nDatos del usuario " << i + 1 << ":" << endl;
        cout << "Nombre: " << grupo[i].nombre << endl;
        cout << "Apellido: " << grupo[i].apellido << endl;
        cout << "Cedula: " << grupo[i].cedula << endl;
        cout << "Numero de casa: " << grupo[i].numero_casa << endl;
        cout << "Placa vehicular: " << grupo[i].placa << endl;
        cout << "Correo: " << grupo[i].correo << endl;
        cout << "Motivo de visita: " << grupo[i].motivo_visita << endl;
        cout << "Numero de celular: " << grupo[i].celular << endl;
        cout << "Hora de entrada: " << grupo[i].hora_entrada.dia << "/" << grupo[i].hora_entrada.mes << "/"
             << grupo[i].hora_entrada.anio << endl;
        cout << "Hora de salida: " << grupo[i].hora_salida.dia << "/" << grupo[i].hora_salida.mes << "/"
             << grupo[i].hora_salida.anio << endl;
    }
}

void buscar() {
    cambiarColor(1, 0);
    char nombre[MAX], apellido[MAX];
    cout << "Ingrese el nombre del usuario a buscar: ";
    cin.getline(nombre, MAX);
    cout << "Ingrese el apellido del usuario a buscar: ";
    cin.getline(apellido, MAX);

    bool encontrado = false;
    for (int i = 0; i < num_usuario; ++i) {
        if (strcmp(grupo[i].nombre, nombre) == 0 && strcmp(grupo[i].apellido, apellido) == 0) {
            cout << "\nUsuario encontrado:" << endl;
            cout << "Nombre: " << grupo[i].nombre << endl;
            cout << "Apellido: " << grupo[i].apellido << endl;
            cout << "Cedula: " << grupo[i].cedula << endl;
            cout << "Numero de casa: " << grupo[i].numero_casa << endl;
            cout << "Placa vehicular: " << grupo[i].placa << endl;
            cout << "Correo: " << grupo[i].correo << endl;
            cout << "Motivo de visita: " << grupo[i].motivo_visita << endl;
            cout << "Numero de celular: " << grupo[i].celular << endl;
            cout << "Hora de entrada: " << grupo[i].hora_entrada.dia << "/" << grupo[i].hora_entrada.mes << "/"
                 << grupo[i].hora_entrada.anio << endl;
            cout << "Hora de salida: " << grupo[i].hora_salida.dia << "/" << grupo[i].hora_salida.mes << "/"
                 << grupo[i].hora_salida.anio << endl;

            // Registrar hora de salida
            grupo[i].hora_salida = obtenerFechaActual();

            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cambiarColor(1, 12);
        cout << "Usuario no encontrado." << endl;
    }
}

void guardarArchivo() {
    FILE *ofp = fopen(arch_out, "w");
    if (ofp == NULL) {
        cout << "No se pudo abrir el archivo de salida para escritura." << endl;
        return;
    }

    for (int i = 0; i < num_usuario; ++i) {
        fprintf(ofp, "%s %s %s %s %s %s %s %s %d/%d/%d %d/%d/%d\n",
                grupo[i].nombre, grupo[i].apellido, grupo[i].cedula, grupo[i].numero_casa,
                grupo[i].placa, grupo[i].correo, grupo[i].motivo_visita, grupo[i].celular,
                grupo[i].hora_entrada.dia, grupo[i].hora_entrada.mes, grupo[i].hora_entrada.anio,
                grupo[i].hora_salida.dia, grupo[i].hora_salida.mes, grupo[i].hora_salida.anio);
    }

    fclose(ofp);
}

void cargarArchivo() {
    FILE *ifp = fopen(arch_in, "r");
    if (ifp == NULL) {
        cout << "No se pudo abrir el archivo de entrada para lectura." << endl;
        return;
    }

    num_usuario = 0;
    while (fscanf(ifp, "%s %s %s %s %s %s %s %s %d/%d/%d %d/%d/%d\n",
                  grupo[num_usuario].nombre, grupo[num_usuario].apellido, grupo[num_usuario].cedula,
                  grupo[num_usuario].numero_casa, grupo[num_usuario].placa, grupo[num_usuario].correo,
                  grupo[num_usuario].motivo_visita, grupo[num_usuario].celular,
                  &grupo[num_usuario].hora_entrada.dia, &grupo[num_usuario].hora_entrada.mes, &grupo[num_usuario].hora_entrada.anio,
                  &grupo[num_usuario].hora_salida.dia, &grupo[num_usuario].hora_salida.mes, &grupo[num_usuario].hora_salida.anio) == 14) {
        num_usuario++;
        if (num_usuario >= MAX) break;
    }

    fclose(ifp);
}

void abrirArchivo() {
    // Abrir el archivo con el programa predeterminado del sistema
    system("start \"\" \"C:/Users/acer/Documents/TEXTO/RESIDENTES ARMENIA II.txt\"");
}

fecha obtenerFechaActual() {
    time_t t = time(nullptr);
    struct tm* tm = localtime(&t);
    fecha actual;
    actual.anio = tm->tm_year + 1900;
    actual.mes = tm->tm_mon + 1;
    actual.dia = tm->tm_mday;
    return actual;
}

void cambiarColor(int fondo, int texto) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fondo * 16 + texto);
}

void caratula() {
    cambiarColor(1, 15);
    system("cls");
    cout << "Bienvenido al sistema de registro de usuarios del Conjunto Habitacional Armenia II." << endl;
    cout << "Desarrollado por Chuqui Kerly y Ullcu Alexander" << endl;
    cout << "Presione una tecla para continuar...";
    getch();
}
