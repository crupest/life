package javatest.e0301;

public class Circle {
	private static int numOfObjects = 0;

	public static int getNumOfObjects() {
		return numOfObjects;
	}

	private double radius;

	public Circle(double radius) {
		this.radius = radius;
		numOfObjects++;
	}

	public double getArea() {
		return radius * radius * Math.PI;
	}

	public static void printCircle(Circle c) {
		System.out.println("Radius of circle is " + c.radius);
		System.out.println("Area of circle is " + c.getArea());
	}

	public static void main(String[] args) {
		Circle c1 = new Circle(2);
		Circle c2 = new Circle(3);
		Circle.printCircle(c1);
		Circle.printCircle(c2);
		System.out.println("Num of objects is " + Circle.getNumOfObjects());
	}
}
