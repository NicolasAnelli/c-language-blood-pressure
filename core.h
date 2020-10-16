/*
 * core.h
 *
 *  Created on: Oct 15, 2020
 *      Author: nicolasanelli
 */

#ifndef CORE_H_
#define CORE_H_

typedef struct Date {
	int day;
	int month;
	int year;
	int hour;
	int minute;
	char toString[16];
} Date;

typedef struct Measure {
	short systolic;
	short diastolic;
	char toString[6];
	struct Date* date;
} Measure;


typedef struct History {
	struct Measure* measure;
	struct History* next;
} History;



Date* createDate(int year, int month, int day, int hour, int minute) {

	Date* date = (Date*)malloc(sizeof(Date));
	date->year = year;
	date->month = month;
	date->day = day;
	date->hour = hour;
	date->minute = minute;

	sprintf(date->toString, "%04d/%02d/%02d %02d:%02d", date->year, date->month, date->day, date->hour, date->minute);

	return date;
}

Measure* createMeasure(int systolic, int diastolic, Date* date) {

	Measure* measure = (Measure*)malloc(sizeof(Measure));
	measure->systolic = systolic;
	measure->diastolic = diastolic;
	measure->date = date;

	sprintf(measure->toString, "%02d/%02d", measure->systolic, measure->diastolic);

	return measure;
}

History* createHistory() {

	History* history = (History*)malloc(sizeof(History));
	history->measure = NULL;
	history->next = NULL;

	return history;
}

int countHistoryMeasures(History* history) {

	if (history->next) {
		return countHistoryMeasures(history->next) + 1;
	}
	if (history->measure) {
		return 1;
	}
	return 0;
}

void addNewMeasure(History* history, Measure* measure) {

	if (!history->measure) {
		history->measure = measure;
		return;
	}

	if (!history->next) {
		history->next = createHistory();
	}
	addNewMeasure(history->next, measure);
}

Measure* findMeasureByPosition(History* history, int position) {

	History* aux;
	int i = 0;
	aux = history;

	while (i < position) {
		if (aux->next) {
			aux = aux->next;
			i++;
		} else {
			return NULL;
		}
	}
	return aux->measure;
}

void printHistoryTests(History* history) {

	if (history->measure) {
		printf(". History: %s at %s \n", history->measure->toString, history->measure->date->toString);
	}
	if (history->next) {
		printHistoryTests(history->next);
	}
}
#endif /* CORE_H_ */

















