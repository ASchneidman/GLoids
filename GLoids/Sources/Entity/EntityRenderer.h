//
// Created by Alex Schneidman on 2020-05-07.
//

#ifndef GLOIDS_ENTITYRENDERER_H
#define GLOIDS_ENTITYRENDERER_H


#include <glm/vec3.hpp>
#include "../shader.h"

class EntityRenderer {
public:
    EntityRenderer(Shader *inShader);
    void drawEntity(glm::vec3 &position, glm::mat4 &projection,
                    glm::mat4 &view, glm::vec3 &color, glm::vec3 size,
                    float rotate);
private:
    Shader *shader; GLuint VAO;
};


#endif //GLOIDS_ENTITYRENDERER_H
