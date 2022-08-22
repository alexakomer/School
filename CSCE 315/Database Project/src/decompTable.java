
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
/*
Helper class that creates the table for all menu data
 */
public class decompTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public String[] columns = new String [] {
            "menuID", "itemID", "quantity", "units", "itemName"
    };

    @Override
    public int getRowCount() {
        return data.size();
    }

    @Override
    public int getColumnCount() {
        return data.get(0).size();
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return data.get(rowIndex).get(columnIndex);
    }

    @Override
    public String getColumnName(int col){
        return columns[col];
    }

    /**
     * Data indices
     * 0- menuID
     * 1- itemID
     * 2- quantity
     * 3- units
     * 4- itemName
     */
}
