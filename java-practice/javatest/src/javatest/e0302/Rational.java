package javatest.e0302;

public class Rational {
	private long numerator;
	private long denominator;

	private static long gcd(long a, long b) {
		return b != 0 ? gcd(b, a % b) : a;
	}

	public Rational(long numerator, long denominator) {
		long d = gcd(numerator, denominator);
		this.numerator = numerator / d;
		this.denominator = denominator / d;
	}

	public Rational add(Rational secondRational) {
		long d = gcd(this.denominator, secondRational.denominator);
		long dd = this.denominator / d * secondRational.denominator;
		long a = this.numerator * (dd / this.denominator);
		long b = secondRational.numerator * (dd / secondRational.denominator);
		return new Rational(a + b, dd);
	}

	public Rational subtract(Rational secondRational) {
		long d = gcd(this.denominator, secondRational.denominator);
		long dd = this.denominator / d * secondRational.denominator;
		long a = this.numerator * (dd / this.denominator);
		long b = secondRational.numerator * (dd / secondRational.denominator);
		return new Rational(a - b, dd);
	}

	public Rational multiply(Rational secondRational) {
		return new Rational(this.numerator * secondRational.numerator, this.denominator * secondRational.denominator);
	}

	public Rational divide(Rational secondRational) {
		return new Rational(this.numerator * secondRational.denominator, this.denominator * secondRational.numerator);
	}

	@Override
	public String toString() {
		return denominator == 1 ? Long.toString(numerator) : numerator + "/" + denominator;
	}
}
