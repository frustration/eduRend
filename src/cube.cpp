#include "cube.h"


Cube::Cube(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Model(dxdevice, dxdevice_context)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	const float s = 0.5f;

	auto AddFace = [&](Vertex v0, Vertex v1, Vertex v2, Vertex v3)
	{
		unsigned base = (unsigned)vertices.size();

		vertices.push_back(v0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		indices.push_back(base + 0);
		indices.push_back(base + 1);
		indices.push_back(base + 3);

		indices.push_back(base + 1);
		indices.push_back(base + 2);
		indices.push_back(base + 3);
	};

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { -s, -s,  s }; v0.Normal = { 0, 0, 1 }; v0.TexCoord = { 0, 1 };
		v1.Position = { s, -s,  s }; v1.Normal = { 0, 0, 1 }; v1.TexCoord = { 1, 1 };
		v2.Position = { s,  s,  s }; v2.Normal = { 0, 0, 1 }; v2.TexCoord = { 1, 0 };
		v3.Position = { -s,  s,  s }; v3.Normal = { 0, 0, 1 }; v3.TexCoord = { 0, 0 };

		AddFace(v0, v1, v2, v3);
	}

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { s, -s, -s }; v0.Normal = { 0, 0, -1 }; v0.TexCoord = { 0, 1 };
		v1.Position = { -s, -s, -s }; v1.Normal = { 0, 0, -1 }; v1.TexCoord = { 1, 1 };
		v2.Position = { -s,  s, -s }; v2.Normal = { 0, 0, -1 }; v2.TexCoord = { 1, 0 };
		v3.Position = { s,  s, -s }; v3.Normal = { 0, 0, -1 }; v3.TexCoord = { 0, 0 };
		AddFace(v0, v1, v2, v3);
	}

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { s, -s,  s }; v0.Normal = { 1, 0, 0 }; v0.TexCoord = { 0, 1 };
		v1.Position = { s, -s, -s }; v1.Normal = { 1, 0, 0 }; v1.TexCoord = { 1, 1 };
		v2.Position = { s,  s, -s }; v2.Normal = { 1, 0, 0 }; v2.TexCoord = { 1, 0 };
		v3.Position = { s,  s,  s }; v3.Normal = { 1, 0, 0 }; v3.TexCoord = { 0, 0 };
		AddFace(v0, v1, v2, v3);
	}

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { -s, -s, -s }; v0.Normal = { -1, 0, 0 }; v0.TexCoord = { 0, 1 };
		v1.Position = { -s, -s,  s }; v1.Normal = { -1, 0, 0 }; v1.TexCoord = { 1, 1 };
		v2.Position = { -s,  s,  s }; v2.Normal = { -1, 0, 0 }; v2.TexCoord = { 1, 0 };
		v3.Position = { -s,  s, -s }; v3.Normal = { -1, 0, 0 }; v3.TexCoord = { 0, 0 };
		AddFace(v0, v1, v2, v3);
	}

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { -s,  s,  s }; v0.Normal = { 0, 1, 0 }; v0.TexCoord = { 0, 1 };
		v1.Position = { s,  s,  s }; v1.Normal = { 0, 1, 0 }; v1.TexCoord = { 1, 1 };
		v2.Position = { s,  s, -s }; v2.Normal = { 0, 1, 0 }; v2.TexCoord = { 1, 0 };
		v3.Position = { -s,  s, -s }; v3.Normal = { 0, 1, 0 }; v3.TexCoord = { 0, 0 };
		AddFace(v0, v1, v2, v3);
	}

	{
		Vertex v0, v1, v2, v3;
		v0.Position = { -s, -s, -s }; v0.Normal = { 0, -1, 0 }; v0.TexCoord = { 0, 1 };
		v1.Position = { s, -s, -s }; v1.Normal = { 0, -1, 0 }; v1.TexCoord = { 1, 1 };
		v2.Position = { s, -s,  s }; v2.Normal = { 0, -1, 0 }; v2.TexCoord = { 1, 0 };
		v3.Position = { -s, -s,  s }; v3.Normal = { 0, -1, 0 }; v3.TexCoord = { 0, 0 };
		AddFace(v0, v1, v2, v3);
	}

	D3D11_BUFFER_DESC vertexbufferDesc{ 0 };
	vertexbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexbufferDesc.ByteWidth = (UINT)(vertices.size() * sizeof(Vertex));
	D3D11_SUBRESOURCE_DATA vertexData{ 0 };
	vertexData.pSysMem = &vertices[0];
	dxdevice->CreateBuffer(&vertexbufferDesc, &vertexData, &m_vertex_buffer);
	SETNAME(m_vertex_buffer, "VertexBuffer");

	D3D11_BUFFER_DESC indexbufferDesc{ 0 };
	indexbufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDesc.ByteWidth = (UINT)(indices.size() * sizeof(unsigned));
	D3D11_SUBRESOURCE_DATA indexData{ 0 };
	indexData.pSysMem = &indices[0];
	dxdevice->CreateBuffer(&indexbufferDesc, &indexData, &m_index_buffer);
	SETNAME(m_index_buffer, "IndexBuffer");

	m_number_of_indices = (unsigned int)indices.size();
}

void Cube::Render() const
{
	// Bind our vertex buffer
	const UINT32 stride = sizeof(Vertex); //  sizeof(float) * 8;
	const UINT32 offset = 0;
	m_dxdevice_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);

	// Bind our index buffer
	m_dxdevice_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);

	// Make the drawcall
	m_dxdevice_context->DrawIndexed(m_number_of_indices, 0, 0);
}