总结：
    1.使用VBO/EBO管理数据；[GenBUffers/BindBuffer]
    2.使用着色器和着色器程序编写渲染引擎；
    3.使用glVertexAttribPointer和glEnableAttribPointer设定对应数据的解析属性; [AttribPointer]
    4.使用VAO存储数据和属性之间的关联; [GenVertexArrays/BindVertexArray]

    notice:先绑定VAO，再设定数据和属性，从而配置VAO

概述：
    1. 原始数据
    {
    (1)顶点数据
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        }

    (2)顶点索引
        unsigned int indices[] = { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
        };
    }

    2. 在GPU上开辟内存存储数据，并通过VBO/EBO管理该片内存
    {
    (1)VBO:
        //创建VBO
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //复制原始数据给VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    (2)EBO:
        //创建EBO
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY, EBO);
        //复制数据的索引到EBO
        glBufferData(GL_ELEMENT_ARRAY, sizeof(indices), indices, GL_STATIC_DRAW);
    }

    3. 接下来创建着色器 - 访问VBO/EBO管理的数据、指示GPU如何处理数据
    {
    (1)顶点着色器:
        //创建着色器
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        //编译着色器
        glCompileShader(vertexShader);
        //打印编译结果
        int success; char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog); cout << infoLog << endl;
        }

    (2)片段着色器:
        //创建着色器
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        //编译着色器
        ...
        //打印编译结果
    }

    4. 创建着色器程序 - 多个着色器合并之后的最终版本
    {
    (1)创建着色器程序
        //创建着色器程序
        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        //链接着色器
        glAttachShader(shaderProgram, vertexShader); 
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        //打印链接结果
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog); cout << infoLog << endl;
        }

    (2)使用着色器程序
        glUseProgram(shaderProgram);

    (3)删除着色器对象
        //在链接成着色器程序后就可删除了
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    5. 配置顶点属性 - 告知OPENGL如何处理数据(数据来源于之前绑定的VBO或者EBO)
    {
    (1)当顶点属性少时
        //告知OpenGL如何解析顶点数据
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        //启用顶点属性 - 默认关闭
        glEnableAttribPointer(0);

    (2)使用VAO - 当顶点属性很多时
        //创建VAO
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
    }

    6. 开始绘制
    {
        //启用渲染引擎
        glUseProgram(shaderProgram);
        //数据、属性、解析
        glBindVertexArray(VAO);
        //开始绘制
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //注意：当使用EBO时
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


