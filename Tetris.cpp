#include <GL/freeglut.h>

float squareX = 0.0f;
float squareY = 0.0f;
float squareSize = 0.1f;
float color[3] = {0.2f, 0.7f, 1.0f};

// Function to draw text on screen
void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_9_BY_15,
                     reinterpret_cast<const unsigned char*>(text));	
}

// Small helper: draw one square at (x, y) with size s
void drawSquare(float x, float y, float s)
{
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + s, y);
        glVertex2f(x + s, y + s);
        glVertex2f(x, y + s);
    glEnd();
}

/* =========================
   Tetromino Functions
   ========================= */

// O Piece (2x2 square)
void drawOPiece()
{
    float s = squareSize;
    drawSquare(squareX, squareY, s);
    drawSquare(squareX + s, squareY, s);
    drawSquare(squareX, squareY + s, s);
    drawSquare(squareX + s, squareY + s, s);
}

/*
// I Piece
void drawIPiece()
{
    float s = squareSize;
    for (int i = 0; i < 4; i++) {
        drawSquare(squareX + i*s, squareY, s);
    }
}

// T Piece
void drawTPiece()
{
    float s = squareSize;
    drawSquare(squareX, squareY, s);
    drawSquare(squareX + s, squareY, s);
    drawSquare(squareX + 2*s, squareY, s);
    drawSquare(squareX + s, squareY + s, s);
}
*/
// S Piece
void drawSPiece()
{
    float s = squareSize;
    drawSquare(squareX + s, squareY, s);
    drawSquare(squareX + 2*s, squareY, s);
    drawSquare(squareX, squareY + s, s);
    drawSquare(squareX + s, squareY + s, s);
}
/*
// Z Piece
void drawZPiece()
{
    float s = squareSize;
    drawSquare(squareX, squareY, s);
    drawSquare(squareX + s, squareY, s);
    drawSquare(squareX + s, squareY + s, s);
    drawSquare(squareX + 2*s, squareY + s, s);
}

// J Piece
void drawJPiece()
{
    float s = squareSize;
    drawSquare(squareX, squareY, s);
    drawSquare(squareX, squareY + s, s);
    drawSquare(squareX, squareY + 2*s, s);
    drawSquare(squareX + s, squareY, s);
}

// L Piece
void drawLPiece()
{
    float s = squareSize;
    drawSquare(squareX, squareY, s);
    drawSquare(squareX, squareY + s, s);
    drawSquare(squareX, squareY + 2*s, s);
    drawSquare(squareX - s, squareY, s);
}
*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(color);

    // Active Tetromino (currently O Piece)
    // drawOPiece();
    // Uncomment to test others:
    // drawIPiece();
    // drawTPiece();
     drawSPiece();
    // drawZPiece();
    // drawJPiece();
    // drawLPiece();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.95f, 0.85f, "Normal keys: R/G/B change color, C resets, Esc quits");
    drawText(-0.95f, 0.70f, "Arrow keys move the piece (handled by glutSpecialFunc)");

    glutSwapBuffers();
}

void handleNormalKeys(unsigned char key, int, int)
{
    switch (key) {
    case 'r':
    case 'R':
        color[0] = 1.0f; color[1] = 0.1f; color[2] = 0.1f;
        break;
    case 'g':
    case 'G':
        color[0] = 0.2f; color[1] = 1.0f; color[2] = 0.2f;
        break;
    case 'b':
    case 'B':
        color[0] = 0.2f; color[1] = 0.5f; color[2] = 1.0f;
        break;
    case 'c':
    case 'C':
        color[0] = 0.2f; color[1] = 0.7f; color[2] = 1.0f;
        squareX = 0.0f;
        squareY = 0.0f;
        break;
    case 27:
        glutLeaveMainLoop();
        return;
    default:
        return;
    }

    glutPostRedisplay();
}

void handleSpecialKeys(int key, int, int)
{
    const float step = 0.05f;
    switch (key) {
    case GLUT_KEY_LEFT:
        squareX -= step;
        break;
    case GLUT_KEY_RIGHT:
        squareX += step;
        break;
    case GLUT_KEY_UP:
        squareY += step;
        break;
    case GLUT_KEY_DOWN:
        squareY -= step;
        break;
    default:
        return;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 520);
    glutCreateWindow("glutKeyboardFunc example with movement");

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(handleNormalKeys);
    glutSpecialFunc(handleSpecialKeys);

    glutMainLoop();
    return 0;
}

