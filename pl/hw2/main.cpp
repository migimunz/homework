#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    std::cerr << "USAGE: " << argv[0] << " [heapsize]\n";
    return 1;
  }

  int heapsize = std::atoi(argv[1]);
  if(heapsize < 0 || heapsize % 2 == 1) {
    std::cerr << "Heap size must be positive and even.\n";
    return 1;
  }

  Heap heap(heapsize);

  std::string line;
  while(std::getline(std::cin, line)) {
    std::stringstream stream(line);
    std::string command;
    stream >> command;

    if(command == "set") {
      // Usage: set [field path] = [field path]
      // OR:    set [field path] = new [type]
      // Example: set a b c = d e
      // OR:      set a = new Yogurt
      // TODO
    }
    else if(command == "type") {
      // Usage: type [name] [field list]
      // Example: type BinaryTreeNode pparent pleft pright fvalue
      // All fields are four bytes at the moment...
      Type::create(stream);
    }
    else {
      std::cerr << "Unknown command: \"" << command << "\"\n";
    }
  }

  return 0;
}
