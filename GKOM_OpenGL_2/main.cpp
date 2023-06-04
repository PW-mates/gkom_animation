#include "OpenGLWindow.h"

// Remaining task list:
// 1. support for basic input file type with 3D model : obj - done
// 2. Phong shading - done
// 3. interpretation of material properties : diffuse, specular - done
// 4. point light support - the ability to move the light, edit
//  properties of light - done
// 5. the ability to make a simple animation :
//  (a)inserting and editing keyframes for transformations(translation,
//      rotation, scaling)
//  (b)fixed and linear interpolation between frames
// 6. perspective camera - the ability to move around the stage and rotate
// 7. the ability to render animation to a video file


int main()
{
    Program::setProgramsDirectory("../Resources/Shaders/");
    
    OpenGLWindow openglWindow;

    openglWindow.InitWindow();
    
    openglWindow.InitScene();

    openglWindow.MainLoop();

    return 0;
}