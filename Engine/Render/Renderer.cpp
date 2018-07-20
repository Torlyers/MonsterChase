#include "Renderer.h"

namespace Engine
{

	Renderer::Renderer()
	{
	}

	Renderer::Renderer(SharedPointer<GameObject> i_GameObject)
	{
		m_GameObject = i_GameObject;
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Init()
	{

	}

	void Renderer::Run()
	{
		GLib::Sprites::RenderSprite(*m_Sprite, GLib::Point2D{ m_GameObject->GetPosition().x(), m_GameObject->GetPosition().y() }, m_GameObject->GetRotation());
	}

	void Renderer::ShutDown()
	{
		GLib::Sprites::Release(m_Sprite);
	}

	GLib::Sprites::Sprite* Renderer::GetSprite()
	{
		return m_Sprite;
	}

	void Renderer::SetSprite(GLib::Sprites::Sprite* i_sprite)
	{
		m_Sprite = i_sprite;
	}
	
}