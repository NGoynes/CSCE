package sample;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.input.MouseEvent;
import javafx.scene.image.ImageView;


public class Controller implements Initializable {
    @FXML
    private ImageView btnTwo, btnThree, btnFour, btnClose;

    @FXML
    private AnchorPane h_queryTwo, h_queryThree, h_queryFour;

    @FXML
    private void handleButtonAction(MouseEvent event) {
        if(event.getTarget() == btnTwo) {
            h_queryTwo.setVisible(true);
            h_queryThree.setVisible(false);
            h_queryFour.setVisible(false);
        }
        else if (event.getTarget() == btnThree) {
            h_queryThree.setVisible(true);
            h_queryTwo.setVisible(false);
            h_queryFour.setVisible(false);
        }
        else if (event.getTarget() == btnFour) {
            h_queryFour.setVisible(true);
            h_queryThree.setVisible(false);
            h_queryTwo.setVisible(false);
        }
        else if (event.getTarget() == btnClose) {
            h_queryFour.setVisible(false);
            h_queryThree.setVisible(false);
            h_queryTwo.setVisible(false);
        }
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {

    }
}

