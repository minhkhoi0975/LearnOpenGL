#pragma once

#include <vector>

enum class ElementType
{
	Int = 0,
	Unsigned_Int = 1,
	Float = 2,
};

int GetOpenGlType(ElementType elementType)
{
	switch (elementType)
	{
	case ElementType::Int:
		return GL_INT;
		break;
	case ElementType::Unsigned_Int:
		return GL_UNSIGNED_INT;
		break;
	case ElementType::Float:
		return GL_FLOAT;
		break;
	default:
		return GL_INVALID_ENUM;
		break;
	}
}

class VertexAttribute
{
public:
	ElementType elementType;
	int elementCount;
	bool shouldBeNormalized;
	int offset;

	int GetSize()
	{
		int elementSize = 0;
		switch (elementType)
		{
		case ElementType::Int:
			elementSize = sizeof(int);
			break;
		case ElementType::Unsigned_Int:
			elementSize = sizeof(unsigned int);
			break;
		case ElementType::Float:
			elementSize = sizeof(float);
			break;
		}

		return elementSize * elementCount;
	}
};

class VertexSpecification
{
public:
	void AddVertexAttribute(ElementType elementType, int elementCount)
	{
		VertexAttribute newVertexAttribute;
		newVertexAttribute.elementType = elementType;
		newVertexAttribute.elementCount = elementCount;

		vertexAttributes.push_back(newVertexAttribute);

		UpdateStridesAndOffsets();
	}

	void Apply()
	{
		for (int i = 0; i < vertexAttributes.size(); ++i)
		{
			glVertexAttribPointer(i, vertexAttributes[i].elementCount, GetOpenGlType(vertexAttributes[i].elementType), vertexAttributes[i].shouldBeNormalized ? GL_TRUE : GL_FALSE, stride, (void*)vertexAttributes[i].offset);
			glEnableVertexAttribArray(i);
		}
	}

private:
	std::vector<VertexAttribute> vertexAttributes;
	int stride;

	void UpdateStridesAndOffsets()
	{
		stride = 0;
		int offset = 0;

		for (int i = 0; i < vertexAttributes.size(); ++i)
		{
			vertexAttributes[i].offset = offset;
			int attributeSize = vertexAttributes[i].GetSize();
			stride += attributeSize;
			offset += attributeSize;
		}
	}
};