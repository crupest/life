package javatest;

public class E0203 {
	public static void main(String[] args) {
		int[] array = new int[] { 1, 2, 3, 4 };
		intArray.printArray(array);
		System.out.println();
		intArray.printArray(intArray.reverse(array));
	}
}

class intArray {
	public static void printArray(int[] array) {
		for (int i = 0; i < array.length; i++) {
			System.out.print(array[i] + " ");
		}
	}

	public static int[] reverse(int[] list) {
		int[] result = new int[list.length];
		for (int i = 0; i < list.length; i++) {
			result[i] = list[list.length - i - 1];
		}
		return result;
	}
}
