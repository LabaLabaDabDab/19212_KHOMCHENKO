package nsu.khomchenko.hexxagon;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * ���� ����� �������� �� ��������� ��������� ������
 */
public class Highlight implements DrawableEntity {

	private int     type; //��� ���������
	private boolean enable; //�������� ��� ��������� ��������� (�������/������)
	private float   scale; //�������
	private float   x, y; //����������
	private BufferedImage image; //����� ��� ��� ���� ������

	public Highlight(float x, float y, float scale, int type) {
		this.x = x;
		this.y = y;
		this.type = type;
		enable = false;
		this.scale = scale;
		if (type == 0) {
			image = Assets.highlight1;
		}
		else {
			image = Assets.highlight2;
		}
	}

	@Override
	public void draw(Graphics2D g2d) {
		if (enable) g2d.drawImage(image, (int) x, (int) y, (int) (image.getWidth() * scale), (int) (image.getHeight() *
																									scale), null);
	}

	public float[] getCenterPosition() { //���������� ������� ������ ������ � �������� ����������� � ���� �������
		return new float[] { image.getWidth() * scale / 2 + x, image.getHeight() * scale / 2 + y };
	}

	public void enable(int type) { //�������� ���������, ������������� ��������� ��� � ��������� �����������
		this.type = type;
		enable = true;
		if (type == 0) {
			image = Assets.highlight1;
		}
		else {
			image = Assets.highlight2;
		}
	}

	public void disable() { //��������� ���������
		enable = false;
	}

	public boolean isEnable() { //���? �� ���?
		return enable;
	}
}
