case "$(uname)" in
Darwin)
  clang++ main.cpp -framework OpenGL -framework GLUT
  ;;
*)
  g++ main.cpp -lGL -lGLUT
  ;;
esac
