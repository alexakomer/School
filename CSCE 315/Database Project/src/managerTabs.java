import javax.swing.*;

public class managerTabs extends JTabbedPane {
    private javax.swing.JPanel inventoryPanel;
    private javax.swing.JPanel menuPanel;
    private javax.swing.JPanel favoritesPanel;
    private javax.swing.JPanel usagePanel;

    /**
     * Creates new form managerInventory
     */
    public managerTabs() {
        initComponents();
    }

    //initialize components of window
    private void initComponents() {
        inventoryPanel = new managerInventory();
        this.add("Inventory", inventoryPanel);
        menuPanel = new ManagerMenu();
        this.add("Menu", menuPanel);
        favoritesPanel = new FavoriteMenu();
        this.add("Favorites", favoritesPanel);
        usagePanel = new inventoryUsage();
        this.add("Usage", usagePanel);
    }
}