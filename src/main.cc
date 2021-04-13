
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
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <iostream>

#include "Shapes.hh"
#include "core.hh"
#include "shader.hpp"

#include "core.hh"
using namespace octetos;


int main( void )
{
	// Initialise GLFW
	cobgl::Window window(640, 480, "Tutorial 02 - Red triangle");
	

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "src/SimpleTransform.vertexshader", "src/SingleColor.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
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
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	
	octetos::cobgl::Triangle<float> triangle;
	octetos::cobgl::Vertex3D<float>& v1 = triangle.getVertex()[0];
	v1.x = -1.0f;
	v1.y = -1.0f;
	v1.z = 0.0f;
	octetos::cobgl::Vertex3D<float>& v2 = triangle.getVertex()[1];
	v2.x = 1.0f;
	v2.y = -1.0f;
	v2.z = 0.0f;
	octetos::cobgl::Vertex3D<float>& v3 = triangle.getVertex()[2];
	v3.x = 0.0f;
	v3.y = 1.0f;
	v3.z = 0.0f;
	triangle.getVertex().GenBuffers(1);

	octetos::cobgl::Cube<float> cube;
	//t1
	cube.getVertex()[0].x = -1.0;
	cube.getVertex()[0].y = -1.0;
	cube.getVertex()[0].z = -1.0;
	cube.getVertex()[1].x = -1.0;
	cube.getVertex()[1].y = -1.0;
	cube.getVertex()[1].z = 1.0;
	cube.getVertex()[2].x = -1.0;
	cube.getVertex()[2].y = 1.0;
	cube.getVertex()[2].z = 1.0;
	//t2
	cube.getVertex()[3].x = 1.0;
	cube.getVertex()[3].y = 1.0;
	cube.getVertex()[3].z = -1.0;
	cube.getVertex()[4].x = -1.0;
	cube.getVertex()[4].y = -1.0;
	cube.getVertex()[4].z = 1.0;
	cube.getVertex()[5].x = -1.0;
	cube.getVertex()[5].y = 1.0;
	cube.getVertex()[5].z = -1.0;
	//t3
	cube.getVertex()[6].x = 1.0;
	cube.getVertex()[6].y = -1.0;
	cube.getVertex()[6].z = 1.0;
	cube.getVertex()[7].x = -1.0;
	cube.getVertex()[7].y = -1.0;
	cube.getVertex()[7].z = -1.0;
	cube.getVertex()[8].x = 1.0;
	cube.getVertex()[8].y = -1.0;
	cube.getVertex()[8].z = -1.0;
	//t4
	cube.getVertex()[9].x = 1.0;
	cube.getVertex()[9].y = 1.0;
	cube.getVertex()[9].z = -1.0;
	cube.getVertex()[10].x = 1.0;
	cube.getVertex()[10].y = -1.0;
	cube.getVertex()[10].z = -1.0;
	cube.getVertex()[11].x = -1.0;
	cube.getVertex()[11].y = -1.0;
	cube.getVertex()[11].z = -1.0;
	//t5
	cube.getVertex()[12].x = -1.0;
	cube.getVertex()[12].y = -1.0;
	cube.getVertex()[12].z = -1.0;
	cube.getVertex()[13].x = -1.0;
	cube.getVertex()[13].y = 1.0;
	cube.getVertex()[13].z = 1.0;
	cube.getVertex()[14].x = -1.0;
	cube.getVertex()[14].y = 1.0;
	cube.getVertex()[14].z = -1.0;
	//t6
	cube.getVertex()[15].x = 1.0;
	cube.getVertex()[15].y = -1.0;
	cube.getVertex()[15].z = 1.0;
	cube.getVertex()[16].x = -1.0;
	cube.getVertex()[16].y = -1.0;
	cube.getVertex()[16].z = 1.0;
	cube.getVertex()[17].x = -1.0;
	cube.getVertex()[17].y = -1.0;
	cube.getVertex()[17].z = -1.0;
	//t7
	cube.getVertex()[18].x = -1.0;
	cube.getVertex()[18].y = 1.0;
	cube.getVertex()[18].z = 1.0;
	cube.getVertex()[19].x = -1.0;
	cube.getVertex()[19].y = -1.0;
	cube.getVertex()[19].z = 1.0;
	cube.getVertex()[20].x = 1.0;
	cube.getVertex()[20].y = -1.0;
	cube.getVertex()[20].z = 1.0;
	//t8
	cube.getVertex()[21].x = 1.0;
	cube.getVertex()[21].y = 1.0;
	cube.getVertex()[21].z = 1.0;
	cube.getVertex()[22].x = 1.0;
	cube.getVertex()[22].y = -1.0;
	cube.getVertex()[22].z = -1.0;
	cube.getVertex()[23].x = 1.0;
	cube.getVertex()[23].y = 1.0;
	cube.getVertex()[23].z = -1.0;
	//t8
	cube.getVertex()[24].x = 1.0;
	cube.getVertex()[24].y = 1.0;
	cube.getVertex()[24].z = 1.0;
	cube.getVertex()[25].x = 1.0;
	cube.getVertex()[25].y = -1.0;
	cube.getVertex()[25].z = -1.0;
	cube.getVertex()[26].x = 1.0;
	cube.getVertex()[26].y = -1.0;
	cube.getVertex()[26].z = 1.0;
	//t9
	cube.getVertex()[27].x = 1.0;
	cube.getVertex()[27].y = -1.0;
	cube.getVertex()[27].z = -1.0;
	cube.getVertex()[28].x = 1.0;
	cube.getVertex()[28].y = 1.0;
	cube.getVertex()[28].z = 1.0;
	cube.getVertex()[29].x = 1.0;
	cube.getVertex()[29].y = -1.0;
	cube.getVertex()[29].z = 1.0;
	//t10
	cube.getVertex()[30].x = 1.0;
	cube.getVertex()[30].y = 1.0;
	cube.getVertex()[30].z = 1.0;
	cube.getVertex()[31].x = 1.0;
	cube.getVertex()[31].y = 1.0;
	cube.getVertex()[31].z = -1.0;
	cube.getVertex()[32].x = -1.0;
	cube.getVertex()[32].y = 1.0;
	cube.getVertex()[32].z = -1.0;
	//t11
	cube.getVertex()[33].x = 1.0;
	cube.getVertex()[33].y = 1.0;
	cube.getVertex()[33].z = 1.0;
	cube.getVertex()[34].x = -1.0;
	cube.getVertex()[34].y = 1.0;
	cube.getVertex()[34].z = -1.0;
	cube.getVertex()[35].x = -1.0;
	cube.getVertex()[35].y = 1.0;
	cube.getVertex()[35].z = -1.0;
	//t12
	cube.getVertex()[36].x = 1.0;
	cube.getVertex()[36].y = 1.0;
	cube.getVertex()[36].z = 1.0;
	cube.getVertex()[37].x = -1.0;
	cube.getVertex()[37].y = 1.0;
	cube.getVertex()[37].z = 1.0;
	cube.getVertex()[38].x = 1.0;
	cube.getVertex()[38].y = -1.0;
	cube.getVertex()[38].z = 1.0;
	
	glm::mat4 tranM = glm::translate(glm::mat4(1), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::vec4 transformedVector(4.0f,3.0f,3.0f,0.0f);
	glm::vec4 ttemp;
	
	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);
				
		
		/*ttemp = tranM * transformedVector;
		std::cout<<glm::to_string(transformedVector)<<std::endl;
		transformedVector = ttemp;
		std::cout<<glm::to_string(transformedVector)<<std::endl;*/
		
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		triangle.getVertex().BindBuffer();
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
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	//glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

