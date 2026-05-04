#include <iostream>
using namespace std; 


// uso puntero * para modificar el saldo
void aplicarCargo(double *saldo) {
    // aqui uso el puntero donde el * sirve para acceder al valor real donde  no es copia, es el valor original
    *saldo = *saldo - 5; // resto 5 al saldo
}

//aqui creo la clase, la billetera virtual

class Billetera {

private:

    // variable de datos : private significa que no se pueden usar desde afuera
    string propietario; // nombre del usuario
    double saldo; // dinero disponible

    // array para guardar gastos
    // maximo 20 posiciones
    double gastos[20];

    int cantidadGastos; // cuantos gastos llevo

public:
// constructor, se ejecuta cuando creo el objeto
    Billetera(string nombre, double saldoInicial) {

        // guardo el nombre
        propietario = nombre;

        // guardo el saldo inicial
        saldo = saldoInicial;

        // inicio en 0 porque aun no hay gastos
        cantidadGastos = 0;
    }

    //agregar ingreso

    void agregarIngreso(double monto) {

        // valido que no sea negativo
        if (monto <= 0) {
            cout << "Error, monto invalido" << endl;
            return; // salgo del metodo
        }

        // sumo al saldo
        saldo = saldo + monto;
    }
    // registro gasto y uso referencia 

    void registrarGasto(double monto, int &contadorSesion) {

//las validaciones 

        // no permitir negativos
        if (monto <= 0) {
            cout << "Error, monto invalido" << endl;
            return;
        }

        // verificar saldo suficiente
        if (monto > saldo) {
            cout << "Error, saldo insuficiente" << endl;
            return;
        }

        // verificar limite del array
        if (cantidadGastos >= 20) {
            cout << "Error, limite alcanzado" << endl;
            return;
        }

      //aqui esta el proceso

        // descuento el saldo
        saldo = saldo - monto;

        // guardo el gasto en el array
        gastos[cantidadGastos] = monto;

        // aumento el contador interno
        cantidadGastos = cantidadGastos + 1;

        // uso referencia y me modifica la variable del main directamente
        contadorSesion = contadorSesion + 1;

        cout << "Gasto registrado. Saldo: $" << saldo << endl;
    }
    // calcular promedio y retorna un valor (requisito)
  
    double calcularPromedio() {

        // si no hay gastos
        if (cantidadGastos == 0) {
            return 0;
        }

        double suma = 0;

        // recorro el array
        for (int i = 0; i < cantidadGastos; i++) {

            // voy sumando
            suma = suma + gastos[i];
        }

        // calculo promedio
        double promedio = suma / cantidadGastos;

        return promedio;
    }

 //retorno al puntero

    double* obtenerSaldo() {

        // devuelvo la direccion de memoria
        return &saldo;
    }

//muestro la historia
    void verHistorial() {

        cout << "=== HISTORIAL ===" << endl;

        // recorro el array
        for (int i = 0; i < cantidadGastos; i++) {

            cout << "Gasto " << i + 1 << ": $" << gastos[i] << endl;
        }
    }

//muestra estado
    void verEstado() {

        cout << "Propietario: " << propietario << endl;
        cout << "Saldo: $" << saldo << endl;
        cout << "Gastos: " << cantidadGastos << endl;
    }
};

//main empieza el programa 
int main() {

    string nombre;
    double saldoInicial;

    // pido datos al usuario
    cout << "Propietario: ";
    cin >> nombre;

    cout << "Saldo inicial: ";
    cin >> saldoInicial;

    // creo el objeto usando el constructor
    Billetera miBilletera(nombre, saldoInicial);

    int opcion;

    // contador de la sesion, para referencias 
    int gastosSesion = 0;

    // menu con while 
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

            miBilletera.agregarIngreso(monto);
        }

        else if (opcion == 2) {

            double monto;
            cout << "Monto: ";
            cin >> monto;

            // envio la variable por referencia
            miBilletera.registrarGasto(monto, gastosSesion);
        }

        else if (opcion == 3) {

            miBilletera.verHistorial();
        }

        else if (opcion == 4) {

            miBilletera.verEstado();
        }

        else if (opcion == 5) {

            cout << "Promedio: $" 
                 << miBilletera.calcularPromedio() << endl;
        }

        else if (opcion == 6) {

            // uso funcion externa con puntero
            aplicarCargo(miBilletera.obtenerSaldo());

            cout << "Cargo aplicado. Nuevo saldo: $" 
                 << *miBilletera.obtenerSaldo() << endl;
        }

    } while (opcion != 7);

    // mensaje final
    cout << "Sesion terminada. Gastos registrados: " 
         << gastosSesion << endl;

    return 0;
}