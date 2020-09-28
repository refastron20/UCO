/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package examples;

import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import javax.swing.*;

/**
 *
 * @author salcines
 */
public class MiVentana1 extends JFrame {
    
    public MiVentana1() {
        super("Añadir usuario");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Panel de fecha
        JPanel panelFecha = new JPanel();
        panelFecha.setLayout(new FlowLayout());
        panelFecha.add(new JTextField(2));
        panelFecha.add(new JLabel("/"));
        panelFecha.add(new JTextField(2));
        panelFecha.add(new JLabel("/"));
        panelFecha.add(new JTextField(2));

        // Panel de datos
        JPanel panelDatos = new JPanel();
        GridLayout gl = new GridLayout(3,2,0,5);
        panelDatos.setLayout(gl);
        panelDatos.add(new JLabel("Nombre:"));
        panelDatos.add(new JTextField(10));
        panelDatos.add(new JLabel("DNI:"));
        panelDatos.add(new JTextField(10));
        panelDatos.add(new JLabel("Fecha de nacimiento: "));
        panelDatos.add(panelFecha);

        // Panel de botones
        JPanel panelBotones = new JPanel(); 
        panelBotones.setLayout(new FlowLayout()); 
        panelBotones.add(new JButton("Aceptar")); 
        panelBotones.add(new JButton("Cancelar"));
        
        Container cp = getContentPane(); 
        cp.add(panelDatos, BorderLayout.CENTER); 
        cp.add(panelBotones, BorderLayout.SOUTH);
    }
    
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            javax.swing.UIManager.LookAndFeelInfo[] installedLookAndFeels=javax.swing.UIManager.getInstalledLookAndFeels();
            for (int idx=0; idx<installedLookAndFeels.length; idx++)
                if ("Nimbus".equals(installedLookAndFeels[idx].getName())) {
                    javax.swing.UIManager.setLookAndFeel(installedLookAndFeels[idx].getClassName());
                    break;
                }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Antenna.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Antenna.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Antenna.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Antenna.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        MiVentana1 v = new MiVentana1();
        v.setSize(300, 200); 
        v.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        v.setVisible(true);
        v.setLocationRelativeTo(null);
    }
    
}
