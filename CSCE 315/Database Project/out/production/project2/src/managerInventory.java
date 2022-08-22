import javax.swing.*;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.AbstractTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;

public class managerInventory extends javax.swing.JPanel {
    // Variables declaration
    private javax.swing.JTextField addSKU;
    private javax.swing.JTextField addQuantity;
    private javax.swing.JTextField addContainer;
    private javax.swing.JTextField addPrice;
    private javax.swing.JTextField addState;
    private javax.swing.JTextField addDescription;
    private javax.swing.JTextField addItemName;
    private javax.swing.JTextField addType;
    private javax.swing.JTextField addUnit;
    private javax.swing.JTextField addTotalPrice;
    private javax.swing.JTextField addFillLevel;

    private java.awt.Button addButton;
    private java.awt.Button removeButton;
    private Button restockButton = new Button();
    private javax.swing.JButton backButton;
    private javax.swing.JScrollPane jScrollPane1;
    public static javax.swing.JTable inventory;
    private java.awt.Button submitButton;
    public ArrayList<ArrayList<Object>> inventoryItems = new ArrayList<>();
    public inventoryTable tableFormat;
    public static ArrayList<change> changeList = new ArrayList<change>();
    // End of variables declaration

    /**
     * Creates new form managerInventory
     */
    public managerInventory() {
        initComponents();
    }

    //initialize components of window
    private void initComponents() {

        //fetch new inventory items if necessary
        if(inventoryItems.isEmpty()){
            inventoryItems = getInventoryItems();
        }
//        //sort menu items by ID
//        inventoryItems.sort(new Comparator<ArrayList<Object>>() {
//            @Override
//            public int compare(ArrayList<Object> o1, ArrayList<Object> o2) {
//                return Integer.compare(Integer.parseInt((String) o1.get(0)), Integer.parseInt((String) o2.get(0)));
//            }
//        });
        //create UI
        addSKU = new javax.swing.JTextField();
        addQuantity = new javax.swing.JTextField();
        addContainer = new javax.swing.JTextField();
        addPrice = new javax.swing.JTextField();
        addState = new javax.swing.JTextField();
        addDescription = new javax.swing.JTextField();
        addItemName = new javax.swing.JTextField();
        addType = new javax.swing.JTextField();
        addUnit = new javax.swing.JTextField();
        addTotalPrice = new javax.swing.JTextField();
        addFillLevel = new javax.swing.JTextField();

        addButton = new java.awt.Button();
        addButton.setActionCommand("addItem");
        addButton.setBackground(java.awt.Color.green);
        addButton.setLabel("Add");
        addButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addButtonActionPerformed(evt, addSKU.getText(), addQuantity.getText(), addContainer.getText(),
                        addPrice.getText(), addState.getText(), addDescription.getText(), addItemName.getText(),
                        addType.getText(), addUnit.getText(), addTotalPrice.getText(), addFillLevel.getText());
            }
        });

        removeButton = new java.awt.Button();
        removeButton.setActionCommand("removeItem");
        removeButton.setBackground(java.awt.Color.red);
        removeButton.setLabel("Remove");
        removeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                removeButtonActionPerformed(evt);
            }
        });

        jScrollPane1 = new javax.swing.JScrollPane();
        submitButton = new java.awt.Button();
        backButton = new javax.swing.JButton();
        inventoryTable.data = inventoryItems;
        tableFormat = new inventoryTable();
        inventory = new javax.swing.JTable(tableFormat);
        jScrollPane1.setViewportView(inventory);
        submitButton.setActionCommand("submitChanges");
        submitButton.setBackground(java.awt.Color.green);
        submitButton.setLabel("Submit");
        restockButton.setLabel("Restock");
        restockButton.setBackground(Color.CYAN);
        submitButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                submitButtonActionPerformed(evt);
            }
        });
        restockButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                restockButtonActionPerformed(evt);
            }
        });
        backButton.setActionCommand("backToMenu");
        backButton.setBackground(java.awt.Color.red);
        backButton.setLabel("Back");
        backButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                backButtonActionPerformed(evt);
            }
        });
        //UI formatting
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 427, Short.MAX_VALUE)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(addSKU, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addQuantity, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addContainer, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addPrice, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addState, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addDescription, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addItemName, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addType, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addUnit, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addTotalPrice, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE)
                                .addComponent(addFillLevel, javax.swing.GroupLayout.DEFAULT_SIZE, 100, Short.MAX_VALUE))
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(removeButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(addButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(submitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGroup(layout.createSequentialGroup()
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(restockButton, GroupLayout.PREFERRED_SIZE, 200, 200)
                                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))

        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 266, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(addSKU, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addQuantity, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addContainer, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addPrice, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addState, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addDescription, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addItemName, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addType, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addUnit, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addTotalPrice, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addFillLevel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(removeButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(submitButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(addButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(60, 60, 60)
                                .addGroup(layout.createParallelGroup(GroupLayout.Alignment.CENTER)
                                        .addComponent(restockButton, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)))
        );
    }

    //gets inventory from DB
    public static ArrayList<ArrayList<Object>> getInventoryItems(){
        ArrayList<ArrayList<Object>> returnMap = new ArrayList<>();
        ArrayList<String> sqlValues;
        String query = "SELECT * FROM inventory";
        try{
            //get inventory data and put in hash map
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
            for(int i = 0; i < sqlValues.size(); ++i){
                if(i % 11 == 0){
                    returnMap.add(new ArrayList<>());
                }
                returnMap.get(returnMap.size()-1).add(sqlValues.get(i));
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return returnMap;
    }

    //submit button is pushed
    private void submitButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        if(!changeList.isEmpty()){
            for(change c : changeList){
                commitChange(c);
            }
            //show pop up message
            JOptionPane.showMessageDialog(guiManager.appFrame, "Changes successfully submitted.");
        }
        changeList.clear();
    }
    //Goes to start menu
    private void backButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "startMenu");
    }
    public void restockButtonActionPerformed(ActionEvent evt){
        //get new data from server if user modified
        restockPanel.getRestockData();
        //remake table
        restockPanel.restockTableDisplay.fireTableDataChanged();
        //switch card layout
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "restockPanel");
    }
    //add button is pushed
    private void addButtonActionPerformed(java.awt.event.ActionEvent evt, String sku, String quantity, String container,
                                          String price, String state, String description, String itemName, String type,
                                          String unit, String totalPrice, String fillLevel){
//        System.out.println("Add button pressed");
        String query;
        try{
            Statement stmt = jdbc.conn.createStatement();
            query = "INSERT INTO inventory VALUES ('" + sku + "','" + quantity + "','" + container + "','" + price + "','" + state + "','" + description + "','" + itemName + "','" + type + "','" + unit + "','" + totalPrice + "');";
            stmt.execute(query);
            inventoryItems.clear();
            inventoryItems = getInventoryItems();
            inventoryTable.data.clear();
            inventoryTable.data = inventoryItems;
            //show pop up message
            JOptionPane.showMessageDialog(guiManager.appFrame, "Item added.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    //remove button is pushed
    private void removeButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
//        if(!sku.isEmpty()){
            //show pop up message
            String sku = JOptionPane.showInputDialog(guiManager.appFrame, "What is the sku of the item you want to remove?");
            int confirm = JOptionPane.showConfirmDialog(guiManager.appFrame, "Are you sure you want to remove item " + sku + "?");
            if( confirm == JOptionPane.YES_OPTION){
                try {
                    Statement stmt = jdbc.conn.createStatement();
                    String query = "DELETE FROM inventory WHERE sku = '" + sku + "';";
                    stmt.execute(query);
                    inventoryItems.clear();
                    inventoryItems = getInventoryItems();
                    inventoryTable.data.clear();
                    inventoryTable.data = inventoryItems;
                    JOptionPane.showMessageDialog(guiManager.appFrame, "Item removed.");
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
//        }
        changeList.clear();
    }

    public void commitChange(change c){
        String query;
        try{
            Statement stmt = jdbc.conn.createStatement();
            query = "UPDATE inventory SET \"" + inventoryTable.columns[c.col] + "\" = '" + c.value.toString() +
                    "' WHERE inventory.sku = '" + c.sku + "';";
            stmt.execute(query);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}