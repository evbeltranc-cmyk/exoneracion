#include <iostream>
using namespace std;

// Funcion externa 
// usa puntero * para modificar el saldo
void aplicarCargo(double *saldo) {
    // aqui accedo al valor usando el puntero
    *saldo -= 5; // resto 5 dolares al saldo
}

// aqui entramos a la clase principal
class Billetera {

private:
    // datos del usuario
    
    string propietario; // nombre del dueño
    double saldo; // dinero disponible

    // array para guardar historial de gastos (maximo 20)
    double gastos[20];

    // contador de cuantos gastos se han registrado
    int cantidadGastos;

public:

    // --------------------------------------------------
    // CONSTRUCTOR (se ejecuta al crear el objeto)
    // --------------------------------------------------
    Billetera(string nombre, double saldoInicial) {
        propietario = nombre; // guardo nombre
        saldo = saldoInicial; // guardo saldo inicial

        // inicializo contador en 0 porque no hay gastos aun
        cantidadGastos = 0;
    }

    // --------------------------------------------------
    // METODO PARA AGREGAR INGRESO
    // --------------------------------------------------
    void agregarIngreso(double monto) {

        // valido que no sea negativo o cero
        if (monto <= 0) {
            cout << "Error: monto invalido" << endl;
            return; // salgo del metodo
        }

        // sumo el dinero al saldo
        saldo += monto;
    }

    // --------------------------------------------------
    // METODO PARA REGISTRAR GASTO
    // usa referencia (&)
    // --------------------------------------------------
    void registrarGasto(double monto, int &contadorSesion) {

        // valido monto negativo
        if (monto <= 0) {
            cout << "Error: monto invalido" << endl;
            return;
        }

        // valido que haya suficiente saldo
        if (monto > saldo) {
            cout << "Error: saldo insuficiente" << endl;
            return;
        }

        // valido que no se pase del limite del array
        if (cantidadGastos >= 20) {
            cout << "Error: limite de gastos alcanzado" << endl;
            return;
        }

        // descuento el gasto del saldo
        saldo -= monto;

        // guardo el gasto en el array
        gastos[cantidadGastos] = monto;

        // aumento contador interno
        cantidadGastos++;

        // aumento contador externo (REFERENCIA)
        // esto modifica la variable del main directamente
        contadorSesion++;

        cout << "Gasto registrado. Saldo: $" << saldo << endl;
    }

    // --------------------------------------------------
    // METODO QUE RETORNA UN VALOR (promedio)
    // --------------------------------------------------
    double calcularPromedio() {

        // si no hay gastos retorno 0
        if (cantidadGastos == 0) return 0;

        double suma = 0;

        // recorro el array y sumo todos los gastos
        for (int i = 0; i < cantidadGastos; i++) {
            suma += gastos[i];
        }

        // retorno el promedio
        return suma / cantidadGastos;
    }

    // --------------------------------------------------
    // METODO QUE RETORNA UN PUNTERO
    // --------------------------------------------------
    double* obtenerSaldo() {

        // retorno la direccion de memoria del saldo
        return &saldo;
    }

    // --------------------------------------------------
    // MOSTRAR HISTORIAL
    // --------------------------------------------------
    void verHistorial() {

        cout << "=== HISTORIAL ===" << endl;

        // recorro el array
        for (int i = 0; i < cantidadGastos; i++) {
            cout << "Gasto " << i + 1 << ": $" << gastos[i] << endl;
        }
    }

    // --------------------------------------------------
    // MOSTRAR ESTADO DEL USUARIO
    // --------------------------------------------------
    void verEstado() {

        cout << "Propietario: " << propietario << endl;
        cout << "Saldo: $" << saldo << endl;
        cout << "Gastos: " << cantidadGastos << endl;
    }
};

// ------------------------------------------------------
// FUNCION PRINCIPAL
// ------------------------------------------------------
int main() {

    string nombre;
    double saldoInicial;

    // pido datos al usuario
    cout << "Propietario: ";
    cin >> nombre;

    cout << "Saldo inicial: ";
    cin >> saldoInicial;

    // creo objeto de la clase
    Billetera b(nombre, saldoInicial);

    int opcion;

    // variable para contar gastos en esta sesion
    int gastosSesion = 0;

    // menu con while (requisito del examen)
    do {

        cout << "\n=== MENU ===" << endl;
        cout << "1. Agregar ingreso" << endl;
        cout << "2. Registrar gasto" << endl;
        cout << "3. Ver historial" << endl;
        cout << "4. Ver estado" << endl;
        cout << "5. Ver promedio" << endl;
        cout << "6. Aplicar cargo" << endl;
        cout << "7. Salir" << endl;

        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            double monto;
            cout << "Monto: ";
            cin >> monto;

            b.agregarIngreso(monto);
        }

        else if (opcion == 2) {
            double monto;
            cout << "Monto: ";
            cin >> monto;

            // envio variable por referencia
            b.registrarGasto(monto, gastosSesion);
        }

        else if (opcion == 3) {
            b.verHistorial();
        }

        else if (opcion == 4) {
            b.verEstado();
        }

        else if (opcion == 5) {
            cout << "Promedio: $" << b.calcularPromedio() << endl;
        }

        else if (opcion == 6) {

            // uso funcion externa con puntero
            aplicarCargo(b.obtenerSaldo());

            cout << "Cargo aplicado. Nuevo saldo: $" 
                 << *b.obtenerSaldo() << endl;
        }

    } while (opcion != 7);

    // mensaje final usando referencia
    cout << "Sesion terminada. Gastos registrados: " 
         << gastosSesion << endl;

    return 0;
}