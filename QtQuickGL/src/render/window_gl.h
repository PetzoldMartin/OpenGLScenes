#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>

class WindowGL : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
public:
    WindowGL();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void Initialize();
    void Render();
    void Cleanup();
    void Sync();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    QOpenGLShaderProgram* shader;

    qreal m_t;
    qreal m_thread_t;
};

#endif // WINDOW_GL_H
