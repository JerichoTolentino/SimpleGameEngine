#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>

namespace SimpleGameEngine::Display
{
	class Window
	{
	private:
		GLFWwindow * m_window;
		int m_width;
		int m_height;
		double m_prevTime, m_deltaTime;
		double m_centerX, m_centerY;
		double m_mouseX, m_mouseY;
		double m_deltaMouseX, m_deltaMouseY;
		bool * m_mouseButtons;
		bool * m_keys;



	public:
		/// <summary>
		/// Initializes a new instance of a <see cref="Window"/>.
		/// </summary>
		Window();

		/// <summary>
		/// Initializes a new instance of a <see cref="Window"/>.
		/// </summary>
		/// <param name="w">The width.</param>
		/// <param name="h">The height.</param>
		Window(int w, int h);

		/// <summary>
		/// Destroys this window.
		/// </summary>
		~Window();



		/// <summary>
		/// Clears the contents of this window.
		/// </summary>
		void clear();

		/// <summary>
		/// Updates the contents of this window and its state.
		/// </summary>
		void update();

		/// <summary>
		/// Resizes this window.
		/// </summary>
		/// <param name="w">The new width.</param>
		/// <param name="h">The new height.</param>
		void resize(int w, int h);

		/// <summary>
		/// Forces this window to close.
		/// </summary>
		void forceClose() const;



		/// <summary>
		/// Checks if this window is closed.
		/// </summary>
		/// <returns></returns>
		bool isClosed() const;

		/// <summary>
		/// Checks if a key is pressed.
		/// </summary>
		/// <param name="key">The key code.</param>
		/// <returns></returns>
		bool isKeyDown(int key) const;

		/// <summary>
		/// Checks if a mouse button is pressed.
		/// </summary>
		/// <param name="button">The button code.</param>
		/// <returns></returns>
		bool isMouseButtonDown(int button) const;

		/// <summary>
		/// Gets the current mouse position.
		/// </summary>
		/// <param name="x">The mouse x-coordinate.</param>
		/// <param name="y">The mouse y-coordinate.</param>
		void getMousePos(double & x, double & y) const;

		/// <summary>
		/// Gets the delta mouse position since last update.
		/// </summary>
		/// <param name="x">The delta x-coordinate.</param>
		/// <param name="y">The delta y-coordinate.</param>
		void getDeltaMousePos(double & x, double & y) const;

		/// <summary>
		/// Gets the size of this window.
		/// </summary>
		/// <param name="w">The window width.</param>
		/// <param name="h">The window height.</param>
		void getWindowSize(int & w, int & h) const;

		/// <summary>
		/// Gets the amount of time that has passed since last update.
		/// </summary>
		/// <returns></returns>
		double getTimeFactor() const;



		/// <summary>
		/// Callback function that OpenGL calls when an error occurs.
		/// </summary>
		static void APIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);



	private:

		/// <summary>
		/// Initializes this window.
		/// </summary>
		/// <exception cref="DisplayException"></exception>
		void init();

		/// The below function callbacks do not conform to the C++17 standards
		/// This leads to a compiler error when trying to pass these as function pointers to glfwSet...Callback() functions.
		/// For now, just set in project settings:
		/// Project Properties -> C/C++ -> Language -> Conformance mode -> No

		/// <summary>
		/// Callback for when a key is pressed.
		/// Updates the current state of the keys.
		/// </summary>
		/// <exception cref="DisplayException"></exception>
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/// <summary>
		/// Callback for when the cursor position changes.
		/// Updates the current position of the mouse.
		/// </summary>
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		/// <summary>
		/// Callback for when a mouse button is pressed.
		/// Updates the current state of the mouse buttons.
		/// </summary>
		/// <exception cref="DisplayException"></exception>
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		/// <summary>
		/// Callback for when the scroll wheel is moved.
		/// Currently does nothing.
		/// </summary>
		friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		/// <summary>
		/// Callback for when the window is resized.
		/// Resizes the current window.
		/// </summary>
		friend static void window_size_callback(GLFWwindow* window, int width, int height);
	};
}
