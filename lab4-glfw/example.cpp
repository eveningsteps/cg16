#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

using glm::vec3;
using glm::uvec3;
using glm::mat4;

struct SimpleMesh
{
    std::vector<vec3> vertices, colors;
    std::vector<uvec3> faces;
    std::vector<GLuint> buf_ids;

    GLuint vshader, fshader, shader_program;
    GLint attr_coord3d, attr_v_color, unif_mvp;

    SimpleMesh() {}
    ~SimpleMesh() {}

    virtual void init() = 0;
    virtual void render(const mat4 &) = 0;
};

struct Tetraeder: SimpleMesh
{
    Tetraeder(){}
    ~Tetraeder(){}
    void init()
    {
        // setting geometry and filling buffers

        buf_ids.resize(3);
        glGenBuffers(3, buf_ids.data());

        vertices.push_back(vec3(3.0, 2.0, 4.0)); // top
        vertices.push_back(vec3(0.0, 0.0, 1.0));
        vertices.push_back(vec3(6.0, 0.0, 1.0));
        vertices.push_back(vec3(3.0, 4.0, 1.0));
        glBindBuffer(GL_ARRAY_BUFFER, buf_ids[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

        for(int i = 0; i < 4; ++i)
            colors.push_back(vec3((rand() % 256) / 256.0, (rand() % 256) / 256.0, (rand() % 256) / 256.0));
        glBindBuffer(GL_ARRAY_BUFFER, buf_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(colors[0]), colors.data(), GL_STATIC_DRAW);

        faces.push_back(uvec3(0, 1, 2));
        faces.push_back(uvec3(0, 2, 3));
        faces.push_back(uvec3(0, 3, 1));
        faces.push_back(uvec3(1, 2, 3));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_ids[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(faces[0]), faces.data(), GL_STATIC_DRAW);


        // setting shaders

        vshader = glCreateShader(GL_VERTEX_SHADER);
        const char *vshader_source[] =
        {
            "attribute vec3 coord3d;",
            "attribute vec3 v_color;",
            "uniform mat4 mvp;",
            "varying vec3 f_color;",
            "void main(void)",
            "{",
            "  gl_Position = mvp * vec4(coord3d, 1.0);",
            "  f_color = v_color;",
            "}"
        };

        glShaderSource(vshader, 9, vshader_source, NULL);
        glCompileShader(vshader);

        fshader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fshader_source[] =
        {
            "varying vec3 f_color;",
            "void main(void)",
            "{",
            "  gl_FragColor = vec4(f_color.xyz, 1.0);",
            "}"
        };
        glShaderSource(fshader, 5, fshader_source, NULL);
        glCompileShader(fshader);

        shader_program = glCreateProgram();
        glAttachShader(shader_program, vshader);
        glAttachShader(shader_program, fshader);
        glLinkProgram(shader_program);


        // getting attributes' locations

        attr_coord3d = glGetAttribLocation(shader_program, "coord3d");
        attr_v_color = glGetAttribLocation(shader_program, "v_color");
        unif_mvp = glGetUniformLocation(shader_program, "mvp");
    }

    void render(const mat4 &mvp)
    {
        glUseProgram(shader_program);

        glUniformMatrix4fv(unif_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

        glEnableVertexAttribArray(attr_coord3d);
        glBindBuffer(GL_ARRAY_BUFFER, buf_ids[0]);
        glVertexAttribPointer(attr_coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(attr_v_color);
        glBindBuffer(GL_ARRAY_BUFFER, buf_ids[1]);
        glVertexAttribPointer(attr_v_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf_ids[2]);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    }
};

mat4 build_mvp_matrix(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    double yaw, pitch;
    glfwGetCursorPos(window, &yaw, &pitch);

    float scale = 0.2;

    vec3 ox(1.0, 0.0, 0.0), oy(0.0, 1.0, 0.0);
    mat4 rot = glm::rotate(glm::rotate(mat4(), glm::radians((float)yaw), oy), glm::radians((float)pitch), ox);
    mat4 tl = glm::translate(mat4(), vec3(0.0f, 0.0f, 3.0f));
    mat4 sc = glm::scale(mat4(), vec3(scale, scale, scale));

    mat4 model =  tl * rot * sc;
    mat4 view = glm::lookAt(oy, vec3(0.0f, 0.0f, 3.0f), oy);
    mat4 projection = glm::perspective(glm::radians(45.0f), float(width)/height, 0.1f, 10.0f);

    mat4 mvp = projection * view * model;
    return mvp;
}

int main(void)
{
    srand(time(0));
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Now we can initialize OpenGL functions */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Error: " << (const char *)glewGetErrorString(err) << std::endl;
        return -1;
    }

    Tetraeder tetraeder;
    tetraeder.init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(.3, .4, .5, 1.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        tetraeder.render(build_mvp_matrix(window));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
