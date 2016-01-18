// ---------------------------------------------------------------------------
// Project Name		:	VolkEngine Game Engine
// File Name		:	ResourceManager.h
// Author			:	Volkan Ilbeyli
// Creation Date	:	2015/11/12
// Purpose			:	Resource manager for file I/O
// History			:
// - 2015/10/22		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <utility>
#include <set>
#include <list>

class ResourceManager
{
	typedef std::pair<std::string, std::string> CompNAPair;	// component name-arguments pair
	typedef std::list<CompNAPair>				CompList;	// list of component name-arguments pair - essentially a component

	struct SerializedObject
	{
		std::string name;
		CompList componentList;
	};

	// functions
public:
	// static functions
	static ResourceManager* Inst();
	static const std::string ReadContents(const char*);

	// system functions
	bool Init();
	bool Load(const char*);	// level name

	// member functions
	std::set<std::string> GetTextureFiles()	const;
	//void ClearArchetypeList();	

	// getters & setters
	inline int TextureCount() const	{ return _texturesFiles.size(); }
	inline const std::list<SerializedObject>& GetLevelData() const { return _levelData; }
	inline const std::list<SerializedObject>& GetArchetypeList() const { return _archetypeList; }



private:
	bool ReadArchetypes();
	bool IsArchetypeName(const std::string&);
	bool IsObjectName(const std::string&);
	bool ConstructDefaultArchetype(SerializedObject&, const std::string&);
	CompNAPair ParseComponent(const std::string&);
	bool ConstructOverriddenArchetype(SerializedObject&);
	bool ReadLevelData(const char*);

	// data
private:	// static members
	static ResourceManager* _instance;

private:	// members
	std::set  <std::string     >	_archetypeFiles;
	std::list <SerializedObject>	_archetypeList;	// assumes uniqueness of archetype names
	std::list <SerializedObject>	_levelData;
	std::set  <std::string     >	_texturesFiles;
};
#endif
