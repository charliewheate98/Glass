#pragma once

#include "pch.h"
#include "Core.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

namespace Glass
{
	struct Character
	{
		Vertex	  m_Vertices[6];
		glm::vec2 m_Position;
		short     m_Index = 0;
		bool      m_Caps = false;	
		float     m_Size;
		uint32_t  m_KeyCode;

		Character(const char c, const glm::vec2 position, float size) : 
			m_Position(position),
			m_Size(size)
		{
			m_Vertices[0] = Vertex(glm::vec3(position.x,        position.y,         0.f), glm::vec2(0.0f, 0.0f));
			m_Vertices[1] = Vertex(glm::vec3(position.x + size, position.y,         0.f), glm::vec2(1.0f, 0.0f));
			m_Vertices[2] = Vertex(glm::vec3(position.x + size, position.y + size,  0.f), glm::vec2(1.0f, 1.0f));

			m_Vertices[3] = Vertex(glm::vec3(position.x,        position.y,		    0.f), glm::vec2(0.0f, 0.0f));
			m_Vertices[4] = Vertex(glm::vec3(position.x,		position.y + size,  0.f), glm::vec2(0.0f, 1.0f));
			m_Vertices[5] = Vertex(glm::vec3(position.x + size,	position.y + size,  0.f), glm::vec2(1.0f, 1.0f));
		}
	};

	class GLASS_API Text
	{
	public:
		Text(const std::string text, const glm::vec2& position) : 
			m_FontSize(0.5f),
			m_CharacterSpacing(0.6f)
		{
			for (int i = 0; i < text.size(); ++i)
			{
				if (text[i] == ' ')
					m_CharacterSpacing = 2.f;
				else m_CharacterSpacing = .6f;

				uint32_t ascii_code = (uint32_t)text[i];
				m_Characters.emplace_back(text[i], glm::vec2(position.x + i * m_CharacterSpacing, position.y), m_FontSize);
				m_Characters[m_Characters.size() - 1].m_KeyCode = ascii_code;
			}

			m_VertexArray  = std::make_unique<VertexArray>();
			m_VertexBuffer = std::make_unique<VertexBuffer>();
			m_IndexArray   = std::make_unique<IndexBuffer>();

			glEnableVertexAttribArray(POSITIONS_ATTRIB);
			glVertexAttribPointer(POSITIONS_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
			glEnableVertexAttribArray(TEXCOORDS_ATTRIB);
			glVertexAttribPointer(TEXCOORDS_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::_uv)));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		~Text() 
		{}
		 
		void Optimise() 
		{
		}

		void Process() 
		{
			static std::vector<Vertex> m_Vertices;
			m_Vertices.resize(m_Characters.size() * 6);

			uint32_t m_CurrentVertex = 0;

			for (size_t i = 0; i < m_Characters.size(); ++i) 
			{
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[0];
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[1];
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[2];
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[3];
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[4];
				m_Vertices[m_CurrentVertex++] = m_Characters[i].m_Vertices[5];
			}

			m_VertexBuffer->BindBuffer();
			m_VertexBuffer->UpdateBuffer(STATIC_CAST(GLsizei, m_Vertices.size() * sizeof(Vertex)), NULL , GL_DYNAMIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, STATIC_CAST(GLsizei, m_Vertices.size() * sizeof(Vertex)), &m_Vertices[0]);
		}

		void Render()
		{
			m_VertexArray->BindVertexArray();

			RendererCommands::DrawArrays(m_Characters.size() * 6);
		}
	private:
		std::vector<Character>		  m_Characters;

		std::unique_ptr<VertexArray>  m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer>  m_IndexArray;

		float m_CharacterSpacing;
		float m_FontSize;
	};
};



