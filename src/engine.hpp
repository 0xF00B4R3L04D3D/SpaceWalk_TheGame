#ifndef ENGINE
#define ENGINE
/* Game will be built like a linked list and a graph(tree). */
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "tinyxml2.h"

class World;
class Object;
class Room;
class Entity;
class Mission;
class Choice;

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
 * @typedef Entity wrapped in shared_ptr, so World can keep track.
 * 
 */
typedef std::shared_ptr<Entity> ent;
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
 * @typedef Vector of entities.
 * 
 */
typedef std::vector<ent> entities;

/**
 * @brief Base class for a NPC, USER or any other Entity living in the game world.
 * 
 */
class Entity {
	const std::string name;
	items inventory;
	int hp;
	int stamina;
	int intelligence;
	int agility;
	int strenght;
	int stealth;
	int carisma;
public:
	/**
	 * @brief Construct a new Entity object
	 * 
	 * @param n (std::string)
	 */
	Entity(const std::string& n) : name(n) {}
	/**
	 * @brief Get the Name of the Entity
	 * 
	 * @return std::string 
	 */
	std::string getName() const {return name;}
	/**
	 * @brief Add Item to Entity's inventory
	 * 
	 * @param i (item&): Item to move to Entity's inventory
	 * @return Entity&
	 */
	Entity& addItem(item& i) {
		inventory.emplace_back(std::move(i));
		return *this;
	}
	~Entity() {
		for (items::iterator it = inventory.begin(); it != inventory.end(); it++) {
			it->reset();
		}
	}
};

/**
 * @brief Part of the World. A room that contains items, that can be collected, players or npc can move in and out of these rooms.
 * 
 * 
 */
class Room {
	nodes neighbours; // Neighbouring rooms.
	const std::string roomName; // Name of the room.
	const int roomID; // ID of the room, that connects a key to this room.
	items inventory; // Items, that can be found in the room.
	const std::string description; // Description of the room.
	bool locked;
public:
	/**
	 * @brief Construct a new Room object
	 * 
	 * @param n (std::string&): Name of the Room that cant be changed later. 
	 * @param id (int): This have to be a unique ID to be able to connect keys with rooms. 
	 * @param desc (std::string&): Description of the room. Cant be changed later.
	 */
	Room(const std::string& n, int id, const std::string& desc) : roomName(n), roomID(id), description(desc) {}
	/**
	 * @brief Get the Name of the Room
	 * 
	 * @return roomName (std::string) 
	 */
	std::string getName() const {return roomName;}
	/**
	 * @brief Get the roomID of the Room 
	 * 
	 * @return roomID (int) 
	 */
	int getID() const {return roomID;}
	/**
	 * @brief Get the Description of the Room
	 * 
	 * @return description (std::string) 
	 */
	std::string getDescription() const {return description;}
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
		inventory.emplace_back(std::move(i));
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
			inventory.emplace_back(std::move(*it));
		}
		return *this;
	}
	/**
	 * @brief Destroy the Room object. Reset all nodes in the neighours vector and all items in inventory.
	 *
	 * 
	 */
	~Room() {
		for (nodes::iterator nit = neighbours.begin(); nit != neighbours.end(); nit++) {
			nit->reset();
		}
		for (items::iterator iit = inventory.begin(); iit != inventory.end(); iit++) {
			iit->reset();
		}
		std::cerr << "LOG: RoomID: " << roomID << " deleted" << std::endl;
	}
};

/**
 * @brief Base class for any object that can be owned by an Entity or Room.
 * 
 */
class Object {
	const std::string objectName;
	const std::string objectDescriptor;
	const int objID;
public:
	/**
	 * @brief Construct a new Object object
	 * 
	 * @param n (std::string&) Name of the Object
	 * @param d (std::string&): Description of the object
	 * @param id (int): Creation ID of the item
	 */
	Object(const std::string& n, const int id, const std::string& d) : objectName(n), objID(id), objectDescriptor(d) {}
	/**
	 * @brief Get the Name object
	 * 
	 * @return objectName (std::string) 
	 */
	std::string getName() const {return objectName;}
	/**
	 * @brief Get the ID of the object
	 * 
	 * @return objID (int) 
	 */
	int getID() const {return objID;}
	/**
	 * @brief Get the Description of the object
	 * 
	 * @return objectDescription (std::string) 
	 */
	std::string getDescription() const {return objectDescriptor;}
	~Object() {
		std::cerr << "LOG: ObjectID: " << objID << " deleted" << std::endl;
	}
};

/**
 * @brief An object that can open a room.
 * 
 */
class Key : public Object {
	std::string keyID;
};

/**
 * @brief The world that contains and manages all the rooms, entities. 
 * A World object will able to parse the story file and initialize the game and run it.
 * 
 */
class World {
	nodes worldRooms;
	entities population;
	tinyxml2::XMLDocument story;
public:
	World(const char* path2story) {
		story.LoadFile(path2story);
	}
	/**
	 * @brief Create Room with initial params and add it to worldRooms.
	 * 
	 * @param name (const std::string&): Name of the Room
	 * @param id (const std::string&): ID of the Room
	 * @param desc (const std::string&): Description of the Room
	 */
	void RoomFactory(const std::string& name, int id, const std::string& desc) {
		worldRooms.emplace_back(new Room(name, id, desc));
	}
	void EntityFactory(const std::string& name) {
		population.emplace_back(new Entity(name));
	}
	/**
	 * @brief Destroy the World object. This is very importand step, because all things in the world are contained in smart pointers.
	 * 
	 */
	~World() {
		for (nodes::iterator it = worldRooms.begin(); it != worldRooms.end(); it++) {
			it->reset();
		}
		for (entities::iterator it = population.begin(); it != population.end(); it++) {
			it->reset();
		}
	}
};
#endif