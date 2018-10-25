#pragma once
#include <iostream>
#include <string>

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	static void printMessage(const char* message);
	static void printMessage(std::string message);
};

