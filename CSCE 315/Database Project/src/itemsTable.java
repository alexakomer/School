
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
/*
Helper class that creates the table for all menu data
 */
public class itemsTable extends AbstractTableModel {

    public static ArrayList<ArrayList<Object>> data;
    public static double total;
    public String[] columns = new String [] {
            "Menu Item", "Name", "Description", "Price", "Quantity"
    };
    //edits cell in array
    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        if(columnIndex == getColumnCount()-1){
            return true;
        }
        else{
            return false;
        }
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
        //Updates the total for orders
        updateTotal();
        //updates user side price
        serverMenu.updatePrice();
    }
    //updates the total based on new quantities
    public void updateTotal(){
        total = 0;
        for(ArrayList<Object> l : data){
            if(Integer.parseInt(String.valueOf(l.get(l.size() - 1))) != 0){
                total = total + Integer.parseInt(String.valueOf(l.get(l.size() - 1))) * Float.parseFloat(String.valueOf(l.get(3)));
            }
        }
    }
    //sets all quantities in table to 0
    public void zeroTable(){
        for(int i = 0;i < data.size(); ++i){
            if(Integer.parseInt(String.valueOf(data.get(i).get(data.get(i).size() - 1))) != 0){
                data.get(i).set(4, 0);
                fireTableCellUpdated(i, 4);
            }
        }
        total = 0;
    }
    /**
     * Data indices
     * 0- itemNo.
     * 1- name
     * 2- description
     * 3- price
     * 4- Quantity
     */
}
