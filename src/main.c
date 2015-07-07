#include <pebble.h>

#define WAKEUP_RESON 0
#define WAKEUP_ID_KEY 0

Window *my_window;
static WakeupId s_wakeup_id;

static void tick_handler(struct tm *tick_time, TimeUnits changed) {
	// 5minute
	int minuts = tick_time->tm_min;
	if(minuts%5 == 0){
		vibes_short_pulse();
	}
}

static void wakeup_handler(WakeupId id, int32_t reson)
{
	vibes_short_pulse();
	time_t timestamp = time(NULL) + 10;
	s_wakeup_id = wakeup_schedule(timestamp, WAKEUP_RESON, true);
	persist_write_int(WAKEUP_ID_KEY, s_wakeup_id);
}

void handle_init(void) {
	my_window = window_create();

#ifdef PBL_SDK_3
	window_set_background_color(my_window, GColorRed);
#endif
	/* tick_timer_service_subscribe(MINUTE_UNIT, tick_handler); */

	time_t timestamp = time(NULL) + 10;
	s_wakeup_id = wakeup_schedule(timestamp, WAKEUP_RESON, true);
	persist_write_int(WAKEUP_ID_KEY, s_wakeup_id);

	wakeup_service_subscribe(wakeup_handler);

	window_stack_push(my_window, true);
}


void handle_deinit(void) {
	window_destroy(my_window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
