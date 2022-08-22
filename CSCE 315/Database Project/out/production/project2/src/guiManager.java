import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.sql.SQLException;
/*
This class holds the layout manager and the main frame for the app
 */
public class guiManager {
    public static JFrame appFrame;
    public static JPanel layoutManager;
    //Creates frame and manager
    public static void init(){
        appFrame = new JFrame();
        appFrame.setSize(400, 400);
        layoutManager = new JPanel();
        //Enables us to switch between layouts
        layoutManager.setLayout(new CardLayout());
        layoutManager.add(new startMenu(), "startMenu");
        layoutManager.add(new serverMenu(), "serverMenu");
        layoutManager.add(new managerTabs(), "managerTabs");
        layoutManager.add(new AddMenu(), "addMenu");
        layoutManager.add(new PopupTable(), "popupTable");
        layoutManager.add(new restockPanel(), "restockPanel");
        appFrame.setContentPane(layoutManager);
        appFrame.pack();
        appFrame.setVisible(true);
        appFrame.addWindowListener(new WindowListener() {
            //Most of these are required methods that are not implemented
            @Override
            public void windowOpened(WindowEvent e) {

            }
            //Closes database and exits code when window is closed
            @Override
            public void windowClosing(WindowEvent e) {
                jdbc.closeConnection();
                System.exit(0);
            }

            @Override
            public void windowClosed(WindowEvent e) {
            }

            @Override
            public void windowIconified(WindowEvent e) {

            }

            @Override
            public void windowDeiconified(WindowEvent e) {

            }

            @Override
            public void windowActivated(WindowEvent e) {

            }

            @Override
            public void windowDeactivated(WindowEvent e) {

            }
        });
    }
}