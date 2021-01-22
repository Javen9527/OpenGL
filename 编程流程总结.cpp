
一、glfw创建窗口
{
    glfwInit();
    glfwWindowHint(MINOR, 3);
    glfwWindowHint(MAJOR, 3);
    glfwWindowHint(PROFILE, CORE);
    #ifdef __APPLE__
    glfwWindowHint(FORWARD, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow();
    glfwMakeCurrentContext();
}

二、注册窗口操作相关函数
{
    glfwSetFrameBufferSizeCallback();
    glfwSetCursorPosCallBack();
    glfwSetScrollCallBack();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

二、加载OPENGL函数
{
    gladLoadGLLoader((GLADloadProc)glfwGetProcAddress);
}

三、Shader管理类
{
1.实现的功能：
    ① 读取Shader源码(构造函数实现)
    ② 编译Shader源码并链接成程序(构造函数实现)
    ③ 对Shader程序中的uniform变量提供修改接口(接口函数实现)
2.Shader管理类：
    class Shader
    {
    public:
    //program ID
        int ID;
    //读取源码 + 编译链接
        Shader(const char *vpath, const char *fpath)
        {
            //读取源码
            string vCode, fCode;
            ifstream vFile, fFile;
            vFile.exceptions(ifstream::failbit | ifstream::badbit);
            fFile.exceptions(ifstream::failbit | ifstream::badbit);
            try
            {
                vFile.open(vpath);
                fFile.open(fpath);

                stringstream vstream, fstream;
                vstream << vFile.rdbuf();
                fstream << fFile.rdbuf();

                vCode = vstream.str();
                fCode = fstream.str();

                vFile.close();
                fFile.close();
            }
            catch(const ifstream::failure& e)
            {
                std::cout << "Faile read..." << std::endl;
            }

            //编译源码 + 链接成程序
            const char *vertexCode = vCode.c_str();
            const char *fragmentCode = fCode.c_str();

            unsigned int vertex, fragment;
            glCreateShader(1, &vertex);
            glShaderSource(vertex, vertexCode);
            glCompileShader(vertex);

            glCreateShader(1, &fragment);
            glShaderSource(fragment, fragmentCode);
            glCompilerShader(fragment);

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
    //激活Shader程序
        void use(){glUseProgram(ID);}
    //设置uniform变量接口函数
        void setInt(const string &UniformName, int value)
        {
            glUniform1i(glGetUniformLocation(ID, UniformName.c_str()), vaule);
        }
    }
}

四、创建管理数据、属性的VAO、VBO、EBO等
{
1.先VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

2.后VBO
    unsigned int VBO;
    glGenBuffers(1, &VB0);
    glBindBuffer(VBO);

    //传输数据至VBO
    glBufferData(VBO, data);

3.设置多个属性（即告诉Shader程序如何去读取数据）
    glVertexAttribPointer();
    glEnableVertexAttribArray();
}

五、设置纹理
{
1.创建纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //设置纹理参数
    glTexParameteri(...);
2.读入图像
    glTexImage2D(image);
    glGenerateMipmap();
3.设定Shader程序中的纹理参数
    Shader类.use();
    Shader类.setInt("texture", 0);
}

六、渲染循环
{
1.处理窗口输入事件

2.清除背景
    glCreateColor();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

3.激活纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

4.激活Shader程序
    Shader类.use();

5.坐标系变换（观察 + 投影） + 摄像机视图
    //投影矩阵
    glm::mat4 projection = glm::perspective(摄像机的zoom);
    shader类.setMat4("projection", projection);
    //观察矩阵
    glm::mat4 view = 摄像机参数
    shader类.setMat4("view", view);

6.坐标系变换（模型） + 顶点属性绑定 + 渲染
    //绑定VAO
    glBindVertexArray(VAO);
    //模型矩阵 + 渲染
    for(每一个渲染Object)
    {
        glm::mat4 model = glm::tranlsate + glm::rotate + glm::scale;
        shader类.setMat4("model", model);

        glDrawArrays();
    }
    
7.双缓冲 + 抛出事件
    glfwSwapBuffers(window);
    glfwPollEvents();
}

七、删除VAO VBO，退出
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}