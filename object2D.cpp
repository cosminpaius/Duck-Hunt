#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 top,
    glm::vec3 color,
    float radius,
    bool fill)
{

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;
    std::vector<VertexFormat> vertices;

    const int nroftr = 75;
    const int nrofvrt = 77;
    int i;
    float theta;
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

    for (i = 0; i <= nroftr - 1; i++) {
        theta = 2 * i * M_PI / nroftr - 1;
        vertices.push_back(VertexFormat(glm::vec3(cos(theta) * radius, sin(theta) * radius, 0), color));
        indices.push_back(i);
    }

    indices.push_back(nroftr);
    indices.push_back(1);
    if (fill) {
        circle->SetDrawMode(GL_TRIANGLE_FAN);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 top,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 auxtop = top;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(auxtop, color),
        VertexFormat(auxtop - glm::vec3(height, height / 5, 0), color),
        VertexFormat(auxtop - glm::vec3(height, -height / 5, 0), color)
    };

    Mesh* tris = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        tris->SetDrawMode(GL_LINE_LOOP);
    }

    tris->InitFromData(vertices, indices);
    return tris;
}
