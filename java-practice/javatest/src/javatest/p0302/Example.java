package javatest.p0302;

class A {
	float a; // ����һ��float��ʵ������a
	static float b; // ����һ��float�������b,��static����b

	void setA(float a) {
		this.a = a; // ������a��ֵ��ֵ����Ա����a
	}

	void setB(float b) {
		this.b = b; // ������b��ֵ��ֵ����Ա����b
	}

	float getA() {
		return a;
	}

	float getB() {
		return b;
	}

	void inputA() {
		System.out.println(a);
	}

	static void inputB() {
		System.out.println(b);
	}
}

public class Example {
	public static void main(String args[]) {
		A.b = 100; // ͨ���������������b,����ֵ100
		A.inputB(); // ͨ���������÷���inputB()
		A cat = new A();
		A dog = new A();
		cat.setA(200); // cat����÷���setA(int a)��cat�ĳ�Աa��ֵ����Ϊ200
		cat.setB(400); // cat���÷���setB(int b)��cat�ĳ�Աb��ֵ����Ϊ400
		dog.setA(150); // dog����÷���setA(int a)��dog�ĳ�Աa��ֵ����Ϊ150
		dog.setB(300); // dog���÷���setB(int b)��dog�ĳ�Աb��ֵ����Ϊ300
		cat.inputA(); // cat����inputA()��
		cat.inputB(); // cat����inputB()��
		dog.inputA(); // dog����inputA()��
		dog.inputB(); // dog����inputB()��
	}
}
