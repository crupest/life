package javatest;

public class ArrayDemo2 {
	public static void main(String args[]) {
		int score[][] = { { 10, 3 }, { -1, 119, -51 }, { 100, 56, 90, 49 } };
		for (int i = 0; i < score.length; i++) {
			for (int j = 0; j < score[i].length; j++) {
				System.out.print(score[i][j] + "\t");
			}
			System.out.println("");
		}
	}
}
