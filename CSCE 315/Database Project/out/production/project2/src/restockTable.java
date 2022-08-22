import javax.swing.event.TableModelEvent;
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;

/*
This class contains methods for the restock table
 */
public class restockTable extends AbstractTableModel {
    public static ArrayList<restockItem> restockItems;
    public String[] columns = new String [] {
            "SKU", "Description", "Quantity", "Total"
    };

    @Override
    public String getColumnName(int column) {
        return columns[column];
    }

    @Override
    public int getRowCount() {
        return restockItems.size();
    }

    @Override
    public int getColumnCount() {
        return restockItem.getNumData();
    }
    @Override
    //populate data in table
    public Object getValueAt(int rowIndex, int columnIndex) {
        return restockItems.get(rowIndex).numToObject(columnIndex);
    }
}
