#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"
#include "event.h"



/* initalizes the calendar */
int 
init_calendar(const char *name, int days, 
  int (*comp_func) (const void *ptr1, const void *ptr2),
  void (*free_info_func) (void *ptr), Calendar ** calendar) {

	if (calendar && name && days >= 1) {

		(*calendar) = malloc(sizeof(Calendar));

		if (calendar) {

			(*calendar)->name = malloc(sizeof(char) * (strlen(name) + 1));
			
			if ((*calendar)->name) {

				strcpy((*calendar)->name, name);

				(*calendar)->events = calloc(days + 1, sizeof(Event *));

				(*calendar)->days = days;
				(*calendar)->total_events = 0;
				(*calendar)->comp_func = comp_func;
				(*calendar)->free_info_func = free_info_func;

				return SUCCESS;
			}
		} 
	}
	return FAILURE;
}

int
print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {

	Event *event;
	int i;

	if (calendar && output_stream) {

		if (print_all) {

			fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
			fprintf(output_stream, "Days: %d\n", calendar->days);
			fprintf(output_stream, "Total Events: %d\n\n", calendar->total_events);

		}

		fprintf(output_stream, "**** Events ****\n");
					
		event = calendar->events[1];
	
		if (calendar->total_events > 0) {	

			for (i = 1; i <= calendar->days; i++) {
		
				fprintf(output_stream, "Day %d\n", i);
				event = calendar->events[i];

				while (event) {
			
					fprintf(output_stream, "Event's Name: \"%s\", ", event->name);	
					fprintf(output_stream, "Start_time: %d, ", event->start_time);
					fprintf(output_stream, "Duration: %d\n", event->duration_minutes);

					event = event->next;
				}
			}
		}
		return SUCCESS;

	}
	return FAILURE;
}

/* adds an event to the calendar */
int
add_event(Calendar *calendar, const char *name, int start_time,
  int duration_minutes, void *info, int day) {

	Event *new_event, *curr_ptr, *prev_ptr;

	if (calendar && name && (start_time >= 0) && (start_time <= 2400)
	  && (start_time % 100 < 60) && duration_minutes > 0
	  && day >= 1 && day <= calendar->days) {

		if (find_event(calendar, name, NULL) == FAILURE) {

			new_event = malloc(sizeof(Event));
			new_event->name = malloc(sizeof(char) * (strlen(name) + 1));
			
			if (new_event && new_event->name) {

				strcpy(new_event->name, name);
				new_event->start_time = start_time;
				new_event->duration_minutes = duration_minutes;
				new_event->info = info;

				curr_ptr = calendar->events[day];
	
				/* if it is the first event assigned to the day */
				if (!curr_ptr) {
					calendar->events[day] = new_event;
					new_event->next = NULL;
				}
				else if (curr_ptr) {

					/* if the event will be added to the front */
					if (calendar->comp_func(curr_ptr, new_event) > 0) {

						calendar->events[day] = new_event;					
						new_event->next = curr_ptr;
	
					}
					else {

						prev_ptr = calendar->events[day];			
						curr_ptr = curr_ptr->next;
						prev_ptr->next = curr_ptr;

						while (curr_ptr && calendar->comp_func(curr_ptr, new_event) <= 0) {
	
							prev_ptr = curr_ptr;
							curr_ptr = curr_ptr->next;
		
						}

						new_event->next = curr_ptr;
						prev_ptr->next = new_event;	

					}
				}	
				calendar->total_events++;		
				return SUCCESS;
				
			}
		}
	}
	return FAILURE;
}

/* finds the event if present in the calendar */
int 
find_event(Calendar *calendar, const char *name, Event **event) {

	int i;
	Event *curr_ptr;

	if (calendar && name) {

		for (i = 1; i <= calendar->days; i++) {
			curr_ptr = calendar->events[i];

			while (curr_ptr && strcmp(curr_ptr->name, name)) {
				curr_ptr = curr_ptr->next;
			}

			if (curr_ptr) {

				if (event) {
					*event = curr_ptr;
				}
				return SUCCESS;
			}

		}

	}	
	return FAILURE;
}

int
find_event_in_day(Calendar *calendar, const char *name, int day,
  Event **event) {

	Event *curr_ptr;

	if (calendar && name) {

		if (event) {

			curr_ptr = calendar->events[day];
			
			while (curr_ptr && strcmp(curr_ptr->name, name)) {
				curr_ptr = curr_ptr->next;
			}

			if (curr_ptr) {

				*event = curr_ptr;
				return SUCCESS;
			}

		}
	}	
	return FAILURE;
}

/* removes event from calendar if found */
int
remove_event(Calendar *calendar, const char *name) {
	Event *curr_ptr, *prev_ptr;
	int i;

	if (calendar && name) {
	
		for (i = 1; i <= calendar->days; i++) {

			curr_ptr = calendar->events[i];

			/* if first event is being removed */
			if (curr_ptr && !strcmp(curr_ptr->name, name)) {

				calendar->events[i] = curr_ptr->next;	
				curr_ptr->next = NULL;

			}
			else {	/* if not the first event is being removed */

				while (curr_ptr && strcmp(curr_ptr->name, name)) {
					prev_ptr = curr_ptr;
					curr_ptr = curr_ptr->next;
				}				
		
				/* if curr_ptr is the event that matches the name */
				if (curr_ptr) {

					prev_ptr->next = curr_ptr->next;
					curr_ptr->next = NULL;

				}
			}

			if (curr_ptr && !strcmp(curr_ptr->name, name)) {

				free(curr_ptr->name);
				curr_ptr->name = NULL;

				if (curr_ptr->info && calendar->free_info_func) {
					calendar->free_info_func(curr_ptr->info);
				}

				curr_ptr->info = NULL;
				/* remove_event 
	 			* the free(curr_ptr) below is causing the core dump */
				free(curr_ptr);
				curr_ptr = NULL;

				(calendar->total_events)--;
				return SUCCESS;

			}
		}
	}	
	return FAILURE;
}

/* returns the info of an event */
void
*get_event_info(Calendar *calendar, const char *name) {

	Event *event = NULL;

	find_event(calendar, name, &event);

	if (event) {
		return event->info;
	}
	return NULL;
}

/* clears the entire calendar of all of its events */
int
clear_calendar(Calendar *calendar) {

	int i;
	
	if (calendar) {

		for (i = 1; i <= calendar->days; i++) {
			clear_day(calendar, i);
		}

		return SUCCESS;
	}
	return FAILURE;
}

/* removes all the events from a day */
int
clear_day(Calendar *calendar, int day) {

	Event *curr_ptr, *garb_ptr;

	if (calendar && day >= 1 && day <= calendar->days) {

		if (calendar->total_events > 0) {

			curr_ptr = calendar->events[day];

			while (curr_ptr) {
				
				garb_ptr = curr_ptr;
				curr_ptr = curr_ptr->next;

				free(garb_ptr->name);

				if (garb_ptr->info && calendar->free_info_func) {
					calendar->free_info_func(garb_ptr->info);
				}

				free(garb_ptr);
				garb_ptr = NULL;

				(calendar->total_events)--;			
			}
		}

		calendar->events[day] = NULL;
		return SUCCESS;
	}	
	return FAILURE;
}


/* frees all memory assigned to the calendar and its events */
int
destroy_calendar(Calendar *calendar) {

	if (calendar) {

		clear_calendar(calendar);

		free(calendar->events);
		calendar->events = NULL;
		free(calendar->name);
		calendar->name = NULL;
		free(calendar);		
		calendar = NULL;

		return SUCCESS;
	}
	return FAILURE;
}





