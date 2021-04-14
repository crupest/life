package javatest.p0303;

import javatest.p0303.sub.*;

class SunRise {
	public static void main(String args[]) {
		SquareEquation equation = new SquareEquation(4, 5, 1);
		equation.getRoots();
		equation.setCoefficient(-3, 4, 5);
		equation.getRoots();
	}
}
