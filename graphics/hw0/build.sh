case "$(uname)" in
Darwin)
  clang++ -DDARWIN main.cpp -framework OpenGL -framework GLUT
  ;;
*)
  g++ -DLINUX main.cpp -lGL -lGLU -lglut
  ;;
esac
