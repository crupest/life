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
		System.out.println("���,�Է�����?");
	}

	// ��дpublic void speakHello()������Ҫ��������ơ���ã�������������
	// ������Ϣ
	public void averageHeight() {
		height = 173;
		System.out.println("�й��˵�ƽ����ߣ�" + height + "����");
	}

	// ��дpublic void averageHeight()������Ҫ���������
	// ���й��˵�ƽ����ߣ�168.78���ס������ĺ�����Ϣ
	public void averageWeight() {
		weight = 67.34;
		System.out.println("�й��˵�ƽ�����أ�" + weight + "����");
	}

	// ��дpublic void averageWeight()������
	// Ҫ��������ơ��й��˵�ƽ�����أ�65��������ĺ�����Ϣ
	public void chinaGongfu() {
		System.out.println("������,վ����,˯�繭");// ����й���������Ϣ�����磺"������,վ����,˯�繭"��
	}
}

class AmericanPeople extends People {
	public void speakHello() {
		System.out.println("How do You do");
	}

	// ��дpublic void speakHello()������Ҫ���������
	// ��How do you do��������Ӣ����Ϣ��
	public void averageHeight() {
		height = 188;
		System.out.println("Amerian Average height:" + height + " cm");
	}

	// ��дpublic void averageHeight()����
	public void averageWeight() {
		weight = 80.23;
		System.out.println("Amerian Average weight:" + weight + " kg");
	}

	// ��дpublic void averageWeight()����
	public void americanBoxing() {
		System.out.println("ֱȭ����ȭ");// ���ȭ������Ϣ�����磬��ֱȭ��������ȭ����
	}
}

class BeijingPeople extends ChinaPeople {
	public void speakHello() {
		System.out.println("����");
	}

	// ��дpublic void speakHello()������Ҫ��������ơ����á������ĺ�����Ϣ
	public void averageHeight() {
		height = 16;
		System.out.println("�����˵�ƽ����ߣ�" + height + "����");
	}

	// ��дpublic void averageHeight()����
	public void averageWeight() {
		weight = 6;
		System.out.println("�����˵�ƽ�����أ�" + weight + "����");
	}

	// ��дpublic void averageWeight()����
	public void beijingOpera() {
		System.out.println("��������");// ����������Ϣ
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
