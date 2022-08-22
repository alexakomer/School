
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
/*
Helper class that creates the table for all menu data
 */
public class conversionTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public String[] columns = new String [] {
            "itemID", "sku", "conversionFactor", "description", "units"
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
     * 0- itemID
     * 1- sku
     * 2- conversionFactor
     * 3- description
     * 4- units
     */
}
