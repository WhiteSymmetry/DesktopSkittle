/****************************************************************************
**
** This file is derived from the OpenGL example as part of the Qt Toolkit
** produced by Nokia.  Skittle is provided as Open Source under the GPL.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <math.h>
#include <QKeyEvent>
#include <QCursor>
#include <string>
#include "BasicTypes.h"
#include "UiVariables.h"
#include "MdiChildWindow.h"

class UiVariables;
class FastaReader;
class AbstractGraph;
class NucleotideDisplay;
class BiasDisplay;
class RepeatMap;
class AnnotationDisplay;
class CylinderDisplay;
class RepeatOverviewDisplay;
class OligomerDisplay;
class HighlightDisplay;
class GtfReader;
class QFrame;

using namespace std;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    UiVariables* ui;
    string chromosomeName;
    MdiChildWindow* parent;
    FastaReader* reader;
    GtfReader*	trackReader;
    NucleotideDisplay* nuc;//make this private
    RepeatMap* freq;
    BiasDisplay* bias;
    AnnotationDisplay* gtfTrack;
    CylinderDisplay* cylinder;
    RepeatOverviewDisplay* align;
    OligomerDisplay* olig;
    HighlightDisplay* highlight;


    GLWidget(UiVariables *gui, QWidget* parent = 0);
    ~GLWidget();
    void addGraph(AbstractGraph* graph);
    void createButtons();
    void createConnections();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    double getZoom();
    void setTotalDisplayWidth();

    void keyPressEvent( QKeyEvent *event );
    void keyReleaseEvent( QKeyEvent *event );
    int tool();
    void zoomToolActivate(QMouseEvent *event, point2D oglCoords);
    color colors(char nucleotide);
    void setupColorTable();
    color spectrum(double i);
    
    const string* seq();

    vector<QScrollArea*> settingsUi();


public slots:
    void reportOnFinish(int);
    void changeZoom(int z);
    void displayString(const string* sequence);
    void zoomExtents();
    void on_moveButton_clicked();
    void on_selectButton_clicked();
    void on_findButton_clicked();
    void on_screenCaptureButton_clicked();
    void on_resizeButton_clicked();
    void on_zoomButton_clicked();
    void setTool(int tool);
    void slideHorizontal(int);
    void invalidateDisplayGraphs();
    void updateDisplay();
    void updateDisplaySize();
    void jumpToAnnotation(bool forward);
    AnnotationDisplay* addAnnotationDisplay(QString fileName);
    AnnotationDisplay* findMatchingAnnotationDisplay(string fileName);
    vector<AnnotationDisplay*> getAllAnnotationDisplays();
    void addTrackEntry(track_entry entry, string gtfFileName);
    void loadFile(QString);
    bool removeAllAnnotations();
    //void setUi(UiVariables);
    
signals:
    void totalWidthChanged(int);
    void xOffsetChange(int);
    void printText(QString);
    void printHtml(QString);
    void addGraphMode(AbstractGraph*);
    void addDivider();
    void AnnotationDisplayAdded(AnnotationDisplay*);
    void displaySizeChanged();
    void hideSettings(QScrollArea*);
    void showSettings(QScrollArea*);

protected:
    void displayTrack(const vector<track_entry>& track);
    QPointF pixelToGlCoords(QPoint pCoords, double z = 0);
    int openGlGridHeight();
    int openGlGridWidth();
    void initializeGL();
    void paintGL();
    
    void resizeGL(int width, int height);
    bool event(QEvent *);
    vector<string> mouseOverText(point2D oglCoords);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void drawSelectionBox(QPointF startPoint, QPointF endPoint);
    void translate(float dx, float dy);
    void translateOffset(float dx, float dy);
    void changeCursor(Qt::CursorShape cNumber);
    void placeMarker(QPoint);
    void redraw();
    void createCursors();

private:
    vector<AbstractGraph*> graphs;
    vector<color> colorTable;
    GLuint object;
    GLuint marker;
    QCursor zoomInCursor;
    QCursor zoomOutCursor;
    double xTransOffset;
    double yTransOffset;
    double zTransOffset;
    QPoint lastPos;
    int xPosition;
    int xOrigin;
    int border;
    int currentTool;
    int frame;
    QImage read_framebuffer(const QSize &size, bool alpha_format, bool include_alpha);
    void convertFromGLImage(QImage &img, int w, int h, bool alpha_format, bool include_alpha);
    int getTotalPixelWidth();
    bool selectionBoxVisible;
    QPointF startPoint;
    QPointF endPoint;
};
//! [3]
/* Alu Consensus Sequence 290bp
GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGGGAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGACCAGCCTGGCCAACAT
GGTGAAACCCCGTCTCTACTAAAAATACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCAGCTACTCGGGAGGCTGAGGCAGGAGAATCGCT
TGAACCCGGGAGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCCAGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAAAAA */

#define MOVE_TOOL 1
#define RESIZE_TOOL 2
#define SELECT_TOOL 3
#define ZOOM_TOOL 4
#define FIND_TOOL 5
#define SCREENCAPTURE_TOOL 6

#endif
