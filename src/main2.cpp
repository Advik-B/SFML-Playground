#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec2 resolution;

    void main() {
        vec2 uv = gl_FragCoord.xy / resolution;
        FragColor = vec4(uv, 0.0, 1.0);
    }
)";

int main() {
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL Window");
    window.setVerticalSyncEnabled(true);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Set resolution uniform
    GLint resolutionLocation = glGetUniformLocation(shaderProgram, "resolution");
    if (resolutionLocation != -1) {
        glUniform2f(resolutionLocation, 800.0f, 600.0f);
    } else {
        std::cerr << "Failed to locate uniform variable 'resolution'" << std::endl;
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.display();
    }

    // Clean up
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    return 0;
}
