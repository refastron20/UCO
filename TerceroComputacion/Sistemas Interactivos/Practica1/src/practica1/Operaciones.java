<<<<<<< HEAD
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;

/**
 *
 * @author rhorm
 */
public class Operaciones {
    public static int factorial(int entrada){
        int factorial = 1;
        int copiaEntrada = entrada;
        while(copiaEntrada>0){
            factorial*=copiaEntrada;
            copiaEntrada--;
        }
        return factorial;
    }
}
=======
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package MyPackage;

/**
 *
 * @author rhorm
 */
public class Operaciones {
    public static int factorial(int entrada){
        int factorial = 1;
        int copiaEntrada = entrada;
        while(copiaEntrada>0){
            factorial*=copiaEntrada;
            copiaEntrada--;
        }
        return factorial;
    }
}
>>>>>>> ebb036f4183f06208a67d15ddc5b7d57c069a526
