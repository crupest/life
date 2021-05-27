package javatest.e0702;

import java.util.*;
import java.time.*;
import java.time.format.DateTimeFormatter;

public class Main {
	public static void main(String[] args) {
		try (Scanner scanner = new Scanner(System.in)) {
			LocalDateTime birthday = LocalDate.parse(scanner.nextLine(), DateTimeFormatter.ISO_DATE).atStartOfDay();
			LocalDateTime now = LocalDate.now().atStartOfDay();
			System.out.println("你的生日距今天" + Duration.between(birthday, now).toDays() + "天！");
		}
	}
}
