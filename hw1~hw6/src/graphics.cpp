#include "./point.h"
#include "./two_dimensional_vector.h"
#include "./triangle.h"
#include "./rectangle.h"
#include "./circle.h"
#include "./shape.h"
#include "./compound_shape.h"
#include "./iterator/null_iterator.h"
#include "./iterator/list_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/bfs_compound_iterator.h"
#include "./bounding_box.h"
#include "./visitor/collision_detector.h"
#include "./builder/shape_parser.h"

#include "./utils/file_reader.h"
#include "./graphics/sdl_adapter.h"
#include "./graphics/sdl/sdl_renderer.h"
#include "./graphics/event_listener.h"
#include "./graphics/drag_and_drop/drag_and_drop.h"
#include "./graphics/drag_and_drop/command/command_history.h"
#include "./graphics/drag_and_drop/command/grab_command.h"
#include "./graphics/drag_and_drop/command/drop_command.h"
#include "./graphics/drag_and_drop/command/move_command.h"
#include "./graphics/drag_and_drop/command/undo_command.h"
#include "./graphics/drag_and_drop/command/refresh_command.h"

#include <iostream>

int main(int argc, char *args[])
{
    if (argc < 2)
    {
        std::cout << "Missing the path of input.txt" << std::endl;
        throw "Missing the path of input.txt";
    }
    FileReader reader(args[1]);
    std::string input = reader.read();
    ShapeParser parser(input);
    parser.parse();
    std::vector<Shape *> shapes = parser.getResult();

    EventListener *eventListener = new EventListener();
    SDL *renderer = new SDLRenderer(30, eventListener);   // Adaptee
    Canvas *canvas = new SDLAdapter(1024, 768, renderer); // Adapter

    DragAndDrop *dragAndDrop = new DragAndDrop(shapes);
    CommandHistory *commandHistory = new CommandHistory();
    eventListener->on("Left_Mouse_Down", new GrabCommand(dragAndDrop, commandHistory));
    eventListener->on("Left_Mouse_Move", new MoveCommand(dragAndDrop, commandHistory));
    eventListener->on("Left_Mouse_Up", new DropCommand(dragAndDrop, commandHistory));
    eventListener->on("Right_Mouse_Down", new UndoCommand(dragAndDrop, commandHistory));
    eventListener->on("Refresh", new RefreshCommand(canvas, shapes));
    canvas->display();

    for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); it++)
        delete (*it);
    delete eventListener;
    delete renderer;
    delete canvas;
}