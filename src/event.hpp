#include <Windows.h>
#include <deque>
#include <map>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#ifndef EVENT_H
#define EVENT_H
struct message_t {
	std::string type;
	std::string data;
};

typedef int (*handler_p)(message_t);
typedef std::vector<handler_p> HandlerList;
typedef std::unordered_map<std::string, HandlerList> HandlerMap;
typedef std::deque<message_t> queue_t;

class Event {
private:
	queue_t queue;
	HandlerMap listeners;

	void run();
	void parse_message(message_t *message);
protected:
public:
	static const int STATE_STOPPED = 0;
	static const int STATE_RUNNING = 1;

	int state;

	void send(message_t *message);
	bool connect(std::string type, handler_p handler);

	int start();
	int start(int *q);
	
	static BOOL ctrl_handler(DWORD type);
};

#endif /* EVENT_H */