#include "RenderManager.h"
#include "File/File.h"

#include "GLib.h"

namespace Engine
{

	void RenderManager::Init()
	{
	}

	void RenderManager::Run()
	{
		GLib::BeginRendering();
		GLib::Sprites::BeginRendering();
		for (int i = 0; i < Renderers.size(); ++i)
		{			
			Renderers[i]->Run();
		}

		GLib::Sprites::EndRendering();
		GLib::EndRendering();		
	}

	void RenderManager::ShutDown()
	{
	}

	RenderManager::RenderManager()
	{
	}


	RenderManager::~RenderManager()
	{
	}

	GLib::Sprites::Sprite* RenderManager::CreateSprite(const char* i_FileName)
	{
		size_t sizeTextureFile = 0;

		// Load the source file (texture data)
		uint8_t * pTextureFile = LoadFile(i_FileName, sizeTextureFile);

		// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
		GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

		// exit if something didn't work
		// probably need some debug logging in here!!!!
		if (pTextureFile)
			delete[] pTextureFile;

		unsigned int width = 0;
		unsigned int height = 0;
		unsigned int depth = 0;

		// Get the dimensions of the texture. We'll use this to determine how big it is on screen
		bool result = GLib::GetDimensions(pTexture, width, height, depth);
		assert(result == true);
		assert((width > 0) && (height > 0));

		// Define the sprite edges
		GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
		GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
		GLib::RGBA							Color = { 255, 255, 255, 255 };

		// Create the sprite
		GLib::Sprites::Sprite* sprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
		if (sprite == nullptr)
		{
			GLib::Release(pTexture);
		}

		// Bind the texture to sprite
		GLib::Sprites::SetTexture(*sprite, *pTexture);

		return sprite;
	}

	void RenderManager::AddRenderer(shared_ptr<GameObject> go, const char* i_FileName)
	{
		
		Renderer* renderer = new Renderer(go);

		GLib::Sprites::Sprite* sprite = CreateSprite(i_FileName);
		renderer->SetSprite(sprite);		
		go->SetRenderer(renderer);		

		Renderers.push_back(renderer);
	}
}
