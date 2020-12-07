#ifndef DATETIME_H
#define DATETIME_H

#define LANG_ENUS	0
#define LANG_PTBR	1

typedef struct __DATETIME{
	int weekDay;
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
} Datetime;


enum eWEEK_DAYS{
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

enum eMONTHS{
	JANUARY = 0,
	FEBRUARY,
	MARCH,
	APRIL,
	MAIO,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

extern const char months[12][2][11];
extern const char weekDays[7][2][20];

int getDateOnFormat	(char *format, char *response, char *actualDate, int lang);

void getDayOfWeek	(char *inputDate, char *output, const int contract, int lang);
void getMonth		(char *inputDate, char *output, const int contract, int lang);

#endif