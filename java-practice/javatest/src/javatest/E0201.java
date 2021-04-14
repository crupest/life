package javatest;

public class E0201 {
	public static int max(int a, int b) {
		return a > b ? a : b;
	}

	public static double max(double a, double b) {
		return a > b ? a : b;
	}

	public static int max(int a, int b, int c) {
		return max(a, max(b, c));
	}

	public static void main(String[] args) {
		System.out.println(max(1, 2));
		System.out.println(max(2.2, 3.3));
		System.out.println(max(1, 2, 3));
	}
}
