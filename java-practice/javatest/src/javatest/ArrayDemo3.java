package javatest;

public class ArrayDemo3 {
	public static void main(String args[]) {
		int score[] = { 25, 78, 35, 84, 69, 74, 12, 56 };
		int age[] = { 32, 52, 12, 63, 42, 15, 75, 23, 56 };
		sort(score); // �������򷽷�
		print(score); // �����������
		System.out.println("\n-----------------------------------------");
		sort(age);
		print(age);
	}

	public static void sort(int temp[]) { // ��������
		for (int i = 1; i < temp.length; i++) { // ð���㷨
			for (int j = 0; j < temp.length; j++) {
				if (temp[i] < temp[j]) {
					int x = temp[i];
					temp[i] = temp[j];
					temp[j] = x;
				}
			}
		}
	}

	public static void print(int x[]) { // �������
		for (int i = 0; i < x.length; i++) {
			System.out.print(x[i] + " , ");
		}
	}
}
