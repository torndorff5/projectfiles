
import java.awt.*;

public class GameChar {
    static final int NORTH = -1;
    static final int SOUTH = 1;
    static final int WEST = -1;
    static final int EAST = 1;
    String[] items;
    String username;
    Point location;

    GameChar(String un, Point loc) {

        items = new String[]{"brass lantern", "rope", "rations", "staff"};
        username = un;
        location = loc;
    }

    GameChar(String un, Point loc, String[] items) {

        this.items = items;
        username = un;
        location = loc;
    }

    boolean go(int direction, boolean latlong) {
        if (latlong) {
            int temp = location.y + direction;
            if (temp >= Map.vertboundary || temp < Map.LOWBOUNDARY) {
                return false;
            } else {
                location.setLocation(location.x, temp);
                return true;
            }
        } else {
            int temp = location.x + direction;
            if (temp >= Map.horiboundary || temp < Map.LOWBOUNDARY) {
                return false;
            } else {
                location.setLocation(temp, location.y);
                return true;
            }
        }
    }
}