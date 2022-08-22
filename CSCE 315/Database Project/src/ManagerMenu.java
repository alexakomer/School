import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * This class contains all methods for server window
 */
public class ManagerMenu extends javax.swing.JPanel {
    // Variables declaration

    private javax.swing.JTextField addMenuItem;
    private javax.swing.JTextField addName;
    private javax.swing.JTextField addDescription;
    private javax.swing.JTextField addPrice;

    private javax.swing.JTextField updateMenuItem;
    private javax.swing.JTextField updatePrice;

    private java.awt.Label label1;
    private java.awt.Label label2;
    private java.awt.Label label3;
    private java.awt.Label label4;
    private java.awt.Label label5;
    private java.awt.Label label8;

    private java.awt.Button backButton;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable menu;
    private java.awt.Button addButton;
    private java.awt.Button updateButton;
    public ArrayList<ArrayList<Object>> menuItems = new ArrayList<>();

    public menuTable formatTable;
    // End of variables declaration
    /**
     * Creates new form ManagerMenu
     */
    public ManagerMenu() {
        initComponents();
    }
    //initialize components of window
    private void initComponents() {

        //fetch new menu items if necessary
        if(menuItems.isEmpty()){
            menuItems = getMenuItems();
        }
        //sort menu items by ID
        menuItems.sort(new Comparator<ArrayList<Object>>() {
            @Override
            public int compare(ArrayList<Object> o1, ArrayList<Object> o2) {
                return Integer.compare(Integer.parseInt((String) o1.get(0)), Integer.parseInt((String) o2.get(0)));
            }
        });
        //create UI

        addMenuItem = new javax.swing.JTextField();
        addName = new javax.swing.JTextField();
        addDescription = new javax.swing.JTextField();
        addPrice = new javax.swing.JTextField();

        updateMenuItem = new javax.swing.JTextField();
        updatePrice = new javax.swing.JTextField();

        label1 = new java.awt.Label();
        label2 = new java.awt.Label();
        label3 = new java.awt.Label();
        label4 = new java.awt.Label();
        label5 = new java.awt.Label();
        label8 = new java.awt.Label();

        jScrollPane1 = new javax.swing.JScrollPane();
        addButton = new java.awt.Button();
        updateButton = new java.awt.Button();
        backButton = new java.awt.Button();

        menuTable.data = menuItems;
        formatTable = new menuTable();
        menu = new javax.swing.JTable(formatTable);
        jScrollPane1.setViewportView(menu);
        addButton.setActionCommand("addItem");
        addButton.setBackground(java.awt.Color.green);
        updateButton.setActionCommand("updateItem");
        updateButton.setBackground(java.awt.Color.orange);
        addButton.setLabel("Add");
        updateButton.setLabel("Update");


        // addMenuItem.setText("Menu Item");
        // addName.setText("Name");
        // addDescription.setText("Description");
        // addPrice.setText("Price");


        // updateMenuItem.setText("Menu Item");
        // updatePrice.setText("Price");


        label1.setText("menuItem");
        label2.setText("name");
        label3.setText("description");
        label4.setText("price");
        label5.setText("menuItem");
        label8.setText("price");


        // Adding action listeners to each button

        addButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addButtonActionPerformed(evt, addMenuItem.getText(), addName.getText(), addDescription.getText(), addPrice.getText());
            }
        });

        updateButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                updateButtonActionPerformed(evt, updateMenuItem.getText(), updatePrice.getText());
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
            .addComponent(jScrollPane1)
            .addGroup(layout.createSequentialGroup()
                .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, 52, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 31, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(addMenuItem, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(20, 20, 20)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(addName, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(29, 29, 29)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(addDescription, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label3, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(28, 28, 28)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(addPrice, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(44, 44, 44)
                                .addComponent(addButton))
                            .addComponent(label4, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(label5, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(updateMenuItem, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(20, 20, 20)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(updatePrice, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(28, 28, 28)
                                .addComponent(updateButton))
                            .addComponent(label8, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 313, Short.MAX_VALUE)
                .addGap(27, 27, 27)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label4, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(6, 6, 6)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(addButton)
                            .addComponent(addMenuItem, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(addName, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(addDescription, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(addPrice, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(36, 36, 36)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(label5, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label8, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(6, 6, 6)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(updateButton)
                            .addComponent(updateMenuItem, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(updatePrice, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(12, 12, 12))
        );
    }


    //add button is pushed
    private void addButtonActionPerformed(java.awt.event.ActionEvent evt, String menuItem, String name, String description, String price) {
        try {
            Statement stmt = jdbc.conn.createStatement();
            String sqlStatement = "DELETE FROM MENU WHERE MENU.\"menuItem\" = " + menuItem + ";";
            stmt.execute(sqlStatement);
            Statement stmt2 = jdbc.conn.createStatement();
            String sqlStatement2 = "INSERT INTO MENU VALUES (" + menuItem + ",\'" + name + "\',\'" + description + "\'," + Float.parseFloat(price) + ");";
            stmt2.execute(sqlStatement2);
            JOptionPane.showMessageDialog(guiManager.appFrame, "Menu Item " + menuItem + " successfully created!");
            CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
            c1.show(guiManager.layoutManager, "addMenu");
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(guiManager.appFrame, "Menu Item " + menuItem + " could not be created.");
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }

        menuItems = getMenuItems();
        menuTable.data = menuItems;
        formatTable.fireTableDataChanged();
        itemsTable.data = serverMenu.getMenuItems();
        serverMenu.tableFormat.fireTableDataChanged();
    }

    //update button is pushed
    private void updateButtonActionPerformed(java.awt.event.ActionEvent evt, String menuItem, String price) {
        try {

            Statement stmt = jdbc.conn.createStatement();
            String sqlStatement = "SELECT 1 from menu WHERE menu.\"menuItem\" = " + menuItem + ";";
            ResultSet rs = stmt.executeQuery(sqlStatement);
            ArrayList<String> sqlValues = jdbc.extractData(rs);
            if (sqlValues.size() == 0)
                JOptionPane.showMessageDialog(guiManager.appFrame, "Menu Item " + menuItem + " could not be updated.");
            else
            {
                Statement stmt2 = jdbc.conn.createStatement();
                String sqlStatement2 = "UPDATE menu SET price = " + price + "WHERE menu.\"menuItem\" = " + menuItem + ";";
                stmt2.execute(sqlStatement2);
                JOptionPane.showMessageDialog(guiManager.appFrame, "Menu Item " + menuItem + " successfully updated!");    
            }
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(guiManager.appFrame, "Menu Item " + menuItem + " could not be updated.");
                e.printStackTrace();
                System.err.println(e.getClass().getName() + ": " + e.getMessage());
            }

        menuItems = getMenuItems();
        menuTable.data = menuItems;
        formatTable.fireTableDataChanged();
        itemsTable.data = serverMenu.getMenuItems();
        serverMenu.tableFormat.fireTableDataChanged();
    }


    //gets menu from DB
    public ArrayList<ArrayList<Object>> getMenuItems(){
        ArrayList<ArrayList<Object>> returnMap = new ArrayList<>();
        ArrayList<String> sqlValues;
        String query = "SELECT * FROM menu";
        try{
            //get menu data and put in hash map
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
            for(int i = 0; i < sqlValues.size(); ++i){
                //Different indices for menu
                if(i % 4 == 0){
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

    //Goes to start menu
    private void backButtonActionPerformed(java.awt.event.ActionEvent evt) {
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "startMenu");
    }

}
