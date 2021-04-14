package javatest.e0401;

public class Program {
	public static boolean equalArea(GeometricObject object1, GeometricObject object2) {
		return object1.findArea() == object2.findArea();
	}

	public static void displayGeometricObject(GeometricObject object) {
		if (object instanceof Circle) {
			System.out.println("A Circle.");
		} else if (object instanceof Rectangle) {
			System.out.println("A Rectangle.");
		}
	}

	public static void main(String[] args) {
		Circle circle = new Circle(3);
		Rectangle rectangle = new Rectangle(2, 4);

		System.out.println(equalArea(circle, rectangle));
		displayGeometricObject(circle);
		displayGeometricObject(rectangle);
	}
}

abstract class GeometricObject {
	protected String color;

	public abstract double findArea();

	public abstract double findPerimeter();
}

class Circle extends GeometricObject {

	private double radius;

	public Circle(double radius) {
		this.radius = radius;
	}

	@Override
	public double findArea() {
		return radius * radius * Math.PI;
	}

	@Override
	public double findPerimeter() {
		return radius * 2 * Math.PI;
	}
}

class Rectangle extends GeometricObject {

	private double width;
	private double height;

	public Rectangle(double width, double height) {
		this.width = width;
		this.height = height;
	}

	@Override
	public double findArea() {
		return width * height;
	}

	@Override
	public double findPerimeter() {
		return (width + height) * 2;
	}
}
