## Steps to install required libraries:

Importing GLFW, GLAD, and GLM requires some extra setup that may complicate things, but to avoid whatever legal nonsense may come with
adding them to the project, I have attached instructions on how to add them yourself. 

- [GLFW/GLAD](https://www.youtube.com/watch?v=Y4F0tI7WlDs) <-- Particularly tricky
- GLM - Go to its [repository](https://github.com/g-truc/glm) and copy the glm folder to your include folder.

At the end, the folder structure should look like this:

client
    - .vscode
    - build
    - include
        - glad
            -glad.h
        - GLFW
            - glfw3.h
            - glfw3native.h
        - glm
            - all of glms stuff (its a lot)
        - KHR
            - khrplatform.h
        - Other headers we create.
    - lib
        - glfw3.lib
    - src
        - glad.c
        - Other source code we create.
    - glfw3.dll

