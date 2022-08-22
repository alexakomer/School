import java.io.FileReader;
import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.time.LocalDate;


public class jdbc {

    //MAKE SURE YOU ARE ON VPN or TAMU WIFI TO ACCESS DATABASE

    //updates inventory based on sales data
    public static Connection conn;
    public LocalDate localDate = LocalDate.of(2022, 2, 12);
    // public Date sqlDate = Date.valueOf(localDate);
    public static int orderID = 0;

    //opens connection to our database
    public void openConnection() {
        //Building the connection with your credentials
        //TODO: update teamNumber, sectionNumber, and userPassword here
        conn = null;
        String teamNumber = "27";
        String sectionNumber = "905";
        String dbName = "csce315" + sectionNumber + "_" + teamNumber + "db";
        String dbConnectionString = "jdbc:postgresql://csce-315-db.engr.tamu.edu/" + dbName;
        String userName = "csce315" + sectionNumber + "_" + teamNumber + "user";
        String userPassword = "WindowsOnly";
        //Connecting to the database
        try {
            conn = DriverManager.getConnection(dbConnectionString, userName, userPassword);
            Class.forName("org.postgresql.Driver");
        } catch (Exception e) {
            e.printStackTrace();
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
            System.exit(0);
        }

        System.out.println("Opened database successfully");
    }

    //closes connection to our database
    public static void closeConnection() {
        try {
            conn.close();
            System.out.println("Connection Closed.");
        } catch (Exception e) {
            System.out.println("Connection NOT Closed.");
        }//end try catch
    }

    /*
    This function parses the return query from the database
     */
    public void parseQuery(ResultSet rs){
        //get column count
        try{
            ResultSetMetaData rsmd = rs.getMetaData();
            int columnCount = rsmd.getColumnCount();
            while(rs.next()){
                for(int i = 1; i <= columnCount; ++i){
                    //extract column name and value and print to console
                    String columnValue = rs.getString(i);
                    System.out.println(rsmd.getColumnName(i) + ": " + columnValue);
                }
                System.out.println();
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }

    /*
    This function extracts data from a query in array list form;
     */
    public static ArrayList<String> extractData(ResultSet rs){
        ArrayList<String> vals = new ArrayList<>();
        try {
            //extract column data and values and add to arraylist
            ResultSetMetaData rsmd = rs.getMetaData();
            int columnCount = rsmd.getColumnCount();
            while (rs.next()) {
                for (int i = 1; i <= columnCount; ++i) {
                    String columnValue = rs.getString(i);
                    vals.add(columnValue);
                }
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }
        return vals;
    }

    /*
    This function processes input array from the parser
     */
    public void executeSQL(String filename){
        ArrayList<String> parsedSQL= parser.sqlParser(filename);
        String queryBuilder = "";
        //iterate through array returned by the parser
        for(String s : parsedSQL){
            //differentiate commends from sql commands
            if(s.contains("//")){
                if(!(queryBuilder.equals(""))){
                    try {
                        Statement stmt = conn.createStatement();
                        ResultSet rs = stmt.executeQuery(queryBuilder);
                        parseQuery(rs);
                        queryBuilder = s;
                        //replace forward slashes in SQL command list
                        queryBuilder = queryBuilder.replaceAll("//", "");
                        System.out.println(queryBuilder);
                        queryBuilder = "";

                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
                else{
                    queryBuilder = s;
                    queryBuilder = queryBuilder.replaceAll("//", "");
                    System.out.println(queryBuilder);
                    queryBuilder = "";
                }
            }
            else{
                queryBuilder += s;
            }
        }
        try {
            //execute sql command parsed from file
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(queryBuilder);
            parseQuery(rs);
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
    /*
    This function returns a hashmap of all of the orders and their prices
     */
    public HashMap<Integer, Float> getMenuPrices(){
        HashMap<Integer, Float> returnMap = new HashMap<>();
        ArrayList<String> sqlValues;
        String query = "SELECT \"menuItem\", price FROM menu WHERE 1=1";
        try{
            //get menu data and put in hash map
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            sqlValues = extractData(rs);
            for(int i = 0; i < sqlValues.size(); i+=2){
                returnMap.put(Integer.parseInt(sqlValues.get(i)), Float.parseFloat(sqlValues.get(i + 1)));
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
        return returnMap;
    }
    /*
    This function uploads orders, decrements inventory and updates the drawer
     */
    public void setOrders(String orderFile){
        ArrayList<ArrayList<String>> csvOutput = parser.parseCSV(orderFile);
        ArrayList<String> sqlValues = new ArrayList<>();
        float totalForDay = 0;
        //get menu data from function
        HashMap<Integer, Float> orderPrices = new HashMap<>();
        orderPrices = getMenuPrices();
        for(ArrayList<String> entry : csvOutput){
            Integer menuID;
            Integer quantity;
            String query;
            Float price;
            if(entry.size() == 4 || entry.size() == 5){
                //increments the date
                localDate = localDate.plusDays(1);
                totalForDay = 0;
                continue;
            }
            else if(entry.size() != 2){
                continue;
            }
            else{
                menuID = Integer.parseInt(entry.get(0));
                quantity = Integer.parseInt(entry.get(1));

                try{
                    Statement stmt = conn.createStatement();
                    price = orderPrices.get(menuID) * quantity;
                    totalForDay += price;
                    //upload values into inventory from tables
                    for(int i = 0; i < quantity; ++i) {
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
                    query = "INSERT INTO drawer VALUES("+ this.orderID + "," + totalForDay + "," + "'" +  (Date.valueOf(localDate)).toString() + "'" + ")";
                    stmt.execute(query);
                    orderID++;
                    //insert items into drawer and orders
                    query = "INSERT INTO orders VALUES ("+ "'" + (Date.valueOf(localDate)).toString() + "'" + "," + price + "," + menuID + "," + quantity + ")";
                    stmt.execute(query);
                }
                catch (Exception e){
                    e.printStackTrace();
                }
            }
        }

    }

    /*
    This function uploads menu to inventory conversion data to our sql database
     */
    public void uploadConversions(String conversionFile){
        ArrayList<ArrayList<String>> parsedInput = parser.parseCSV(conversionFile);
        int itemID;
        String sku;
        float conversionFactor;
        String description;
        String units;
        String query;
        for(ArrayList<String> line : parsedInput){
            //ignores line
            if(line.get(0).equals("\uFEFFItemID")){
                continue;
            }
            else{
                //parse data into conversions
                itemID = Integer.parseInt(line.get(0));
                sku = line.get(1);
                conversionFactor = Float.parseFloat(line.get(2));
                description = line.get(3);
                units = line.get(4);
                query = "INSERT INTO conversions VALUES ("+ itemID + "," +
                        "'"+ sku + "'" +"," +  conversionFactor  + "," +  "'" + description + "'" +
                        "," +  "'" + units + "'" +")";
                try{
                    Statement stmt = conn.createStatement();
                    stmt.execute(query);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        }
    }

    /*
    This function uploads the composition of a menu item to our sql database
     */
    public void uploadComposition(String compositionFile){
        ArrayList<ArrayList<String>> parsedInput = parser.parseCSV(compositionFile);
        //composition values
        int menuID;
        int itemID;
        int quantity;
        String units;
        String itemName;
        String query;
        for(ArrayList<String> line : parsedInput){
            if(line.get(0).equals("\uFEFFmenuID")){
                continue;
            }
            else{
                //upload data into composition
                menuID = Integer.parseInt(line.get(0));
                itemID = Integer.parseInt(line.get(1));
                quantity = Integer.parseInt(line.get(2));
                units = line.get(3);
                itemName = line.get(4);
                query = "INSERT INTO orderDecomposition VALUES ("+ menuID + "," +
                        itemID  +"," +  quantity  + "," +  "'" + units + "'" +
                        "," +  "'" + itemName + "'" +")";
                try{
                    Statement stmt = conn.createStatement();
                    stmt.execute(query);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        }
    }
    /*
    This function uploads the menu
     */
    public void uploadMenu(String menuFile){
        ArrayList<ArrayList<String>> parsedInput =
                parser.parseCSV(menuFile);
        float item;
        String name;
        String description = "";
        float price;
        String query;
        //iterates through menu items
        for(ArrayList<String> itemList : parsedInput){
            if(itemList.size() != 1 && !itemList.get(0).equals("Item ")){
                item = Float.parseFloat(itemList.get(0));
                name = itemList.get(1);
                if(itemList.size() == 3){
                    price = Float.parseFloat(itemList.get(2));
                }
                else{
                    description = itemList.get(2);
                    price = Float.parseFloat(itemList.get(3));
                }
                //get items from menu and upload into table
                query = "INSERT INTO menu Values("+ item + "," +
                        "'"+ name + "'" +"," + "'" + description + "'" + "," +  price + ")";
                try{
                    Statement stmt = conn.createStatement();
                    stmt.execute(query);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
            }
        }
    }

    //updates inventory based on input inventory file
    public void setInventory(String inventoryFile) throws SQLException {
        String itemType = null;
        String description;
        String sku;
        float quantity;
        String container;
        String priceString;
        float price;
        float netPrice;
        String unit;
        String state;
        String itemName;
        String query;
        Statement stmt = conn.createStatement();
        ArrayList<ArrayList<String>> parsedInput =
                parser.parseCSV(inventoryFile);
        for(ArrayList<String> itemList : parsedInput){
            //sanitizing junk indices of input array
            if(itemList.get(0).equals("Description")){
            }
            else if(itemList.get(0).equals("Initial order ")){
            }
            else if(itemList.get(0).equals("Case/invoice total")){
            }
            else if(itemList.size() == 1){
                itemType = itemList.get(0);
            }
            else{
                //extract data from parser and create sql statement
                itemName = itemList.get(0);
                sku = itemList.get(1);
                quantity = Float.parseFloat(itemList.get(2)) * Float.parseFloat(itemList.get(6));
                unit = itemList.get(4);
                priceString = itemList.get(7).replace(",", "");
                price = Float.parseFloat(priceString);
                container = itemList.get(5);
                priceString = itemList.get(8).replace(",", "");
                netPrice = Float.parseFloat(priceString);
                state = itemList.get(9);
                description = itemList.get(11);
                query = "INSERT INTO inventory Values(" + "'" + sku + "'"  + "," + quantity + "," +
                        "'"+ container + "'" + "," + price + "," + "'" + state + "'" + "," + "'"+ description+ "'" + "," + "'" + itemName + "'"
                        + "," + "'" + itemType + "'" + "," + "'" + unit + "'" + "," + netPrice + ")";
                try{
                    stmt.addBatch(query);
                } catch (SQLException throwables) {
                    throwables.printStackTrace();
                }
                //send data to database
            }
        }
        stmt.executeBatch();
    }
}