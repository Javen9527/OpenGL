总结：
    1.着色器是运行在GPU上的程序；
    2.着色器之间通过输入和输出进行沟通；
    3.主要针对图形计算：向量和矩阵预算
    
    4.着色器类的主要功能：
        ① 读入着色器程序
        ② 编译着色器程序
        ③ 设置着色器中的uniform变量
      本类中通过构造函数实现了①②功能，通过use函数和各类set函数实现了③功能

概述：
    1.典型结构：
    {
        #version version_number
        in type in_variable_name;
        out type out_variable_name;
        uniform type uniform_name;

        int main()
        {
            //处理输入并进行图形计算操作
            ...
            //输出结果
            out_variable_name = weird_stuff_we_processed;
        }
    }

    2.数据类型
    {
    (1)基础数据类型
        int float double uint bool
    (2)容器
        vector(向量) matrix(矩阵)
    }

    3.输入输出
    {
    (1)顶点着色器的输入
        每个输入变量叫做顶点属性
        layout (location = 0)

    (2)片段着色器的输出
        需要一个vec4的颜色输出变量

    (3)其他着色器
    }

    4.Uniform
    {
        //是一种从CPU程序向GPU着色器发送数据的方式、全局的

        //给Uniform变量赋值：找到着色器中uniform的位置(索引) -> 赋值
        int UniformIndex = glGetUniformLocation(shaderProgram, "Uniform_Name");
        glUseProgram(ShaderProgram);
        glUniform4f(UniformIndex, 0.0f, 0.0f, 0.0f, 0.0f);
    }

    5.在原始数据中配置更多属性
    {
    //原始数据
        float vertices[] = {
        // 位置              // 颜色
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f};  // 顶部
    //顶点着色器
        #version 330 core
        layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
        layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

        out vec3 ourColor; // 向片段着色器输出一个颜色

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
            ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
        }
    //片段着色器
        #version 330 core
        out vec4 FragColor;  
        in vec3 ourColor; // 与顶点着色器中定义的输出变量名字相同即可关联

        void main()
        {
            FragColor = vec4(ourColor, 1.0);
        }
    //顶点属性
        //位置属性
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //颜色属性
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

    }

    6.着色器类
    {
    #ifndef SHADER_H
    #define SHADER_H

    #include <glad.h>
    #include <string>
    #include <fstream>
    #include <sstream>
    #include <iostream>

    class Shader
    {
    public:
        //程序ID
        unsigned int ID;

        //构造器读取并构建着色器
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        //使用/激活程序
        void use();

        //Uniform工具函数
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
    };

    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {
    //1.从文件路径获取顶点/片段着色器
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILED_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
    //2.编译着色器
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        //vertex
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cout << "ERROR: SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //fragment
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cout << "ERROR: SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        //着色器程序
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cout << "ERROR: SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        }
        //删除着色器
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::use()
    {
        glUseProgram(ID);
    }

    void Shader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    #endif
    }

    7.使用着色器类
    {
        Shader ourShader("C风格字符串路径", "C风格字符串路径")；
        ourShader.use();
        ourShader.setFloat("Uniform_name", 1.0f);
    }
