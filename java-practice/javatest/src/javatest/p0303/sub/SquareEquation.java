package javatest.p0303.sub;

public class SquareEquation {
	double a, b, c;
	double root1, root2;
	boolean boo;

	public SquareEquation(double a, double b, double c) {
		this.a = a;
		this.b = b;
		this.c = c;
		if (a != 0) {
			boo = true;
		} else {
			boo = false;
		}
	}

	public void getRoots() {
		if (boo) {
			System.out.println("��һԪ2�η���");
			double disk = b * b - 4 * a * c;
			if (disk >= 0) {
				root1 = (-b + Math.sqrt(disk)) / (2 * a);
				root2 = (-b - Math.sqrt(disk)) / (2 * a);
				System.out.printf("���̵ĸ�:%f,%f\n", root1, root2);
			} else {
				System.out.printf("����û��ʵ��\n");
			}

		} else {
			System.out.println("����һԪ2�η���");
		}
	}

	public void setCoefficient(double a, double b, double c) {
		this.a = a;
		this.b = b;
		this.c = c;
		if (a != 0) {
			boo = true;
		} else {
			boo = false;
		}
	}
}
