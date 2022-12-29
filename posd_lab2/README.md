# Pattern Oriented Software Design 2022 Final Exam

### Deadline: 12/26 Mon. 16:00

## Introduction

In this exam, you are asked to apply the `Observer` pattern to redraw the shapes.

The deadline is at 16:00, 12/26(Mon.).

## Problem statement

In the last assignment, we have complete the drag and drop function on shapes. When a shape is moved, its position on window should be repainted. However, the existing implementation depends on polling, meaning that the window actively asks for repainting every 50ms. In this exam, you are asked to replace the polling with a `Observer`, by which the window repaints shapes only when the shape is moved.

Below is the structure of the `Observer` pattern. The `Subject` refers to an observable, the one that is operated. It knows several `Observer`s. Whenever there is a new changes on the subject, the subject notifies its observers to update their states by getting new states from the subject.

![Observer structure](/materials/ObserverStructure.png)

The class diagram is shown below. On the left side of the diagram, there are classes we used to open a window and render shapes. On the right side, the classes with bolder borders are the ones you need to implement:

1. The standard interfaces of the `Observer` pattern, `Subject` and `Observer`.
2. The `Drawing` class, which represents the rendered shapes. It owns the shape instances. Classes that need to make changes on shapes should ask `Drawing` for access.
3. The `RealCanvas` class, which helps to repaint shapes on the window. It is *attached* on the `Drawing` for monitoring any changes happen on the shapes.

![Observer class diagram](/materials/Observer.png)

When we click and move a shape, the correspond commands are triggered to call the DragAndDrop to carry out the drag function. In the previous assignment, the DragAndDrop takes the shape instances directly; in this exam instead, it takes `Drawing` to access the shape instances. It asks `Drawing` to get all shapes to find out the one the user chosen.

After moving a shape, the DragAndDrop has to let the `RealCanvas` know that there is a new change on shapes, meaning that it should call `notify` from `Drawing`.

Then, the `RealCanvas` gets notified because it is attached on the `Drawing`. It calls `ShapePrinter` to redraw shapes on the window.

In this exam, you are asked to apply the `Observer` pattern, the four classes described above, to replace the polling used in the previous assignment.

## File structure

The file structure is as followed. The project has two parts: `src` and `test`. All unit tests should be implemented in `test` folder and all classes should be implemented in `src`. **Please follow our interface, file structure, and file name** because we will test your code with our test data. Although we will not modify your source code and just replace the test files, any compilation errors due to non-compliant change could fail the assignment.
```diff
 .
 ├── bin
 │   └── ut_all
 ├── src
 │   ├── builder
 |   |   ├── scanner.h
 |   |   ├── shape_builder.h
 |   |   └── shape_parser.h
 │   ├── graphics
 |   |   ├── drag_and_drop
 |   |   |   ├── command
 |   |   |   |   ├── command.h
 |   |   |   |   ├── grab_command.h
 |   |   |   |   ├── move_command.h
 |   |   |   |   ├── drop_command.h
 |   |   |   |   ├── undo_command.h
 |   |   |   |   ├── macro_command.h
 |   |   |   |   ├── command_history.h
 |   |   |   |   └── refresh_command.h
 |   |   |   ├── drag_and_drop.h
 |   |   |   └── mouse_position.h
+|   |   ├── observer
+|   |   |   ├── observer.h
+|   |   |   └── subject.h
 |   |   ├── sdl
 |   |   |   ├── piece
 |   |   |   |   ├── cir_piece.h
 |   |   |   |   ├── line_piece.h
 |   |   |   |   └── piece.h
 |   |   |   ├── sdl_renderer.h
 |   |   |   └── sdl.h
 |   |   ├── canvas.h
 |   |   ├── event_listener.h
+|   |   ├── drawing.h
+|   |   ├── real_canvas.h
 |   |   └── sdl_adapter.h
 │   ├── iterator
 |   |   ├── factory
 |   |   |   ├── iterator_factory.h
 |   |   |   ├── iterator_factory.cpp
 |   |   |   ├── bfs_iterator_factory.h
 |   |   |   ├── bfs_iterator_factory.cpp
 |   |   |   ├── dfs_iterator_factory.h
 |   |   |   ├── dfs_iterator_factory.cpp
 |   |   |   ├── list_iterator_factory.h
 |   |   |   └── list_iterator_factory.cpp
 │   │   ├── bfs_compound_iterator.h
 │   │   ├── dfs_compound_iterator.h
 |   |   ├── list_compound_iterator.h
 │   │   ├── iterator.h
 │   │   └── null_iterator.h
 │   ├── utils
 │   │   └── file_reader.h
 │   ├── visitor
 │   │   ├── shape_visitor.h
 │   │   └── collision_detector.h
 │   ├── bounding_box.h
 │   ├── circle.h
 │   ├── compound_shape.h
 │   ├── point.h
 │   ├── rectangle.h
 │   ├── shape.h
 │   ├── triangle.h
 │   ├── two_dimensional_vector.h
 │   └── graphics.cpp
 ├── test
 │   ├── builder
 |   |   ├── ut_scanner.h
 |   |   ├── ut_shape_builder.h
 |   |   └── ut_shape_parser.h
 │   ├── graphics
 |   |   ├── drag_and_drop
 |   |   |   ├── command
 |   |   |   |   ├── mock_command.h
 |   |   |   |   ├── ut_grab_command.h
 |   |   |   |   ├── ut_move_command.h
 |   |   |   |   ├── ut_drop_command.h
 |   |   |   |   ├── ut_undo_command.h
 |   |   |   |   ├── ut_macro_command.h
 |   |   |   |   └── ut_command_history.h
 |   |   |   └── mock_drag_and_drop.h
+|   |   ├── observer
+|   |   |   ├── mock_observer.h
+|   |   |   └── ut_subject.h
 |   |   ├── mock_sdl_renderer.h
+|   |   ├── ut_drawing.h
+|   |   ├── ut_real_canvas.h
 |   |   └── ut_sdl_adapter.h
 │   ├── iterator
 │   │   ├── ut_bfs_compound_iterator.h
 │   │   ├── ut_dfs_compound_iterator.h
 │   │   └── ut_null_iterator.h
 │   ├── utils
 │   │   ├── test_input.txt
 │   │   └── ut_file_reader.h
 │   ├── visitor
 │   │   └── ut_collision_detector.h
 │   ├── ut_bounding_box.h
 │   ├── ut_circle.h
 │   ├── ut_compound_shape.h
 │   ├── ut_main.cpp
 │   ├── ut_point.h
 │   ├── ut_rectangle.h
 │   ├── ut_triangle.h
 │   └── ut_two_dimensional_vector.h
 └── makefile
```

## Implementation

**This section describes all implementation conditions that you should abide by. Please read them carefully.**

To support the `Observer` pattern, you first need to copy the files below to update their implementation.

* [graphics.app](src/graphics.cpp)
* [drag_and_drop.h](src/graphics/drag_and_drop/drag_and_drop.h)

`Subject`: the `Subject` interface. It basically has three methods: `attach`, `detach`, and `notify`.

`attach` takes an observer pointer as an argument and saves the observer in `Subject`. `detach` also takes an observer pointer as an argument. It removes the corresponding observer from `Subject`. An exception should be threw if the observer passed-in is not found. `notify` notifies all observers the `Subject` owns by calling their `update`.

**Note that `Subject` does not have the ownership of observers.** It does NOT delete observer in its destructor.

`Subject` has an additional method: `getObservers` to return its observers for testability.

`Observer`: the `Observer` interface. It has one method: `update`. This method is virtual and takes no argument. It should be overridden by subclasses.

`Drawing`: a class owning all shape instances. It inherits from the `Subject` class. Since `Subject` does not have virtual methods, `Drawing` does not override any methods.

Its constructor takes a vector of the pointers to shapes as an argument. **`Drawing` owns these shapes. It is responsible for deleting shapes when being destroyed.**

`Drawing` has an additional method named `shapes`, which returns the vector to let other classes make manipulation on shapes.

`RealCanvas`: a class helping to repaint shapes on the window. It is an `Observer`. The overridden method `update` of `RealCanvas` uses `ShapePrinter` to redraw all shapes. **You can refer to the `RefreshCommand` written in the previous assignment.**

Its constructor takes the instances of `Canvas` and `Drawing` as the arguments. **You can make a decision whether `RealCanvas` attaches itself to the `Drawing` in its constructor or let `graphics.cpp` do this.** If you want `RealCanvas` to attach itself to the `Drawing` in its constructor, remember to remove the statement at line 51 in `graphics.cpp`.

**`RealCanvas` does not own the `Canvas` and `Drawing`.**

- **Each class method declared in header files must be implemented and have at least one test case.**
- **No tests are required for the Observer class because is only has a virtual method.**
- For all classes above, an exception should raise if we give any illegal input to the constructor. The exception type is not specified, which can be as simple as `string`.
- If the type of returned value is `double`, your assertion should compare the value with the error not greater than `0.001`.
- All `double` values should be rounded to two decimal place and be padded with 0 when turned into `string`, e.g., `-1.999` will be `"-2.00"`.
- You can use `M_PI` in `cmath` for calculation of π.
- You can use [GeoGebra](https://www.geogebra.org/calculator) to design your test data.

## Submission

Please use the [workspace](http://140.124.181.100/course/environment_setting) you have setup in assignment 1. If the setting is correct, whenever you push your code to the repository, the repository will trigger a test job titled `posd2022f_<student_id>_HW` from [the CI server](http://140.124.181.97:8080/). You can check whether your unit tests pass from the test job. Once all tests pass, another test job will be trigger, `posd2022f_<student_id>_HW_TA`. In this job, your code will be tested with our test data. You can also check whether your code pass all tests we made. Make sure all tests pass before the deadline.

## Grading Rubrics

- Unit tests written by yourself: 50%.
- Unit tests written by TA: 50%.
- To save time, no points are deducted for any memory leaks, but you are encouraged to eliminate leaks where possible.

## You Will Get 0 Points If

- your test still cannot be executed after the deadline; for example, your code fails to compile or a unit test breaks due to a runtime exception;
- you unit tests pass in an unreasonable way; for example, all tests use `ASSERT_TRUE(true)`;
- your code is copied from another student's assignment.


## Notes

- For unit testing, consider as many cases as possible.
- Discussion is encouraged but the code must be your own.
- Feel free to contact us if you have any suggestions or concerns.

## References

- [POSD2022F course link](http://140.124.181.100/yccheng/posd2022f)
- [Environment setting](http://140.124.181.100/course/environment_setting)
- [Makefile tutorial](http://140.124.181.100/course/makefile_tutorial)
- [C++.com](http://www.cplusplus.com/reference/)
- [C++ exception handling](https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm)
- [Vector introduction](https://mathinsight.org/cross_product_formula)
- [Magnitude(length) of a vector](https://mathinsight.org/definition/magnitude_vector)
- [Dot product formula](https://mathinsight.org/dot_product_formula_components)
- [Cross product formula](https://mathinsight.org/cross_product_formula)
- [GeoGebra](https://www.geogebra.org/calculator)
- [Depth-First Search](https://www.wikiwand.com/en/Depth-first_search)
- [Breadth-First Search](https://www.wikiwand.com/en/Breadth-first_search)
- [Stack and Heap Memory](https://courses.engr.illinois.edu/cs225/fa2022/resources/stack-heap/)
- [SDL tutorials](https://lazyfoo.net/tutorials/SDL/index.php)
- [Drag and drop](https://www.wikiwand.com/en/Drag_and_drop)
## TA Contact

    Name: James Jhang, Paul Lai
    Email: e8315402, xie57813 (gmail)
    Office room: 宏裕科技大樓 13F 1321(後門)
    Office hours: 10am - 12pm , Tue/Wed