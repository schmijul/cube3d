#include <GL/glut.h>
#include <math.h>

// Animation state
float rotationAngle = 0.0f;
float colorPhase = 0.0f;

// Vertex coordinates for the cube
GLfloat vertices[][3] = {
    {-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, 
    {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5},
    {-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5},
    {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}
};

// Color data for each vertex
GLfloat colors[][3] = {
    {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
    {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0},
    {1.0, 1.0, 1.0}, {0.5, 0.5, 0.5}
};

// Function to draw a face of the cube
void drawFace(int a, int b, int c, int d) {
    glBegin(GL_QUADS);
    float phase = colorPhase;
    
    // Calculate smooth color transitions
    float colorR = (sin(phase + vertices[a][0]) + 1.0f) / 2.0f;
    float colorG = (sin(phase + vertices[a][1] + 2.0f) + 1.0f) / 2.0f;
    float colorB = (sin(phase + vertices[a][2] + 4.0f) + 1.0f) / 2.0f;
    
    glColor3f(colorR, colorG, colorB);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

// Display function - called for each frame
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Position the camera
    gluLookAt(0.0f, 0.0f, 3.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);
    
    // Apply rotations
    glRotatef(rotationAngle, 1.0f, 1.0f, 1.0f);
    
    // Draw all faces of the cube
    drawFace(0, 1, 2, 3); // Front
    drawFace(1, 5, 6, 2); // Right
    drawFace(5, 4, 7, 6); // Back
    drawFace(4, 0, 3, 7); // Left
    drawFace(3, 2, 6, 7); // Top
    drawFace(4, 5, 1, 0); // Bottom
    
    glutSwapBuffers();
}

// Update function for animation
void update(int value) {
    rotationAngle += 2.0f;
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    
    colorPhase += 0.05f;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS timing
}

// Initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Animated Cube");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}
