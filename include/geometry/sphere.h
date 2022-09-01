#pragma once

#include <SGE/SGE.h>

void initVertexDataSphere(std::vector<SGEPosition>& vertices, std::vector<uint16_t>& indices)
{
	vertices.clear();
	indices.clear();

	uint16_t slices = 20, stacks = 20;

	// Calc The Vertices
	for (int i = 0; i <= slices; i++)
	{
		float phi = i * (glm::pi<float>() / slices);

		// Loop Through Slices
		for (int j = 0; j < stacks; j++)
		{
			float theta = j * (glm::pi <float>() * 2 / stacks);

			// Calc The Vertex Positions
			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			// Push Back Vertex Data
			vertices.push_back(SGEPosition{x, y, z});
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < vertices.size() - stacks; i++)
	{
		if ((i + 1) % stacks == 0)
		{
			indices.push_back(i);
			indices.push_back(i - stacks + 1);
			indices.push_back(i + stacks);

			indices.push_back(i - stacks + 1);
			indices.push_back(i + stacks);
			if (i + 1 == indices.size())
				indices.push_back(vertices.size() - stacks);
			else
				indices.push_back(i + 1);
		}
		else
		{
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + stacks);

			indices.push_back(i + 1);
			indices.push_back(i + stacks);
			indices.push_back(i + stacks + 1);
		}
	}
}