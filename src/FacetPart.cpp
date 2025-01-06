#include "FacetPart.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

// Constructor
FacetPart::FacetPart(std::string filename) {
    std::cout<<"Executed from class FacetPart: "<<filename<<std::endl;
    bool isAscii=false;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    // Read the first 80 bytes (header)
    char header[80] = {};
    char num_tris_data[4]={};
    char buffer[2]={};
    file.read(header, 80);
    file.read(num_tris_data,4);
    int num_tris;
    std::memcpy(&num_tris, num_tris_data,4);
    // Check if the header starts with "solid"
    std::string headerStr(header, 80);
    if (headerStr.find("solid") == 0) {
        //Put in some more checks incase there is an stl that contains solid for some reason but is binary
        isAscii=true;
    }

    char vert_number_data[4];
    if(isAscii)
        std::cout<<"ASCII STL"<<std::endl;
    else{
        for(int i=0;i<num_tris;i++){
            //create an array to store the facet data in, then pass that array through the facet struct into storage
            float points[12];
            for(int i=0;i<12;i++){
                file.read(vert_number_data,4);
                std::memcpy(&points[i],vert_number_data,4);
            }
            this->addFacet({points[3], points[4], points[5],
                                 points[6], points[7], points[8],
                                 points[9], points[10], points[11],
                                 points[0], points[1], points[2]});
            file.read(buffer,2);
        }
    }
}

// Add a facet to the storage
void FacetPart::addFacet(const Facet& facet) {
    vertices.push_back(facet);
}

// Get a facet by index
Facet FacetPart::getFacet(size_t index) const {
    if (index >= vertices.size()) {
        throw std::out_of_range("Index out of range");
    }
    return vertices[index];
}

// Get the total count of vertices
size_t FacetPart::getFacetCount() const {
    return vertices.size();
}

//export the data to an stl format
void FacetPart::printPart() const{
    if (vertices.size()==0)
        std::cout<<"Error: No model data"<<std::endl;
    else{
        std::ofstream export_part;
        Facet currentFacet;
        export_part.open("exported_part.stl");
        export_part<<"solid testicles"<<std::endl;
        for(int i=0;i<vertices.size();i++){
            //export facet data with file structure of ascii stl. See doc/filetype_reference for more detail reference.
            //TODO: add in export option for binary stl
            currentFacet=this->getFacet(i);
            export_part<<"  facet normal "<<currentFacet.nx<<" "<<currentFacet.ny<<" "<<currentFacet.nz<<" "<<std::endl;
            export_part<<"    outer loop"<<std::endl;
            export_part<<"      facet "<<currentFacet.v1x<<" "<<currentFacet.v1y<<" "<<currentFacet.v1z<<" "<<std::endl;
            export_part<<"      facet "<<currentFacet.v2x<<" "<<currentFacet.v2y<<" "<<currentFacet.v2z<<" "<<std::endl;
            export_part<<"      facet "<<currentFacet.v3x<<" "<<currentFacet.v3y<<" "<<currentFacet.v3z<<" "<<std::endl;
            export_part<<"    endloop"<<std::endl;
            export_part<<"  endfacet"<<std::endl;
        }
        export_part<<"endsolid testicles";
        export_part.close();
    }
}

// Destructor
FacetPart::~FacetPart() {
    // Clean-up if needed
}
