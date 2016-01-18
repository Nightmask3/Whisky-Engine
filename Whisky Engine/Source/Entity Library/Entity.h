#ifndef Entity_h
#define Entity_h


class Entity
{
	
public:
	enum EntityType
	{
		GameObject,
		Camera,

		ENTITY_COUNT
	};
	// Used in Game Object Factory to determine what type of object to create
	EntityType mType;

	Entity(EntityType type) : mType(type) {}
	virtual ~Entity() {}
};
#endif