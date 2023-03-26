import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;

public class inventoryUsage extends javax.swing.JPanel {
    // Variables declaration

    private javax.swing.JComboBox<Object> Date1;
    private javax.swing.JLabel Date1Label;
    private javax.swing.JComboBox<Object> Date2;
    private javax.swing.JLabel Date2Label;
    private javax.swing.JButton backButton;
    private javax.swing.JScrollPane usedPane;
    private javax.swing.JTable usedTable;
    private javax.swing.JButton submitButton;
    public ArrayList<ArrayList<Object>> usedItems = new ArrayList<>();
    public usageTable used1Table;
    // End of variables declaration

    public inventoryUsage() {
        initComponents();
    }
    //initialize components of window
    private void initComponents() {

        //fetch new used items if necessary
        if (usedItems.isEmpty()) {
            usedItems = getUsedItems("2022/02/27", "2022/02/27");
        }
        //create UI

        Object[] dates = getDates().toArray();

        Date1 = new javax.swing.JComboBox<>(dates);
        Date2 = new javax.swing.JComboBox<>(dates);
        Date1Label = new javax.swing.JLabel();
        Date2Label = new javax.swing.JLabel();
        backButton = new javax.swing.JButton();
        submitButton = new javax.swing.JButton();
        usedPane = new javax.swing.JScrollPane();
        usedTable = new javax.swing.JTable();
        // Date1.setText("2022/02/27");
        // Date2.setText("2022/02/27");
        Date1Label.setText("Initial Date");
        Date2Label.setText("Final Date");
        backButton.setText("Back");
        backButton.setBackground(java.awt.Color.red);
        submitButton.setText("Go");
        submitButton.setBackground(java.awt.Color.green);


        usageTable.data = usedItems;
        used1Table = new usageTable();
        usedTable = new javax.swing.JTable(used1Table);
        usedPane.setViewportView(usedTable);

        // Adding action listeners to each button

        submitButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                submitButtonActionPerformed(evt, String.valueOf(Date1.getSelectedItem()), String.valueOf(Date2.getSelectedItem()));
            }
        });

        // backButton.setActionCommand("backToMenu");

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
                        .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                        .addComponent(submitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                        .addComponent(Date2Label, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                                .addGroup(layout.createSequentialGroup()
                                                                        .addContainerGap()
                                                                        .addComponent(Date1Label, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                                .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                                                        .addGap(20, 20, 20)
                                                                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                                                .addComponent(Date2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                                                .addComponent(Date1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                                                .addGroup(layout.createSequentialGroup()
                                                        .addGap(20, 20, 20)
                                                        .addComponent(backButton))))
                                .addGap(18, 18, 18)
                                .addComponent(usedPane, javax.swing.GroupLayout.PREFERRED_SIZE, 375, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addGap(21, 21, 21)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(layout.createSequentialGroup()
                                                .addComponent(usedPane, javax.swing.GroupLayout.PREFERRED_SIZE, 275, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(0, 0, Short.MAX_VALUE))
                                        .addGroup(layout.createSequentialGroup()
                                                .addComponent(Date1Label)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(Date1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(22, 22, 22)
                                                .addComponent(Date2Label)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(Date2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(26, 26, 26)
                                                .addComponent(submitButton, javax.swing.GroupLayout.PREFERRED_SIZE, 73, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addComponent(backButton)))
                                .addContainerGap())
        );
    }

    //submit button is pushed
    private void submitButtonActionPerformed(java.awt.event.ActionEvent evt, String date1, String date2) {
        usedItems = getUsedItems(date1, date2);
        usageTable.data = usedItems;
        used1Table.fireTableDataChanged();
    }

    // get distinct date values for dropdowns
    public ArrayList<String> getDates(){
        ArrayList<String> sqlValues = new ArrayList<>();
        String query = "select orders.\"orderDate\" from orders group by orders.\"orderDate\" order by orders.\"orderDate\" ASC;";
        try{
            //get dates into arraylist
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
        }
        catch (Exception e){
            e.printStackTrace();
        }

        return sqlValues;
    }

    // gets usage from DB
    public ArrayList<ArrayList<Object>> getUsedItems(String date1, String date2){

        date1 = date1.replace("/", "");
        date2 = date2.replace("/", "");

        ArrayList<ArrayList<Object>> returnMap = new ArrayList<>();
        ArrayList<String> sqlValues;
        String query = "SELECT inventory.\"itemName\", sum(orders.\"orderQuantity\" * orderdecomposition.quantity * conversions.\"conversionFactor\") AS \"inventoryUsage\", conversions.units " +
                "FROM orders " +
                "INNER JOIN orderdecomposition ON orders.\"menuItem\" = orderdecomposition.\"menuID\" " +
                "INNER JOIN conversions ON orderdecomposition.\"itemID\" = conversions.\"itemID\" " +
                "INNER JOIN inventory ON conversions.sku = inventory.sku " +
                "WHERE orders.\"orderDate\" BETWEEN '" + date1 + "' AND '" + date2 + "' " +
                "GROUP BY inventory.\"itemName\", conversions.units " +
                "ORDER BY \"itemName\" ASC;";
        try{
            //get usage data and put in hash map
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
            for(int i = 0; i < sqlValues.size(); ++i){
                //Different indices for menu
                if(i % 3 == 0){
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