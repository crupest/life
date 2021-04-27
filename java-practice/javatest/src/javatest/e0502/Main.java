package javatest.e0502;

abstract class Animal {
	public Animal(String name, String color, String type) {
		super();
		this.name = name;
		this.color = color;
		this.type = type;
	}

	private String name;
	private String color;
	private String type;

	abstract void eat();

	abstract void makeSound();

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}
}

class Rabbit extends Animal {
	public Rabbit() {
		super("����", "��ɫ", "������");
	}

	@Override
	public void eat() {
		System.out.println("���ӳ�...");
	}

	@Override
	public void makeSound() {
		System.out.println("���ӽ�...");
	}
}

interface Swimmable {
	void swim();
}

class Frog extends Animal implements Swimmable {
	public Frog() {
		super("����", "��ɫ", "�ǲ�����");
	}

	@Override
	public void eat() {
		System.out.println("���ܳ�...");
	}

	@Override
	public void makeSound() {
		System.out.println("���ܽ�...");
	}

	@Override
	public void swim() {
		System.out.println("������Ӿ...");
	}
}

public class Main {
	public static void main(String[] args) {
		Rabbit rabbit = new Rabbit();
		Frog frog = new Frog();
		
		Animal animal = rabbit;
		animal.eat();
		animal.makeSound();
		
		animal = frog;
		animal.eat();
		animal.makeSound();
		
		Swimmable swimmable = frog;
		swimmable.swim();
	}
}
