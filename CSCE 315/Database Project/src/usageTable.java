import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;

public class usageTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public String[] columns = new String [] {
            "Item Name", "Usage", "Units"
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
}
