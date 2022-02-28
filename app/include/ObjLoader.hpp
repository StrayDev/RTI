#pragma once

#include <string>

#define TINYOBJLOADER_IMPLEMENTATION

#include "Math.hpp"
#include "Tri.hpp"
#include "tiny_obj_loader.h"

using namespace tinyobj;

struct MeshData
{
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
				std::cerr << "TinyObjReader: " << reader.Error() << '\n';
			}
			return false;
		}

		// print warnings
		if (!reader.Warning().empty())
		{
			std::cout << "TinyObjReader: " << reader.Warning()  << '\n';
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
				//triangleList.push_back(Tri());
				Tri::Vertices vertices;
				Tri::Normals  normals;

				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++)
				{
					/// access to vertex
					index_t idx = shapes[s].mesh.indices[index_offset + v];
					real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
					vertices[v] = Vector3{ vx, vy, vz };

					/// Get normals negative = no normal data
					if (idx.normal_index > -1)
					{
						tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
						tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
						tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
						normals[v] = Vector3{ nx, ny, nz };
					}
				}

				/// create the tri and add to the list
				triangleList.emplace_back(Tri(vertices, normals));

				index_offset += fv;
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
