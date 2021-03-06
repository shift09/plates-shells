#include <iostream>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "node.h"
#include "element.h"
#include "hinge.h"

Hinge::Hinge(Node* n0, Node* n1, Node* n2, Node* n3, Element* el1, Element* el2)
 : m_const(1), m_k(1),
   m_el1(el1), m_el2(el2),
   m_node0(n0), m_node1(n1),
   m_node2(n2), m_node3(n3)
{
    nodes_order_check();

    Eigen::Vector3d ve0 = *(m_node1->get_xyz()) - *(m_node0->get_xyz());
    double e0 = ve0.norm();
    double a0 = m_el1->get_area() + m_el2->get_area();
    m_const = 6.0 * pow(e0, 2) / a0;  // FIXME: should be 2.0 * in order to match beam bending

    //TODO: calculate psi0
    m_psi0 = 0;
}

// unify the surface normal directions
// TODO: this should guarantee all directions to be the same
void Hinge::nodes_order_check() {
    Eigen::Vector3d e0 = *(m_node1->get_xyz()) - *(m_node0->get_xyz());
    Eigen::Vector3d e3 = *(m_node2->get_xyz()) - *(m_node1->get_xyz());
    Eigen::Vector3d e4 = *(m_node3->get_xyz()) - *(m_node1->get_xyz());

    Eigen::Vector3d n1 = e0.cross(e3);
    n1 = n1 / (n1.norm());
    Eigen::Vector3d n2 = -e0.cross(e4);
    n2 = n2 / (n2.norm());

    if (n1.dot(n2) < 0)
        std::swap(m_node0, m_node1);
}

Node* Hinge::get_node(int num) const {
    switch (num) {
        case 0:
            return m_node0;
        case 1:
            return m_node1;
        case 2:
            return m_node2;
        case 3:
            return m_node3;
        default:
            std::cerr << "Local number of node can only be 0, 1, 2, 3" << std::endl;
            exit(1);
    }
}

unsigned int Hinge::get_node_num(const int num) const {
    switch (num) {
        case 0:
            return m_node0->get_num();
        case 1:
            return m_node1->get_num();
        case 2:
            return m_node2->get_num();
        case 3:
            return m_node3->get_num();
        default:
            std::cerr << "Local number of node can only be 0, 1, 2, 3" << std::endl;
            exit(1);
    }
}

double Hinge::get_psi0() const {
    return m_psi0;
}