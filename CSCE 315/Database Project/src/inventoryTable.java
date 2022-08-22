import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;

public class inventoryTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public static String[] columns = new String [] {
            "sku", "quantity", "container", "price", "state", "description", "itemName", "type", "unit", "totalPrice", "fillLevel"
    };

    //edits cell in array
    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
//        if(columnIndex == 0){
//            return false;
//        }
        return true;
    }

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

    //Edits value in array
    @Override
    public void setValueAt(Object value, int rowIndex, int colIndex){
        data.get(rowIndex).set(colIndex, value);
        //Updates table
        fireTableCellUpdated(rowIndex, colIndex);
        change temp = new change();
        temp.value = value;
        temp.sku = getValueAt(rowIndex, 0).toString();
        temp.col = colIndex;
        managerInventory.changeList.add(temp);
//        System.out.println("Change detected in the table.");
    }
}

class change{
    public Object value;
    public String sku;
    public int col;
}