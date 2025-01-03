#include "VertexPart.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cctype>

// Constructor
VertexPart::VertexPart(std::string filename) {
    std::cout<<"Executed from class VertexPart: "<<filename<<std::endl;
    bool isAscii=false;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    // Read the first 80 bytes (header)
    char header[80] = {};
    file.read(header, 80);

    // Check if the header starts with "solid"
    std::string headerStr(header, 80);
    if (headerStr.find("solid") == 0) {
        // Check for binary data after the header
        char buffer[512];
        file.read(buffer, sizeof(buffer));

        for (size_t i = 0; i < sizeof(buffer); ++i) {
            if (!isprint(buffer[i]) && !isspace(buffer[i])) {
                isAscii=false; // Contains non-ASCII characters -> likely binary
                break;
            }
        }

        isAscii=true;
    }

    if(isAscii)
        std::cout<<"ASCII STL"<<std::endl;
    else
        std::cout<<"Binary STL"<<std::endl;
}

// Add a vertex to the storage
void VertexPart::addVertex(const Vertex& vertex) {
    vertices.push_back(vertex);
}

// Get a vertex by index
Vertex VertexPart::getVertex(size_t index) const {
    if (index >= vertices.size()) {
        throw std::out_of_range("Index out of range");
    }
    return vertices[index];
}

// Get the total count of vertices
size_t VertexPart::getVertexCount() const {
    return vertices.size();
}

// Destructor
VertexPart::~VertexPart() {
    // Clean-up if needed
}
