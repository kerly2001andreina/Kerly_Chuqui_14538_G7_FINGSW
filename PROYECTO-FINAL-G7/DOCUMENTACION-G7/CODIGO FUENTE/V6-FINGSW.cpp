#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip> 

using namespace std;

void clearScreen() {
    system("cls");
}

// Funcion para mostrar la hora actual
string getCurrentTime() {
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
    return string(buffer);
}

// Funcion para validar cedula
bool isValidCedula(const string& cedula) {
    if (cedula.length() != 10) return false;
    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Funcion para validar numero de celular
bool isValidCellNumber(const string& cellNumber) {
    if (cellNumber.length() != 10) return false;
    for (char c : cellNumber) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Funcion para registrar nuevo usuario
void registerUser() {
    clearScreen();
    string nombreApellido, cedula, tipoUsuario, motivoVisita, placaVehiculo, celular, numeroCasa;
    
    cout << "Ingrese nombre y apellido: ";
    getline(cin, nombreApellido);
    
    while (true) {
        cout << "Ingrese numero de cedula (10 digitos): ";
        getline(cin, cedula);
        if (isValidCedula(cedula)) break;
        cout << "Cedula invalida. Debe tener 10 digitos y solo numeros.\n";
    }
    
    cout << "Numero de casa a la que se dirige: ";
    getline(cin, numeroCasa);
    
    cout << "Es residente o visita? (residente/visita): ";
    getline(cin, tipoUsuario);
    
    if (tipoUsuario == "visita") {
        cout << "Motivo de la visita: ";
        getline(cin, motivoVisita);
    }
    
    cout << "Tiene vehiculo? (si/no): ";
    string tieneVehiculo;
    getline(cin, tieneVehiculo);
    
    if (tieneVehiculo == "si") {
        cout << "Ingrese placa vehicular: ";
        getline(cin, placaVehiculo);
    }
    
    while (true) {
        cout << "Ingrese numero de celular (10 digitos): ";
        getline(cin, celular);
        if (isValidCellNumber(celular)) break;
        cout << "Numero de celular invalido. Debe tener 10 digitos y solo numeros.\n";
    }
    
    string entradaHora = getCurrentTime();
    
    // Guardar en archivo
    ofstream outFile("usuarios.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Nombre y Apellido: " << nombreApellido << endl;
        outFile << "Numero de Cedula: " << cedula << endl;
        outFile << "Numero de Casa: " << numeroCasa << endl;
        outFile << "Tipo de Usuario: " << tipoUsuario << endl;
        if (tipoUsuario == "visita") {
            outFile << "Motivo de la Visita: " << motivoVisita << endl;
        }
        if (tieneVehiculo == "si") {
            outFile << "Placa Vehicular: " << placaVehiculo << endl;
        }
        outFile << "Numero de Celular: " << celular << endl;
        outFile << "Hora de Entrada: " << entradaHora << endl;
        outFile << "---------------------------" << endl;
        outFile.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar.\n";
    }
    
    cout << "Usuario registrado exitosamente. Hora de entrada: " << entradaHora << endl;
}

// Funcion para mostrar lista de usuarios
void showUsers() {
    clearScreen();
    ifstream inFile("usuarios.txt");
    string line;
    
    if (inFile.is_open()) {
        cout << "Contenido del archivo usuarios.txt:\n";
        cout << "--------------------------------------\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "No se pudo abrir el archivo para leer.\n";
    }
}

// Funcion para registrar salida
void registerExit() {
    clearScreen();
    string cedula, line;
    string tempFileName = "temp.txt";
    string outputFileName = "usuarios.txt";

    cout << "Ingrese numero de cedula para registrar salida: ";
    getline(cin, cedula);

    ifstream inFile(outputFileName);
    ofstream outFile(tempFileName);

    bool found = false;
    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            size_t pos = line.find("Numero de Cedula: " + cedula);

            if (pos != string::npos) {
                string salidaHora = getCurrentTime();
                size_t horaEntradaPos = line.find("Hora de Entrada:");

                if (horaEntradaPos != string::npos) {
                    // Asegúrate de agregar o actualizar la hora de salida
                    size_t horaSalidaPos = line.find("Hora de Salida:");

                    if (horaSalidaPos != string::npos) {
                        // Actualiza solo la hora de salida si ya existe
                        line = line.substr(0, horaSalidaPos) + "Hora de Salida: " + salidaHora;
                    } else {
                        // Añade la hora de salida si no existe
                        line += "\nHora de Salida: " + salidaHora;
                    }
                } else {
                    // La hora de entrada no se encontró, lo que indica un problema
                    line += "\nHora de Salida: " + salidaHora;
                }
                outFile << line << endl;
                found = true;
            } else {
                outFile << line << endl;
            }
        }
        inFile.close();
        outFile.close();

        if (found) {
            remove(outputFileName.c_str());
            rename(tempFileName.c_str(), outputFileName.c_str());
            cout << "Hora de salida registrada exitosamente.\n";
        } else {
            remove(tempFileName.c_str());
            cout << "Cedula no encontrada.\n";
        }
    } else {
        cout << "No se pudo abrir el archivo.\n";
    }
}

// Función para abrir y visualizar el archivo de usuarios
void openFile() {
    clearScreen();
    ifstream inFile("usuarios.txt");
    string line;

    if (inFile.is_open()) {
        cout << "Contenido del archivo usuarios.txt:\n";
        cout << "--------------------------------------\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "No se pudo abrir el archivo para leer.\n";
    }
}

// Función principal
int main() {
    int opcion;
    
    do {
        clearScreen();
        cout << "-----------------------BIENVENIDO AL REGISTRO DE ENTRADA Y SALIDA CONJUNTO HABITACIONAL ARMENIA II-----------------\n";
        cout << "MENU\n";
        cout << "1. Ingresar nuevo usuario\n";
        cout << "2. Guardar usuarios en archivo txt\n";
        cout << "3. Mostrar lista de usuarios en archivo txt\n";
        cout << "4. Registrar salida\n";
        cout << "5. Abrir y visualizar archivo\n";
        cout << "6. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer del teclado
        
        switch(opcion) {
            case 1:
                registerUser();
                break;
            case 2:
                cout << "Usuarios ya guardados en archivo.\n";
                break;
            case 3:
                showUsers();
                break;
            case 4:
                registerExit();
                break;
            case 5:
                openFile();
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
        cout << "Presione una tecla para continuar...";
        cin.get();
    } while (opcion != 6);
    
    return 0;
}

