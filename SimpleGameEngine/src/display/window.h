#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include "../utils/MessageHandler.h"

class Window
{
private:
	GLFWwindow *window;
	static Window *currWindow;
	int windowWidth, windowHeight;
	static double centerX, centerY;
	static double mouseX, mouseY;
	static double deltaMouseX, deltaMouseY;
	static bool *keys;
	static bool *mouseButtons;
	static double prevTime, deltaTime;
public:
	Window();
	~Window();

	Window(int w, int h);

	void resize(int w, int h);
	void clear();
	void update();
	bool isClosed() const;
	void forceClose();
	bool isKeyDown(int key) const;
	bool isKeyUp(int key) const;
	bool isMouseButtonDown(int button) const;
	bool isMouseButtonUp(int button) const;
	void getMousePos(double &x, double &y) const;
	void getDeltaMousePos(double &x, double &y) const;
	void getWindowSize(int &w, int &h) const;
	double getTimeFactor() const;
private:
	void init();
	static void checkKeys(int key, int action);
	static void checkMouse(double x, double y);
	static void checkMouseButtons(int button, int action);
	static void checkScrollWheel(double xoff, double yoff);
	static void windowResize(GLFWwindow *window, int width, int height);
private:
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	friend static void window_size_callback(GLFWwindow* window, int width, int height);
};

