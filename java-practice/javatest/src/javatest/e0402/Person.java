package javatest.e0402;

public class Person {
	public void cut() {
	}

	public static void main(String[] args) {
		Person player = new Player();
		Person cooker = new Cooker();
		Person cuter = new Cuter();

		player.cut();
		cooker.cut();
		cuter.cut();
	}
}

/** ��Ա */
class Player extends Person {
	/** ��д */
	public void cut() {
		System.out.println("ֹͣ��Ϸ");
	}
}

/** ��ʦ */
class Cooker extends Person {
	/** ��д */
	public void cut() {
		System.out.println("��ʼ�в�");
	}
}

/** ��ʦ */
class Cuter extends Person {
	/** ��д */
	public void cut() {
		System.out.println("��ʼ��ͷ��");
	}
}
