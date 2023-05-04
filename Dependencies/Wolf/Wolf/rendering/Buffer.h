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
			std::string name;
			ShaderDataType type;
			uint32_t size;
			uint32_t offset;
			bool normalized;

			BufferAttribute() = default;
			BufferAttribute(const std::string& name, ShaderDataType type, bool normalized)
			 : name(name),
			   type(type),
			   normalized(normalized),
			   size(ShaderDataTypeSize(type)), 
			   offset(0) {}

			uint32_t GetComponentCount() const
			{
				switch (type)
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
					std::cout << "UNINPLEMENTED_SHADER_DATA_TYPE_COMPONENT_COUNT: " << type << std::endl;
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
			BufferLayout(std::initializer_list<BufferAttribute> attributes) : _attributes(attributes)
			{
				CalculateOffsetsAndStride();
			}
			uint32_t GetStride() { return _stride; }

			std::vector<BufferAttribute>::iterator begin() { return _attributes.begin(); }
			std::vector<BufferAttribute>::iterator end() { return _attributes.end(); }

		private:

			void CalculateOffsetsAndStride()
			{
				/*
				Calculates the offset of all 
				the atributes and then sets 
				the stride value
				*/
				uint32_t offset = 0;
				for (BufferAttribute& attribute : _attributes)
				{
					attribute.offset = offset;
					offset += attribute.size;
				}
				_stride = offset;
			}

			std::vector<BufferAttribute> _attributes;
			uint32_t _stride;
		};


		class VertexBuffer
		{
		public:
			virtual void bind() const = 0;
			virtual void unbind() const = 0;
			virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset) = 0;
			virtual void set_buffer_layout(const BufferLayout& layout) = 0;
			virtual BufferLayout& get_buffer_layout() = 0;
			static std::shared_ptr<VertexBuffer> create(const void* data, unsigned int size);

			static std::shared_ptr<VertexBuffer> allocate(unsigned int size);
		};

		class IndexBuffer
		{
		public:
			virtual void bind() const = 0;
			virtual void unbind() const = 0;
			virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset) = 0;
			virtual unsigned int get_count() const = 0;
			static std::shared_ptr<IndexBuffer> create(const unsigned int* data, unsigned int count);
		};
	}
}


#endif