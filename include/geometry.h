#ifndef PLATES_SHELLS_GEOMETRY_H
#define PLATES_SHELLS_GEOMETRY_H

#include "type_alias.h"

class Parameters;
class Node;
class Element;
class Edge;
class Hinge;

class Geometry {

public:
    Geometry(Parameters* SimPar);
    ~Geometry();

    // modifier
    void set_datum(const int var);
    void set_nsd(const int var);
    void set_nen(const int var);
    void set_rec_len(const double var);
    void set_rec_wid(const double var);
    void set_num_nodes_len(const unsigned int var);
    void set_num_nodes_wid(const unsigned int var);
    void set_dx(const double var);
    void set_angle(const double var);
    void set_nn();
    void set_nel();
    void set_nedge();
    void set_nhinge();

    void findMassVector();
    void translateNodes(int dir, double amt);

    // accessor
    int           datum() const;
    int           nsd() const;
    int           nen() const;
    double        rec_len() const;
    double        rec_wid() const;
    unsigned int  num_nodes_len() const;
    unsigned int  num_nodes_wid() const;
    double        dx() const;
    double        angle() const;
    unsigned int  nn() const;
    unsigned int  nel() const;
    unsigned int  nedge() const;
    unsigned int  nhinge() const;

    bool hingeNumCheck() const;
    bool edgeNumCheck() const;
    void printMesh();
    void writeConnectivity();

    // public geometry variables
    double m_mi;                          // mass per node

    VectorNodes m_nodes;   // coordinates       (nn  x nsd)
    VectorMesh m_mesh;     // connectivity      (nel x nen)

    VectorN m_mass;               // nodal mass vector, mx1, my1, mz1, mx2, my2, mz2, ...
    
    std::vector<Node>    m_nodeList;
    std::vector<Element> m_elementList;
    std::vector<Edge*>   m_edgeList;
    std::vector<Hinge*>  m_hingeList;

private:

    // geometry parameters
    int             m_datum;                      // initial datum plane
    int             m_nsd;                        // degree of freedom per node
    int             m_nen;                        // number of nodes per element
    double          m_rec_len;                    // length of the rectangular domain
    double          m_rec_wid;                    // width of the rectangular domain
    double          m_dx;                         // spatial discretization step size
    double          m_angle;                      // rotation angle about origin
    unsigned int    m_num_nodes_len;              // number of nodes along the length
    unsigned int    m_num_nodes_wid;              // number of nodes along the width
    unsigned int    m_nn;                         // total number of nodes
    unsigned int    m_nel;                        // total number of elements
    unsigned int    m_nedge;                      // number of edges
    unsigned int    m_nhinge;                     // number of hinges

    // pointer to parameters
    Parameters* m_SimPar;

};

// inline implementations for short functions
inline void Geometry::set_datum(const int var)                   { m_datum = var; }
inline void Geometry::set_nsd(const int var)                     { m_nsd = var; }
inline void Geometry::set_nen(const int var)                     { m_nen = var; }
inline void Geometry::set_rec_len(const double var)              { m_rec_len = var; }
inline void Geometry::set_rec_wid(const double var)              { m_rec_wid = var; }
inline void Geometry::set_num_nodes_len(const unsigned int var)  { m_num_nodes_len = var; }
inline void Geometry::set_num_nodes_wid(const unsigned int var)  { m_num_nodes_wid = var; }
inline void Geometry::set_dx(const double var)                   { m_dx = var; }
inline void Geometry::set_angle(const double var)                { m_angle = var; }
inline void Geometry::set_nn()             { m_nn = m_num_nodes_len * m_num_nodes_wid; }
inline void Geometry::set_nel()            { m_nel = 2 * (m_num_nodes_len-1) * (m_num_nodes_wid-1); }
inline void Geometry::set_nedge()          { m_nedge = 3 * m_nel - m_nhinge; }
inline void Geometry::set_nhinge()         { m_nhinge = (3 * m_nel - 2 * (m_num_nodes_len + m_num_nodes_wid - 2)) / 2; }

inline int           Geometry::datum() const                     { return m_datum; }
inline int           Geometry::nsd() const                       { return m_nsd; }
inline int           Geometry::nen() const                       { return m_nen; }
inline double        Geometry::rec_len() const                   { return m_rec_len; }
inline double        Geometry::rec_wid() const                   { return m_rec_wid; }
inline unsigned int  Geometry::num_nodes_len() const             { return m_num_nodes_len; }
inline unsigned int  Geometry::num_nodes_wid() const             { return m_num_nodes_wid; }
inline double Geometry::dx() const                               { return m_dx; }
inline double Geometry::angle() const                            { return m_angle; }
inline unsigned int  Geometry::nn() const                        { return m_nn; }
inline unsigned int  Geometry::nel() const                       { return m_nel; }
inline unsigned int  Geometry::nedge() const                     { return m_nedge; }
inline unsigned int  Geometry::nhinge() const                    { return m_nhinge; }

inline bool Geometry::hingeNumCheck() const                      { return (m_hingeList.size() == m_nhinge); }
inline bool Geometry::edgeNumCheck() const                       { return (m_edgeList.size() == m_nedge); }

#endif //PLATES_SHELLS_GEOMETRY_H
