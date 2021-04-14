package javatest;

public class E0202 {
	public static int F(int n) {
		if (n == 1 || n == 2) return 1;
		return F(n - 2) + F(n - 1);
	}
	
	public static void main(String[] args) {
		System.out.println(F(6));
	}
}
