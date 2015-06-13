Event List
===================
An event list library. Help for multi callback.

How to
---
First of all, we need to create an event list:

 1. Header file (.h)
	 1.1. Define your callback function
			 ``` typedef void (*event_callback) (void *data);```
	1.2. Define the event list prototype
			```EVENT_LIST_PROTO(NAME, event_callback)```
	1.3. Extern the Event List in header file (.h)
			```extern event_list_NAME_t el_test;```

 2. Source file (.c)
	 2.1. Define event list functions
			 ```EVENT_LIST_DEFINE(NAME)```
	  2.2. Initialize event list
			  ```event_list_NAME_t el_test = EVENT_LIST_INIT("event list for test");```

Then use it.

 - attach event handle.
	`el_NAME_attach(&el_test, my_callback, NULL);`
	`my_callback` is an user-defined callback function
	
 - fire the event
	 - if the callback function has extra arguments
	 `EVENT_LIST_FIRE(&el_test, ARG1, ARG2);`
	 - if there is no extra argument in callback function
	 ` EVENT_LIST_CALL(&el_test);`
Note
---
Event list is not thread-safe!
Author
---
iXuan <kxuanobj@gmail.com>

License
---
MIT

