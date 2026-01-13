
GLFWDIR=$(realpath ~/local)
g++ -I"$GLFWDIR/include" -L"$GLFWDIR"/lib -framework OpenGL -framework Cocoa -framework IOKit -framework QuartzCore -lglfw3 src/main.cpp src/Framework.cpp src/plot.cpp src/world.cpp src/character.cpp src/plotwindow.cpp src/background.cpp src/dynamicobject.cpp src/plotcamera.cpp src/plotinteractor.cpp -o build/plot_window
