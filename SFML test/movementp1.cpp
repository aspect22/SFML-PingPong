#include <Windows.h>
#include <SFML/Graphics.hpp>
sf::RectangleShape line(sf::Vector2f(150, 20)); // Define line globally
sf::RectangleShape line2(sf::Vector2f(150, 20)); // Define line globally
static DWORD WINAPI movement_Handler(LPVOID parameter)
{
	while (true)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			Sleep(20);
			line.setPosition(line.getPosition().x, line.getPosition().y - 20);
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			Sleep(20);
			line.setPosition(line.getPosition().x, line.getPosition().y + 20);
		}

		try {
			if (line.getPosition().y <= 0)
				line.setPosition(line.getPosition().x, 0);
			if (line.getPosition().y >= 900 - 150)
				line.setPosition(line.getPosition().x, 900 - 150);
		}
		catch (std::exception e)
		{
		}
	}
	return 0;
}