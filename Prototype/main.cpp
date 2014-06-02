#include <iostream>
#include <QWindow>
#include <QScreen>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLPaintDevice>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QTimer>
#include <QObject>
#include <QGuiApplication>
#include <GL/glu.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <QMatrix4x4>
#include <vector>


#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

#define USE_GLSL_120 // for old notebooks

#ifdef USE_GLSL_330

// GLSL 330 Vertex Shader
static const char *vertexShaderSource =
        "#version 330\n"
        "in vec4 vPosition;\n"
        "in vec4 vColor;\n"
        "uniform mat4 matrix;\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vColor;\n"
        "   gl_Position = matrix*vPosition;\n"
        "}\n";

// GLSL 330 Fragment Shader
static const char *framentShaderSource =
        "#version 330\n"
        "in vec4 color;\n"
        "in vec4 position;\n"
        "out vec4 fColor;\n"
        "void main() {\n"
        "    fColor = color;\n"
        "}\n";

#endif//USE_GLSL_330

#ifdef USE_GLSL_120
// GLSL 120 Vertex Shader
static const char *vertexShaderSource =
        "#version 120\n"
        "attribute vec4 vPosition;\n"
        "attribute vec4 vColor;\n"
        "uniform mat4 matrix;\n"
        "varying vec4 color;\n"
        "varying vec4 position;\n"
        "void main() {\n"
        "   color = vColor;\n"
        "   position = vPosition;\n"
        "   gl_Position = matrix*vPosition;\n"
        "}\n";

// GLSL 120 Fragment Shader
static const char *framentShaderSource =
        "#version 120\n"
        "varying vec4 color;\n"
        "varying vec4 position;\n"
        "void main() {\n"
        "    gl_FragColor = color;\n"
        "}\n";

#endif//USE_GLSL_120



// typedefs to work conveniently with points and colors
typedef QVector4D vec4;
typedef QMatrix4x4 mat4;
typedef vec4 point4;
typedef vec4 color4;

// the vertices of the cube
static const point4 positions[8] = {
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4( 0.5,  0.5,  0.5, 1.0),
    point4( 0.5, -0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4( 0.5,  0.5, -0.5, 1.0),
    point4( 0.5, -0.5, -0.5, 1.0)
};

// the colors of the vertices of the cube
static color4 colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ), //black
    color4( 1.0, 0.0, 0.0, 1.0 ), //red
    color4( 1.0, 1.0, 0.0, 1.0 ), //yellow
    color4( 0.0, 1.0, 0.0, 1.0 ), //green
    color4( 0.0, 0.0, 1.0, 1.0 ), //blue
    color4( 1.0, 0.0, 1.0, 1.0 ), //magenta
    color4( 1.0, 1.0, 1.0, 1.0 ), //white
    color4( 0.0, 1.0, 1.0, 1.0 )  //cyan
};

/**
 * @brief The MyGLWindow class
 * A MyGLWindow opens a QT window containing a GL surface displaying a colored cube
 */
class MyGLWindow : public QWindow, protected QOpenGLFunctions {

    Q_OBJECT

public: // constructors
    /**
     * @brief MyGLWindow
     * The standard constructor initializes the shader program and the GL context to NULL. It sets
     * the SurfaceType of the window to an OpenGLSurface so we can use it later to display th GL
     * context.
     */
    MyGLWindow()
        : m_program(NULL)
        , m_context(NULL)
        , m_frame(0)
    {
        // Important to create a GL context on this window:
        setSurfaceType(QWindow::OpenGLSurface);
    }

    ~MyGLWindow()
    {
        // free all the memory allocated
        delete m_program;
        delete m_context;
        delete[] glVPositions;
        delete[] glVColors;
    }

public: // methods

    /**
     * @brief initialize
     * Initialize inits the shader programs and the cube, links the program.
     */
    void initialize() {
        std::cout << "init" << std::endl;
        // initialize the coordinates and colors of the cube vertices

        cube();

        glVPositions = getGLArray(vPositions);
        glVColors = getGLArray(vColors);

        m_program = new QOpenGLShaderProgram(this);
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, framentShaderSource);
        m_program->link();


        GLuint vPSize = vPositions.size()*4*sizeof(GLfloat);
        GLuint vCSize = vColors.size()*4*sizeof(GLfloat);

        // Create VBO (virtual buffer objects)

        GLuint vbo;
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vPSize + vCSize, NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vPSize, glVPositions);
        glBufferSubData(GL_ARRAY_BUFFER, vPSize, vCSize, glVColors);


/*
        m_vao = new QOpenGLVertexArrayObject(this);
        m_vao->bind();

        m_positionBuffer.create();
        m_positionBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_positionBuffer.bind();
        m_positionBuffer.allocate(glVPositions, vPSize);

        m_colorBuffer.create();
        m_colorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_colorBuffer.bind();
        m_colorBuffer.allocate(glVColors, vCSize);
*/

        // Associate shader variables with vertex arrays
        // associate m_vPosition with vPosition
        GLuint m_vPosition = m_program->attributeLocation("vPosition");
        glEnableVertexAttribArray(m_vPosition);
        glVertexAttribPointer(m_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        // associate m_vColor with vColor
        GLuint m_vColor = m_program->attributeLocation("vColor");
        glEnableVertexAttribArray(m_vColor);
        glVertexAttribPointer(m_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vPSize));

        m_matrix = m_program->uniformLocation("matrix");

        m_program->bind();
    }

    /**
     * @brief resizeGL If the window gets resized by the user, this function resizes the
     * glViewport to the new dimensions and sets up the correct view frustrum
     * @param width New width of the resized
     * @param height New height of the resized window
     */
    void resizeGL(int width, int height) {
        glViewport(0, 0, width, height);

        GLfloat aspectRatio = (float)width / (float)height;
        GLfloat zNear = 0.5; // 0.5 -
        GLfloat zFar  = 100.0; // 4.0
        GLfloat fov = 25.0;

        projection.setToIdentity();
        projection.perspective(fov, aspectRatio, zNear, zFar);
    }

    /**
     * @brief render draws the GL scene
     */
    void render() {

        resizeGL(width(), height());

        // initialize
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // cull the non-visible faces
        glEnable(GL_CULL_FACE);

        //enable multisampling
        glEnable(GL_MULTISAMPLE);

        // initialize object transformation matrix
        QMatrix4x4 matrix;
        matrix.setToIdentity();
        matrix.translate(0, 0, -4);

        // rotate object transformation matrix
        matrix.rotate(10.0f * m_frame / 60.0f, 1, 0, 0); // x-axis
        matrix.rotate(-5.0f * m_frame / 60.0f, 0, 1, 1); // y-axis
        matrix.rotate(20.0f * m_frame / 60.0f, 0, 1, 0); // z-axis

        // use rotation matrix in shader
        m_program->setUniformValue(m_matrix, projection * matrix);

        // draw all the triangles
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        //m_program->release();

        // display double buffer
        m_context->swapBuffers(this);


        // this frame is done
        ++m_frame;
    }


    /**
     * @brief event Eventhandler for interactions with the GUI. right now handles only update requests
     * for the wndow.
     * @param event the event
     * @return a boolean
     */
    bool event(QEvent *event) {
        switch(event->type()) {
        case QEvent::UpdateRequest:
            std::cout << "update" << std::endl;
            renderNow();
            return true;
        default:
            return QWindow::event(event);
        }
    }

    void timerEvent(QTimerEvent *event) {
        Q_UNUSED(event);
        std::cout << "timer" << std::endl;
        renderNow();
    }

    /**
     * @brief exposeEvent causes a rerendering ot the window content, when some area of the window
     * is invalidated.
     * @param event
     */
    void exposeEvent(QExposeEvent *event)
    {
        Q_UNUSED(event);

        if (isExposed()) {
            std::cout << "expose" << std::endl;
            renderNow();
        }
    }

    /**
     * @brief resizeEvent causes a rerendering of the window if its size has changed.
     * @param event unused
     */
    void resizeEvent(QResizeEvent *event)
    {
        Q_UNUSED(event);

        if (isExposed()) {
            std::cout << "resize" << std::endl;
            renderNow();
        }
    }


    /**
     * @brief renderNow
     * renderNow renders the graphics on first call it calls @link initialize to set up
     * the graphics environment. On repeated calls it merely updates the display.
     */
public slots:
    void renderNow() {
        if(!isExposed())
            return;

        float needsInitialize = false;

        if(!m_context) {
            m_context = new QOpenGLContext(this);
            m_context->setFormat(this->format());
            m_context->create();

            needsInitialize = true;
        }

        m_context->makeCurrent(this);

        if(needsInitialize) {
            initializeOpenGLFunctions();
            initialize();
        }

        render();
    }

public:

    void setAnimate(bool animating) {
        if(animating) {
            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
            timer->start(1000/60);
        } else {

        }
        //QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }

private: // methods

    /**
     * @brief getGLArray takes a vector of vec4's and transforms it to raw data that may be sent
     * to the GPU
     * @param list a std::vector<vec4> that contains either point4's or color4's
     * @return a pointer to a newly allocized array of GLfloats that contains the raw data of the list
     */
    GLfloat *getGLArray(const std::vector<vec4> &list) {
        int length = list.size()*4;
        GLfloat *result = new GLfloat[length];
        int index = 0;
        std::vector<vec4>::const_iterator it;
        for(it = list.begin(); it != list.end(); ++it) {
            for(int i=0;i<4;++i) {
                result[index] = (*it)[i];
                ++index;
           }
        }
        return result;
    }

    /**
     * @brief quad a helper function that returns the 2 triangles from which the qudrilateral a,b,c,d is
     * composed of and stores them in vPositions and vColors.
     * a---b
     * |  /|
     * |/  |
     * c---d
     * @param a index of the first vertex.
     * @param b index of the second vertex.
     * @param c index of the third vertex.
     * @param d index of the fourth vertex.
     */
    void quad(int a, int b, int c, int d) {

        vColors.push_back(colors[a]); vPositions.push_back(positions[a]);
        vColors.push_back(colors[b]); vPositions.push_back(positions[b]);
        vColors.push_back(colors[c]); vPositions.push_back(positions[c]);

        vColors.push_back(colors[a]); vPositions.push_back(positions[a]);
        vColors.push_back(colors[c]); vPositions.push_back(positions[c]);
        vColors.push_back(colors[d]); vPositions.push_back(positions[d]);
    }

    /**
     * @brief cube a function that computes all the triangles the cube to be displayed is composed of.
     */
    void cube() {
        quad(1,0,3,2);
        quad(2,3,7,6);
        quad(3,0,4,7);
        quad(6,5,1,2);
        quad(4,5,6,7);
        quad(5,4,0,1);
    }

private: // members

    std::vector<point4> vPositions;  // the application model of the scene
    std::vector<color4> vColors;     // the colors

    GLfloat *glVPositions;           // the raw data that is sent to the GPU
    GLfloat *glVColors;              // the colors

    QOpenGLShaderProgram *m_program; // the shader program
    QOpenGLContext *m_context;       // the GL context

    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_positionBuffer;
    QOpenGLBuffer m_colorBuffer;

    GLuint m_matrix;                 // handle of the rotation matrix
    QMatrix4x4 projection;

    long m_frame;
};

#include "main.moc"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(4);           // allow multisampling
    format.setDepthBufferSize(24);  // allow depth buffering with 24 bit
    format.setVersion(3,3);         // set prefered GL version -> GLSL
    format.setProfile(QSurfaceFormat::CoreProfile);

    MyGLWindow window;
    window.resize(640,480);
    window.setFormat(format);

    window.show();
    window.renderNow();       // render the scene
    window.setAnimate(true); // set animating

    return app.exec(); // execute the application
}

