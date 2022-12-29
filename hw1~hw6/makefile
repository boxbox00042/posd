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
		test/ut_bounding_box.h \
		test/visitor/ut_collision_detector.h \
		test/builder/ut_shape_builder.h \
		test/builder/ut_scanner.h \
		test/builder/ut_shape_parser.h \
		test/utils/ut_file_reader.h \


GRAPHICS_TEST = test/graphics/mock_sdl_renderer.h \
		test/graphics/ut_sdl_adapter.h \
		test/graphics/drag_and_drop/command/ut_commany_history.h \
		test/graphics/drag_and_drop/mock_drag_and_drop.h \
		test/graphics/drag_and_drop/command/ut_grab_command.h \
		test/graphics/drag_and_drop/command/ut_move_command.h \
		test/graphics/drag_and_drop/command/ut_drop_command.h \
		test/graphics/drag_and_drop/command/ut_undo_command.h \
		test/graphics/drag_and_drop/command/ut_macro_command.h \

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
		src/iterator/factory/iterator_factory.h \
		src/iterator/factory/bfs_iterator_factory.h \
		src/iterator/factory/dfs_iterator_factory.h \
		src/iterator/factory/list_iterator_factory.h \
		src/bounding_box.h \
		src/visitor/shape_visitor.h \
		src/visitor/collision_detector.h \
		src/builder/shape_builder.h \
		src/builder/scanner.h \
		src/builder/shape_parser.h \
		src/utils/file_reader.h \
		src/visitor/shape_printer.h \

GRAPHICS = src/graphics/canvas.h \
		src/graphics/sdl_adapter.h \
		src/graphics/sdl/sdl.h \
		src/graphics/sdl/sdl_renderer.h \
		src/graphics/sdl/piece/piece.h \
		src/graphics/sdl/piece/cir_piece.h \
		src/graphics/sdl/piece/line_piece.h \
        src/graphics/event_listener.h \
        src/graphics/drag_and_drop/drag_and_drop.h \
        src/graphics/drag_and_drop/mouse_position.h \
        src/graphics/drag_and_drop/command/command.h \
        src/graphics/drag_and_drop/command/command_history.h \
        src/graphics/drag_and_drop/command/grab_command.h \
        src/graphics/drag_and_drop/command/drop_command.h \
        src/graphics/drag_and_drop/command/move_command.h \
        src/graphics/drag_and_drop/command/undo_command.h \
        src/graphics/drag_and_drop/command/refresh_command.h \

FACTORY = obj/iterator_factory.o \
		obj/dfs_iterator_factory.o \
		obj/bfs_iterator_factory.o \
		obj/list_iterator_factory.o \

sdl: src/graphics.cpp $(SRC) $(GRAPHICS) $(FACTORY)
	g++ -std=c++17 src/graphics.cpp $(FACTORY) -o bin/graphics -lSDL2 -lSDL2_image

ut_main: test/ut_main.cpp $(TEST) $(GRAPHICS_TEST) $(SRC) $(GRAPHICS) $(FACTORY)
	g++ -std=c++17 test/ut_main.cpp $(FACTORY) -o bin/ut_all -lgtest -lpthread

obj/iterator_factory.o: src/iterator/factory/iterator_factory.h src/iterator/factory/iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/iterator_factory.cpp -o obj/iterator_factory.o

obj/dfs_iterator_factory.o: src/iterator/factory/dfs_iterator_factory.h src/iterator/factory/dfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/dfs_iterator_factory.cpp -o obj/dfs_iterator_factory.o

# obj/dfs_step_iterator_factory.o: src/iterator/factory/dfs_step_iterator_factory.h src/iterator/factory/dfs_step_iterator_factory.cpp
# 	g++ -std=c++17 -c src/iterator/factory/dfs_step_iterator_factory.cpp -o obj/dfs_step_iterator_factory.o

obj/bfs_iterator_factory.o: src/iterator/factory/bfs_iterator_factory.h src/iterator/factory/bfs_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/bfs_iterator_factory.cpp -o obj/bfs_iterator_factory.o

# obj/bfs_step_iterator_factory.o: src/iterator/factory/bfs_step_iterator_factory.h src/iterator/factory/bfs_step_iterator_factory.cpp
# 	g++ -std=c++17 -c src/iterator/factory/bfs_step_iterator_factory.cpp -o obj/bfs_step_iterator_factory.o

obj/list_iterator_factory.o: src/iterator/factory/list_iterator_factory.h src/iterator/factory/list_iterator_factory.cpp
	g++ -std=c++17 -c src/iterator/factory/list_iterator_factory.cpp -o obj/list_iterator_factory.o

directories:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -rf bin obj

test: all
	bin/ut_all

graphics: directories sdl
	bin/graphics ./input.txt

# valgrind: CXXFLAGS += -O0 -g
valgrind: clean all
	valgrind \
	--tool=memcheck --error-exitcode=1 --track-origins=yes --leak-check=full --leak-resolution=high \
	--num-callers=50 --show-leak-kinds=definite,possible --show-error-list=yes \
	bin/ut_all --gtest_output=xml:result.xml

