<<<<<<< HEAD
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;
import java.util.Scanner;

/**
 *
 * @author rhorm
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int a;
        System.out.println("Inserte un número");
        a = reader.nextInt();
        int b = Operaciones.factorial(a);
        System.out.println(b);
        Profesor p= new Profesor();
        p.setNombre("Enrique");
        p.setApellidos("García Salcines");
        p.setEdad(40);
        p.setUniversidad("UCO");
        p.setId_profesor(1);
        System.out.println("El profesor "+p.getNombre()+" "+p.getApellidos()+" con edad "+p.getEdad()+
        " trabaja en la universidad "+p.getUniversidad()+" y tiene un id de profesor "+p.getId_profesor());
    }
    
}
=======
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica1;

import static MyPackage.Operaciones.factorial;
import java.util.Scanner;

/**
 *
 * @author rhorm
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int a;
        System.out.println("Inserte un número");
        a = reader.nextInt();
        int b = factorial(a);
        System.out.println(b);
        Profesor p= new Profesor();
        p.setNombre("Enrique");
        p.setApellidos("García Salcines");
        p.setEdad(40);
        p.setUniversidad("UCO");
        p.setId_profesor(1);
        System.out.println("El profesor "+p.getNombre()+" "+p.getApellidos()+" con edad "+p.getEdad()+
        " trabaja en la universidad "+p.getUniversidad()+" y tiene un id de profesor "+p.getId_profesor());
    }
    
}
>>>>>>> ebb036f4183f06208a67d15ddc5b7d57c069a526
