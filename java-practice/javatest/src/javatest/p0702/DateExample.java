package javatest.p0702;

import java.util.*;
import java.time.*;

import javax.swing.JOptionPane;

public class DateExample {
	public static void main(String args[]) {
		String str = JOptionPane.showInputDialog("�����һ�����ڵ����:");
		int yearOne = Integer.parseInt(str);
		str = JOptionPane.showInputDialog("���������·�:");
		int monthOne = Integer.parseInt(str);
		str = JOptionPane.showInputDialog("������·ݵ�����:");
		int dayOne = Integer.parseInt(str);
		str = JOptionPane.showInputDialog("����ڶ������ڵ����:");
		int yearTwo = Integer.parseInt(str);
		str = JOptionPane.showInputDialog("���������·�:");
		int monthTwo = Integer.parseInt(str);
		str = JOptionPane.showInputDialog("������·ݵ�����:");
		int dayTwo = Integer.parseInt(str);
		Calendar calendar = Calendar.getInstance(); // ��ʼ����������
		calendar.set(yearOne, monthOne, dayOne); // ��calendar��ʱ������ΪyearOne��monthOne��dayOne��
		long timeOne = calendar.getTimeInMillis(); // calendar��ʾ��ʱ��ת���ɺ���
		calendar.set(yearTwo, monthTwo, dayTwo); // ��calendar��ʱ������ΪyearTwo��monthTwo��dayTwo��
		long timeTwo = calendar.getTimeInMillis(); // calendar��ʾ��ʱ��ת���ɺ��롣
		Date date1 = new Date(timeOne); // ��timeOne����������date1
		Date date2 = new Date(timeTwo); // ��timeTwo����������date2
		if (date2.equals(date1)) {
			System.out.println("�������ڵ��ꡢ�¡�����ȫ��ͬ");
		} else if (date2.after(date1)) {
			System.out.println("������ĵڶ������ڴ��ڵ�һ������");
		} else if (date2.before(date1)) {
			System.out.println("������ĵڶ�������С�ڵ�һ������");
		}
		long days = Duration.between(date1.toInstant(), date2.toInstant()).toDays();// �������������������
		System.out.println(yearOne + "��" + monthOne + "��" + dayOne + "�պ�" + yearTwo + "��" + monthTwo + "��" + dayTwo
				+ "���" + days + "��");
	}
}
