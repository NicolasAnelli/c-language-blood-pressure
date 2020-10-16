#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "layout.h"
#include "warning.h"
#include "core.h"

#define SYSTEM_NAME "Medical History - Blood Pressure"

/** Screen header **/
void header(char* menu);

/** Main menu **/
void mainMenu();
void printMainMenu();

/** Add new measurement **/
void addNewMeasurementScreen();
void addNewMeasurementForm(int systolic, int diastolic, int year, int month, int day, int hour, int minute);

/** List all measures **/
void listAllMeasurementScreen();
void printMeasuresPage(int page, int per_page);

/** Auto tests **/
void triggerAutoTests();
void addFakeData();

/** Main program **/
History* __history;
int main() {

	__history = createHistory();

	mainMenu();
	clearScreen();

	return EXIT_SUCCESS;
}

/** Implementations **/

void header(char* menu) {
	filledLine();
	line(SYSTEM_NAME, 'C');
	line(menu, 'C');
	filledLine();
	printWarning();
}

void mainMenu() {

	char *opt = (char*)malloc(sizeof(char));

	while (1) {
		clearScreen();
		printMainMenu();
		printf("Choose your option: ");
		scanf(" %[^\n]", opt);

		switch(*opt) {

            case '1':
            	addNewMeasurementScreen();
                break;

            case '2':
            	listAllMeasurementScreen();
                break;

            case 'f': // Add fake data for testing
            	addFakeData();
            	break;

            case 'a': // Trigger auto test
            	triggerAutoTests();
            	break;

            case 'd': // Show current status of __history
            	printHistoryTests(__history);
            	printf("Type any to return: ");
            	scanf(" %[^\n]", opt);
            	break;

            case '0':
                free(opt);
                return;
		}
	}
}
void printMainMenu() {
	header("Main menu");
	line("1. Add new measurement", 'L');
	emptyLine();
	line("2. Show history", 'L');
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	line("0. Exit", 'L');
	emptyLine();
	filledLine();
}

void addNewMeasurementScreen() {

	time_t now;
	time(&now);
	struct tm *tm = localtime(&now);

	char *opt = (char*)malloc(sizeof(char));

	int systolic=12, diastolic=8;

	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;

	while(1) {

		clearScreen();
		addNewMeasurementForm(systolic, diastolic, year, month, day, hour, minute);

		printf("Choose your option: ");
		scanf(" %[^\n]", opt);

		switch(*opt) {

			case '1':
				clearScreen();
				addNewMeasurementForm(systolic, diastolic, year, month, day, hour, minute);
				printf("Type your blood pressure (dd/dd): ");
				scanf(" %d/%d", &systolic, &diastolic);
				break;

			case '2':
				clearScreen();
				addNewMeasurementForm(systolic, diastolic, year, month, day, hour, minute);
				printf("Type your date (YYYY/MM/DD HH:MI): ");
				scanf(" %d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
				break;

			case '3':
				if (systolic<=0 || diastolic <=0) {
					setWarning("Error: Check your blood pressure values!");
					break;
				}
				if (year<=2000 || month<1 || month >12 || day <1 || day > 31 || hour <0 || hour >23 || minute <0 || minute > 59) {
					setWarning("Error: Check your date!");
					break;
				}

				addNewMeasure(__history, createMeasure(systolic, diastolic,
						createDate(year, month, day, hour, minute)));

				setWarning("Measure successfully registered!");
//				return; // todo voltar pro menu ou não?

				break;
			case '0':
				free(opt);
				return;
			default:
				setWarning("Invalid option!");
		}
	}


}
void addNewMeasurementForm(int systolic, int diastolic, int year, int month, int day, int hour, int minute) {

	char *aux = (char*)malloc(80*sizeof(char));

	header("Add new measurement");
	sprintf(aux, "1. Blood Pressure:  %02d/%02d", systolic, diastolic);
	line(aux, 'L');
	emptyLine();
	sprintf(aux, "2. Date:  %04d/%02d/%02d %02d:%02d", year, month, day, hour, minute);
	line(aux, 'L');
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	line("3. Save", 'L');
	emptyLine();
	emptyLine();
	line("0. Back", 'L');
	emptyLine();
	filledLine();

	free(aux);
}

void listAllMeasurementScreen() {

	int page, min, max, per_page;
	char *opt = (char*)malloc(sizeof(char));

	per_page = 12;
	min = 0;
	max = countHistoryMeasures(__history) / per_page;

	page = min;

	while (1) {

		clearScreen();
		printMeasuresPage(page, per_page);
		printf("Choose your option: ");
		scanf(" %[^\n]", opt);

		switch(*opt) {

		case '1':
			if(page > min)
				page--;
			break;

		case '2':
			if(page < max)
				page++;
			break;

		case '0':
			free(opt);
			return;
		}
	}
}
void printMeasuresPage(int page, int per_page) {

	int i, p, start, end;
	char* aux = (char*)malloc(80*sizeof(char));
	Measure* m;

	i = 0;
	start = page * per_page;
	end = start + per_page;

	header("History");
	emptyLine();

	p = 0;
	for (i=start; i<end; i++) {
		m = findMeasureByPosition(__history, i);
		if (m) {
			sprintf(aux, " %3d. %s at %s", i, m->toString, m->date->toString);
			line(aux, 'L');
			p++;
		}
	}
	while(p<per_page) {
		emptyLine();
		p++;
	}

	emptyLine();
	line("1 - Anterior | Proxima - 2", 'C');
	line("0. Voltar", 'L');
	emptyLine();
	filledLine();

}

void triggerAutoTests() {

	clearScreen();

	printf("========= Triggering auto tests =========\n\n");

	printf("1. Creating date\n");
	printf("Date* date = createDate(2020, 15, 10, 22, 52); \n");
	Date* date = createDate(2020, 15, 10, 22, 52);
	printf("date->toString: %s \n\n", date->toString);

	printf("2. Creating measure\n");
	printf("Measure* measure = createMeasure(14, 10, date); \n");
	Measure* measure = createMeasure(14, 10, date);
	printf("measure->toString: %s \n", measure->toString);
	printf("measure->date->toString: %s \n\n", measure->date->toString);

	printf("3. Creating history\n");
	printf("History* history = createHistory(); \n");
	History* history = createHistory();
	printf("history->measure: %x \n", (int)history->measure);
	printf("history->next: %x \n", (int)history->next);
	printf("countHistoryMeasures(history): %d \n\n", countHistoryMeasures(history));

	printf("4. Print empty history\n");
	printf("printHistoryTests(history); \n");
	printHistoryTests(history);
	printf("\n");

	printf("5. Add measure to history\n");
	printf("addNewMeasure(history, measure); \n");
	addNewMeasure(history, measure);
	printf("\n");

	printf("6. Print history\n");
	printf("printHistoryTests(history); \n");
	printHistoryTests(history);
	printf("countHistoryMeasures(history): %d \n\n", countHistoryMeasures(history));
	printf("\n");

	printf("7. Add ANOTHER measure to history\n");
	printf("-- 12/8 at 2020/15/10 23:42\n");
	date = createDate(2020, 15, 10, 23, 42);
	measure = createMeasure(12, 8, date);
	addNewMeasure(history, measure);
	printf("\n");

	printf("8. Print history\n");
	printf("printHistory(history); \n");
	printHistoryTests(history);
	printf("countHistoryMeasures(history): %d \n\n", countHistoryMeasures(history));

	printf("9. Find measure by position 0\n");
	printf("Measure* m = findMeasureByPosition(history, 0); \n");
	Measure* m = findMeasureByPosition(history, 0);
	printf("m->toString: %s \n", m->toString);
	printf("m->date->toString: %s \n\n", m->date->toString);

	printf("10. Find measure by position 1\n");
	printf("Measure* m2 = findMeasureByPosition(history, 1); \n");
	Measure* m2 = findMeasureByPosition(history, 1);
	printf("m2->toString: %s \n", m2->toString);
	printf("m2->date->toString: %s \n\n", m2->date->toString);

	printf("10. Find measure by position 2\n");
	printf("Measure* m3 = findMeasureByPosition(history, 2); \n");
	Measure* m3 = findMeasureByPosition(history, 2);
	printf("m3: %x \n", (int)m3);


	printf("\nAll tests working!\n");
	printf("Type any to return: ");
	char *opcao = (char*)malloc(sizeof(char));
	scanf(" %[^\n]", opcao);
}
void addFakeData() {

	addNewMeasure(__history, createMeasure(12, 8, createDate(2020, 5, 5, 7, 10)));
	addNewMeasure(__history, createMeasure(12, 7, createDate(2020, 15, 5, 18, 30)));
	addNewMeasure(__history, createMeasure(12, 10, createDate(2020, 25, 5, 12, 40)));
	addNewMeasure(__history, createMeasure(12, 8, createDate(2020, 5, 6, 15, 42)));
	addNewMeasure(__history, createMeasure(14, 8, createDate(2020, 13, 6, 16, 57)));
	addNewMeasure(__history, createMeasure(12, 10, createDate(2020, 20, 6, 8, 00)));
	addNewMeasure(__history, createMeasure(18, 12, createDate(2020, 27, 6, 3, 23)));
	addNewMeasure(__history, createMeasure(10, 9, createDate(2020, 2, 6, 14, 2)));
	addNewMeasure(__history, createMeasure(12, 8, createDate(2020, 9, 7, 17, 4)));
	addNewMeasure(__history, createMeasure(14, 8, createDate(2020, 19, 7, 13, 44)));
	addNewMeasure(__history, createMeasure(14, 10, createDate(2020, 25, 7, 3, 32)));
	addNewMeasure(__history, createMeasure(12, 11, createDate(2020, 30, 7, 22, 57)));
	addNewMeasure(__history, createMeasure(12, 10, createDate(2020, 12, 8, 23, 00)));
	addNewMeasure(__history, createMeasure(7, 8, createDate(2020, 22, 8, 10, 23)));
	addNewMeasure(__history, createMeasure(10, 8, createDate(2020, 15, 9, 12, 43)));
	addNewMeasure(__history, createMeasure(12, 8, createDate(2020, 27, 9, 16, 18)));
	addNewMeasure(__history, createMeasure(12, 8, createDate(2020, 1, 10, 19, 37)));
	addNewMeasure(__history, createMeasure(15, 6, createDate(2020, 8, 10, 18, 32)));
	addNewMeasure(__history, createMeasure(12, 11, createDate(2020, 13, 10, 23, 58)));
	addNewMeasure(__history, createMeasure(14, 10, createDate(2020, 15, 10, 17, 20)));


	setWarning("Fake data added!");
}






















