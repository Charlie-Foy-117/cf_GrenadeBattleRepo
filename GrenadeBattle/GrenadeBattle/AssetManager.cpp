#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffer;

sf::Texture& AssetManager::RequestTexture(std::string textureName)
{
	// TODO: insert return statement here
	auto pairFound = textures.find(textureName);

	if (pairFound != textures.end())
	{
		//we found an existing texture, use it
		return pairFound->second; //the value in the key-value pair
	}
	else
	{
		sf::Texture& newTexture = textures[textureName];
		newTexture.loadFromFile(textureName);
		return newTexture;
	}
}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
	//insert return statement here
	auto pairFound = fonts.find(assetName);

	if (pairFound != fonts.end())
	{
		//we found an existing soundbuffer, use it
		return pairFound->second; //the value in the key-value pair
	}
	else
	{
		sf::Font& newFont = fonts[assetName];
		newFont.loadFromFile(assetName);
		return newFont;
	}
}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string assetName)
{
	//insert return statement here
	auto pairFound = soundBuffer.find(assetName);

	if (pairFound != soundBuffer.end())
	{
		//we found an existing soundbuffer, use it
		return pairFound->second; //the value in the key-value pair
	}
	else
	{
		sf::SoundBuffer& newSoundBuffer = soundBuffer[assetName];
		newSoundBuffer.loadFromFile(assetName);
		return newSoundBuffer;
	}
}

void AssetManager::DestroyAllAssets()
{
	textures.clear();
	fonts.clear();
	soundBuffer.clear();
}
