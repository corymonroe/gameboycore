
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

#include <stdexcept>

#include "screen_renderer.h"

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::Gameboy& gameboy) :
		window_(sf::VideoMode(160 * 2, 144 * 2), "Dotrix [beta]"),
		screen_renderer_{gameboy},
		joypad_{gameboy.getJoypad()}
	{
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
			case sf::Event::Resized:
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::TextEntered:
				break;
			case sf::Event::KeyPressed:
				handleKeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				handleKeyReleased(event.key.code);
				break;
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;
			case sf::Event::JoystickButtonPressed:
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				break;
			case sf::Event::JoystickConnected:
				break;
			case sf::Event::JoystickDisconnected:
				break;
			case sf::Event::Count:
				std::runtime_error("Invalid event type");
				break;
			}
		}

		window_.clear(sf::Color(255, 0, 0, 255));
		screen_renderer_.draw(window_);
		window_.display();
	}

	void updateTextures()
	{
		screen_renderer_.update();
	}

	bool isOpen()
	{
		return window_.isOpen();
	}

	~Window()
	{
	}

private:

	void handleKeyPressed(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Key::W:
			joypad_.press(gb::Joypad::Key::UP);
			break;
		case sf::Keyboard::Key::A:
			joypad_.press(gb::Joypad::Key::LEFT);
			break;
		case sf::Keyboard::Key::D:
			joypad_.press(gb::Joypad::Key::RIGHT);
			break;
		case sf::Keyboard::Key::S:
			joypad_.press(gb::Joypad::Key::DOWN);
			break;

		case sf::Keyboard::RShift:
			joypad_.press(gb::Joypad::Key::SELECT);
			break;
		case sf::Keyboard::Return:
			joypad_.press(gb::Joypad::Key::START);
			break;

		case sf::Keyboard::J:
			joypad_.press(gb::Joypad::Key::A);
			break;
		case sf::Keyboard::K:
			joypad_.press(gb::Joypad::Key::B);
			break;

		default:
			break;
		}
	}

	void handleKeyReleased(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Key::W:
			joypad_.release(gb::Joypad::Key::UP);
			break;
		case sf::Keyboard::Key::A:
			joypad_.release(gb::Joypad::Key::LEFT);
			break;
		case sf::Keyboard::Key::D:
			joypad_.release(gb::Joypad::Key::RIGHT);
			break;
		case sf::Keyboard::Key::S:
			joypad_.release(gb::Joypad::Key::DOWN);
			break;

		case sf::Keyboard::RShift:
			joypad_.release(gb::Joypad::Key::SELECT);
			break;
		case sf::Keyboard::Return:
			joypad_.release(gb::Joypad::Key::START);
			break;

		case sf::Keyboard::J:
			joypad_.release(gb::Joypad::Key::A);
			break;
		case sf::Keyboard::K:
			joypad_.release(gb::Joypad::Key::B);
			break;

		default:
			break;
		}
	}

private:
	sf::RenderWindow window_;
	ScreenRenderer screen_renderer_;

	gb::Joypad joypad_;
};


#endif // EMULATOR_WINDOW_H
