
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

#include <stdexcept>

class Window
{
public:
	Window(gb::TileRAM& tile_ram) :
		window_(sf::VideoMode(250, 250), "Gameboy Emulator"),
		tile_ram_(tile_ram)
	{
		if (!tileset_texture_.create(120, 120))
			throw std::runtime_error("Could not create texture");

		tileset_sprite_.setTexture(tileset_texture_);
		tileset_sprite_.setPosition(10, 10);
	}

	void update()
	{
		// pump event loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window_.close();
				break;
			}
		}

		window_.clear();

		updateTilesetTexture();
		window_.draw(tileset_sprite_);

		window_.display();
	}

	bool isOpen()
	{
		return window_.isOpen();
	}

	~Window()
	{
	}

private:
	void drawTileset()
	{
		
	}

	void updateTilesetTexture()
	{
		std::vector<sf::Uint8> pixel_data(120 * 120 * 4, 255);
		
		std::vector<gb::Tile> tiles = tile_ram_.getTiles();

		int tile_x     = 0;
		int tile_y     = 0;
		int tile_count = 0;

		for (int idx = 0; idx < tiles.size(); ++idx)
		{
			gb::Tile tile = tiles[idx];

			int pixel = 0;
			for (int row = 0; row < 8; ++row)
			{
				for (int col = 0; col < 8; ++col)
				{
					sf::Color color = getColor(tile.color[pixel++]);
					writePixel(pixel_data, tile_x + col, tile_y + row, color);
				}
			}

			tile_x += 8;
			tile_count++;
			if (tile_count >= 15)
			{
				tile_y += 8;
				tile_x     = 0;
				tile_count = 0;
			}
		}

		/*
		for (gb::Tile& tile : tiles)
		{
		int pixel = 0;
		for (int row = tile_pixel_offset_y; row < tile_pixel_offset_y + 8; ++row)
		{
		for (int col = tile_pixel_offset_x; col < tile_pixel_offset_x + 8; ++col)
		{
		sf::Color color = getColor(tile.color[pixel++]);
		writePixel(pixel_data, col, row, color);
		}
		}

		tile_pixel_offset_x += 8;
		tile_count++;
		if (tile_count >= 15)
		{
		tile_pixel_offset_y += 8;
		tile_pixel_offset_x = 0;
		}
		}
		*/

		// update the tileset texture
		tileset_texture_.update(&pixel_data[0]);
	}

	void writePixel(std::vector<sf::Uint8>& pixels, int x, int y, sf::Color c)
	{
		const unsigned int pixels_per_row = 120; // pixels per row

		int byte_offset = ((y * pixels_per_row) + x) * 4;

		pixels[byte_offset + 0] = c.r;
		pixels[byte_offset + 1] = c.g;
		pixels[byte_offset + 2] = c.b;
		pixels[byte_offset + 3] = c.a;
	}

	sf::Color getColor(uint8_t idx)
	{
		static sf::Color colors[] = {
			{255, 255, 255, 255},
			{192, 192, 192, 255},
			{ 96,  96,  96, 255},
			{  0,   0,   0, 255}
		};

		return colors[idx];
	}

private:
	sf::RenderWindow window_;
	

	gb::TileRAM tile_ram_;
	sf::Texture tileset_texture_;
	sf::Sprite tileset_sprite_;

};


#endif // EMULATOR_WINDOW_H

