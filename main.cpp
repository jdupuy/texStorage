////////////////////////////////////////////////////////////////////////////////
// \author   Jonathan Dupuy
//
////////////////////////////////////////////////////////////////////////////////
// GL libraries
#include "glew.hpp"
#include "GL/freeglut.h"

// Standard librabries
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

////////////////////////////////////////////////////////////////////////////////
// Global variables
//
////////////////////////////////////////////////////////////////////////////////

// From tables 3.12 and 3.14(section 3.9.3) of OpenGL4.2 specs
const GLenum internalFormats[] = {
	// RED
	GL_R8,
	GL_R8_SNORM,
	GL_R16,
	GL_R16_SNORM,
	GL_R16F,
	GL_R32F,
	GL_R8I,
	GL_R8UI,
	GL_R16I,
	GL_R16UI,
	GL_R32I,
	GL_R32UI,
	GL_COMPRESSED_RED,
	GL_COMPRESSED_RED_RGTC1,
	GL_COMPRESSED_SIGNED_RED_RGTC1,

	// RG
	GL_RG8,
	GL_RG8_SNORM,
	GL_RG16,
	GL_RG16_SNORM,
	GL_RG16F,
	GL_RG32F,
	GL_RG8I,
	GL_RG8UI,
	GL_RG16I,
	GL_RG16UI,
	GL_RG32I,
	GL_RG32UI,
	GL_COMPRESSED_RG,
	GL_COMPRESSED_RG_RGTC2,
	GL_COMPRESSED_SIGNED_RG_RGTC2,

	// RGB
	GL_R3_G3_B2,
	GL_RGB4,
	GL_RGB5,
	GL_RGB8,
	GL_RGB8_SNORM,
	GL_RGB10,
	GL_RGB12,
	GL_RGB16,
	GL_RGB16_SNORM,
	GL_SRGB8,
	GL_RGB16F,
	GL_RGB32F,
	GL_R11F_G11F_B10F,
	GL_RGB9_E5,
	GL_RGB8I,
	GL_RGB8UI,
	GL_RGB16I,
	GL_RGB16UI,
	GL_RGB32I,
	GL_RGB32UI,
	GL_COMPRESSED_RGB,
	GL_COMPRESSED_SRGB,
/*		GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
	GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,*/

	// RGBA
	GL_RGBA2,
	GL_RGBA4,
	GL_RGB5_A1,
	GL_RGBA8,
	GL_RGBA8_SNORM,
	GL_RGB10_A2,
	GL_RGB10_A2UI,
	GL_RGBA12,
	GL_RGBA16,
	GL_RGBA16_SNORM,
	GL_SRGB8_ALPHA8,
	GL_RGBA16F,
	GL_RGBA32F,
	GL_RGBA8I,
	GL_RGBA8UI,
	GL_RGBA16I,
	GL_RGBA16UI,
	GL_RGBA32I,
	GL_RGBA32UI,
	GL_COMPRESSED_RGBA,
	GL_COMPRESSED_SRGB_ALPHA/*,
	GL_COMPRESSED_RGBA_BPTC_UNORM,
	GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM*/
};

	const GLchar* internalFormatsStr[] = {
	// RED
	"GL_R8",
	"GL_R8_SNORM",
	"GL_R16",
	"GL_R16_SNORM",
	"GL_R16F",
	"GL_R32F",
	"GL_R8I",
	"GL_R8UI",
	"GL_R16I",
	"GL_R16UI",
	"GL_R32I",
	"GL_R32UI",
	"GL_COMPRESSED_RED",
	"GL_COMPRESSED_RED_RGTC1",
	"GL_COMPRESSED_SIGNED_RED_RGTC1",

	// RG
	"GL_RG8",
	"GL_RG8_SNORM",
	"GL_RG16",
	"GL_RG16_SNORM",
	"GL_RG16F",
	"GL_RG32F",
	"GL_RG8I",
	"GL_RG8UI",
	"GL_RG16I",
	"GL_RG16UI",
	"GL_RG32I",
	"GL_RG32UI",
	"GL_COMPRESSED_RG",
	"GL_COMPRESSED_RG_RGTC2",
	"GL_COMPRESSED_SIGNED_RG_RGTC2",

	// RGB
	"GL_R3_G3_B2",
	"GL_RGB4",
	"GL_RGB5",
	"GL_RGB8",
	"GL_RGB8_SNORM",
	"GL_RGB10",
	"GL_RGB12",
	"GL_RGB16",
	"GL_RGB16_SNORM",
	"GL_SRGB8",
	"GL_RGB16F",
	"GL_RGB32F",
	"GL_R11F_G11F_B10F",
	"GL_RGB9_E5",
	"GL_RGB8I",
	"GL_RGB8UI",
	"GL_RGB16I",
	"GL_RGB16UI",
	"GL_RGB32I",
	"GL_RGB32UI",
	"GL_COMPRESSED_RGB",
	"GL_COMPRESSED_SRGB",
/*		"GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
	"GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,*/

	// RGBA
	"GL_RGBA2",
	"GL_RGBA4",
	"GL_RGB5_A1",
	"GL_RGBA8",
	"GL_RGBA8_SNORM",
	"GL_RGB10_A2",
	"GL_RGB10_A2UI",
	"GL_RGBA12",
	"GL_RGBA16",
	"GL_RGBA16_SNORM",
	"GL_SRGB8_ALPHA8",
	"GL_RGBA16F",
	"GL_RGBA32F",
	"GL_RGBA8I",
	"GL_RGBA8UI",
	"GL_RGBA16I",
	"GL_RGBA16UI",
	"GL_RGBA32I",
	"GL_RGBA32UI",
	"GL_COMPRESSED_RGBA",
	"GL_COMPRESSED_SRGB_ALPHA"/*,
	"GL_COMPRESSED_RGBA_BPTC_UNORM",
	"GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM"*/
};


////////////////////////////////////////////////////////////////////////////////
// Functions
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Convert GL error code to string
static GLvoid gl_debug_message_callback(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar* message,
                                        GLvoid* userParam)
{
	GLuint index = *reinterpret_cast<GLuint*>(userParam);
	std::cerr << "[DEBUG_OUTPUT] "
	          << message
	          << " (internalformat= "
	          << internalFormatsStr[index]
	          << ')'
	          << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// on init cb
void on_init()
{
	// variables
	GLuint i=0;
	GLuint texture=0;
	GLuint iterationCnt=sizeof(internalFormats)/(sizeof(GLenum));

	// Configure debug output
	glDebugMessageCallbackARB(
			reinterpret_cast<GLDEBUGPROCARB>(&gl_debug_message_callback),
			&i );

	// 1D tests
	for(i=0; i<iterationCnt; ++i)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_1D, texture);
			glTexStorage1D(GL_TEXTURE_1D,
			               1,
			               internalFormats[i],
			               1);
		glDeleteTextures(1, &texture);
	}
	std::cerr << '\n';

	// 2D tests
	for(i=0; i<iterationCnt; ++i)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
			glTexStorage2D(GL_TEXTURE_2D,
			               1,
			               internalFormats[i],
			               1,
			               1);
		glDeleteTextures(1, &texture);
	}
	std::cerr << '\n';

	// 3D tests
	for(i=0; i<iterationCnt; ++i)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_3D, texture);
			glTexStorage3D(GL_TEXTURE_3D,
			               1,
			               internalFormats[i],
			               1,
			               1,
			               1);
		glDeleteTextures(1, &texture);
	}
}


////////////////////////////////////////////////////////////////////////////////
// on clean cb
void on_clean()
{

}


////////////////////////////////////////////////////////////////////////////////
// on update cb
void on_update()
{

}


////////////////////////////////////////////////////////////////////////////////
// on resize cb
void on_resize(GLint w, GLint h)
{

}


////////////////////////////////////////////////////////////////////////////////
// on key down cb
void on_key_down(GLubyte key, GLint x, GLint y)
{

}


////////////////////////////////////////////////////////////////////////////////
// on mouse button cb
void on_mouse_button(GLint button, GLint state, GLint x, GLint y)
{

}


////////////////////////////////////////////////////////////////////////////////
// on mouse motion cb
void on_mouse_motion(GLint x, GLint y)
{

}


////////////////////////////////////////////////////////////////////////////////
// on mouse wheel cb
void on_mouse_wheel(GLint wheel, GLint direction, GLint x, GLint y)
{

}


////////////////////////////////////////////////////////////////////////////////
// Main
//
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	const GLuint CONTEXT_MAJOR = 4;
	const GLuint CONTEXT_MINOR = 2;

	// init glut
	glutInit(&argc, argv);
	glutInitContextVersion(CONTEXT_MAJOR ,CONTEXT_MINOR);

	glutInitContextFlags(GLUT_DEBUG);
	glutInitContextProfile(GLUT_CORE_PROFILE);

//	glutInitContextFlags(GLUT_DEBUG | GLUT_FORWARD_COMPATIBLE);
//	glutInitContextProfile(GLUT_CORE_PROFILE);


	// build window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL");

	// init glew
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		std::stringstream ss;
		ss << err;
		std::cerr << "glewInit() gave error " << ss.str() << std::endl;
		return 1;
	}

	// glewInit generates an INVALID_ENUM error for some reason...
	glGetError();

	// set callbacks
	glutCloseFunc(&on_clean);
	glutReshapeFunc(&on_resize);
	glutDisplayFunc(&on_update);
	glutKeyboardFunc(&on_key_down);
	glutMouseFunc(&on_mouse_button);
	glutPassiveMotionFunc(&on_mouse_motion);
	glutMotionFunc(&on_mouse_motion);
	glutMouseWheelFunc(&on_mouse_wheel);

	// run
	on_init();

	return 0;
}

