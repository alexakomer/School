import javax.swing.*;
import java.awt.*;

public class startMenu extends javax.swing.JPanel {

    /**
     * Creates new form startMenu
     */
    public startMenu() {
        initComponents();
    }


    private void initComponents() {
        //gets button layout for start menu
        managerButton = new javax.swing.JButton();
        serverButton = new javax.swing.JButton();

        managerButton.setText("manager");
        managerButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                managerButtonActionPerformed(evt);
            }
        });

        serverButton.setText("server");
        serverButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                serverButtonActionPerformed(evt);
            }
        });
        GridBagLayout layout = new GridBagLayout();
        this.setLayout(layout);
        serverButton.setPreferredSize(new Dimension(400, 200));
        managerButton.setPreferredSize(new Dimension(400, 200));
        this.setLayout(layout);
        this.add(serverButton);
        this.add(Box.createRigidArea(new Dimension(300, 0)));
        this.add(managerButton);

    }
    //switches card to server menu
    private void serverButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "serverMenu");
    }
    //switches card to manager menu
    private void managerButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "managerTabs");

    }


    // Variables declaration
    private javax.swing.JButton managerButton;
    private javax.swing.JButton serverButton;
    // End of variables declaration
}
