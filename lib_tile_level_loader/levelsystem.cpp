#include "levelsystem.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

//smart ptr storing the tiles in a tile array 
std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
//setting the width and height variables to have the max possible values for them
size_t LevelSystem::_width;
size_t LevelSystem::_height;
sf::Vector2f LevelSystem::_offset = Vector2f{ 0,0 };

//setting the size of each tile
float LevelSystem::_tileSize(100.f);
//smart ptr for storing the sprites in rectangles 
vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

//creating a map that assigns the tiles to a colour
std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours
{
	{WALL, Color::White}, {END, Color::Red}
};

//search through the colours map and find a colour relating the tile that you have inputted
sf::Color LevelSystem::getColor(LevelSystem::TILE t)
{
	auto it = _colours.find(t);
	if(it == _colours.end())
	{
		_colours[t] = Color::Transparent;
	}
	return _colours[t];
}

//insert a new colour and tile associated to the colour into the map
void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c)
{
	_colours.insert(std::pair<LevelSystem::TILE, sf::Color>(t, c));
}

//load in the text file, change the tile size if you want
void LevelSystem::loadLevelFile(const std::string &path, float tileSize)
{
	_tileSize = tileSize;
	size_t w =0, h=0;
	string buffer;
	
	//load in file to buffer
	ifstream f(path);
	if(f.good())
	{
		f.seekg(0,std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else
	{
		throw string("couldn't open level file") + path;
	}
	
	std::vector<TILE> temp_tiles;
	for(int i =0; i< buffer.size(); i++)
	{
		const char c = buffer[i];
		switch(c)
		{
			case 'w':
				temp_tiles.push_back(WALL);
				break;
			case 's':
				temp_tiles.push_back(START);
				break;
			case 'e':
				temp_tiles.push_back(END);
				break;
			case ' ':
				temp_tiles.push_back(EMPTY);
				break;
			case '+':
				temp_tiles.push_back(WAYPOINT);
				break;
			case 'n':
				temp_tiles.push_back(ENEMY);
				break;
			case '\n':  //end of a line
				if(w==0)
				{
					w = i; //set the width
				}
				h++;  //increment the height
				break;
				default:
				cout<<c <<endl; //dont know what tile type this is
		}
	}
	if (temp_tiles.size() != (w*h))
	{
		//something went wrong
		throw string("can't parse level file") + path;
	}
	//now we know how big the level is, make an array.
	_tiles = std::make_unique<TILE[]>(w*h);
	_width = w; //set static class vars
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	cout << "Level " << path << "Loaded. " << w << "x" << h << std::endl;
	buildSprites();
}

void LevelSystem::buildSprites()
{
	_sprites.clear();
	for(size_t y=0;y<LevelSystem::getHeight();++y)
	{
		for(size_t x=0; x<LevelSystem::getWidth();++x)
		{
			auto s = make_unique<sf::RectangleShape>();
			s->setPosition(getTilePosition({x, y}));
			s->setSize(Vector2f(_tileSize, _tileSize));
			s->setFillColor(getColor(getTile({x, y})));
			_sprites.push_back(move(s));
		}
	}
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p)
{
	return (Vector2f(p.x,p.y) * _tileSize);
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul p)
{
	if(p.x>_width || p.y>_height)
	{
		throw string("Tile out of range: ") + to_string(p.x) + "," + to_string(p.y) + ")";
	}
	return _tiles[(p.y * _width) + p.x];
}

LevelSystem::TILE LevelSystem::getTileAt(Vector2f v)
{
	auto a = v - _offset;
	if(a.x<0 || a.y<0)
	{
		throw string("Tile out of range ");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

std::vector<sf::Vector2f> LevelSystem::findTiles(TILE t)
{
	vector<Vector2f> foundTiles;
	for (size_t y = 0; y < LevelSystem::getHeight(); ++y)
	{
		for (size_t x = 0; x < LevelSystem::getWidth(); ++x)
		{
			if (getTile({ x, y }) == t)
			{
				foundTiles.push_back((getTilePosition(Vector2ul{ x, y }) + Vector2f(_tileSize / 2.f, _tileSize / 2.f)));
			}
		}
	}
	return foundTiles;
}

const size_t LevelSystem::getHeight()
{
	return _height;
}

const size_t LevelSystem::getWidth()
{
	return _width;
}

void LevelSystem::render(RenderWindow &window)
{
	for(size_t i=0;i<_width * _height; ++i)
	{
		window.draw(*_sprites[i]);
	}
}
