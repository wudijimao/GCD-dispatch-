#pragma once
#include<Windows.h>
#define GLEW_STATIC
#include <GL\glew.h>

struct GLColor {
	BYTE r = '\0';
	BYTE g = '\0';
	BYTE b = '\0';
	BYTE a = '\0';
};
void creatFramBuf() {
	GLuint colorBuf;
	glGenRenderbuffers(1, &colorBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, colorBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_SRGB8_ALPHA8, 100, 100);
	GLuint frameBuf;
	glGenFramebuffers(1, &frameBuf);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuf);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuf);

	int ret = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GLColor piexls[100 * 100];
	if (ret == GL_FRAMEBUFFER_COMPLETE)
	{
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glReadPixels(0, 0, 100, 100, GL_RGBA, GL_UNSIGNED_BYTE, piexls);
	}
}
class GLHelper
{
public:
	GLHelper();
	~GLHelper();
	static bool winInit(HWND hWnd);
	static bool init();
private:

};

GLHelper::GLHelper()
{
}

GLHelper::~GLHelper()
{
}

bool GLHelper::winInit(HWND hWnd) {
	//windows
	HDC hdc;
	hdc = ::GetDC(hWnd);
	int bits = 32;
	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	int piexelFormat = ChoosePixelFormat(hdc, &pfd);
	if (!SetPixelFormat(hdc, piexelFormat, &pfd)) {
		return false;
	}

	HGLRC context = wglCreateContext(hdc);
	if (!wglMakeCurrent(hdc, context)) {
		return false;
	}
	::ReleaseDC(hWnd, hdc);//һ��Ҫ�ͷž��
	return init();
}

bool GLHelper::init() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		return false;
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return true;
}