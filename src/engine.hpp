#ifndef ENGINE
#define ENGINE
/* Game will be built like a linked list and a graph(tree). */
#include <vector>
#include <memory>
#include <string>
#include <map>

class World;
class Object;
class Room;
class Entity;

/**
 * @typedef Room wrapped in a shared_ptr to be able to connect it to other nodes.
 * 
 */
typedef std::shared_ptr<Room> node;
/**
 * @typedef Object wrapped in a unique_ptr, because it can be only owned by one Entity or Room.
 * 
 */
typedef std::unique_ptr<Object> item;
/**
 * @typedef Vector of nodes.
 * 
 */
typedef std::vector<node> nodes;
/**
 * @typedef Vector of items.
 * 
 */
typedef std::vector<item> items;


/**
 * @brief Base class for an NPC, user, or any other entity living in the game world.
 * 
 */
class Entity {
protected:	
	std::string entityName;
	int hp;
	int intelligence;
	int strength;
	std::string appearance;
public:
	/**
	 * @brief Construct a new Entity object
	 * 
	 * @param n (std::string): Name of the entitiy
	 * @param app (std::string): Description of the entity
	 */
	Entity(std::string n,std::string app):entityName(n),appearance(app){}
	
	/**
	 * @brief Get the Entity Name object
	 * 
	 * @return std::string The name of the entity be it an NPC, user or anything else.
	 */
	std::string getEntityName () const {return entityName;}
	/**
	 * @brief Get the HP of the Entity
	 * 
	 * @return int The HP of the entity, not const cuz it can change
	 */
	int getHP () {return hp;}
	/**
	 * @brief Get the intelligence of the entity
	 * 
	 * @return int The intelligence of the enemy, not const it can change
	 */
	int getInt () {return intelligence;}
	/**
	 * @brief Get the strength of the entity
	 * 
	 * @return int The strength of the entity, it can change
	 */
	int getStr () {return strength;}
	/**
	 * @brief Get the appeareance of an entity
	 * 
	 * @return std::string The appearance of any entity, can't change
	 */
	std::string getApp () const {return appearance;}
};
/**
 * @brief Hero of the story
 * 
 */
class Hero : public Entity {
	int heroID;

};

/**
 * @brief Part of the World. A room that contains items, that can be collected.
 * 
 * 
 */
class Room {
	nodes neighbours; // Neighbouring rooms.
	std::string roomName; // Name of the room.
	std::string roomID; // ID of the room, that connects a key to this room.
	items inventory; // Items, that can be found in the room.
	std::string description; // Description of the room.
public:
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 */
	Room(const std::string& n) : roomName(n) {}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (item&): An item that will be added to the inventory of the room.
	 */
	Room(const std::string& n, item& inv) : roomName(n) {inventory.push_back(std::move(inv));}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (items&): Vector of items, that will be added to the inventory of the room.
	 */
	Room(const std::string& n, items& inv) : roomName(n) {
		addItems(inv);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param ne (node&): A node that will be added to the neighbours of the room.
	 */
	Room(const std::string& n, node& ne) : roomName(n) {
		addNeighbour(ne);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param ns (nodes&): Nodes that will be the neighbourhood of the room.
	 */
	Room(const std::string& n, nodes& ns) : roomName(n) {
		addNeighbours(ns);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (item&): An item that will be added to the inventory of the room.
	 * @param ne (node&): A node that will be added to the neighbours of the room.
	 */
	Room(const std::string& n, item& inv, node& ne) : roomName(n) {
		inventory.push_back(std::move(inv));
		addNeighbour(ne);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (item&): An item that will be added to the inventory of the room.
	 * @param ns (nodes&): Nodes that will be the neighbourhood of the room.
	 */
	Room(const std::string& n, item& inv, nodes& ns) : roomName(n) {
		inventory.push_back(std::move(inv));
		addNeighbours(ns);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (items&): Vector of items, that will be added to the inventory of the room. 
	 * @param ne (node&): A node that will be added to the neighbours of the room.
	 */
	Room(const std::string& n, items& inv, node& ne) : roomName(n) {
		addNeighbour(ne);
		addItems(inv);
	}
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (const std::string&): The name of the room.
	 * @param inv (items&): Vector of items, that will be added to the inventory of the room. 
	 * @param ns (nodes&): Nodes that will be the neighbourhood of the room.
	 */
	Room(const std::string& n, items& inv, nodes& ns) : roomName(n) {
		addNeighbours(ns);
		addItems(inv);
	}
	/**
	 * @brief Get the Name object
	 * 
	 * @return roomName (std::string) 
	 */
	std::string getName() const {return roomName;}
	/**
	 * @brief Get the Neighbours object
	 * 
	 * @return neighbours (const nodes) 
	 */
	nodes getNeighbours() const {return neighbours;}	
	/**
	 * @brief Add a neighbour to the Neighours object
	 * 
	 * @param nn (node&) A new Room, that will be added to the Neighbours object.
	 * @return Room&
	 */
	Room& addNeighbour(node& nn) {
		neighbours.push_back(node(nn));
		return *this;
	}
	/**
	 * @brief Add multiple neighbours to the Neighbours object 
	 * 
	 * @param ns (nodes&) Vector of Neighbours object 
	 * @return Room& 
	 */
	Room& addNeighbours(nodes& ns) {
		for (nodes::const_iterator it = ns.cbegin(); it != ns.cend(); it++) {
			neighbours.push_back(node(*it));
		}
		return *this;
	}
	/**
	 * @brief Get the Items object
	 * 
	 * @return items const& 
	 */
	items const& getItems() {return inventory;}	
	/**
	 * @brief Add new item to the Inventory of the Room 
	 * 
	 * @param i (item&) new Item
	 * @return Room& 
	 */
	Room& addItem(item& i) {
		inventory.push_back(item(std::move(i)));
		return *this;
	}
	/**
	 * @brief Add new Items to the Inventory of the Room 
	 * 
	 * @param inv (items&) Vector of Items to be added to the Inventory of the Room
	 * @return Room& 
	 */
	Room& addItems(items& inv) {
		for (items::iterator it = inv.begin(); it != inv.end(); it++) {
			inventory.push_back(item(std::move(*it)));
		}
		return *this;
	}
};

/**
 * @brief Base class for any object that can be owned by an Entity or Room.
 * 
 */
class Object {
	std::string objectName;
public:
	/**
	 * @brief Construct a new Object object
	 * 
	 * @param n (std::string&) Name of the Object
	 */
	Object(const std::string& n) : objectName(n) {}
	/**
	 * @brief Get the Name object
	 * 
	 * @return objectName (std::string) 
	 */
	std::string getName() const {return objectName;}
};

/**
 * @brief An object that can open a room.
 * 
 */
class Key : public Object {
	std::string keyID;
};
#endif