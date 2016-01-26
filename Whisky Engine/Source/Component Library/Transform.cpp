// Component header files
//#include "PhysicsComponent.h"
#include "Transform.h"
#include <string>
// Matrix Transformation header files
#include "..\..\Dependencies\glm\glm\gtc\matrix_transform.hpp"


Transform::Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale) 
	: 
	mPosition_(position), // Used in GameObjectFactory::Instantiate
	mRotation_(rotation), 
	mScale_(scale) , 
	Component(ComponentType::TRANSFORM, "Transform") 
{}


Transform::~Transform() {}

//void Transform::Serialize(std::string & Contents, unsigned int & Count)
//{
//	unsigned char tempC;
//	unsigned int tempI = 0;
//	std::string::size_type end;			// size_type is a typedef-ed type that is used to guarantee that no matter how large the size of the input file, it can be contained (example : if larger than int)
//	std::string DataType;				// Used to check the type of data being supplied before adding to corresponding list
//	std::string TempData;				// Used to get the different vertex properties into their respective list
//	std::string Token = "";
//	std::string TempLine = "";
//	GLfloat Array[3];					// Used to hold the X, Y and Z values of the properties
//	GLfloat TempFloat = 0.0f;
//	DataType.reserve(64);
//	Count += 5;
//	while (Contents.at(Count) != '\0')
//	{
//		while ((Contents.at(Count) != '\r')) // Reads character by character until new line
//		{
//			tempC = Contents.at(Count++);
//			DataType += tempC;				// Gets type of component to create
//		}
//		Count += 2;										// To skip the \r, \n and the '{' and its \r and \n
//		end = Contents.find('\n', Count);				// Finds the end of the current vertex property array
//		TempData = Contents.substr(Count, end - Count); // Second parameter is the length of the string
//		std::istringstream TempStream(TempData);		// Gets a string stream constructed from the temp data string
//
//		while (std::getline(TempStream, Token, ','))
//		{
//			TempFloat = strtof(Token.c_str(), NULL);
//			Array[tempI++] = TempFloat;
//		}
//	
//		if (strcmp(DataType.c_str(), "Position") == 0)
//		{
//			Translate(Array[0], Array[1], Array[2]);
//		}
//		else if (strcmp(DataType.c_str(), "Rotation") == 0)
//		{
//			Rotate(Array[0], Array[1], Array[2]);
//		}
//		else if (strcmp(DataType.c_str(), "Scale") == 0)
//		{
//			Scale(Array[0], Array[1], Array[2]);
//		}
//		Count = end + 1; // To skip the \r and \n characters
//		if (Contents.at(Count) == '}') // Serialization of this component complete
//		{
//			Count += 3;
//			return;
//		}
//		if (Contents.at(Count) == '-')
//		{
//			Count += 3;
//			return;
//		}
//		if (Count > Contents.size())	// End of file
//		{
//			return;
//		}
//		DataType = "";
//		TempLine = "";
//		Token = "";
//		tempI = 0;
//	}
//}

void Transform::Update()
{
	// Transform Component does not update itself!
}

glm::mat4 Transform::ModelTransformationMatrix() const
{
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), mScale_);
	//glm::mat4 rotate = glm::rotate(scale, 0.0f, );	// TODO: FIGURE ROTATIONS OUT
	glm::mat4 tr = glm::translate(glm::mat4(1.0f), mPosition_);

	return tr * scale;
}

Transform* Transform::Deserialize(const char* params)
{
	Transform* t = NULL;
	std::vector<std::string> parameters = split(params);
	try
	{	// if the argument is '-' : initialize default Transform
		if (parameters[0].size() == 1 && parameters[0][0] == '-') t = new Transform();
		else
		{
			glm::vec3 pos(std::stof(parameters[0]), std::stof(parameters[1]), std::stof(parameters[2]));
			glm::vec3 rot(std::stof(parameters[3]), std::stof(parameters[4]), std::stof(parameters[5]));
			glm::vec3 scl(std::stof(parameters[6]), std::stof(parameters[7]), std::stof(parameters[8]));
			t = new Transform(pos, rot, scl);
		}
	}
	catch (const std::invalid_argument& ia)
	{
		std::cout << "Invalid argument creating transform: " << ia.what() << std::endl;
	}
	return t;
}