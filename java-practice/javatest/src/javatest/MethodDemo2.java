package javatest;

public class MethodDemo2 {
	public static void main(String args[]) {
		int one = add(29, 58); // ����addOne()����
		int three = add(25, 58, 10); // ����addOne()����
		float two = add(26.35f, -12.84f); // ����addTwo()����
		System.out.println("add(int x,int y)=" + one);
		System.out.println("add(int x,int y,int z)=" + three);
		System.out.println("add(float x,float y)=" + two);
	}

	public static int add(int x, int y) { // ���巽�������������ӷ�������һ����������
		int temp = 0; // tempΪ�ֲ�������ֻ�ڴ˷�������Ч
		temp = x + y;
		return temp; // ���ؼ�����
	}

	public static int add(int x, int y, int z) { // ���巽�������������ӷ�������һ����������
		int temp = 0; // tempΪ�ֲ�������ֻ�ڴ˷�������Ч
		temp = x + y + z;
		return temp; // ���ؼ�����
	}

	public static float add(float x, float y) {
		float temp = 0;
		temp = x + y;
		return temp;
	}
}
