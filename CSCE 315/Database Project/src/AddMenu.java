import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;

/**
 * This class contains all methods for server window
 */
public class AddMenu extends javax.swing.JPanel {
    // Variables declaration

    private javax.swing.JButton backButton;
    private javax.swing.JButton conversionButton;
    private javax.swing.JTextField conversionsConversionFactor;
    private javax.swing.JTextField conversionsDescription;
    private javax.swing.JTextField conversionsItemID;
    private javax.swing.JTextField conversionsSKU;
    private javax.swing.JTextField conversionsUnits;
    private javax.swing.JButton decompButton;
    private javax.swing.JTextField decompItemID;
    private javax.swing.JTextField decompItemName;
    private javax.swing.JTextField decompMenuID;
    private javax.swing.JTextField decompQuantity;
    private javax.swing.JTextField decompUnits;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JButton popupTables;

    /**
     * Creates new form AddMenu
     */
    public AddMenu() {
        initComponents();
    }
    //initialize components of window
    private void initComponents() {

        popupTables = new javax.swing.JButton();
        decompMenuID = new javax.swing.JTextField();
        decompItemID = new javax.swing.JTextField();
        decompQuantity = new javax.swing.JTextField();
        decompUnits = new javax.swing.JTextField();
        decompItemName = new javax.swing.JTextField();
        conversionsItemID = new javax.swing.JTextField();
        conversionsSKU = new javax.swing.JTextField();
        conversionsConversionFactor = new javax.swing.JTextField();
        decompButton = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        jLabel6 = new javax.swing.JLabel();
        jLabel7 = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        conversionsDescription = new javax.swing.JTextField();
        jLabel9 = new javax.swing.JLabel();
        conversionsUnits = new javax.swing.JTextField();
        jLabel10 = new javax.swing.JLabel();
        conversionButton = new javax.swing.JButton();
        backButton = new javax.swing.JButton();

        // Add action listers to each button

        backButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                backButtonActionPerformed(evt);
            }
        });

        popupTables.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                popupTablesActionPerformed(evt);
            }
        });

        decompButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                decompButtonActionPerformed(evt, decompMenuID.getText(), decompItemID.getText(), decompQuantity.getText(), decompUnits.getText(), decompItemName.getText());
            }
        });

        conversionButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                conversionButtonActionPerformed(evt, conversionsItemID.getText(), conversionsSKU.getText(), conversionsConversionFactor.getText(), conversionsDescription.getText(), conversionsUnits.getText());
            }
        });

        popupTables.setText("See tables");
        backButton.setText("Back");

        // decompMenuID.setText("menuID");
        // decompItemID.setText("itemID");
        // decompQuantity.setText("quantity");
        // decompUnits.setText("units");
        // decompItemName.setText("itemName");
        decompButton.setText("Add pieces of order");

        jLabel1.setText("menuID");
        jLabel2.setText("itemID");
        jLabel3.setText("quantity");
        jLabel4.setText("units");
        jLabel5.setText("itemName");
        jLabel6.setText("itemID");
        jLabel7.setText("SKU");
        jLabel8.setText("conversionFactor");
        jLabel9.setText("description");
        jLabel10.setText("units");

        // conversionsItemID.setText("itemID");
        // conversionsSKU.setText("sku");
        // conversionsConversionFactor.setText("conversionFactor");
        // conversionsDescription.setText("description");
        // conversionsUnits.setText("units");

        conversionButton.setText("Add ingredient conversions");


        //UI formatting
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);

        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(decompMenuID, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel1))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(decompItemID, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel2))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(decompQuantity, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel3))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(decompUnits, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel4))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(decompItemName, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(45, 45, 45)
                                        .addComponent(decompButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                    .addComponent(jLabel5)))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(conversionsItemID, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel6))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(conversionsSKU, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel7))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(conversionsConversionFactor, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel8))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(conversionsDescription, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(jLabel9))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(jLabel10)
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(conversionsUnits, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(18, 18, 18)
                                        .addComponent(conversionButton)))))
                        .addGap(0, 9, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(backButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(popupTables)
                        .addContainerGap())))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGap(12, 12, 12)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(jLabel2)
                    .addComponent(jLabel3)
                    .addComponent(jLabel4)
                    .addComponent(jLabel5))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(decompMenuID, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(decompItemID, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(decompQuantity, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(decompUnits, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(decompItemName, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(decompButton))
                .addGap(36, 36, 36)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel6)
                    .addComponent(jLabel7)
                    .addComponent(jLabel8)
                    .addComponent(jLabel9)
                    .addComponent(jLabel10))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(conversionsItemID, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(conversionsSKU, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(conversionsConversionFactor, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(conversionsDescription, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(conversionsUnits, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(conversionButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 47, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(backButton)
                    .addComponent(popupTables))
                .addGap(36, 36, 36))
        );
    }


    // goes back to manager menu
    private void backButtonActionPerformed(java.awt.event.ActionEvent evt) {
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "managerTabs");
    }

    // creates popup tables for convenience
    private void popupTablesActionPerformed(java.awt.event.ActionEvent evt) {
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "popupTable");
    }

    // when decompButton is pushed
    private void decompButtonActionPerformed(java.awt.event.ActionEvent evt, String menuID, String itemID, String quantity, String units, String itemName) {
        try {
            Statement stmt = jdbc.conn.createStatement();
            String sqlStatement = "INSERT INTO orderdecomposition VALUES (" + menuID + "," + itemID + "," + quantity + ",\'" + units + "\',\'" + itemName + "\');";
            stmt.execute(sqlStatement);
            JOptionPane.showMessageDialog(guiManager.appFrame, "New meal ingredient " + itemName + " successfully added to menuItem " + menuID + "!");
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(guiManager.appFrame, "New meal ingredient " + itemName + " could not be added to menuItem " + menuID + "!");
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }
    }

    // when conversionButton is pushed
    private void conversionButtonActionPerformed(java.awt.event.ActionEvent evt, String itemID, String sku, String conversionFactor, String description, String units) {
        try {
            Statement stmt = jdbc.conn.createStatement();
            String sqlStatement = "INSERT INTO conversions VALUES (" + itemID + ",\'" + sku + "\'," + Float.parseFloat(conversionFactor) + ",\'" + description + "\',\'" + units + "\');";
            stmt.execute(sqlStatement);
            JOptionPane.showMessageDialog(guiManager.appFrame, "New conversion containing " + description + " successfully created!");
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(guiManager.appFrame, "New conversion containing " + description + " could not be created.");
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }
    }

}
