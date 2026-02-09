#include "cube.h"


Cube::Cube(
	ID3D11Device* dxdevice,
	ID3D11DeviceContext* dxdevice_context)
	: Model(dxdevice, dxdevice_context)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;

	Vertex v;

	v.Position = { -0.5f, -0.5f, -0.5f }; v.Normal = { 0, 0, -1 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, -0.5f };  v.Normal = { 0, 0, -1 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, 0.5f, -0.5f };   v.Normal = { 0, 0, -1 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, 0.5f, -0.5f };  v.Normal = { 0, 0, -1 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);

	v.Position = { -0.5f, -0.5f, 0.5f };  v.Normal = { 0, 0, 1 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, 0.5f };   v.Normal = { 0, 0, 1 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, 0.5f, 0.5f };    v.Normal = { 0, 0, 1 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, 0.5f, 0.5f };   v.Normal = { 0, 0, 1 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);

	v.Position = { -0.5f, 0.5f, 0.5f };   v.Normal = { -1, 0, 0 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, 0.5f, -0.5f };  v.Normal = { -1, 0, 0 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, -0.5f, -0.5f }; v.Normal = { -1, 0, 0 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { -0.5f, -0.5f, 0.5f };  v.Normal = { -1, 0, 0 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);

	v.Position = { 0.5f, 0.5f, 0.5f };    v.Normal = { 1, 0, 0 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { 0.5f, 0.5f, -0.5f };   v.Normal = { 1, 0, 0 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, -0.5f };  v.Normal = { 1, 0, 0 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, 0.5f };   v.Normal = { 1, 0, 0 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);

	v.Position = { -0.5f, -0.5f, -0.5f }; v.Normal = { 0, -1, 0 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, -0.5f };  v.Normal = { 0, -1, 0 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, -0.5f, 0.5f };   v.Normal = { 0, -1, 0 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, -0.5f, 0.5f };  v.Normal = { 0, -1, 0 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);

	v.Position = { -0.5f, 0.5f, -0.5f };  v.Normal = { 0, 1, 0 }; v.TexCoord = { 0, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, 0.5f, -0.5f };   v.Normal = { 0, 1, 0 }; v.TexCoord = { 1, 1 }; vertices.push_back(v);
	v.Position = { 0.5f, 0.5f, 0.5f };    v.Normal = { 0, 1, 0 }; v.TexCoord = { 1, 0 }; vertices.push_back(v);
	v.Position = { -0.5f, 0.5f, 0.5f };   v.Normal = { 0, 1, 0 }; v.TexCoord = { 0, 0 }; vertices.push_back(v);

	for (unsigned i = 0; i < 6; i++)
	{
		unsigned base = i * 4;
		indices.push_back(base + 0);
		indices.push_back(base + 2);
		indices.push_back(base + 1);
		indices.push_back(base + 0);
		indices.push_back(base + 3);
		indices.push_back(base + 2);
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