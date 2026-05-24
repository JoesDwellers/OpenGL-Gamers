#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <fstream>


using boost::asio::ip::tcp;
using std::cout, std::cin, std::cerr, std::endl;

void chat_client(const std::string& server_ip) {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::make_address(server_ip), 12345));
    
        cout << "Connected to " << server_ip << endl;
    
        char data[1024];
        while (true) {
            std::string message;
            cout << "You: " << endl;
            std::getline(cin, message);

            boost::system::error_code error;
            boost::asio::write(socket, boost::asio::buffer(message), error);

            if (error) throw boost::system::system_error(error);

            std::memset(data, 0, sizeof(data));
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof) break;
            else if (error) throw boost::system::system_error(error);

            cout << "Server: " << data << endl;
        }

    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
}

GLint modifier;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;
    switch (key) {
        case GLFW_KEY_ESCAPE :
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_KP_ADD :
            modifier += 1;
            break;
        case GLFW_KEY_KP_SUBTRACT :
            modifier -= 1;
            break;
        default :
            break;
    }
    return;
}

GLFWwindow* Init() {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    GLFWwindow* window = glfwCreateWindow(800, 600, "Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwSetKeyCallback(window, keyCallback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }   
    return window;
}

int main() {

    GLFWwindow* window = Init();

    glm::mat3 vertices = glm::mat3(
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    );
    
    // Needed to do stuff idk
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    
    // CREATING VERTEX SHADER /////////////////////////////////
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char* vertexShaderSource;
    
    std::ifstream vertFile("shaders/vertex.glsl");
    if (vertFile.is_open()) {
        vertFile.seekg(0, std::ios::end);
        std::streamsize fileSize = vertFile.tellg();
        vertFile.seekg(0, std::ios::beg);
        vertexShaderSource = new char[fileSize + 1];
        vertFile.read(vertexShaderSource, fileSize);
        vertexShaderSource[fileSize] = '\0';
    } else {
        cerr << "Failed to open shader file" << endl;
        exit(-1);
    }

    


    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);       
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cerr << "Error with Compiling vertex shader: " << infoLog << endl;
        exit(-1);
    }
    
    // CREATING FRAGMENT SHADER /////////////////////////////////
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragFileSource;
    
    std::ifstream fragFile("shaders/fragment.glsl");
    if (fragFile.is_open()) {
        fragFile.seekg(0, std::ios::end);
        std::streamsize fileSize = fragFile.tellg();
        fragFile.seekg(0, std::ios::beg);
        fragFileSource = new char[fileSize + 1];
        fragFile.read(fragFileSource, fileSize);
        fragFileSource[fileSize] = '\0';
        
    } else {
        cerr << "Failed to open fragment file" << endl;
        exit(-1);
    }

    glShaderSource(fragmentShader, 1, &fragFileSource, NULL);
    glCompileShader(fragmentShader);       
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cerr << "Error with Compiling fragment shader: " << infoLog << endl;
        exit(-1);
    }


    // CREATING SHADER PROGRAM //////////////////////////
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cerr << "Error with Compiling shader program: " << infoLog << endl;
        exit(-1);    
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat3), glm::value_ptr(vertices), GL_STATIC_DRAW);
    
    // Linking Vertex attributes (Describing how OpenGL reads from our vertices buffer)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLint rotationVal = 0;
    GLint rotationLoc = glGetUniformLocation(shaderProgram, "rotation");


    while (!glfwWindowShouldClose(window)) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glClear(GL_COLOR_BUFFER_BIT);
        rotationVal++;
        glUniform1i(rotationLoc, rotationVal);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        Sleep(100);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    delete[] vertexShaderSource;
    delete[] fragFileSource;
    return 0;
}