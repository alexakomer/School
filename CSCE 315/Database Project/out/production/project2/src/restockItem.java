
/*
This class holds various data for items that need to be restocked
 */
public class restockItem {
    public String SKU;
    public String description;
    public double quantity;
    public double total;

    //Edit this function if more data is needed for restock items. Return n data members in class.
    public static int getNumData(){
        return 4;
    }

    //This function converts column no. to item. Edit this if more fields need to be added.
    public Object numToObject(Integer index){
        switch (index){
            case 0:
                return SKU;
            case 1:
                return description;
            case 2:
                return quantity;
            case 3:
                return total;
            default:
                return -1;

        }
    }

}
