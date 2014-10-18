/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SQUIRCLE_H
#define SQUIRCLE_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <cpglquads.h>
#include <simulator.h>

//! [1]
class MolecularDynamicsRenderer : public QObject {
    Q_OBJECT
public:
    std::vector<float> *m_positions;
    Simulator m_simulator;
    MolecularDynamicsRenderer();
    ~MolecularDynamicsRenderer();

    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void resetProjection();
    void incrementRotation(double deltaPan, double deltaTilt, double deltaRoll);
    void incrementZoom(double deltaZoom);

    double zoom() const;
    void setZoom(double zoom);

    double pinchScale() const;
    void setPinchScale(double pinchScale);

public slots:
    void paint();

private:
    QSize m_viewportSize;
    double m_tilt;
    double m_pan;
    double m_roll;
    double m_zoom;
    double m_pinchScale;
    QOpenGLShaderProgram *m_program;

    QMatrix4x4 m_projection;
    CPGLQuads *m_glQuads;
};
//! [1]

//! [2]
class MolecularDynamics : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(double xPoint READ xPoint WRITE setxPoint NOTIFY xPointChanged)
    Q_PROPERTY(double yPoint READ yPoint WRITE setyPoint NOTIFY yPointChanged)
    Q_PROPERTY(double pinchScale READ pinchScale WRITE setPinchScale NOTIFY pinchScaleChanged)
    Q_PROPERTY(double pinchRotation READ pinchRotation WRITE setPinchRotation NOTIFY pinchRotationChanged)

public:
    MolecularDynamics();
    Q_INVOKABLE void step(double dt);
    Q_INVOKABLE void onPinchedFinished();

    double xPoint() const
    {
        return m_xPoint;
    }

    double yPoint() const
    {
        return m_yPoint;
    }

    double pinchRotation() const
    {
        return m_pinchRotation;
    }

    double pinchScale() const
    {
        return m_pinchScale;
    }

public slots:
    void sync();
    void cleanup();
    void incrementRotation(double deltaPan, double deltaTilt, double deltaRoll);
    void incrementZoom(double deltaZoom);

    void setxPoint(double arg)
    {
        if (m_xPoint == arg)
            return;

        m_xPoint = arg;
        emit xPointChanged(arg);
    }

    void setyPoint(double arg)
    {
        if (m_yPoint == arg)
            return;

        m_yPoint = arg;
        emit yPointChanged(arg);
    }

    void setPinchRotation(double arg)
    {
        if (m_pinchRotation == arg)
            return;

        m_pinchRotation = arg;
        emit pinchRotationChanged(arg);
    }

    void setPinchScale(double arg)
    {
        if (m_pinchScale == arg)
            return;

        m_pinchScale = arg;
        emit pinchScaleChanged(arg);
        if(m_renderer) m_renderer->setPinchScale(m_pinchScale);
    }

signals:
    void xPointChanged(double arg);

    void yPointChanged(double arg);

    void pinchRotationChanged(double arg);

    void pinchScaleChanged(double arg);

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    std::vector<float> m_positions;
    MolecularDynamicsRenderer *m_renderer;
    double m_xPoint;
    double m_yPoint;
    double m_pinchRotation;
    double m_pinchScale;

};
//! [2]

#endif // SQUIRCLE_H
