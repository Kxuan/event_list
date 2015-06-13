#include "ontime.h"
#include <stdlib.h>
#include <signal.h>

EVENT_LIST_DEFINE(ontime);
event_list_ontime_t el_ontime = EVENT_LIST_INIT("time changed");

timer_t timerid;

static void sig_usr1_handler(int signum) {
	time_t now;
	time(&now);
	EVENT_LIST_FIRE(&el_ontime, now);
}
void time_init(void) {
	struct sigevent sevp = {
		.sigev_notify = SIGEV_SIGNAL,
		.sigev_signo = SIGUSR1
	};
	struct sigaction sig_sa = {
		.sa_handler = sig_usr1_handler
	};
	struct itimerspec timer_spec = {
		.it_value = {
			.tv_sec = 1
		},
		.it_interval = {
			.tv_sec = 1
		}
	};

	if (sigaction(SIGUSR1, &sig_sa, NULL)) {
		perror("sigaction");
		exit(1);
	}

	if (timer_create(CLOCK_REALTIME, &sevp, &timerid)) {
		perror("timer_create");	
		exit(1);
	}
	if (timer_settime(&timerid, 0, &timer_spec, NULL)) {
		perror("timer_settime");
		exit(1);
	}

}
