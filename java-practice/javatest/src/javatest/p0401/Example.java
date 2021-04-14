package javatest.p0401;

class People {
	protected double weight, height;

	public void speakHello() {
		System.out.println("yayawawa");
	}

	public void averageHeight() {
		height = 173;
		System.out.println("average height:" + height);
	}

	public void averageWeight() {
		weight = 70;
		System.out.println("average weight:" + weight);
	}
}

class ChinaPeople extends People {
	public void speakHello() {
		System.out.println("你好,吃饭了吗?");
	}

	// 重写public void speakHello()方法，要求输出类似“你好，吃了吗”这样的
	// 汉语信息
	public void averageHeight() {
		height = 173;
		System.out.println("中国人的平均身高：" + height + "厘米");
	}

	// 重写public void averageHeight()方法，要求输出类似
	// “中国人的平均身高：168.78厘米”这样的汉语信息
	public void averageWeight() {
		weight = 67.34;
		System.out.println("中国人的平均体重：" + weight + "公斤");
	}

	// 重写public void averageWeight()方法，
	// 要求输出类似“中国人的平均体重：65公斤”这样的汉语信息
	public void chinaGongfu() {
		System.out.println("坐如钟,站如松,睡如弓");// 输出中国武术的信息，例如："坐如钟,站如松,睡如弓"等
	}
}

class AmericanPeople extends People {
	public void speakHello() {
		System.out.println("How do You do");
	}

	// 重写public void speakHello()方法，要求输出类似
	// “How do you do”这样的英语信息。
	public void averageHeight() {
		height = 188;
		System.out.println("Amerian Average height:" + height + " cm");
	}

	// 重写public void averageHeight()方法
	public void averageWeight() {
		weight = 80.23;
		System.out.println("Amerian Average weight:" + weight + " kg");
	}

	// 重写public void averageWeight()方法
	public void americanBoxing() {
		System.out.println("直拳、钩拳");// 输出拳击的信息，例如，“直拳”、“钩拳”等
	}
}

class BeijingPeople extends ChinaPeople {
	public void speakHello() {
		System.out.println("您好");
	}

	// 重写public void speakHello()方法，要求输出类似“您好”这样的汉语信息
	public void averageHeight() {
		height = 16;
		System.out.println("北京人的平均身高：" + height + "厘米");
	}

	// 重写public void averageHeight()方法
	public void averageWeight() {
		weight = 6;
		System.out.println("北京人的平均体重：" + weight + "公斤");
	}

	// 重写public void averageWeight()方法
	public void beijingOpera() {
		System.out.println("京剧术语");// 输出京剧的信息
	}
}

public class Example {
	public static void main(String args[]) {
		ChinaPeople chinaPeople = new ChinaPeople();
		AmericanPeople americanPeople = new AmericanPeople();
		BeijingPeople beijingPeople = new BeijingPeople();
		chinaPeople.speakHello();
		americanPeople.speakHello();
		beijingPeople.speakHello();
		chinaPeople.averageHeight();
		americanPeople.averageHeight();
		beijingPeople.averageHeight();
		chinaPeople.averageWeight();
		americanPeople.averageWeight();
		beijingPeople.averageWeight();
		chinaPeople.chinaGongfu();
		americanPeople.americanBoxing();
		beijingPeople.beijingOpera();
		beijingPeople.chinaGongfu();
	}
}
