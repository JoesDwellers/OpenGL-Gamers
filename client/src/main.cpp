#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>


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



int main() {
    
    std::string server_ip;
    cout << "Enter server IP: ";
    cin >> server_ip;
    cin.ignore();
    chat_client(server_ip);
    return 0;
    
    
    
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    // if (window == NULL) {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }

    // while (!glfwWindowShouldClose(window)) {
        
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    // glfwTerminate();
    return 0;
}