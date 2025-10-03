#include <GL/freeglut.h>

// Globals

float squareSize = 0.2f;
float moveX = 0.0f;
bool piecePlaced = false;
bool JPiecePlaced = false;
bool TPiecePlaced = false;
bool IPiecePlaced = false;
bool tetrisClear = false;
bool showClearText = true; // controls blinking text
void toggleClearText(int); // blink function

float green[3] = { 0.0f, 1.0f, 0.0f };
float purple[3] = { 1.0f, 0.0f, 1.0f };
float red[3] = { 1.0f, 0.0f, 0.0f };
float yellow[3] = { 1.0f, 1.0f, 0.0f };
float blue[3] = { 0.0f, 0.0f, 1.0f };
float orange[3] = { 1.0f, 0.5f, 0.0f };
float cyan[3] = { 0.2f, 0.7f, 1.0f };
float white[3] = { 1.0f, 1.0f, 1.0f };

// Movable piece controlled by arrow keys
float squareX = 0.0f;
float squareY = 0.0f;
float currentColor[3] = { 0.2f, 0.7f, 1.0f };


// Helper Functions

void drawSquare(float x, float y, float s)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + s, y);
    glVertex2f(x + s, y + s);
    glVertex2f(x, y + s);
    glEnd();
}

// Pieces
void drawOPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x + s, y + s, s);
}

void drawIPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    for (int i = 0; i < 4; i++)
        drawSquare(x + i * s, y, s);
}

void drawTPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x + 2 * s, y, s);
    drawSquare(x + s, y + s, s);
}

void drawSPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x + s, y + s, s);
    drawSquare(x + 2 * s, y + s, s);
}

void drawZPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x + s, y, s);
    drawSquare(x + 2 * s, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x + s, y + s, s);
}

void drawLPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x, y + 2 * s, s);
    drawSquare(x + s, y, s);
}

void drawJPiece(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x, y + 2 * s, s);
    drawSquare(x - s, y, s);
}

// Rotated Pieces
void drawTPieceRight(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x, y + s, s);
    drawSquare(x + s, y + s, s);
    drawSquare(x, y + 2 * s, s);
}

void drawTPieceDown(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    drawSquare(x, y, s);
    drawSquare(x + s, y, s);
    drawSquare(x + 2 * s, y, s);
    drawSquare(x + s, y - s, s);
}

void drawIPieceVertical(float x, float y, float color[3])
{
    glColor3fv(color);
    float s = squareSize;
    for (int i = 0; i < 4; i++)
        drawSquare(x, y - i * s, s);
}

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,
        reinterpret_cast<const unsigned char*>(text));
}

// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.95f, 0.85f, "Ansari Franco E. Alip III");
    drawText(-0.95f, 0.70f, "Mark David Solomon");
    drawText(-0.95f, 0.55f, "Tn34");
    drawText(0.4f, 0.85f, "Tetris with Freeglut");

    if (!tetrisClear) {

        // Pre-placed blocks
        drawSPiece(-0.8f, -1.0f, green);
        drawTPieceRight(-1.0f, -1.0f, purple);
        drawZPiece(-1.0f, -0.6f, red);
        drawOPiece(0.4f, -0.8f, yellow);
        drawLPiece(0.2f, -1.0f, orange);
        drawJPiece(0.8f, -1.0f, blue);
        drawIPiece(0.2f, -0.4f, cyan);

        // Third piece (I)
        if (TPiecePlaced && !IPiecePlaced) {
            if (squareY > 0.9f) {
                drawIPiece(squareX, squareY, cyan);
            }
            else if (squareX < 0.0f) {
                moveX = 0.02f;
                drawIPieceVertical(squareX, squareY, cyan);
            }
            else if (squareY > -0.4f) {
                moveX = 0.0f;
                drawIPieceVertical(squareX, squareY, cyan);
            }
            else {
                drawIPieceVertical(0.0f, -0.4f, cyan);
                piecePlaced = IPiecePlaced = true;
                tetrisClear = true;

                // Start blinking text when cleared
                glutTimerFunc(500, toggleClearText, 0);
            }
        }
        else if (TPiecePlaced) {
            drawIPieceVertical(0.0f, -0.4f, cyan);
        }

        // Second piece (T)
        if (JPiecePlaced && !TPiecePlaced) {
            if (squareY > 0.6f) {
                drawTPiece(squareX, squareY, purple);
            }
            else if (squareX > -0.2f) {
                moveX = -0.02f;
                drawTPieceRight(squareX, squareY, purple);
            }
            else if (squareX > -0.4f && squareY > -0.5f) {
                moveX = -0.02f;
                drawTPieceDown(squareX, squareY, purple);
            }
            else if (squareX > -0.59f && squareY > -0.4f) {
                drawTPieceDown(squareX, squareY, purple);
            }
            else if (squareY > -0.4f) {
                moveX = 0.0f;
                drawTPieceDown(squareX, squareY, purple);
            }
            else {
                drawTPieceDown(-0.6f, -0.4f, purple);
                piecePlaced = TPiecePlaced = true;
                squareY = 1.0f;
                squareX = -0.4f;
            }
        }
        else if (JPiecePlaced) {
            drawTPieceDown(-0.6f, -0.4f, purple);
        }

        // First piece (J)
        if (!JPiecePlaced) {
            if (squareY > -1.0f) {
                drawJPiece(squareX, squareY, blue);
            }
            else if (squareX > -0.2f) {
                moveX = -0.02f;
                drawJPiece(squareX, squareY, blue);
            }
            else {
                drawJPiece(-0.2f, -1.0f, blue);
                piecePlaced = JPiecePlaced = true;
            }
        }
        else {
            drawJPiece(-0.2f, -1.0f, blue);
        }
    }
    else {


        // Blinking "ALL CLEAR!" text
        if (showClearText) {
            glColor3f(1.0f, 0.9f, 0.0f);
            drawText(-0.25f, 0.0f, "ALL CLEAR!");
        }
    }

    glutSwapBuffers();
}

// ======================
// Effects
// ======================


// blinking for text
void toggleClearText(int value) {
    showClearText = !showClearText;
    glutPostRedisplay();
    glutTimerFunc(500, toggleClearText, 0); // toggle every 500ms
}

// keyboard handling
void handleSpecialKeys(int key, int, int)
{
    const float step = 0.2f;
    switch (key) {
    case GLUT_KEY_LEFT:  squareX -= step; break;
    case GLUT_KEY_RIGHT: squareX += step; break;
    case GLUT_KEY_UP:    squareY += step; break;
    case GLUT_KEY_DOWN:  squareY -= step; break;
    }
    glutPostRedisplay();
}

void handleNormalKeys(unsigned char key, int, int)
{
    switch (key) {
    case 'r': case 'R': currentColor[0] = 1.0f; currentColor[1] = 0.1f; currentColor[2] = 0.1f; break;
    case 'g': case 'G': currentColor[0] = 0.2f; currentColor[1] = 1.0f; currentColor[2] = 0.2f; break;
    case 'b': case 'B': currentColor[0] = 0.2f; currentColor[1] = 0.5f; currentColor[2] = 1.0f; break;
    case 'c': case 'C':
        currentColor[0] = 0.2f; currentColor[1] = 0.7f; currentColor[2] = 1.0f;
        squareX = 0.0f; squareY = 0.0f;
        break;
    case 27: glutLeaveMainLoop(); return;
    }
    glutPostRedisplay();
}

//automatic movements
void update(int value)
{
    const float stepY = 0.02f;
    squareY -= stepY;
    squareX += moveX;

    if (squareY <= -1.0f) {
        squareY = -1.0f;
        if (piecePlaced) {
            piecePlaced = false;
            squareX = 0.0f;
            moveX = 0.0f;
            squareY = 1.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

//main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 520);
    glutCreateWindow("Pre-placed & Movable Tetromino Example");

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleNormalKeys);
    glutSpecialFunc(handleSpecialKeys);

    glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}
