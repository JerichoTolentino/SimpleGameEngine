#include "MessageHandler.h"



MessageHandler::MessageHandler()
{
}


MessageHandler::~MessageHandler()
{
}

void MessageHandler::printMessage(const char * message)
{
	std::cout << message << "\n";
}

void MessageHandler::printMessage(std::string message)
{
	MessageHandler::printMessage(message.c_str());
}