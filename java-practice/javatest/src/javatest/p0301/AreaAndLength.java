package javatest.p0301;

class Trangle {
	double sideA, sideB, sideC, area, length;
	boolean boo;

	public Trangle(double a, double b, double c) {
		sideA = a;
		sideB = b;
		sideC = c;// ����a,b,c�ֱ�ֵ��sideA,sideB,sideC
		if (a + b > c && a + c > b && c + b > a) // a,b,c���������ε��������ʽ
		{
			boo = true; // ��boo��ֵ��
		} else {
			boo = false; // ��boo��ֵ��
		}
	}

	double getLength() {
		if (boo) {
			length = sideA + sideB + sideC;
			return length;
		} else {
			System.out.println("����һ��������,���ܼ����ܳ�");
			return 0;
		}
		// �����壬Ҫ������length��ֵ������
	}

	public double getArea() {
		if (boo) {
			double p = (sideA + sideB + sideC) / 2.0;
			area = Math.sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
			return area;
		} else {
			System.out.println("����һ��������,���ܼ������");
			return 0;
		}
	}

	public void setABC(double a, double b, double c) {
		sideA = a;
		sideB = b;
		sideC = c; // ����a,b,c�ֱ�ֵ��sideA,sideB,sideC
		if (a + b > c && a + c > b && c + b > a) // a,b,c���������ε��������ʽ
		{
			boo = true; // ��boo��ֵ��
		} else {
			boo = false; // ��boo��ֵ��
		}
	}
}

class Lader {
	double above, bottom, height, area;

	Lader(double a, double b, double h) {
		above = a;
		bottom = b;
		height = h;
		// �����壬������a,b,c�ֱ�ֵ��above,bottom,height
	}

	double getArea() {
		area = (above + bottom) / 2 * height;
		return area;
		// �����壬,Ҫ������area����
	}
}

class Circle {
	double radius, area;

	Circle(double r) {
		radius = r; // ������
	}

	double getArea() {
		return 3.14 * radius * radius; // �����壬Ҫ������area����
	}

	double getLength() {
		return 3.14 * 2 * radius; // getArea������Ĵ���,Ҫ������length����
	}

	void setRadius(double newRadius) {
		radius = newRadius;
	}

	double getRadius() {
		return radius;
	}
}

public class AreaAndLength {
	public static void main(String args[]) {
		double length, area;
		Circle circle = null;
		Trangle trangle;
		Lader lader;
		circle = new Circle(10); // ��������circle
		trangle = new Trangle(3, 4, 5);// ��������trangle��
		lader = new Lader(3, 4, 10); // ��������lader
		length = circle.getLength(); // circle���÷��������ܳ�����ֵ��length
		System.out.println("Բ���ܳ�:" + length);
		area = circle.getArea();// circle���÷��������������ֵ��area
		System.out.println("Բ�����:" + area);
		length = trangle.getLength(); // trangle���÷��������ܳ�����ֵ��length
		System.out.println("�����ε��ܳ�:" + length);
		area = trangle.getArea(); // trangle���÷��������������ֵ��area
		System.out.println("�����ε����:" + area);
		area = lader.getArea(); // lader���÷��������������ֵ��area
		System.out.println("���ε����:" + area);
		trangle.setABC(12, 34, 1); // trangle���÷������������ߣ�Ҫ���������޸�Ϊ12,34,1��
		area = trangle.getArea(); // trangle���÷��������������ֵ��area
		System.out.println("�����ε����:" + area);
		length = trangle.getLength(); // trangle���÷��������ܳ�����ֵ��length
		System.out.println("�����ε��ܳ�:" + length);
	}
}
