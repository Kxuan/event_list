#include "ontime.h"
#include <time.h>
#include <signal.h>

static int running = 1;
void print_date(void *data, time_t now) {
	struct tm *lt = localtime(&now);
	printf("%s: %04d-%02d-%02d\n", (char *)data, lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday);
}
void print_time(void *data, time_t now) {
	struct tm *lt = localtime(&now);
	printf("%s: %02d:%02d:%02d\n", (char *)data, lt->tm_hour, lt->tm_min, lt->tm_sec);
}

void sig_int_handler(int signum) {
	running = 0;
}
int main(void) {
	time_init();
	el_ontime_attach(&el_ontime, print_date, "date");
	el_ontime_attach(&el_ontime, print_time, "time");
	signal(SIGINT, sig_int_handler);
	while(running)
		pause();

	return 0;
}
