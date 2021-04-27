package javatest.e0501;

import java.util.Scanner;

interface Soundable {
	void makeSound();

	void turnUpVolumn();

	void turnDownVolumn();
}

class Radio implements Soundable {
	private int volumn = 5;

	@Override
	public void makeSound() {
		System.out.println("Radio sound...");
	}

	@Override
	public void turnUpVolumn() {
		volumn++;
	}

	@Override
	public void turnDownVolumn() {
		volumn--;
	}
}

class Walkman implements Soundable {
	private int volumn = 5;

	@Override
	public void makeSound() {
		System.out.println("Walkman sound...");
	}

	@Override
	public void turnUpVolumn() {
		volumn++;
	}

	@Override
	public void turnDownVolumn() {
		volumn--;
	}
}

class Mobilephone implements Soundable {
	private int volumn = 5;

	@Override
	public void makeSound() {
		System.out.println("Mobilephone sound...");
	}

	@Override
	public void turnUpVolumn() {
		volumn++;
	}

	@Override
	public void turnDownVolumn() {
		volumn--;
	}
}

public class Main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		String t = scanner.next();
		Soundable soundable = null;

		switch (t) {
		case "radio":
			soundable = new Radio();
			break;
		case "walkman":
			soundable = new Walkman();
			break;
		case "mobilephone":
			soundable = new Mobilephone();
			break;
		default:
			System.out.println("Unknown device.");
			System.exit(1);
		}
		
		soundable.makeSound();
	}
}
