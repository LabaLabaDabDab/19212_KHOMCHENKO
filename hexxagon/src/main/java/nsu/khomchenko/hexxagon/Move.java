package nsu.khomchenko.hexxagon;

import java.io.Serializable;

/**
 * ���� ����� ������ ���������� � ����: ��������� ������� � ��������.
 */
public class Move implements Serializable {
	private Point from;
	private Point to;
	private int team;
	
	/**
	 * @param xfrom ���������� ���. ������� �� �
	 * @param yfrom ���������� ���. ������� �� �
	 * @param xto ���������� ���. ������� �� �
	 * @param yto ���������� ���. ������� �� �
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
