总结：
    1.使用纹理可避免为每个顶点配置属性的开销

概述：
1.纹理坐标
{
    //指定每个顶点关联一个纹理坐标 其他位置 -> 采样+插值
    float texCoords[] = {
        0.0f, 0.0f, // 左下角
        1.0f, 0.0f, // 右下角
        0.5f, 1.0f // 上中  
    };
}

2.纹理环绕
{
    //纹理坐标范围超出(0, 0)至(1, 1)范围后的行为
    GL_REPEAT
    GL_MIRRORED_REPEAT
    GL_CLAMP_TO_EDGE
    GL_CLAMP_TO_BORDER
    //使用glTexParameter* 对每个坐标轴设定环绕方式
}

3.纹理过滤
{
    //将纹理像素映射到纹理坐标即为纹理过滤
    GL_NEAREST
    GL_LINEAR
    //使用glTexParameter* 设置纹理过滤
}

4.多级渐远纹理
{
    //在纹理被缩小时候使用
    glGenerateMipmaps
}

5.图像加载库
{
    //stb_image.h
    //通过设定STB_IMAGE_IMPLEMENTATION将头文件编程cpp文件
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    //生成纹理后释放内存
    stbi_image_free(data);
}

6.生成纹理
{
    //生成纹理
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //载入图片
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
}

6.应用纹理
{
    //将纹理数据存放到原始数据中
    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    //调整顶点着色器
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
    //调整片段着色器
    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);//GLSL内建的函数texture
    }
    //应用纹理的属性为
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAtrribArray(2);
}

7.纹理单元
{
    //设定多个纹理时候会用到纹理单元
    //在uniform sample2D ourTexture中，声明了uiform变量(采样分配器)，使用glUniform1i可以给纹理采样器分配位置值
    //OPENGL至少有16个纹理单元从GL_TEXTURE0 -> GL_TEXTURE15
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}