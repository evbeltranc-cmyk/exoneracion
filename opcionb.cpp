#include <iostream>
using namespace std;

// Funcion externa que usa puntero * para modificar saldo

void aplicarCargo(double *saldo) { //inicio 
    *saldo -=5: // resta 5 dolares
}

//Clase principal- tipo de objeto 

class Billetera {

    //datos de ella 

// estructura de una clase 

    private:
    string propietario;
    double saldo;
    double gastos[20];       // array para historial

    int cantidadGastos;


    public:
    
    // Constructor con parámetros

    //llamo al tipo de objeto 

    Billetera(string nombre, double saldoInicial) {
        propietario = nombre; //
        saldo = saldoInicial;  //
        cantidadGastos = 0;  //
    }

// Clase principal

    // Metodo para agregar ingreso

    void agregarIngreso(double monto) {
        if (monto <= 0) {
            cout << "error, monto invalido" << endl;
            return;
        }
        saldo += monto;
    }



 // Método con referencia & para poder modificar la variable del main, no se trabaja con la copia sino se modifica la original 

    void registrarGasto(double monto, int &contadorSesion) {

        //son mis condiciones para poder entar al registro de gasto 

        if (monto <= 0) { // si es menor a 0
            cout << "error, monto invalido" << endl;
            return;
        }


        if (monto > saldo) { //si es monto es mayor al saldo 
            cout << "error, saldo insuficiente" << endl;
            return;
        }

        if (cantidadGastos >= 20) { //si la cantidad de gastos es mayor o igual a 20 ya que es es el maximo de gastos que pueden consumir 
            cout << "error, limite de gastos alcanzado" << endl;
            return;
        }

        //si cumple las condiciones 

        saldo -= monto;
        gastos[cantidadGastos] = monto;

        cantidadGastos++;
           // aumento el contador de gastos en la sesion.
        contadorSesion++; // con esto modificamos variable externa
     
//imprimo el gasto registrado 
        cout << "Gasto registrado. Saldo: " << saldo << endl;

    }

  // Método que retorna valor - calcular el promedio

    double calcularPromedio() {

        if (cantidadGastos == 0) return 0;

        double suma = 0;
        for (int i = 0; i < cantidadGastos; i++) {
            suma += gastos[i];
        }
        return suma / cantidadGastos;
    }
 // metodo para retornar puntero 
    double* obtenerSaldo() {
    
        return &saldo;

    }

// necesito mostar el historial 

void verhistorial () {
    cout <<"=== HISTORIAL ==="<< endl;
    for (int i = 0; i < cantidadGastos; i++) {
            cout << "Gasto " << i + 1 << ": $" << gastos[i] << endl; //aqui imprimira los gastos como en el taller gasto 1 y gasto 2 
        }
}


// Mostrar estado
    void verEstado() {
        cout << "Propietario: " << propietario << endl;
        cout << "Saldo: $" << saldo << endl;
        cout << "Gastos: " << cantidadGastos << endl;
    }
};


//empezar todo 

int main() {

    string nombre;
    double saldoInicial;

    //imprime el nombre del propietario 

    cout << "Propietario: ";
    cin >> nombre;
//he imprime el saldo que tiene incial 

    cout << "Saldo inicial: ";
    cin >> saldoInicial;

//guardas mis datos ingresados en mi billetera digital 

    Billetera b(nombre, saldoInicial);

    int opcion;
    int gastosSesion = 0; // variable para referencia 




//usames el ejemplo de ejecucion usando el ejemplo de la guia,mostrando cada 
    do { cout << "=== MENU ===" << endl;
        cout << "1. Agregar ingreso" << endl;
        cout << "2. Registrar gasto" << endl;
        cout << "3. Ver historial" << endl;
        cout << "4. Ver estado" << endl;
        cout << "5. Ver promedio" << endl;
        cout << "6. Aplicar cargo" << endl;
        cout << "7. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        //aqui entra la opcion
      

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
            aplicarCargo(b.obtenerSaldo()); // usamos puntero
            cout << "Cargo aplicado. Nuevo saldo: $" << *b.obtenerSaldo() << endl;
        }

    } while (opcion != 7);

    cout << "Sesion terminada. Gastos registrados: " << gastosSesion << endl;

    return 0;
}














