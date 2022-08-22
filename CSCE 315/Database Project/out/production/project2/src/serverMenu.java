import javax.swing.*;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * This class contains all methods for server window
 */
public class serverMenu extends javax.swing.JPanel {
    // Variables declaration
    private java.awt.Button backButton;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable menu;
    private java.awt.Button submitButton;
    public ArrayList<ArrayList<Object>> menuItems = new ArrayList<>();
    public static double totalForDay;
    public static JLabel price;
    public double currentTotal;
    public static itemsTable tableFormat;
    // End of variables declaration
    /**
     * Creates new form serverMenu
     */
    public serverMenu() {
        initComponents();
    }
    //initialize components of window
    private void initComponents() {

        //gets orderID and running total for day from DB
        String query = "SELECT MAX(\"totalForDay\") FROM drawer WHERE \"orderDate\" = " + "'" + (Date.valueOf(LocalDate.now())).toString() + "'";
        try {
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            ArrayList<String> values = jdbc.extractData(rs);
            if(values.get(0) == null){
                totalForDay = 0;
            }
            else{
                totalForDay = Float.parseFloat(values.get(0));
            }
            query = "SELECT MAX(\"orderID\") FROM drawer";
            rs = stmt.executeQuery(query);
            values = jdbc.extractData(rs);
            jdbc.orderID = Integer.parseInt(values.get(0)) + 1;
        }
        catch(Exception e){
            e.printStackTrace();

        }
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
        jScrollPane1 = new javax.swing.JScrollPane();
        submitButton = new java.awt.Button();
        backButton = new java.awt.Button();
        itemsTable.data = menuItems;
        tableFormat = new itemsTable();
        menu = new javax.swing.JTable(tableFormat);
        jScrollPane1.setViewportView(menu);
        submitButton.setActionCommand("submitOrder");
        submitButton.setBackground(java.awt.Color.green);
        submitButton.setLabel("Submit");
        price = new JLabel("Total: $0.00");
        price.setFont(new Font("Serif", Font.PLAIN,15));
        submitButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                submitButtonActionPerformed(evt);
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
                                .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(price, GroupLayout.PREFERRED_SIZE, 100, GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(submitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE))
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 266, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(submitButton, javax.swing.GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
                                        .addComponent(price)
                                        .addComponent(backButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)))
        );
    }
    //submit button is pushed
    private void submitButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        if(itemsTable.total > 0){
            for(ArrayList<Object> l : itemsTable.data){
                if(Integer.parseInt(String.valueOf(l.get(4))) > 0){
                    float orderTotal = Integer.parseInt((String) l.get(4)) * Float.parseFloat((String) l.get(3));
                    createOrder(Integer.parseInt((String) l.get(4)), Integer.parseInt((String) l.get(0)), orderTotal);
                }
            }
            tableFormat.zeroTable();
            updatePrice();
            //show pop up message
            JOptionPane.showMessageDialog(guiManager.appFrame, "Order " + jdbc.orderID + " successfully created!");
            jdbc.orderID++;
        }
    }
    //gets menu from DB
    public static ArrayList<ArrayList<Object>> getMenuItems(){
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
                    if(i != 0) {
                        returnMap.get(returnMap.size() -1).add("0");
                    }
                    returnMap.add(new ArrayList<>());
                }
                returnMap.get(returnMap.size()-1).add(sqlValues.get(i));
            }
            //Adds 0 in last entry
            returnMap.get(returnMap.size()-1).add("0");
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return returnMap;
    }

    //Goes to start menu
    private void backButtonActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        CardLayout c1 = (CardLayout) guiManager.layoutManager.getLayout();
        c1.show(guiManager.layoutManager, "startMenu");
    }


    public static void updatePrice(){
        price.setText("Total: $" + String.format("%.2f", itemsTable.total));
    }

    //pushes order to tables in DB
    public void createOrder(Integer quantity, Integer menuID, Float totalPrice) {
        String query;
        try {
            Statement stmt = jdbc.conn.createStatement();
            totalForDay += totalPrice;
            LocalDate localDate = LocalDate.now();
            //upload values into inventory from tables
            for (int i = 0; i < quantity; ++i) {
                query = "UPDATE inventory SET quantity = quantity - T.conversionQuantity FROM( " +
                        "SELECT inventory.sku, sum(orderdecomposition.quantity * conversions.\"conversionFactor\") AS conversionQuantity " +
                        "FROM orderdecomposition " +
                        "INNER JOIN conversions ON orderdecomposition.\"itemID\" = conversions.\"itemID\" " +
                        "INNER JOIN inventory ON conversions.sku = inventory.sku " +
                        "WHERE orderdecomposition.\"menuID\" = " + menuID + " " +
                        "group by inventory.sku) AS T WHERE T.sku = inventory.sku;";
                stmt.addBatch(query);
            }
            //account for janitorial data for customer
            query = "UPDATE inventory SET quantity = quantity - T.conversionQuantity  FROM( " +
                    "SELECT inventory.sku, conversions.\"conversionFactor\" AS conversionQuantity " +
                    "FROM conversions " +
                    "INNER JOIN inventory ON conversions.sku = inventory.sku " +
                    "WHERE conversions.\"itemID\" = 13) AS T WHERE T.sku = inventory.sku;";
            stmt.addBatch(query);
            stmt.executeBatch();
            query = "INSERT INTO drawer VALUES(" + jdbc.orderID + "," + totalForDay + "," + "'" + (Date.valueOf(localDate)).toString() + "'" + ")";
            stmt.execute(query);
            //insert items into drawer and orders
            query = "INSERT INTO orders VALUES (" + "'" + (Date.valueOf(localDate)).toString() + "'" + "," + totalPrice + "," + menuID + "," + quantity + ")";
            stmt.execute(query);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
