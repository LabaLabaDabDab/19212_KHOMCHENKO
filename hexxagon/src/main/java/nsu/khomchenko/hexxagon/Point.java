package nsu.khomchenko.hexxagon;

/**
 * ��������� ���������� ���������� �� �������� ������� � ������� (�� ���������� ������� ���� ��� � ������� ���������)
 */
public class Point extends java.awt.Point {
	private static final long serialVersionUID = 1L;

	public Point(int x, int y){
		super(x, y);
	}
	
	/**
	 * ���������� �������� ���������� ����� �������� (�� � �������� �����������, � � ��������)
	 * @param to �� ����� ����� ������� ���������
	 * @return
	 */
	public float getRealDist(Point to){
		float[] coords1 = toCoords(this);
		float[] coords2 = toCoords(to);
		return (float)Math.sqrt(Math.pow(coords1[0] - coords2[0], 2) + Math.pow(coords1[1] - coords2[1], 2));
	}
	
	/**
	 * ��������� ���������� �� �������� ������� � ������� (�� ���������� ������� ���� ��� � ������� ���������)
	 * @param p ����� � ������� �����������
	 * @return
	 */
	public float[] toCoords(Point p){
		return new float[]{ (float) p.x, (float)p.y * 1 + (float)p.x % 2 * 0.5f};
	}
}
