#ifndef ENGINE
#define ENGINE
/* Game will be built like a linked list and a graph(tree). */
class Room {
	std::vector<std::shared_ptr<Room>> parent_nodes;
	std::vector<std::shared_ptr<Room>> child_nodes; 
	std::string name;
public:
	Room(std::vector<std::shared_ptr<Room>> ps, std::vector<std::shared_ptr<Room>> cs) : parent_nodes(ps), child_nodes(cs);
};
#endif
