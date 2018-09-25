#include "Sphere.hpp"

Sphere::Sphere() {
      ;
}

Sphere::~Sphere() {
      ;
}

void
Sphere::createBuffer() {
      int idx = 0;

      float heightSegments = 25.0f;
      float height = 25.0f;
      float width = 25.0f;
      float radius = 1.5f;
      glm::vec3 vertex(1.0f); // Row vec3...

      // Generate vertices, normals and texCoords
      for (int iy = 0; iy <= height; ++iy) {
            std::vector<int> verticesRow;
            float v = iy / heightSegments;

            for (int ix = 0; ix <= width; ++ix) {
                  float u = ix / width;

                  // Vertex. X.
                  vertex.x = -radius * cos( u * M_PI * 2.0f ) * sin( v * M_PI );

                  // Vertex. Y.
                  vertex.y = radius * cos( v * M_PI );

                  // Vertex. Z.
                  vertex.z = radius * sin( u * M_PI * 2.0f ) * sin( v * M_PI );

                  GLfloat aux[] = {vertex.x, vertex.y, vertex.z};
                  posVertex.insert(posVertex.end(), aux, aux + 3);

                  // Normal.
                  glm::vec3 normal(vertex);
                  normal = glm::normalize(normal); // Normalize... Here!

                  GLfloat norm[] = {normal.x, normal.y, normal.z};
                  normals.insert(normals.end(), norm, norm + 3);

                  // TexCoord. Is good because draw the first texture...
                  double texCoord[] = {u, 1.0 - v};
                  texCoords.insert(texCoords.begin(), texCoord, texCoord + 2);
                  verticesRow.push_back( idx++ );
            }
            grid.push_back(verticesRow);
      }

      // Generate índices
      //Sorting of indices...(for triangles-strip)
      for (int iy = 0; iy < height; ++iy ) {
            for (int          ix = 0; ix < width; ++ix ) {
                  int a = grid[ iy ][ ix + 1 ];
                  int b = grid[ iy ][ ix ];
                  int c = grid[ iy + 1 ][ ix ];
                  int d = grid[ iy + 1 ][ ix + 1 ];

                  int aux[] = {a, b, d};
                  indices.insert(indices.end(), aux, aux + 3);

                  int bla[] = {b, c, d};
                  indices.insert(indices.end(), bla, bla + 3);
            }
      }
}
