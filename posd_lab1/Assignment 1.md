# Pattern Oriented Software Design 2022 Fall Assignment

## Assignment 1
#### Deadline: 09/19 Tue. 23:59

### Introduction

In this assignment, you are required to implement the classes: `Shape`, `Triangle`, `Rectangle`, `Circle`, and `TwoDimensionalVector` with the unit tests as you learned from the POSD class. Please practice test-driven development(TDD) to write the corresponding unit tests for each class first and then to implement the class methods. Note that deadline is at 23:59, 09/19(Tue.).

### Problem statement

In a two-dimensional Cartesian coordinate plane, there can be points, vectors, and shapes. These elements are needed to be implemented.

A `Point` is defined from an ordered pair on x-axis and y-axis, i.e., (3, 4) or (-12.7, 4.62). A `Vector`, though is usually defined by (*x*, *y*) representing its direction and magnitude, can also be defined from two points to represent the vector head and tail on the plane. For example, a vector with (5, 11) and (6, 12) indicates that it goes from (5, 11) to (6, 12) and has the length 1.414, as its magnitude.

For shapes, we have `Triangle`, `Rectangle`, and `Circle`. `Triangle` is defined from two vectors that connected with either one's head or tail. By these two vectors, the `area` of a triangle can be calculated with the cross product and the `perimeter` can be calculated with the vector length. `Rectangle` is also defined by two vectors connected with each other at either head or tail, but the vectors should be orthogonal. As `Triangle`, the `area` and `perimeter` of a `Rectangle` can be calculated with the vectors. For `Circle`, it is defined by one vector. The length of the vector is the radius of the circle.

### File structure

The file structure is as followed. The project has two parts: `src` and `test`. All unit tests should be implemented in `test` folder and all classes should be implemented in `src`. **Please follow our interface, file structure, and file name** because we will test your code with our test data. Although we will not modify your source code and just replace the test files, any compilation errors due to non-compliant change could fail the assignment.
```
.
├── bin
│   └── ut_all
├── src
│   ├── circle.h
│   ├── point.h
│   ├── rectangle.h
│   ├── shape.h
│   ├── triangle.h
│   └── two_dimensional_vector.h
├── test
│   ├── ut_circle.h
│   ├── ut_main.cpp
│   ├── ut_point.h
│   ├── ut_rectangle.h
│   ├── ut_triangle.h
│   └── ut_two_dimensional_vector.h
└── makefile
```

### Implementation

This section describes all implementation conditions that you should abide by. Please read them carefully.

`Point`: a class representing two-dimensional points on the plane. It takes two immutable values in double as `x` and `y`. Getters for `x` and `y` are required but no setters. Implementing `operator==` makes the point comparison easier. The `info` of a `Point` should follow the format:
```c++
(new Point(-4.586, -3.471))->info();
> "(-4.59, -3.47)"
```

`TwoDimensionalVector`: a class representing two-dimensional vector, which should be created by two `Point`s, `a` and `b` (vector head and tail). Getters for the two points are required but no setters. The `length` returns the distance of the two points representing the vector's magnitude. In addition, it can calculate cross product (`cross`) and dot product (`dot`) with another vector. The `info` of a `TwoDimensionalVector` should follow the format:
```c++
(new TwoDimensionalVector(
    new Point(-8.42, 3.42),
    new Point(-3.38, 4.3))
)->info();
> "Vector ((-8.42, 3.42), (-3.38, 4.30))"
```

`Shape`: an abstract class declaring the methods that all subtypes (`Rectangle`, `Triangle`, and `Circle`) should inherit and implement, including `area`, `perimeter`, and `info`.

`Triangle`: a subtype of `Shape`. `Triangle` should be created by two non-parallel vectors. Since we use two points to represent a vector, the two vectors should be connected at either head or tail side, for example, `Vector((0, 0), (3, 0))` and `Vector((3, 4), (3, 0))`. Please consider the conditions for triangle creation carefully.

Since that the magnitude of the cross product of two vectors equals the area of the parallelogram spanned by these two vectors, and that the are of the triangle is half of a parallelogram, the triangle area is the cross product divided by 2. For `perimeter`, the third side of triangle can be derived from the two vectors given. The direction of the third vector can point to either vectors. The `info` of a `Triangle` should follow the format:
```c++
(new Triangle(
    new TwoDimensionalVector(Point(0, 0), Point(3, 0)),
    new TwoDimensionalVector(Point(3, 4), Point(3, 0))
))->info();
> "Triangle (Vector ((0.00, 0.00), (3.00, 0.00)), Vector ((3.00, 4.00), (3.00, 0.00)))"
```

`Rectangle`: a subtype of `Shape`. `Rectangle` should be created by two orthogonal vectors as its length side and width side. As `Triangle`, these two vectors should connect with each other at either head or tail. Note that the two parallel vectors with same length are also not allowed.

To obtain the `length` and `width` of the rectangle, return the length of the first vector and the length of the second vector respectively. The `area` and `perimeter` can be calculated by the length of these two vectors. The `info` of a `Rectangle` should follow the format:
```c++
(new Rectangle(
    new TwoDimensionalVector(Point(-2, 1), Point(1.5, 0.47)),
    new TwoDimensionalVector(Point(-2, 1), Point(-1.47, 4.5))
))->info();
> "Rectangle (Vector ((-2.00, 1.00), (1.50, 0.47)), Vector ((-2.00, 1.00), (-1.47, 4.50)))"
```

`Circle`: a subtype of `Shape`. `Circle` should be created by a vector. The length of the vector is the radius of the circle. Use the vector to calculate circle `area` and `perimeter`. The `info` of a `Circle` should follow the format:
```c++
(new Circle(
    new TwoDimensionalVector(Point(-4.284, 0.264), Point(-4.827, 0.728))
))->info();
> "Circle (Vector ((-4.28, 0.26), (-4.83, 0.73)))"
```

- **Each class method declared in header files must be implemented and have at least one test case.**
- For all classes above, an exception should raise if we give any illegal input to the constructor. The exception type is not specified, which can be as simple as `string`.
- If the type of returned value is `double`, your assertion should compare the value with the error not greater than `0.001`.
- All `double` values should be rounded to two decimal place and be padded with 0 when turned into `string`, e.g., `-1.999` will be `"-2.00"`.
- You can use `M_PI` in `cmath` for calculation of π.
- You can use [GeoGebra](https://www.geogebra.org/calculator) to design your test data.

### Submission

Please follow the [environment setting](http://140.124.181.100/course/environment_setting) to setup your workspace, GitLab account, and repository. If the setting is correct, whenever you push your code to the repository, the repository will trigger a test job titled `posd2022f_<student_id>_HW` from [the CI server](http://140.124.181.97:8080/). You can check whether your unit tests pass from the test job. Once all tests pass, another test job will be trigger, `posd2022f_<student_id>_HW_TA`. In this job, your code will be tested with our test data. You can also check whether your code pass all tests we made. Make sure all tests pass before the deadline.

### Grading Rubrics

- Unit tests written by yourself: 50%.
- Unit tests written by TA: 50%.

### You Will Get 0 Points If

- your test still cannot be executed after the deadline; for example, your code fails to compile or a unit test breaks due to a runtime exception;
- you unit tests pass in an unreasonable way; for example, all tests use `ASSERT_TRUE(true)`;
- your code is copied from another student's assignment.


### Notes

- For unit testing, consider as many cases as possible.
- Discussion is encouraged but the code must be your own.
- Feel free to contact us if you have any suggestions or concerns.

### References

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

### TA Contact

    Name: James Jhang, Paul Lai
    Email: e8315402, xie57813 (gmail)
    Office room: 宏裕科技大樓 13F 1321(後門)
    Office hours: 10am - 12pm , Tue/Wed