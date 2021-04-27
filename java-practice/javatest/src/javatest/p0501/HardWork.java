package javatest.p0501;

abstract class Employee {
	public abstract double earnings();
}

class YearWorker extends Employee {
	public double earnings() {
		return 50000.456;
	}
	// 重写earnings()方法
}

class MonthWorker extends Employee {
	public double earnings() {
		return 12 * 2300;
	}
	// 重写earnings()方法。
}

class WeekWorker extends Employee {
	public double earnings() {
		return 52 * 500;
	}
	// 重写earnings()方法。
}

class Company {
	Employee[] employee;
	double salaries = 0;

	Company(Employee[] employee) {
		this.employee = employee;
	}

	public double salariesPay() {
		salaries = 0;
		for (int i = 0; i < employee.length; i++) {
			salaries = salaries + employee[i].earnings();
		}
		// 计算salaries。
		return salaries;
	}
}

public class HardWork {
	public static void main(String args[]) {
		Employee[] employee = new Employee[20];
		for (int i = 0; i < employee.length; i++) {
			if (i % 3 == 0)
				employee[i] = new WeekWorker();
			else if (i % 3 == 1)
				employee[i] = new MonthWorker();
			else if (i % 3 == 2)
				employee[i] = new YearWorker();
		}
		Company company = new Company(employee);
		System.out.println("公司年工资总额:" + company.salariesPay());
	}
}
