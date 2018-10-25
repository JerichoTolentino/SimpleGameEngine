#include "Window.h"

#define MAXKEYS 349
#define MAXBUTTONS 20

bool * Window::keys = new bool[MAXKEYS];
bool * Window::mouseButtons = new bool[MAXBUTTONS];
double Window::centerX = 0;
double Window::centerY = 0;
double Window::mouseX = 0;
double Window::mouseY = 0;
double Window::deltaMouseX = 0;
double Window::deltaMouseY = 0;
double Window::prevTime = 0;
double Window::deltaTime = 0;
Window * Window::currWindow = nullptr;

Window::Window()
{
	this->windowWidth = 1280;
	this->windowHeight = 800;
	this->centerX = windowWidth / 2.0;
	this->centerY = windowHeight / 2.0;

	init();
}

Window::Window(int w, int h)
{
	this->windowWidth = w;
	this->windowHeight = h;
	this->centerX = windowWidth / 2.0;
	this->centerY = windowHeight / 2.0;

	init();
}


void Window::init()
{
	if (!glfwInit())
	{
		MessageHandler::printMessage("GLFW failed to initialize!\n");
		system("EXIT_FAILURE");
	}

	this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, "JTGameEngine", NULL, NULL);
	Window::currWindow = this; //a solution to visibility issues
	glfwMakeContextCurrent(this->window);
	glfwSetKeyCallback(this->window, key_callback);
	glfwSetCursorPosCallback(this->window, cursor_position_callback);
	glfwSetMouseButtonCallback(this->window, mouse_button_callback);
	glfwSetScrollCallback(this->window, scroll_callback);
	glfwSetWindowSizeCallback(this->window, window_size_callback);

	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowPos(this->window, 0, 0);
	
	mouseX = this->windowWidth / 2.0f;
	mouseY = this->windowHeight / 2.0f;

	glClearColor(0.0f, 0.4f, 0.6f, 0.7f);

	for (int i = 0; i < MAXKEYS; i++)
	{
		keys[i] = false;
	}

	for (int i = 0; i < MAXBUTTONS; i++)
	{
		mouseButtons[i] = false;
	}

	if (glewInit() != GLEW_OK)
	{
		MessageHandler::printMessage("Failed to initialized GLEW!\n");
		system("EXIT_FAILURE");
	}
}

Window::~Window()
{
	//delete this->window; No need for this... glfw does it for us apparently
	glfwTerminate(); //turns off ALL of glfw! Need to init again before usage
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
	glfwSwapBuffers(this->window);
	glfwPollEvents();

	//std::cout << "mouseX: " << mouseX << " mouseY: " << mouseY << " --- prevMouseX: " << prevMouseX << " prevMouseY: " << prevMouseY << std::endl;

	deltaMouseX = mouseX - centerX;
	deltaMouseY = mouseY - centerY;

	double time = glfwGetTime();
	deltaTime = time - prevTime;
	prevTime = time;
}

double Window::getTimeFactor() const
{
	return deltaTime;
}

bool Window::isClosed() const
{
	return glfwWindowShouldClose(this->window) == 1;
}

void Window::forceClose()
{
	glfwTerminate();
}

void Window::resize(int w, int h)
{
	this->windowWidth = w;
	this->windowHeight = h;
}

bool Window::isKeyDown(int key) const
{
	return keys[key];
}

bool Window::isKeyUp(int key) const
{
	return !keys[key];
}

bool Window::isMouseButtonDown(int button) const
{
	return mouseButtons[button];
}

bool Window::isMouseButtonUp(int button) const
{
	return !mouseButtons[button];
}

void Window::getMousePos(double &x, double &y) const
{
	x = mouseX;
	y = mouseY;
}

void Window::getDeltaMousePos(double & x, double & y) const
{
	x = deltaMouseX;
	y = deltaMouseY;
	glfwSetCursorPos(this->window, centerX, centerY);
}

void Window::getWindowSize(int &w, int &h) const
{
	w = this->windowWidth;
	h = this->windowHeight;
}

void Window::checkKeys(int key, int action)
{
	if (key < 0)
	{
		MessageHandler::printMessage("Unknown key pressed!\n");
	}
	else
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Window::checkMouse(double x, double y)
{
	mouseX = x;
	mouseY = y;
}

void Window::checkMouseButtons(int button, int action)
{
	if (button > MAXBUTTONS)
	{
		MessageHandler::printMessage("Unknown mouse button pressed!\n");
	}
	else
	{
		if (action == GLFW_PRESS)
			mouseButtons[button] = true;
		if (action == GLFW_RELEASE)
			mouseButtons[button] = false;
	}
}

void Window::checkScrollWheel(double xoff, double yoff)
{
	//std::cout << "Xoff: " << xoff << " Yoff: " << yoff << std::endl;
}

void Window::windowResize(GLFWwindow* window, int width, int height)
{
	if (Window::currWindow != nullptr)
	{
		Window::currWindow->resize(width, height);
		MessageHandler::printMessage("Resized to: (" + std::to_string(width) + "," + std::to_string(height) + ")\tMembers: (" + std::to_string(Window::currWindow->windowWidth) + "," + std::to_string(Window::currWindow->windowHeight) + ")\n");
	}
	else
	{
		MessageHandler::printMessage("ERROR: currWindow pointer is null!\n");
		system("PAUSE");
	}
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window::checkKeys(key, action);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Window::checkMouse(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Window::checkMouseButtons(button, action);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Window::checkScrollWheel(xoffset, yoffset);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	Window::windowResize(window, width, height);
}