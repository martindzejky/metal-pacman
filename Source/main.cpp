#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <lodepng.h>


/**
 * Initialize OpenGL, GLFW, and make a window.
 */
GLFWwindow* initialize() {

    // init GLFW
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW error " << error << ": " << description << std::endl;
    });

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    // create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(800, 800, "OpenGL v2 - GL4, GLFW", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create a window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // setup OpenGL
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // init GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;

}


/**
 * Clear up resources and terminate.
 */
void terminate(GLFWwindow* window, int exitCode = EXIT_SUCCESS) {

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(exitCode);

}


/**
 * Update the OpenGL viewport based on window size.
 */
void updateViewport(GLFWwindow* window) {

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

}


/**
 * Load and compile vertex and fragment shader files.
 */
int setupShaders() {

    // load shader files
    std::ifstream vertexStream("vertex.glsl");
    if (!vertexStream.is_open()) {
        std::cerr << "File vertex.glsl doesn't exist\n";
        return EXIT_FAILURE;
    }

    std::stringstream vsstr;
    vsstr << vertexStream.rdbuf();
    std::string vertexSource = vsstr.str();

    std::ifstream fragmentStream("fragment.glsl");
    if (!fragmentStream.is_open()) {
        std::cerr << "File fragment.glsl doesn't exist\n";
        return EXIT_FAILURE;
    }

    std::stringstream fsstr;
    fsstr << fragmentStream.rdbuf();
    std::string fragmentSource = fsstr.str();

    const char* vertexSourcePtr = vertexSource.c_str();
    const char* fragmentSourcePtr = fragmentSource.c_str();

    // compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
    glCompileShader(vertexShader);

    GLint vstatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vstatus);

    if (vstatus != GL_TRUE) {
        std::cerr << "Failed to compile the vertex shader!\n";

        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

        std::cerr << buffer << std::endl;
        return EXIT_FAILURE;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
    glCompileShader(fragmentShader);

    GLint fstatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fstatus);

    if (fstatus != GL_TRUE) {
        std::cerr << "Failed to compile the fragment shader!\n";

        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

        std::cerr << buffer << std::endl;
        return EXIT_FAILURE;
    }

    // create a program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindFragDataLocation(program, 0, "outColor");

    glLinkProgram(program);
    glUseProgram(program);

    // bind vertex attributes
    GLuint position = (GLuint) glGetAttribLocation(program, "position");
    glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    glEnableVertexAttribArray(position);

    GLuint texcoord = (GLuint) glGetAttribLocation(program, "texcoord");
    glVertexAttribPointer(texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*) (sizeof(float) * 2));
    glEnableVertexAttribArray(texcoord);

    glUniform1i(glGetUniformLocation(program, "tex"), 0);

    return EXIT_SUCCESS;

}


/**
 * Make a quad that can render the texture.
 */
void makeQuad(GLuint* vertices, GLuint* indices) {

    // vertices
    const float vertexArray[] = {
        // positions, texture coords
        -.8f, -.8f, 0.f, 1.f,
         .8f, -.8f, 1.f, 1.f,
         .8f,  .8f, 1.f, 0.f,
        -.8f,  .8f, 0.f, 0.f
    };

    // indices
    const int indexArray[] = {
        0, 1, 2,
        0, 2, 3
    };

    // make a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // buffer objects
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);

    // return
    *vertices = vertexBufferObject;
    *indices = indexBufferObject;

}


/**
 * Load an OpenGL texture.
 */
GLuint loadTexture(const std::string &filename, unsigned int &width, unsigned int &height) {

    // create OpenGL texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // configure it
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the image from the file
    std::vector<unsigned char> buffer;
    buffer.reserve((unsigned long) (width * height * 4));
    if (auto error = lodepng::decode(buffer, width, height, filename)) {
        std::cerr << "Error loading " << filename << ": " << lodepng_error_text(error) << std::endl;
        return 0;
    }

    // modify the image
    for (auto i = 0; i < buffer.size(); ++i) {
        if (i % 4 == 0) {
            if (i / 4  % width >= width / 2) {
                unsigned char tmp = buffer[i];
                buffer[i] = buffer[i + 1];
                buffer[i + 1] = tmp;
            }
        }
        else if (i % 4 == 2) {
            if (i / 4 / width >= height / 2) {
                unsigned char tmp = buffer[i];
                buffer[i] = buffer[i - 2];
                buffer[i - 2] = tmp;
            }
        }
    }

    // save the new texture
    lodepng::encode("new " + filename, buffer, width, height);

    // load the OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());

    // here's the texture
    return texture;

}


/**
 * Entry function.
 */
int main() {

    auto window = initialize();

    GLuint vertices, indices;
    makeQuad(&vertices, &indices);

    unsigned int width = 1024;
    unsigned int height = 1024;
    GLuint texture = loadTexture("angular.png", width, height);

    if (auto code = setupShaders()) {
        terminate(window, code);
    }

    // main loop
    while (!glfwWindowShouldClose(window)) {
        // updateViewport(window);

        // check the ESC key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // clear
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    terminate(window);

}
