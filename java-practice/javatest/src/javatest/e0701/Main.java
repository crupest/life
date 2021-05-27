package javatest.e0701;

public class Main {
	private static int countSubstring(String string, String substring) {
		int count = 0;
		int currentIndex = 0;

		while (true) {
			int i = string.indexOf(substring, currentIndex);
			if (i == -1)
				break;
			count++;
			currentIndex = i + 1;
		}

		return count;
	}

	public static void main(String[] args) {
		String string = "ababaaba";
		String substring = "aba";

		System.out.println(substring + "��" + string + "�г�����" + countSubstring(string, substring) + "�Σ�");
	}
}
