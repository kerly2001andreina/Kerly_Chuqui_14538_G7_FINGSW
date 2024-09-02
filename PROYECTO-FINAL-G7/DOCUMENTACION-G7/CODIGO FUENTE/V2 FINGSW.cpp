#include <iostream>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>

#define MAX 50

using namespace std;

// Declaración de estructuras
struct fecha {
    int anio, mes, dia;
};

struct hora {
    int hora, minuto, segundo;
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
    fecha fecha_entrada;
    hora hora_entrada;
    fecha fecha_salida;
    hora hora_salida;
};

// Prototipo de funciones
void ingreso();
void leer(usuario& u);
void mostrar();
void buscar();
void menu();
void cambiarColor(int fondo, int texto);
void caratula();
void guardarArchivo();
void cargarArchivo();
void abrirArchivo();
fecha obtenerFechaActual();
hora obtenerHoraActual();
bool compararFechas(const usuario& a, const usuario& b);
void limpiarBuffer();

// Variables globales
vector<usuario> usuarios;
const char* arch_in = "C:/Users/acer/Documents/TEXTO/RESIDENTES ARMENIA II.txt";

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
                if (usuarios.empty()) {
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
    cout << "Ingrese el numero de usuarios a aniadir: " << endl;
    cin >> nuevos;
    cin.ignore();  // Limpiar el buffer

    for (int i = 0; i < nuevos; ++i) {
        usuario nuevo;
        cout << "Ingrese datos del usuario " << usuarios.size() + 1 << endl;
        leer(nuevo);

        usuarios.push_back(nuevo);
    }
}

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void leer(usuario& u) {
    cout << "Ingrese nombre: " << endl;
    cin.getline(u.nombre, MAX);

    cout << "Ingrese apellido: " << endl;
    cin.getline(u.apellido, MAX);

    bool cedulaValida;
    do {
        cedulaValida = true;
        cout << "Ingrese cedula de identidad (10 dígitos): " << endl;
        cin.getline(u.cedula, 11);

        // Verificar si la cédula tiene exactamente 10 dígitos
        if (strlen(u.cedula) != 10) {
            cedulaValida = false;
            cambiarColor(1, 12);
            cout << "Cédula inválida, debe ingresar exactamente 10 dígitos." << endl;
            cambiarColor(1, 15);
        } else {
            // Verificar que todos los caracteres sean dígitos
            for (int j = 0; j < 10; ++j) {
                if (!isdigit(u.cedula[j])) {
                    cedulaValida = false;
                    cambiarColor(1, 12);
                    cout << "Cédula inválida, debe ingresar solo dígitos." << endl;
                    cambiarColor(1, 15);
                    break;
                }
            }
        }
        
        if (!cedulaValida) {
            cout << "Inténtelo de nuevo." << endl;
        }

    } while (!cedulaValida);

    limpiarBuffer();  // Limpiar el buffer de entrada después de la validación de cédula

    cout << "Ingrese numero de casa: " << endl;
    cin.getline(u.numero_casa, MAX);

    cout << "Ingrese placa vehicular (dejar vacio si no tiene): " << endl;
    cin.getline(u.placa, MAX);

    cout << "Ingrese correo: " << endl;
    cin.getline(u.correo, MAX);

    cout << "Ingrese motivo de visita (dejar vacio si no es visitante): " << endl;
    cin.getline(u.motivo_visita, MAX);

    cout << "Ingrese numero de celular: " << endl;
    cin.getline(u.celular, MAX);

    // Registrar fecha y hora de entrada automáticamente
    u.fecha_entrada = obtenerFechaActual();
    u.hora_entrada = obtenerHoraActual();

    // Inicializar fecha y hora de salida
    u.fecha_salida.anio = 0;
    u.fecha_salida.mes = 0;
    u.fecha_salida.dia = 0;
    u.hora_salida.hora = 0;
    u.hora_salida.minuto = 0;
    u.hora_salida.segundo = 0;

    limpiarBuffer();  // Limpiar el buffer de entrada después de todos los datos
}

void mostrar() {
    cambiarColor(1, 15);
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << "\nDatos del usuario " << i + 1 << ":" << endl;
        cout << "Nombre: " << usuarios[i].nombre << endl;
        cout << "Apellido: " << usuarios[i].apellido << endl;
        cout << "Cedula: " << usuarios[i].cedula << endl;
        cout << "Numero de casa: " << usuarios[i].numero_casa << endl;
        cout << "Placa vehicular: " << usuarios[i].placa << endl;
        cout << "Correo: " << usuarios[i].correo << endl;
        cout << "Motivo de visita: " << usuarios[i].motivo_visita << endl;
        cout << "Numero de celular: " << usuarios[i].celular << endl;
        cout << "Fecha de entrada: " << usuarios[i].fecha_entrada.dia << "/" << usuarios[i].fecha_entrada.mes << "/"
             << usuarios[i].fecha_entrada.anio << endl;
        cout << "Hora de entrada: " << usuarios[i].hora_entrada.hora << ":" << usuarios[i].hora_entrada.minuto << ":" 
             << usuarios[i].hora_entrada.segundo << endl;
        cout << "Fecha de salida: " << usuarios[i].fecha_salida.dia << "/" << usuarios[i].fecha_salida.mes << "/"
             << usuarios[i].fecha_salida.anio << endl;
        cout << "Hora de salida: " << usuarios[i].hora_salida.hora << ":" << usuarios[i].hora_salida.minuto << ":" 
             << usuarios[i].hora_salida.segundo << endl;
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
    for (auto& u : usuarios) {
        if (strcmp(u.nombre, nombre) == 0 && strcmp(u.apellido, apellido) == 0) {
            cout << "\nUsuario encontrado:" << endl;
            cout << "Nombre: " << u.nombre << endl;
            cout << "Apellido: " << u.apellido << endl;
            cout << "Cedula: " << u.cedula << endl;
            cout << "Numero de casa: " << u.numero_casa << endl;
            cout << "Placa vehicular: " << u.placa << endl;
            cout << "Correo: " << u.correo << endl;
            cout << "Motivo de visita: " << u.motivo_visita << endl;
            cout << "Numero de celular: " << u.celular << endl;
            cout << "Fecha de entrada: " << u.fecha_entrada.dia << "/" << u.fecha_entrada.mes << "/"
                 << u.fecha_entrada.anio << endl;
            cout << "Hora de entrada: " << u.hora_entrada.hora << ":" << u.hora_entrada.minuto << ":" 
                 << u.hora_entrada.segundo << endl;
            cout << "Fecha de salida: " << u.fecha_salida.dia << "/" << u.fecha_salida.mes << "/"
                 << u.fecha_salida.anio << endl;
            cout << "Hora de salida: " << u.hora_salida.hora << ":" << u.hora_salida.minuto << ":" 
                 << u.hora_salida.segundo << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cambiarColor(1, 14);
        cout << "No se encontró al usuario con nombre " << nombre << " y apellido " << apellido << "." << endl;
    }
}

void guardarArchivo() {
    ofstream archivo(arch_in);
    if (archivo.is_open()) {
        for (const auto& u : usuarios) {
            archivo << u.nombre << endl;
            archivo << u.apellido << endl;
            archivo << u.cedula << endl;
            archivo << u.numero_casa << endl;
            archivo << u.placa << endl;
            archivo << u.correo << endl;
            archivo << u.motivo_visita << endl;
            archivo << u.celular << endl;
            archivo << u.fecha_entrada.dia << endl;
            archivo << u.fecha_entrada.mes << endl;
            archivo << u.fecha_entrada.anio << endl;
            archivo << u.hora_entrada.hora << endl;
            archivo << u.hora_entrada.minuto << endl;
            archivo << u.hora_entrada.segundo << endl;
            archivo << u.fecha_salida.dia << endl;
            archivo << u.fecha_salida.mes << endl;
            archivo << u.fecha_salida.anio << endl;
            archivo << u.hora_salida.hora << endl;
            archivo << u.hora_salida.minuto << endl;
            archivo << u.hora_salida.segundo << endl;
        }
        archivo.close();
    } else {
        cambiarColor(1, 12);
        cout << "Error al abrir el archivo para guardar los datos." << endl;
    }
}

void cargarArchivo() {
    ifstream archivo(arch_in);
    if (archivo.is_open()) {
        usuario u;
        while (archivo.getline(u.nombre, MAX)) {
            archivo.getline(u.apellido, MAX);
            archivo.getline(u.cedula, 11);
            archivo.getline(u.numero_casa, MAX);
            archivo.getline(u.placa, MAX);
            archivo.getline(u.correo, MAX);
            archivo.getline(u.motivo_visita, MAX);
            archivo.getline(u.celular, MAX);
            archivo >> u.fecha_entrada.dia >> u.fecha_entrada.mes >> u.fecha_entrada.anio;
            archivo >> u.hora_entrada.hora >> u.hora_entrada.minuto >> u.hora_entrada.segundo;
            archivo >> u.fecha_salida.dia >> u.fecha_salida.mes >> u.fecha_salida.anio;
            archivo >> u.hora_salida.hora >> u.hora_salida.minuto >> u.hora_salida.segundo;
            archivo.ignore(); // Limpiar el buffer para la siguiente línea
            usuarios.push_back(u);
        }
        archivo.close();
    } else {
        cambiarColor(1, 12);
        cout << "Error al abrir el archivo para cargar los datos." << endl;
    }
}

void abrirArchivo() {
    ifstream archivo(arch_in);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    } else {
        cambiarColor(1, 12);
        cout << "Error al abrir el archivo para visualizar datos." << endl;
    }
}

fecha obtenerFechaActual() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    fecha f;
    f.anio = now->tm_year + 1900;
    f.mes = now->tm_mon + 1;
    f.dia = now->tm_mday;
    return f;
}

hora obtenerHoraActual() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    hora h;
    h.hora = now->tm_hour;
    h.minuto = now->tm_min;
    h.segundo = now->tm_sec;
    return h;
}

void cambiarColor(int fondo, int texto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (fondo << 4) | texto);
}


void caratula() {
    cambiarColor(1, 15);
    system("cls");
    cout << "Bienvenido al sistema de registro de usuarios del Conjunto Habitacional Armenia II." << endl;
    cout << "Desarrollado por Chuqui Kerly y Ullcu Alexander" << endl;
    cout << "Presione una tecla para continuar...";
    getch();
}