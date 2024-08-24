#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <regex>
#include <fstream>
#include <cstdlib> // Para usar system()

using namespace std;

struct Usuario {
    string nombreCompleto;
    string numeroCasa;
    string numeroCedula;
    string horaEntrada;
    string horaSalida;
    string placaVehicular;
    string tipoUsuario; // "Residente" o "Visita"
    string casaVisita;  // Para visitas, la casa que están visitando
};

vector<Usuario> usuarios;

string obtenerHoraActual() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ostringstream oss;
    oss << setw(2) << setfill('0') << ltm->tm_hour << ":"
        << setw(2) << setfill('0') << ltm->tm_min << ":"
        << setw(2) << setfill('0') << ltm->tm_sec;
    return oss.str();
}

bool validarCedula(const string &cedula) {
    regex cedulaRegex("\\d{10}");
    return regex_match(cedula, cedulaRegex);
}

// Función para guardar usuarios en un archivo de texto
void guardarUsuariosEnArchivo() {
    ofstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escribir.\n";
        return;
    }

    for (const auto &usuario : usuarios) {
        archivo << "Nombre: " << usuario.nombreCompleto << "\n"
                << "Numero de casa: " << usuario.numeroCasa << "\n"
                << "Numero de cedula: " << usuario.numeroCedula << "\n"
                << "Hora de entrada: " << usuario.horaEntrada << "\n"
                << "Hora de salida: " << usuario.horaSalida << "\n"
                << "Placa vehicular: " << usuario.placaVehicular << "\n"
                << "Tipo de usuario: " << usuario.tipoUsuario << "\n"
                << "-----------------------------------------\n";
    }
    archivo.close();
}

void agregarUsuario() {
    Usuario nuevoUsuario;
    cout << "Ingrese numero de cedula (10 digitos): ";
    getline(cin, nuevoUsuario.numeroCedula);
    
    if (!validarCedula(nuevoUsuario.numeroCedula)) {
        cout << "Cedula invalida. Debe contener exactamente 10 digitos.\n";
        return;
    }

    cout << "Ingrese nombre completo: ";
    getline(cin, nuevoUsuario.nombreCompleto);
    cout << "Es residente o visita? (r/v): ";
    char tipoUsuario;
    cin >> tipoUsuario;
    cin.ignore(); 

    if (tipoUsuario == 'r' || tipoUsuario == 'R') {
        nuevoUsuario.tipoUsuario = "Residente";
        cout << "Ingrese numero de casa: ";
        getline(cin, nuevoUsuario.numeroCasa);
        
        
        
    } else if (tipoUsuario == 'v' || tipoUsuario == 'V') {
        nuevoUsuario.tipoUsuario = "Visita";
        cout << "Ingrese numero de casa: ";
        getline(cin, nuevoUsuario.numeroCasa);
        

    } else {
        cout << "Tipo de usuario invalido.\n";
        return;
    }

    cout << "Tiene vehiculo? (s/n): ";
    char tieneVehiculo;
    cin >> tieneVehiculo;
    cin.ignore(); // Ignorar el salto de línea pendiente

    if (tieneVehiculo == 's' || tieneVehiculo == 'S') {
        cout << "Ingrese placa vehicular: ";
        getline(cin, nuevoUsuario.placaVehicular);
    } else {
        nuevoUsuario.placaVehicular = "N/A";
    }
	
    if (tipoUsuario == 'r' || tipoUsuario == 'R') {
        nuevoUsuario.horaSalida = obtenerHoraActual();
        nuevoUsuario.horaEntrada = "N/A";
        cout << "Usuario agregado exitosamente. Hora de Salida: " << nuevoUsuario.horaSalida << "\n";
    } else if (tipoUsuario == 'v' || tipoUsuario == 'V') {
        nuevoUsuario.horaEntrada = obtenerHoraActual();
        nuevoUsuario.horaSalida = "N/A";
        cout << "Usuario agregado exitosamente. Hora de entrada: " << nuevoUsuario.horaEntrada << "\n";
    }
    
    usuarios.push_back(nuevoUsuario);
    guardarUsuariosEnArchivo(); // Guardar en el archivo cada vez que se agrega un nuevo usuario
}

void registrarSalida() {
    string numeroCedula;
    cout << "Ingrese numero de cedula del usuario que sale: ";
    getline(cin, numeroCedula);

    for (auto &usuario : usuarios) {
        if (usuario.numeroCedula == numeroCedula && usuario.horaSalida == "N/A") {
            usuario.horaSalida = obtenerHoraActual();
            guardarUsuariosEnArchivo(); // Guardar en el archivo cada vez que se registra una salida
            cout << "Salida registrada exitosamente. Hora de salida: " << usuario.horaSalida << "\n";
            return;
        }
    }
    cout << "Usuario no encontrado o ya tiene registrada la salida.\n";
}

void registrarEntrada() {
    string numeroCedula;
    cout << "Ingrese numero de cedula del usuario que entra: ";
    getline(cin, numeroCedula);

    for (auto &usuario : usuarios) {
        if (usuario.numeroCedula == numeroCedula && usuario.horaEntrada == "N/A") {
            usuario.horaEntrada = obtenerHoraActual();
            guardarUsuariosEnArchivo(); // Guardar en el archivo cada vez que se registra una salida
            cout << "Ingreso registrado exitosamente. Hora de Entrada: " << usuario.horaEntrada << "\n";
            return;
        }
    }
    cout << "Usuario no encontrado o ya tiene registrada la salida.\n";
}

void mostrarUsuarios() {
    guardarUsuariosEnArchivo(); // Asegúrate de guardar los usuarios en el archivo antes de abrirlo
    system("notepad usuarios.txt"); // Abre el archivo en el bloc de notas
}

int main() {
    int opcion;

    do {
        cout << "\nSistema de Registro de Usuarios del Conjunto Habitacional Armenia II\n";
        cout << "1. Agregar nuevo usuario\n";
        cout << "2. Registrar salida de usuario\n";
        cout << "3. Registrar entrada de usuario\n";
        cout << "4. Mostrar usuarios registrados\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                agregarUsuario();
                break;
            case 2:
                registrarSalida();
                break;
            case 3: 
                registrarEntrada();
                break;
            case 4:
                mostrarUsuarios();
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}


	