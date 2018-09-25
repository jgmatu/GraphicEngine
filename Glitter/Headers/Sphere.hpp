#ifndef SPHERE_H
#define SPHERE_H

#define _USE_MATH_DEFINES
#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
//#include <GL/glut.h>

#include <vector>
#include <stdio.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Sphere {

public:
      Sphere();
      ~Sphere();

      void createBuffer();

      std::vector<GLfloat> getPosVertex() { return posVertex; };
      std::vector<GLfloat> getNormals() { return normals; };
      std::vector<GLfloat> getTexCoords() { return texCoords; };
      std::vector<GLuint> getIndexes() {return indices; };

protected:

    // Buffers
    std::vector<GLfloat> posVertex;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<unsigned int> indices;


      /* Statement Exercise ... */
      std::vector<std::vector<int>> grid;

};
#endif
