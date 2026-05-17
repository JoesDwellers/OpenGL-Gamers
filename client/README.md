## Steps to install required libraries:

Importing GLFW, GLAD, GLM, and Boost.Asio requires some extra setup that may complicate things, but to avoid whatever legal nonsense may come with
adding them to the project, I have attached instructions on how to add them yourself. 

- [GLFW/GLAD](https://www.youtube.com/watch?v=Y4F0tI7WlDs) <-- Particularly tricky
- GLM - Go to its [repository](https://github.com/g-truc/glm) and copy the glm folder to your include folder.
- [Boost](https://www.boost.org/releases/latest/) and place the entire boost folder either in your include, or somewhere like C:/Tools (My custom spot for it)

At the end, the folder structure should look like this:

client  
&emsp;- .vscode  
&emsp;- build  
&emsp;- include  
&emsp;&emsp;- glad  
&emsp;&emsp;&emsp;-glad.h  
&emsp;&emsp;- GLFW  
&emsp;&emsp;&emsp;- glfw3.h  
&emsp;&emsp;&emsp;- glfw3native.h  
&emsp;&emsp;- glm  
&emsp;&emsp;&emsp;- all of glms stuff (its a lot)  
&emsp;&emsp;- KHR  
&emsp;&emsp;&emsp;- khrplatform.h  
&emsp;&emsp;- Other headers we create.  
&emsp;- lib  
&emsp;&emsp;- glfw3.lib  
&emsp;- src  
&emsp;&emsp;- glad.c  
&emsp;&emsp;- Other source code we create.  
&emsp;- glfw3.dll  

