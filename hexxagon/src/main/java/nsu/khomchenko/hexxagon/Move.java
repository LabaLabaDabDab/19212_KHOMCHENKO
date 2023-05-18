package nsu.khomchenko.hexxagon;

import java.io.Serializable;

/**
 * Этот класс хранит информацию о ходе: начальную позицию и конечную.
 */
public class Move implements Serializable {
	private Point from;
	private Point to;
	private int team;
	
	/**
	 * @param xfrom Координата нач. позиции по х
	 * @param yfrom Координата нач. позиции по у
	 * @param xto Координата кон. позиции по х
	 * @param yto Координата кон. позиции по у
	 */
	public Move(int xfrom, int yfrom, int xto, int yto, int team){
		from = new Point(xfrom, yfrom);
		to = new Point(xto, yto);
		this.team = team;
	}

	public Point getFrom() {
		return from;
	}

	public Point getTo() {
		return to;
	}

	public int getTeam() {
		return this.team;
	}
}
