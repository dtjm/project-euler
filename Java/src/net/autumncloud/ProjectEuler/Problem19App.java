package net.autumncloud.ProjectEuler;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class Problem19App {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		// Keep track of number of Sundays
		int sundaysOnFirstOfTheMonthCount = 0;
		
		// Create a date object on 1 Jan 1901
		GregorianCalendar cal = new GregorianCalendar(1901, 0, 1);
		
		// Create a date object for 31 Dec 2000
		GregorianCalendar end = new GregorianCalendar(2000, 11, 31);
		
		// Loop over the date object and count the number of Sundays that landed on the first of the month
		// Stop when we get to 31 Dec 2000
		while( cal.compareTo( end ) < 0 ) {
			
			System.out.println( cal );
			
			if( cal.get( Calendar.DAY_OF_MONTH ) == 1	// Is it the 1st of the month? 
					&& cal.get( Calendar.DAY_OF_WEEK ) == Calendar.SUNDAY ) {	// Is it Sunday?
				sundaysOnFirstOfTheMonthCount++;		// If so, then increment the counter
			}
			
			// Add 1 day to the calendar
			cal.add(Calendar.DAY_OF_MONTH, 1);			
		}
		
		// Print out the count of days
		System.out.println( sundaysOnFirstOfTheMonthCount +  " Sundays on the first of the month" );
		
	}

}
