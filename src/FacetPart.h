#ifndef FACETPART_H
#define FACETPART_H

#include <vector>
#include <string>

struct Facet {
    float v1x, v1y, v1z;    //Facet 1
    float v2x, v2y, v2z;    //Facet 2
    float v3x, v3y, v3z;    //Facet 3
    float nx, ny, nz;    // Normal
};

class FacetPart {
private:
    std::vector<Facet> vertices; // facet data storage
    std::vector<std::vector<float>> transformation_matrix; //transformations done in gui
    char units; //units from the stl, assumed mm unless otherwise specified

public:
    // Constructor
    FacetPart(std::string filename);

    // Methods to interact with the vertices
    void addFacet(const Facet& facet);
    Facet getFacet(size_t index) const;
    size_t getFacetCount() const;
    void printPart() const;

    // Destructor
    ~FacetPart();
};

#endif // FACETPART_H
