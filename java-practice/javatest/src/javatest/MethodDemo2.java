package javatest;

public class MethodDemo2 {
	public static void main(String args[]) {
		int one = add(29, 58); // 调用addOne()方法
		int three = add(25, 58, 10); // 调用addOne()方法
		float two = add(26.35f, -12.84f); // 调用addTwo()方法
		System.out.println("add(int x,int y)=" + one);
		System.out.println("add(int x,int y,int z)=" + three);
		System.out.println("add(float x,float y)=" + two);
	}

	public static int add(int x, int y) { // 定义方法，两个整数加法，返回一个整型数据
		int temp = 0; // temp为局部变量，只在此方法中有效
		temp = x + y;
		return temp; // 返回计算结果
	}

	public static int add(int x, int y, int z) { // 定义方法，两个整数加法，返回一个整型数据
		int temp = 0; // temp为局部变量，只在此方法中有效
		temp = x + y + z;
		return temp; // 返回计算结果
	}

	public static float add(float x, float y) {
		float temp = 0;
		temp = x + y;
		return temp;
	}
}
