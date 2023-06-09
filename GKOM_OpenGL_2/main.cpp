#include "OpenGLWindow.h"
#include <iostream>

// Remaining task list:
// 1. support for basic input file type with 3D model : obj - done
// 2. Phong shading - done
// 3. interpretation of material properties : diffuse, specular - done
// 4. point light support - the ability to move the light, edit
//  properties of light - done
// 5. the ability to make a simple animation:
//  (a)inserting and editing keyframes for transformations(translation,
//      rotation, scaling) - done
//  (b)fixed and linear interpolation between frames - done
// 6. perspective camera - the ability to move around the stage and rotate
// 7. the ability to render animation to a video file

int main(int argc, char **argv)
{
    std:char *sceneFolder;
    WorkingMode mode = WorkingMode::Frame;
    int frame = 0;

    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path to scene file>"
                  << " [frame/preview/render]"
                  << " [frame=0]" << std::endl;
        return 1;
    } else {
        sceneFolder = argv[1];
    }
    if (argc >= 3)
    {
        if (strcmp(argv[2], "frame") == 0)
        {
			mode = WorkingMode::Frame;
		}
		else
        if (strcmp(argv[2], "preview") == 0)
        {
            mode = WorkingMode::Preview;
        }
        else if (strcmp(argv[2], "render") == 0)
        {
            mode = WorkingMode::Render;
        }
    }
    if (argc >= 4)
    {
        frame = atoi(argv[3]);
    }

    Program::setProgramsDirectory(sceneFolder);
    Program::setWorkingMode(mode);
    Program::setFrame(frame);

    std::string outputDirectory = sceneFolder + std::string("\\output");
    struct stat info;
    if (stat(outputDirectory.c_str(), &info) == -1) {
        std::filesystem::create_directory(outputDirectory);
    }
    Program::setOutputDirectory(outputDirectory);

    OpenGLWindow openglWindow;

    openglWindow.InitWindow();

    openglWindow.InitScene();

    openglWindow.MainLoop();

    return 0;
}