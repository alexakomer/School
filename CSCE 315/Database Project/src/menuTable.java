
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
/*
Helper class that creates the table for all menu data
 */
public class menuTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public String[] columns = new String [] {
            "Menu Item", "Name", "Description", "Price"
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
     * 0- menuItem
     * 1- name
     * 2- description
     * 3- price
     */
}
