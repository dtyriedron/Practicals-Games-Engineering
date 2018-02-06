#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "maths.h"

#define ls LevelSystem

class LevelSystem
{
	public:
		//enum to set the different states of each tile
		enum TILE {EMPTY, START, END, WALL, ENEMY, WAYPOINT};
		
		//allows for the map to be load from a file
		static void loadLevelFile(const std::string&, float tileSize=100.f);
		//allows the map to be rendered
		static void render(sf::RenderWindow &window);
		//getter for the colour of the tile
		static sf::Color getColor(TILE t);
		//setter for setting the colour of the tile
		static void setColor(TILE t, sf::Color c);
		//get Tile at grid coordinate
		static TILE getTile(sf::Vector2ul);
		//get Screenspace coordinate of tile
		static sf::Vector2f getTilePosition(sf::Vector2ul);
		//get the tile at the screenspace pos
		static TILE getTileAt(sf::Vector2f);
		//get the width and height
		const static size_t getHeight();
		const static size_t getWidth();
		//creating offset
		static sf::Vector2f _offset;
	
	protected:
		//put the tiles into an array
		static std::unique_ptr<TILE[]> _tiles;
		//dimesions of the tiles are stored in these variables below
		static size_t _width;
		static size_t _height;
		static float _tileSize;
		//create a map to assign the specific tiles to their colours
		static std::map<TILE, sf::Color> _colours;
		//smart pointer directed at rectangle shapes stored in a variable called sprites
		static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
		
		//function to build the rectangles up
		static void buildSprites();
		
		private:
			//constructor and destructor for the level system
			LevelSystem() = delete;
			~LevelSystem() = delete;
};