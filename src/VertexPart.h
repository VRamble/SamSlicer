#ifndef VERTEXPART_H
#define VERTEXPART_H

#include <vector>
#include <string>

struct Vertex {
    float v1x, v1y, v1z;    //Vertex 1
    float v2x, v2y, v2z;    //Vertex 2
    float v3x, v3y, v3z;    //Vertex 3
    float nx, ny, nz;    // Normal
};

class VertexPart {
private:
    std::vector<Vertex> vertices; // vertex data storage
    std::vector<std::vector<float>> transformation_matrix; //transformations done in gui
    char units; //units from the stl, assumed mm unless otherwise specified

public:
    // Constructor
    VertexPart(std::string filename);

    // Methods to interact with the vertices
    void addVertex(const Vertex& vertex);
    Vertex getVertex(size_t index) const;
    size_t getVertexCount() const;
    void printPart() const;

    // Destructor
    ~VertexPart();
};

#endif // VERTEXPART_H
