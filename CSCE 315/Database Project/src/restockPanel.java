

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

/**
 *
 * @author Patrick
 */
public class restockPanel extends javax.swing.JPanel {
    // Variables declaration
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JButton noButton;
    private javax.swing.JButton yesButton;
    public static restockTable restockTableDisplay;
    public JTable tableContainer;
    public static JLabel price;
    // End of variables declaration
    /**
     * Creates new form NewJPanel
     */
    public restockPanel() {
        initComponents();
    }

    //initializes all components in jpanel
     void initComponents() {
        jScrollPane1 = new javax.swing.JScrollPane();
        restockTableDisplay = new restockTable();
        jLabel1 = new javax.swing.JLabel();
        yesButton = new javax.swing.JButton();
        noButton = new javax.swing.JButton();
        price = new JLabel("Total: $0.00");
        price.setFont(new Font("Serif", Font.PLAIN,15));
        getRestockData();
        tableContainer = new JTable(restockTableDisplay);
        jScrollPane1.setViewportView(tableContainer);
        jLabel1.setText("Would you like to order these items?");
        yesButton.setBackground(java.awt.Color.green);
        yesButton.setText("Yes");
        //creates action function for yes button
        yesButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                yesButtonActionPerformed(evt);
            }
        });

        noButton.setBackground(java.awt.Color.red);
        noButton.setText("No");
        //creates action function for no button
        noButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                noButtonActionPerformed(evt);
            }
        });

        //formatting things
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.LEADING)
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
                        .addGroup(layout.createSequentialGroup()
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(price, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 100, 100))
                        .addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
                                .addGap(93, 93, 93)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
                                        .addGroup(layout.createSequentialGroup()
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addComponent(yesButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(62, 62, 62)
                                                .addComponent(noButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                        .addComponent(jLabel1))));
        layout.setVerticalGroup(
                layout.createParallelGroup(GroupLayout.Alignment.CENTER)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jLabel1)
                                .addGap(37, 37, 37)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
                                        .addComponent(yesButton)
                                        .addComponent(noButton)
                                        .addComponent(price))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))

        );
    }


    private void yesButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        queryRestock();
        //updates the data in inventory table
        inventoryTable.data = managerInventory.getInventoryItems();
        //updates upon successful restock(code didn't break)
        JOptionPane.showMessageDialog(guiManager.appFrame, "Restock Successful!");
        //switch back to manager tab
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "managerTabs");
    }

    private void noButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        //switch back to manager tab
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "managerTabs");
    }

    /*
    This function gets a list of all items that need to be restocked
     */
    public static void getRestockData(){
         restockTable.restockItems = new ArrayList<restockItem>();
         //get items that have less than the fill level
         String query = "SELECT sku, description,(COALESCE(\"fillLevel\", 0) - quantity) AS Quantity, ((COALESCE(\"fillLevel\", 0) - quantity) * price)" +
                 " AS Price " +
                 "FROM inventory WHERE (COALESCE(\"fillLevel\", 0) - quantity) > 0";
         try{
             //get data
             Statement stmt = jdbc.conn.createStatement();
             ResultSet rs = stmt.executeQuery(query);
             ArrayList<String> results = jdbc.extractData(rs);
             //parse data into table
             for(int i = 0; i < results.size(); ++i){
                 switch(i % restockItem.getNumData()){
                     case 0:
                         restockItem item = new restockItem();
                         item.SKU = results.get(i);
                         restockTable.restockItems.add(item);
                         break;
                     case 1:
                         restockTable.restockItems.get(i/4).description = results.get(i);
                         break;
                     case 2:
                         restockTable.restockItems.get(i/4).quantity = Double.parseDouble(results.get(i));
                         break;
                     case 3:
                         restockTable.restockItems.get(i/4).total = Double.parseDouble(results.get(i));
                         break;
                 }
             }
         }
         catch(Exception e){
             e.printStackTrace();
         }
         //updates total
        double total = 0;
        for(restockItem item : restockTable.restockItems){
            total += item.total;
        }
        price.setText("Total: $" + String.format("%.2f", total));
    }
    //updates data in inventory table
    public void queryRestock(){
        try {
            Statement stmt = jdbc.conn.createStatement();
            for (restockItem item : restockTable.restockItems) {
                String query = "UPDATE inventory " + "SET quantity = COALESCE(\"fillLevel\", 0) WHERE inventory.sku = " + "'" + item.SKU + "'";
                stmt.addBatch(query);
            }
            stmt.executeBatch();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}