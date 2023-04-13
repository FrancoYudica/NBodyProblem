#pragma once
#ifndef BUFFER_H
#define BUFFER_H
#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace Wolf
{
	namespace Rendering
	{

		enum ShaderDataType
		{
			Float, Float2, Float3, Float4,
			Int, Int2, Int3, Int4,
			Mat2, Mat3, Mat4
		};

		static unsigned int ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
				case Float:
					return 4;
				case Float2:
					return 4 * 2;
				case Float3:
					return 4 * 3;
				case Float4:
					return 4 * 4;
				case Int:
					return 4;
				case Int2:
					return 4 * 2;
				case Int3:
					return 4 * 3;
				case Int4:
					return 4 * 4;
				case Mat2:
					return 4 * 4;
				case Mat3:
					return 4 * 9;
				case Mat4:
					return 4 * 16;
				default:
					std::cout << "UNINPLEMENTED_SHADER_DATA_TYPE_SIZE: " << type << std::endl;
			}
			return 1;
		}

		struct BufferAttribute
		{
			// Contains all the data of a single attribute
			std::string Name;
			ShaderDataType Type;
			unsigned int Size;
			unsigned int Offset;
			bool Normalized;

			BufferAttribute() = default;
			BufferAttribute(std::string name, ShaderDataType type, bool normalized) : Name(name), Type(type), Normalized(normalized),
				Size(ShaderDataTypeSize(type)), Offset(0) {}

			unsigned int GetComponentCount() const
			{
				switch (Type)
				{
				case Float:
					return 1;
				case Float2:
					return 2;
				case Float3:
					return 3;
				case Float4:
					return 4;
				case Int:
					return 1;
				case Int2:
					return 2;
				case Int3:
					return 3;
				case Int4:
					return 4;
				case Mat2:
					return 4;
				case Mat3:
					return 9;
				case Mat4:
					return 16;
				default:
					std::cout << "UNINPLEMENTED_SHADER_DATA_TYPE_COMPONENT_COUNT: " << Type << std::endl;
				}
				return 1;
			}

		};


		class BufferLayout
		{
			/*
			Used for storing a set of VertexBuffer Attributes.
			Provices automatic calculation of Offset and Stride
			*/
		public:
			BufferLayout() = default;
			BufferLayout(std::initializer_list<BufferAttribute> attributes) : _Attributes(attributes)
			{
				CalculateOffsetsAndStride();
			}
			unsigned int GetStride() { return _Stride; }

			std::vector<BufferAttribute>::iterator begin() { return _Attributes.begin(); }
			std::vector<BufferAttribute>::iterator end() { return _Attributes.end(); }

		private:

			void CalculateOffsetsAndStride()
			{
				/*
				Calculates the offset of all 
				the atributes and then sets 
				the stride value
				*/
				unsigned int offset = 0;
				for (BufferAttribute& attribute : _Attributes)
				{
					attribute.Offset = offset;
					offset += attribute.Size;
				}
				_Stride = offset;
			}

			std::vector<BufferAttribute> _Attributes;
			unsigned int _Stride;
		};


		class VertexBuffer
		{
		public:
			VertexBuffer(const void* data, unsigned int size);
			VertexBuffer(unsigned int size);
			~VertexBuffer();
			virtual void bind();
			virtual void unbind();
			virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
			virtual void set_buffer_layout(const BufferLayout& layout);
			virtual BufferLayout& get_buffer_layout();

		private:
			BufferLayout _Layout;
		public:
			unsigned int ID;
		};

		class IndexBuffer
		{
		public:
			IndexBuffer(const unsigned int* indices, unsigned int count);
			~IndexBuffer();
			virtual void bind();
			virtual void unbind();
			virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
			virtual unsigned int get_count() const {return _Count;}
		public:
			unsigned int ID;
		private:
			unsigned int _Count;
		};
	}
}


#endif