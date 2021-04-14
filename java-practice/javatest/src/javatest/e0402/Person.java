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

/** 演员 */
class Player extends Person {
	/** 重写 */
	public void cut() {
		System.out.println("停止演戏");
	}
}

/** 厨师 */
class Cooker extends Person {
	/** 重写 */
	public void cut() {
		System.out.println("开始切菜");
	}
}

/** 厨师 */
class Cuter extends Person {
	/** 重写 */
	public void cut() {
		System.out.println("开始剪头发");
	}
}
