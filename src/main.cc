
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * octetos-cobgl is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-cobgl is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#include "Vertex.hh"
#include "core.hh"
#include "shader.hpp"

int main( void )
{
	octetos::cobgl::Window wnd(640,480,"Coleccion de Obejtos GL - Octetos");

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(wnd, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "src/SimpleTransform.vertexshader", "src/SingleColor.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix mul

	
	octetos::cobgl::VertexList<float,octetos::cobgl::Vertex3D> vecL(3);
	octetos::cobgl::Vertex3D<float>& v1 = vecL[0];
	v1.x = -1.0f;
	v1.y = -1.0f;
	v1.z = 0.0f;
	octetos::cobgl::Vertex3D<float>& v2 = vecL[1];
	v2.x = 1.0f;
	v2.y = -1.0f;
	v2.z = 0.0f;
	octetos::cobgl::Vertex3D<float>& v3 = vecL[2];
	v3.x = 0.0f;
	v3.y = 1.0f;
	v3.z = 0.0f;

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	std::cout << "Size of g_vertex_buffer_data = " << sizeof(g_vertex_buffer_data) << "\n";
	std::cout << "Size  = " << sizeof(float) * 9 << "\n";
	std::cout << "Size of vecL = " << sizeof(vecL) << "\n";
	std::cout << "Size of unsigned short = " << sizeof(unsigned short) << "\n";
	std::cout << "Size of GLuint = " << sizeof(GLuint) << "\n";
	for(float f : vecL)
	{
		std::cout << "f = " << f << "\n";
	}
	vecL.GenBuffers(1);
	
	do
	{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		vecL.BindBuffer();
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		
		// Swap buffers
		glfwSwapBuffers(wnd);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(wnd, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(wnd) == 0 );

	float buff[9];
	
	// Cleanup VBO and shader
	//glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	//glDeleteVertexArrays(1, &VertexArrayID);

	return 0;
}

