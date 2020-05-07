//
// Created by Alex Schneidman on 2020-05-07.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EntityRenderer.h"

static const float default_vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom left
        0.0f, 0.0f, 0.0f, // Middle
        0.5f, -0.5f, 0.0f // Bottom right

};

EntityRenderer::EntityRenderer(Shader *inShader) {
    this->shader = inShader;

    GLuint VBO;
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(default_vertices), default_vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void EntityRenderer::drawEntity(glm::vec3 &position, glm::mat4 &projection,
                                glm::mat4 &view, glm::vec3 &color, glm::vec3 size,
                                float rotate) {
    // prepare transformations
    this->shader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    // Rotate model around z axis
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z));

    // Scale model
    model = glm::scale(model, size);

    this->shader->setMat4("model", model);
    this->shader->setVec3("inColor", color);
    this->shader->setMat4("view", view);
    this->shader->setMat4("projection", projection);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
