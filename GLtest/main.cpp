#include <iostream>

#include <QApplication>
#include <QOpenGLFunctions>
#include <QGLWidget>



int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    int requestMajor = 4;
    int requestMinor = 1;

    if(app.arguments().size() == 3) {
        requestMajor = app.arguments().at(1).toInt();
        requestMinor = app.arguments().at(2).toInt();
    }

    QGLFormat qglFormat;
    qglFormat.setVersion(requestMajor,requestMinor);
    qglFormat.setProfile(QGLFormat::CoreProfile);

    QGLWidget widget(qglFormat);
    widget.show();
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *version     = glGetString(GL_VERSION);
    const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    GLint nExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS,&nExtensions);

    std::cout << "GL Vendor:     " << vendor << std::endl;
    std::cout << "GL Renderer:   " << renderer << std::endl;
    std::cout << "GL Version:    " << version << std::endl;
    std::cout << "GL Version:    " << major << "." << minor << std::endl;
    std::cout << "GLSL Version:  " << glslVersion << std::endl;

    if(major >= 3 && minor >= 0) {
        for(int i=0;i<nExtensions;++i) {
            std::cout << "GL Extension:  "
                      << glGetString(GL_EXTENSIONS+i) << std::endl;
        }
    }else {
        std::cout << "GL Extensions: " << glGetString(GL_EXTENSIONS) << std::endl;
    }
    //sleep(1);
    return 0;
}

