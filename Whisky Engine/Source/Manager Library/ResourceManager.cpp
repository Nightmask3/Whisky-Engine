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

#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "utils.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::string;
using std::pair;
using std::set;
using std::list;
using std::vector;

	const char* archetype_file_name = "Archetypes/Archetypes.txt";

	ResourceManager* ResourceManager::_instance = NULL;

	///////////////////////////////////////////////////////////////////////////////
	// Static functions
	///////////////////////////////////////////////////////////////////////////////

	ResourceManager* ResourceManager::Inst()
	{
		if (_instance == NULL) _instance = new ResourceManager();
		return _instance;
	}


	const std::string ResourceManager::ReadContents(const char* src)
	{
		std::stringstream content;
		std::ifstream file(src);
		if (!file.is_open())
		{
			cout << "Error opening file " << src << endl;
			return NULL;
		}

		content << file.rdbuf();
		return content.str();
	}

	///////////////////////////////////////////////////////////////////////////////
	// System functions
	///////////////////////////////////////////////////////////////////////////////

	bool ResourceManager::Init()
	{
		cout << "Resource Manager initialized." << endl;
		return true;
	}

	bool ResourceManager::Load(const char* lvl_src)
	{
		cout << "Resource Manager loading..." << endl;
		if (!ReadArchetypes())			return false;
		if (!ReadLevelData(lvl_src))	return false;

		cout << "Resource Manager loaded successfully." << endl;
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Member functions
	///////////////////////////////////////////////////////////////////////////////

	set<string> ResourceManager::GetTextureFiles() const
	{
		return _texturesFiles;
	}

	bool ResourceManager::ReadArchetypes()
	{
		////////////////////////////////
		/// Get the archetype file names

		// open archetype file
		ifstream file(archetype_file_name);
		{
			if (!file.is_open())
			{
				cout << "Error opening archetype list file: " << archetype_file_name << endl;
				return false;
			}

			// store archetype file names
			string file_path("Archetypes/");
			string file_name;
			while (file >> file_name)	_archetypeFiles.emplace(file_path+file_name);
		}
		file.close();

#ifdef LOG
		cout << "Resource Manager: Archetype source files (" << _archetypeFiles.size() << ") registered." << endl;
#endif

		////////////////////////////////
		/// read each archetype file

		// for each archetype file
		for (string file_path : _archetypeFiles)
		{
			// create an archetype and assign its name
			SerializedObject archetype;
			//string tokens = split(file_path.c_str(), '.')[0];
			//archetype.name = tokens[];	// get rid of file extension (assume split returns nonempty vector)
			archetype.name = GetFileNameFromPath(file_path);

			// open file
			file.open(file_path);
			if (!file.is_open())
			{
				cout << "ResourceManager::ReadArcheTypes(): Error opening archetype file: " << file_path << endl;
				return false;
			}

			// read component list in archetype files
			string compName, param;
			list<pair<string, string>> componentList;
			while (getline(file, compName) && getline(file, param))
			{
				componentList.push_back(make_pair(compName, param));

				// store sprite info
				std::transform(compName.begin(), compName.end(), compName.begin(), ::tolower);
				if (compName == "sprite")
				{
					std::transform(param.begin(), param.end(), param.begin(), ::tolower);
					vector<string> fileNames = split(param.c_str(), ' ');
					for (auto fileName : fileNames)
						_texturesFiles.emplace(fileName);
				}
			}

			// push back to the list of archetypes
			archetype.componentList = componentList;
			_archetypeList.push_back(archetype);
			file.close();
		}


		cout << "\tArchetype data is read successfully." << endl;
		return true;
	}

	bool ResourceManager::IsArchetypeName(const std::string& s)
	{
		for (auto arch : _archetypeList)
		{
			if (s == arch.name)
				return true;
		}

		return false;
	}

	bool ResourceManager::IsObjectName(const std::string& s)
	{
		return !IsArchetypeName(s) && s != "}" && s != "{" && s[0] != '\t' && s != "";
	}

	bool ResourceManager::ConstructDefaultArchetype(SerializedObject& obj, const std::string& archetypeName)
	{
		obj.componentList.clear();
		obj.name = archetypeName;
		string path("Archetypes/");

		// open archetype file
		string fileName(path + archetypeName + ".txt");
		ifstream file(fileName);
		if (!file.is_open())
		{
			cout << __FUNCTION__ << " Error opening archetype file: " << fileName << endl;
			return false;
		}

		// read the components from file
		string componentName, params;
		while (getline(file, componentName) && getline(file, params))
			obj.componentList.push_back(std::make_pair(componentName, params));

		return true;
	}

	// removes ':' '\t' and ' ' from string passed and returns 
	// a pair of component name and arguments for component initialization
	ResourceManager::CompNAPair ResourceManager::ParseComponent(const std::string& line)
	{
		CompNAPair comp;

		comp.first = split(line.c_str(), ':')[0];
		comp.second = split(line.c_str(), ':')[1];

		// trim the leading white spaces
		while (comp.first[0] == ' ' || comp.first[0] == '\t')
			comp.first = comp.first.substr(1);

		while (comp.second[0] == ' ' || comp.second[0] == '\t')
			comp.second = comp.second.substr(1);

		// trim the trailing white spaces
		while (comp.first.back() == ' ' || comp.first.back() == '\t')
			comp.first.erase(comp.first.end() - 1);

		while (comp.second.back() == ' ' || comp.second.back() == '\t')
			comp.second.erase(comp.second.end() - 1);

		// check for sprite components
		string name = comp.first; 
		string param = comp.second;		// lowercase both component and file names
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		std::transform(param.begin(), param.end(), param.begin(), ::tolower);
		if (name == "sprite")
		{
			vector<string> fileNames = split(param.c_str(), ' ');	// get all file names if more than 1
			for (auto fileName : fileNames)
				_texturesFiles.emplace(fileName);	// push em back to texture files list
		}

		return comp;
	}

	bool ResourceManager::ConstructOverriddenArchetype(SerializedObject& obj)
	{
		// store the component names to be overridden
		CompList overrideList = obj.componentList;

		string path("Archetypes/");
		// open archetype file
		string fileName(split(obj.name, '#')[0] + ".txt");
		ifstream file(path + fileName);
		if (!file.is_open())
		{
			cout << "Error opening archetype file: " << fileName << endl;
			return false;
		}

		// construct a component list, and edit the override values next
		CompList cmpList;

		// read components from file
		string componentName, params;
		while (getline(file, componentName) && getline(file, params))
			cmpList.push_back(std::make_pair(componentName, params));

		// edit the components to be overridden
		while (overrideList.size() > 0)
		{
			bool found = false;
			for (auto& compPair : cmpList)
			{
				string compName = overrideList.front().first;
				if (compPair.first == compName)
				{
					compPair.second = overrideList.front().second;
					found = true;
					break;
				}
			}
			if (!found)
			{
				cout << "SOMETHINGS WRONG!" << endl;
				return false;
			}

			overrideList.erase(overrideList.begin());
		}

		obj.componentList = cmpList;
		return true;
	}

	bool ResourceManager::ReadLevelData(const char* src)
	{
		// state machine: https://gist.github.com/vilbeyli/a948bb66cd454ac8ad26

		// open level file
		ifstream file(src);
		if (!file.is_open())
		{
			cout << "ResourceManager::ReadLevelData(): Error opening level file: " << src << endl;
			return false;
		}

		// serialized object instance copy
		SerializedObject obj;
		obj.componentList.clear();
		obj.name.clear();


		// read each line
		bool isArchetype = false;
		string line, prev_line;

		getline(file, prev_line);
		while (getline(file, line))
		{

			//cout << line << "\t";

			// ARCHETYPE NAME
			if (IsArchetypeName(line) || IsObjectName(line))
			{
				// prev_line == archetype -> instantiate default archetype | DONE 
				if (IsArchetypeName(prev_line))
				{
					//cout << "default archetype: " << prev_line << endl;
					if (!ConstructDefaultArchetype(obj, prev_line))
						return false;
				}
				// prev_line == gameobject name -> instantiate default gameobject | DONE
				else if (IsObjectName(prev_line))
				{
					//cout << "default game obj: " << prev_line << endl;
					//_levelData.push_back(obj);
				}

				// prev_line == } -> continue loop 
				else if (prev_line == "}")
				{
					obj.name = line;
					prev_line = line;
					continue;
				}

				// execution is not intended to reach here
				else if (prev_line != "")
					cout << "******************WELP?" << endl;

				_levelData.push_back(obj);
				obj.componentList.clear();
				obj.name = line;
			}
			// OPEN BRACE: check for current type we're building
			else if (line == "{")
			{
				//cout << "open brace {" << endl;
				obj.name = prev_line + "#";	// are you sure?
				isArchetype = IsArchetypeName(prev_line);

			}

			// CLOSE BRACE: add the object to the _levelData
			else if (line == "}")
			{
				//cout << "close brace }" << endl;
				if (isArchetype)
				{
					if (!ConstructOverriddenArchetype(obj))
						return false;
					_levelData.push_back(obj);
				}
				else
				{
					_levelData.push_back(obj);
				}

				obj.componentList.clear();
				obj.name.clear();
			}

			// COMPONENT PAIR: add component to the objects component list
			else if (line[0] == '\t')
			{
				//cout << "component " << endl;
				auto componentPair = ParseComponent(line);
				obj.componentList.push_back(componentPair);
			}



			prev_line = line;
		}

		// one last check
		// prev_line == archetype -> instantiate default archetype
		if (IsArchetypeName(prev_line))
		{
			//cout << "default archetype: ";
			if (!ConstructDefaultArchetype(obj, prev_line))
				return false;

			_levelData.push_back(obj);
		}

		// prev_line == archetype -> instantiate default gameobject
		else if (IsObjectName(prev_line))
		{
			//cout << "default game obj: ";
			_levelData.push_back(obj);
		}
		//cout << prev_line << endl;


		file.close();
		cout << "\tLevel data is read successfully." << endl;
		return true;
	}