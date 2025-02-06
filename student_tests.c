#include <stdio.h>
#include <stdlib.h>
#include "event.h"
#include "calendar.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/* Description here: This test checks ...  */
static int test1() {
	int days = 7;
	Calendar *calendar;

	if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {

		if (print_calendar(calendar, stdout, 1) == SUCCESS) {
			printf("before destroy\n");
			return destroy_calendar(calendar);
		}
	}

	return FAILURE;
}

static int test2() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);


	if (find_event(calendar, "event 1", &event) == SUCCESS) {

		if (find_event_in_day(calendar, "event 1", 1, &event) == SUCCESS) {
			if (find_event_in_day(calendar, "event 1", 2, &event) == FAILURE ) {
				destroy_calendar(calendar);
				printf("test2 success\n");
				return SUCCESS;
			}
		}
	}

	return FAILURE;
}

static int test3() {
	Calendar *calendar;
	Event *event;	
	printf("start of test3\n");
	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);
	printf("after init test3\n");
	add_event(calendar, "event 1", 0, 300, NULL, 1);
	printf("after adding event 1\n");
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	printf("after adding events\n");

	if (find_event(calendar, "event 1", NULL)) {
		printf("found event 1\n");
	}
	if (add_event(calendar, "event 1", 0, 300, NULL, 1) == SUCCESS) {
		return FAILURE;
	}
	printf("after first failure check\n");
	if (add_event(calendar, "event 3", 0, 300, NULL, 2) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, "event 2", 0, 300, NULL, 1) == SUCCESS) {
		return FAILURE;
	}
	printf("before destroy test3\n");
	destroy_calendar(calendar);
	printf("test3 success\n");
	return SUCCESS;
}

static int test4() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	if (remove_event(calendar, "event 2") == SUCCESS) {
		destroy_calendar(calendar);
		printf("test4 success\n");
		return SUCCESS;
	}
	return FAILURE;
}

static int test5() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);


	if (remove_event(calendar, "event 1") == SUCCESS) {
	
		if (remove_event(calendar, "event 3") == SUCCESS) {

			destroy_calendar(calendar);	
			printf("test5 success\n");
			return SUCCESS;
		}
	}
	return FAILURE;
}

static int test6() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);


	if (remove_event(calendar, "event 10") == FAILURE) {
	
		if (remove_event(calendar, "event 3") == SUCCESS) {
			print_calendar(calendar, stdout, 1);

			destroy_calendar(calendar);
	
			printf("test6 success\n");
			return SUCCESS;
		}
		
	}
	return FAILURE;
}

static int test7() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	print_calendar(calendar, stdout, 1);
	if (clear_calendar(calendar) == SUCCESS) {
	
		if (clear_calendar(NULL) == FAILURE) {
			print_calendar(calendar, stdout, 1);

			destroy_calendar(calendar);
	
			printf("test7 success\n");
			return SUCCESS;
		}
		
	}
	return FAILURE;
}

static int test8() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	print_calendar(calendar, stdout, 1);
	if (clear_day(calendar, 1) == SUCCESS) {
	
		if (clear_day(NULL, 3) == FAILURE) {
			if (clear_day(calendar, 1) == SUCCESS) {
				print_calendar(calendar, stdout, 1);

				destroy_calendar(calendar);
	
				printf("test8 success\n");
				return SUCCESS;
			}
		}
		
	}
	return FAILURE;
}

static int test9() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	if (add_event(calendar, "event 1", 0, 300, NULL, 1) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, "event 1", 0, 300, NULL, 3) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, "event 4", 0, 300, NULL, 4) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, "event 4", -1, 300, NULL, 3) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, NULL, 0, 300, NULL, 3) == SUCCESS) {
		return FAILURE;
	}
	if (add_event(calendar, "event 4", 2500, 300, NULL, 3) == SUCCESS) {
		return FAILURE;
	}



	destroy_calendar(calendar);
	printf("test9 success\n");
	return SUCCESS;
}

static int test10() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);

	if (remove_event(calendar, NULL) == SUCCESS) {
		return FAILURE;
	}
	if (remove_event(NULL, "event 1") == SUCCESS) {
		return FAILURE;
	}
	if (remove_event(calendar, "event 4") == SUCCESS) {
		return FAILURE;
	}
	if (remove_event(calendar, "event 3") == FAILURE) {
		return FAILURE;
	}
	if (remove_event(calendar, "event 3") == SUCCESS) {
		return FAILURE;
	}
	if (remove_event(calendar, "event 2") == FAILURE) {
		return FAILURE;
	}


	destroy_calendar(calendar);
	printf("test10 success\n");
	return SUCCESS;
}

static int test11() {
	Calendar *calendar;
	Event *event;	

	init_calendar("my calendar", 3, comp_minutes, NULL, &calendar);

	add_event(calendar, "event 1", 0, 300, NULL, 1);
	add_event(calendar, "event 2", 400, 500, NULL, 1);
	add_event(calendar, "event 3", 0, 300, NULL, 2);
	add_event(calendar, "event 4", 0, 300, NULL, 3);
	add_event(calendar, "event 5", 400, 500, NULL, 3);
	add_event(calendar, "event 6", 0, 300, NULL, 3);


	print_calendar(calendar, stdout, 0);
	if (clear_calendar(NULL) == SUCCESS) {
		return FAILURE;
	}
	if (clear_day(NULL, 1) == SUCCESS) {
		return FAILURE;
	}
	if (clear_day(calendar, 1) == FAILURE) {
		return FAILURE;
	}
	if (clear_day(calendar, 1) == FAILURE) {
		return FAILURE;
	}
	if (clear_calendar(calendar) == FAILURE) {
		return FAILURE;
	}
	if (clear_calendar(calendar) == FAILURE) {
		return FAILURE;
	}

	print_calendar(calendar, stdout, 0);
	destroy_calendar(calendar);
	printf("test11 success\n");
	return SUCCESS;
}

static int test12() {
	Calendar *calendar;
	Event *event;	

	if (init_calendar(NULL, 3, comp_minutes, NULL, &calendar) == SUCCESS) {
		return FAILURE;
	}
	if (init_calendar("calendar!", -1, comp_minutes, NULL, &calendar) == SUCCESS) {
		return FAILURE;
	}
	if (init_calendar("calendar !", 3, comp_minutes, NULL, &calendar) == FAILURE) {
		return FAILURE;
	}

	print_calendar(calendar, stdout, 1);
	destroy_calendar(calendar);
	return SUCCESS;
}

int main() {
   int result = SUCCESS;

	if (test1() == FAILURE) result = FAILURE;
	if (test2() == FAILURE) result = FAILURE;
	if (test3() == FAILURE) result = FAILURE;
	if (test4() == FAILURE) result = FAILURE;
	if (test5() == FAILURE) result = FAILURE;
	if (test6() == FAILURE) { result = FAILURE; }
	if (test7() == FAILURE) result = FAILURE;
	if (test8() == FAILURE) result = FAILURE;	

	if (test9() == FAILURE) result = FAILURE;
	if (test10() == FAILURE) result = FAILURE;
	if (test11() == FAILURE) result = FAILURE;
 	if (test12() == FAILURE) result = FAILURE;	

   if (result == FAILURE) {
		printf("exit_failure\n");
		exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
