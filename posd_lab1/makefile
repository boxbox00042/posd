.PHONY: clean test

all: directories ut_main

TEST = test/ut_point.h \
		test/ut_two_dimensional_vector.h \
		test/ut_triangle.h \
		test/ut_rectangle.h \
		test/ut_circle.h \
		test/ut_shape.h \
		test/ut_compound_shape.h \
		test/iterator/ut_null_iterator.h \
		test/iterator/ut_list_compound_iterator.h \
		test/iterator/ut_dfs_compound_iterator.h \
		test/iterator/ut_bfs_compound_iterator.h \
		test/iterator/ut_illegal_node_iterator.h \
		test/iterator/ut_illegal_node_iterator_2.h \
		test/ut_bounding_box.h \
		test/visitor/ut_collision_detector.h \
		test/visitor/ut_closest_shape_finder.h \
		test/visitor/ut_illegal_node_checker.h \
		test/builder/ut_aabb_tree_builder.h \

SRC = src/point.h \
		src/two_dimensional_vector.h \
		src/triangle.h \
		src/rectangle.h \
		src/circle.h \
		src/shape.h \
		src/compound_shape.h \
		src/iterator/iterator.h \
		src/iterator/null_iterator.h \
		src/iterator/list_compound_iterator.h \
		src/iterator/dfs_compound_iterator.h \
		src/iterator/bfs_compound_iterator.h \
		src/iterator/illegal_node_iterator.h \
		src/iterator/factory/iterator_factory.h \
		src/iterator/factory/bfs_iterator_factory.h \
		src/iterator/factory/dfs_iterator_factory.h \
		src/iterator/factory/list_iterator_factory.h \
		src/iterator/factory/illegal_node_iterator_factory.h \
		src/bounding_box.h \
		src/visitor/shape_visitor.h \
		src/visitor/collision_detector.h \
		src/visitor/closest_shape_finder.h \
		src/visitor/illegal_node_checker.h \
		src/builder/aabb_tree_builder.h \

FACTORY = obj/dfs_iterator_factory.o \
		obj/bfs_iterator_factory.o \

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(FACTORY)
	g++ -std=c++17 test/ut_main.cpp $(FACTORY) -o bin/ut_all -lgtest -lpthread

obj/dfs_iterator_factory.o: src/iterator/factory/dfs_iterator_factory.h src/iterator/factory/dfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/dfs_iterator_factory.cpp -o obj/dfs_iterator_factory.o

# obj/dfs_step_iterator_factory.o: src/iterator/factory/dfs_step_iterator_factory.h src/iterator/factory/dfs_step_iterator_factory.cpp
# 	g++ -std=c++17 -c src/iterator/factory/dfs_step_iterator_factory.cpp -o obj/dfs_step_iterator_factory.o

obj/bfs_iterator_factory.o: src/iterator/factory/bfs_iterator_factory.h src/iterator/factory/bfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/bfs_iterator_factory.cpp -o obj/bfs_iterator_factory.o

# obj/bfs_step_iterator_factory.o: src/iterator/factory/bfs_step_iterator_factory.h src/iterator/factory/bfs_step_iterator_factory.cpp
# 	g++ -std=c++17 -c src/iterator/factory/bfs_step_iterator_factory.cpp -o obj/bfs_step_iterator_factory.o

directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf bin obj

test: all
	bin/ut_all
