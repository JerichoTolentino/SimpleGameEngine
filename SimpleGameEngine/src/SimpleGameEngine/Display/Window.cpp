#include "sgepch.h"
#include "Window.h"

#include "DisplayException.h"

#define MAXKEYS 349
#define MAXBUTTONS 20

using namespace SimpleGameEngine::Events;

namespace SimpleGameEngine::Display
{
	Window::Window()
	{
	}

	Window::Window(int w, int h)
	{
		this->m_width = w;
		this->m_height = h;
		this->m_centerX = m_width / 2.0;
		this->m_centerY = m_height / 2.0;
		this->m_keys = new bool[MAXKEYS]();
		this->m_mouseButtons = new bool[MAXBUTTONS]();

		init();
	}

	Window::~Window()
	{
		//delete this->m_window; No need for this... glfw does it for us apparently
		glfwTerminate(); //turns off ALL of glfw! Need to init again before usage
	}



	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()
	{
		glfwSwapBuffers(this->m_window);
		glfwPollEvents();

		// Calculate mouse position deltas
		m_deltaMouseX = m_mouseX - m_centerX;
		m_deltaMouseY = m_mouseY - m_centerY;

		// Calculate time delta
		double time = glfwGetTime();
		m_deltaTime = time - m_prevTime;
		m_prevTime = time;
	}

	void Window::resize(int w, int h)
	{
		this->m_width = w;
		this->m_height = h;

		glViewport(0, 0, w, h);

		SGE_CORE_TRACE("Resized window to {0}x{1}", w, h);

		// Dispatch resize event
		WindowResizeEvent e(w, h);
		for (auto & listener : m_eventListeners)
		{
			listener->onWindowResized(e);
		}
	}

	void Window::forceClose() const
	{
		SGE_CORE_TRACE("Forcing window to close...");
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
		//glfwTerminate();
	}

	void Window::addWindowEventListener(IWindowEventListener * listener)
	{
		m_eventListeners.push_back(listener);
	}



	bool Window::isClosed() const
	{
		return glfwWindowShouldClose(this->m_window) == GLFW_TRUE;
	}

	bool Window::isKeyDown(int key) const
	{
		return m_keys[key];
	}

	bool Window::isMouseButtonDown(int button) const
	{
		return m_mouseButtons[button];
	}

	void Window::getMousePos(double & x, double & y) const
	{
		x = m_mouseX;
		y = m_mouseY;
	}

	void Window::getDeltaMousePos(double & x, double & y) const
	{
		x = m_deltaMouseX;
		y = m_deltaMouseY;
		glfwSetCursorPos(this->m_window, m_centerX, m_centerY);
	}

	void Window::getWindowSize(int &w, int &h) const
	{
		w = this->m_width;
		h = this->m_height;
	}

	double Window::getTimeFactor() const
	{
		return m_deltaTime;
	}



	void Window::init()
	{
		// Initialize GLFW
		if (!glfwInit())
		{
			throw DisplayException("GLFW failed to initialize.");
		}

		// Initialize GLFW m_window
		this->m_window = glfwCreateWindow(this->m_width, this->m_height, "SimpleGameEngine", NULL, NULL);
		glfwSetWindowUserPointer(this->m_window, this);
		glfwMakeContextCurrent(this->m_window);

		SGE_CORE_INFO("GLFW Version: {0}", glfwGetVersionString());

		// Set callbacks
		glfwSetKeyCallback(this->m_window, key_callback);
		glfwSetCursorPosCallback(this->m_window, cursor_position_callback);
		glfwSetMouseButtonCallback(this->m_window, mouse_button_callback);
		glfwSetScrollCallback(this->m_window, scroll_callback);
		glfwSetWindowSizeCallback(this->m_window, window_size_callback);

		// Set m_window configuration
		glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//glfwSetInputMode(this->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Center mouse
		m_mouseX = this->m_width / 2.0f;
		m_mouseY = this->m_height / 2.0f;

		glClearColor(0.0f, 0.4f, 0.6f, 0.7f);

		// Initialize GLEW
		if (glewInit() != GLEW_OK)
		{
			throw DisplayException("Failed to initialized GLEW.");
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglDebugCallback, this);

		SGE_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}



	void Window::openglDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
	{
		const Window * w = static_cast<const Window*>(userParam);

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			SGE_CORE_FATAL("[OpenGL Fatal Error]: ({0}) {1}", id, message);
			w->forceClose();
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			SGE_CORE_ERROR("[OpenGL Error]: ({0}) {1}", id, message);
			break;

		case GL_DEBUG_SEVERITY_LOW:
			SGE_CORE_WARNING("[OpenGL Warning]: ({0}) {1}", id, message);
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			SGE_CORE_TRACE("[OpenGL]: ({0}) {1}", id, message);
			break;
		}
			
	}



	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window * userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (key < 0)
		{
			throw DisplayException("Unknown key pressed.");
		}
		else
		{
			if (action == GLFW_PRESS)
				userWindow->m_keys[key] = true;
			if (action == GLFW_RELEASE)
				userWindow->m_keys[key] = false;
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window * userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		userWindow->m_mouseX = xpos;
		userWindow->m_mouseY = ypos;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window * userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (button > MAXBUTTONS)
		{
			throw DisplayException("Unknown mouse button pressed.");
		}
		else
		{
			if (action == GLFW_PRESS)
				userWindow->m_mouseButtons[button] = true;
			if (action == GLFW_RELEASE)
				userWindow->m_mouseButtons[button] = false;
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		// TODO: Implement this.
	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Window * userWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
		
		userWindow->resize(width, height);
	}
}
