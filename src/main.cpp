#include <stdio.h>
#include <event.h>
#include <iostream>
#include <Windows.h>

Event event;

void on_stop(message_t msg) {
	Beep(750, 100);
	Beep(400, 100);
	event.state = Event::STATE_STOPPED;
}

void on_ping(message_t msg) {
	std::cout << "PINGED with " << msg.data << std::endl;
	message_t message = {"pong", "puter"};
	event.send(&message);
}

void on_pong(message_t msg) {
	std::cout << "PONGED with " << msg.data << std::endl;
	message_t message = {"ping", "frog"};
	event.send(&message);
}

int main (int argc, char * argv[]) {
	message_t message = {"ping", "frog"};

	event.connect("ping", (handler_p)&on_ping);
	event.connect("pong", (handler_p)&on_pong);
	event.connect("_stop", (handler_p)&on_stop);

	event.send(&message);

	return event.start();
}