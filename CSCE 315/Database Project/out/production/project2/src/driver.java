import java.io.File;
import java.io.FilenameFilter;

public class driver {
    //main file that runs the code
    public static void main(String args[]) {
        try{
            jdbc database = new jdbc();

            //create a statement object
            database.openConnection();
//            sets inventory in database
//            database.setInventory("res/inventory/First day order.csv");
//            upload menu to database
//            database.uploadMenu("res/compositions/MenuKey.csv");
//            upload composition to database
//            database.uploadComposition("res/compositions/menuDecomposition.csv");
//            upload unit conversions to database

//            database.uploadConversions("res/compositions/conversions.csv");
            guiManager.init();

//            File f = new File("res/sales");
//            FilenameFilter filter = new FilenameFilter() {
//                @Override
//                public boolean accept(File f, String name) {
//                    return name.endsWith(".csv");
//                }
//            };
//            File[] orderFiles = f.listFiles(filter);
//            for(File file : orderFiles){
//                database.setOrders(file.getPath());
//            }
//            database.setOrders("res/sales/FirstWeekSales.csv");
//            database.executeSQL("res/queries.txt");

//            database.closeConnection();
        } catch (Exception e){
            e.printStackTrace();
            System.err.println(e.getClass().getName()+": "+e.getMessage());
            System.exit(0);
        }
    }//end main
}//end Class
