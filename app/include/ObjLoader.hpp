#pragma once

#include <string>

#define TINYOBJLOADER_IMPLEMENTATION

#include "tiny_obj_loader.h"
#include "Tri.hpp"
#include "Math.hpp"

using namespace tinyobj;

struct MeshData {
	std::vector<Vector3> vertices;
	std::vector<unsigned short> indices;
};

class ObjLoader
{
public:
	ObjLoader() = default;
	~ObjLoader() = default;

	bool LoadObj(std::string path)
	{
		// create needed objects
		auto reader = ObjReader{};
		auto reader_config = ObjReaderConfig{};

		// set the path to the material folder
		reader_config.mtl_search_path = "./";

		// try to read the file
		if (!reader.ParseFromFile(path, reader_config))
		{
			// if not print error and return false
			if (!reader.Error().empty())
			{
				std::cerr << "TinyObjReader: " << reader.Error();
			}
			return false;
		}

		// print warnings
		if (!reader.Warning().empty())
		{
			std::cout << "TinyObjReader: " << reader.Warning();
		}

		// get vectors of data
		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++)
		{
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				triangleList.push_back(Tri());

				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++)
				{
					// access to vertex
					index_t idx = shapes[s].mesh.indices[index_offset + v];
					real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
					auto vertex = Vector3{ vx, vy, vz };
					triangleList.back()[v] = vertex;
				}
				index_offset += fv;

				// per-face material
				//shapes[s].mesh.material_ids[f];
			}
		}
		return true;
	}

	std::vector<Tri>& GetTriangleList()
	{
		return triangleList;
	}


private:
	std::vector<Tri> triangleList;
};
