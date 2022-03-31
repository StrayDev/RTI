#pragma once

#include <string>

#define TINYOBJLOADER_IMPLEMENTATION

#include "Math.hpp"
#include "Tri.hpp"
#include "tiny_obj_loader.h"

#include "glm/mat4x4.hpp"
#include "Object.hpp"

using namespace tinyobj;

class ObjLoader
{
public:
	ObjLoader() = default;
	~ObjLoader() = default;

	bool LoadObj(std::string path, std::string name)
	{
		auto reader = ObjReader{};
		auto reader_config = ObjReaderConfig{};

		reader_config.mtl_search_path = "./";

		if (!reader.ParseFromFile(path, reader_config))
		{
			// if not print error and return false
			if (!reader.Error().empty())
			{
				std::cerr << "TinyObjReader: " << reader.Error() << '\n';
			}
			return false;
		}

		if (!reader.Warning().empty())
		{
			std::cout << "TinyObjReader: " << reader.Warning()  << '\n';
		}

		// get vectors of data
		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		// Loop over shapes
		for (const auto& shape : shapes)
		{
			auto index_offset = 0;
			for (auto f = 0; f < shape.mesh.num_face_vertices.size(); f++)
			{
				Tri::Vertices vertices;
				Tri::Normals  normals;

				auto fv = size_t(shape.mesh.num_face_vertices[f]);
				for (auto v = 0; v < fv; v++)
				{
					/// access to vertex
					auto idx = shape.mesh.indices[index_offset + v];
					auto vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					auto vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					auto vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
					vertices[v] = Vector3{ vx, vy, vz };

					/// Get normals negative = no normal data
					if (idx.normal_index > -1)
					{
						auto nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
						auto ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
						auto nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
						normals[v] = Vector3{ nx, ny, nz };
					}
				}

				/// create the tri and add to the list
				//triangleList.emplace_back(Tri(vertices, normals));
				object_list[name].triangles.emplace_back(Tri(vertices, normals));

				index_offset += fv;
			}
		}
		return true;
	}

	std::vector<Tri>& GetTriangleList()
	{
		return triangleList;
	}

	std::unique_ptr<Object> CreateObject(std::string name)
	{
		return std::make_unique<Object>(object_list[name]);
	}


private:
	std::vector<Tri> triangleList;
	std::map<std::string , Object> object_list;
};
