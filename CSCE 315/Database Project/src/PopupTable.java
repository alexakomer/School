import javax.swing.*;
import java.awt.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.Comparator;

/**
 * This class contains all methods for server window
 */
public class PopupTable extends javax.swing.JPanel {
    // Variables declaration

    private javax.swing.JButton backButton;
    private javax.swing.JLabel conversionsLabel;
    private javax.swing.JScrollPane conversionsPane;
    private javax.swing.JTable conversionsTable;
    private javax.swing.JLabel decompLabel;
    private javax.swing.JScrollPane decompPane;
    private javax.swing.JTable decompsTable;

    public ArrayList<ArrayList<Object>> conversionItems = new ArrayList<>();
    public ArrayList<ArrayList<Object>> decompItems = new ArrayList<>();

    public conversionTable conversionItemsTable;
    public decompTable decompItemsTable;


    /**
     * Creates new form PopupTable
     */
    public PopupTable() {
        initComponents();
    }
    //initialize components of window
    private void initComponents() {

        //fetch new cnoversion items if necessary
        if(conversionItems.isEmpty()){
            conversionItems = getConversionItems();
        }
        //sort conversion items by ID
        conversionItems.sort(new Comparator<ArrayList<Object>>() {
            @Override
            public int compare(ArrayList<Object> o1, ArrayList<Object> o2) {
                return Integer.compare(Integer.parseInt((String) o1.get(0)), Integer.parseInt((String) o2.get(0)));
            }
        });

        //fetch new decomposition items if necessary
        if(decompItems.isEmpty()){
            decompItems = getDecompItems();
        }
        //sort decomposition items by ID
        decompItems.sort(new Comparator<ArrayList<Object>>() {
            @Override
            public int compare(ArrayList<Object> o1, ArrayList<Object> o2) {
                return Integer.compare(Integer.parseInt((String) o1.get(0)), Integer.parseInt((String) o2.get(0)));
            }
        });

        //create UI
        conversionsPane = new javax.swing.JScrollPane();
        conversionsTable = new javax.swing.JTable();
        conversionsLabel = new javax.swing.JLabel();
        decompPane = new javax.swing.JScrollPane();
        decompsTable = new javax.swing.JTable();
        decompLabel = new javax.swing.JLabel();
        backButton = new javax.swing.JButton();

        // conversionsPane.setViewportView(conversionsTable);
        // conversionsLabel.setText("jLabel1");

        // decompPane.setViewportView(decompsTable);
        // decompLabel.setText("jLabel1");

        conversionTable.data = conversionItems;
        conversionItemsTable = new conversionTable();
        conversionsTable = new javax.swing.JTable(conversionItemsTable);
        conversionsPane.setViewportView(conversionsTable);


        decompTable.data = decompItems;
        decompItemsTable = new decompTable();
        decompsTable = new javax.swing.JTable(decompItemsTable);
        decompPane.setViewportView(decompsTable);

        // jScrollPane1 = new javax.swing.JScrollPane();
        // addButton = new java.awt.Button();
        // updateButton = new java.awt.Button();
        // backButton = new java.awt.Button();
        // menuTable.data = menuItems;
        // formatTable = new menuTable();
        // menu = new javax.swing.JTable(formatTable);
        // jScrollPane1.setViewportView(menu);
        // addButton.setActionCommand("addItem");
        // addButton.setBackground(java.awt.Color.green);
        // updateButton.setActionCommand("updateItem");
 


        // Adding action listeners to each button
        backButton.setActionCommand("backToMenu");
        backButton.setBackground(java.awt.Color.red);
        backButton.setText("Back");
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
            .addComponent(decompPane, javax.swing.GroupLayout.DEFAULT_SIZE, 671, Short.MAX_VALUE)
            .addComponent(conversionsPane, javax.swing.GroupLayout.DEFAULT_SIZE, 671, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(312, 312, 312)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(decompLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(conversionsLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(backButton, javax.swing.GroupLayout.PREFERRED_SIZE, 118, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(conversionsLabel)
                .addGap(8, 8, 8)
                .addComponent(conversionsPane, javax.swing.GroupLayout.PREFERRED_SIZE, 204, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(7, 7, 7)
                .addComponent(decompLabel)
                .addGap(8, 8, 8)
                .addComponent(decompPane, javax.swing.GroupLayout.PREFERRED_SIZE, 204, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(backButton, javax.swing.GroupLayout.DEFAULT_SIZE, 31, Short.MAX_VALUE)
                .addContainerGap())
        );
    }

    //gets conversion items from DB
    public ArrayList<ArrayList<Object>> getConversionItems(){
        ArrayList<ArrayList<Object>> returnMap = new ArrayList<>();
        ArrayList<String> sqlValues;
        String query = "SELECT * FROM conversions";
        try{
            //get menu data and put in hash map
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
            for(int i = 0; i < sqlValues.size(); ++i){
                //Different indices for menu
                if(i % 5 == 0){
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

     //gets decomposition items from DB
     public ArrayList<ArrayList<Object>> getDecompItems(){
        ArrayList<ArrayList<Object>> returnMap = new ArrayList<>();
        ArrayList<String> sqlValues;
        String query = "SELECT * FROM orderdecomposition";
        try{
            //get menu data and put in hash map
            Statement stmt = jdbc.conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = jdbc.extractData(rs);
            for(int i = 0; i < sqlValues.size(); ++i){
                //Different indices for menu
                if(i % 5 == 0){
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
        c1.show(guiManager.layoutManager, "addMenu");
    }

}
