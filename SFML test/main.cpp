#include "includes.h"

int velocity = 5;
int score_p1 = 0;
int score_p2 = 0;
int movement = 20;

DWORD WINAPI movement_Handler(LPVOID parameter)
{
	while (true)
	{
		if (GetKeyState(VK_UP) & 0x8000)
		{
			Sleep(20);
			line.setPosition(line.getPosition().x, line.getPosition().y - movement);
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			Sleep(20);
			line.setPosition(line.getPosition().x, line.getPosition().y + movement);
		}

		try {
			if (line.getPosition().y <= 0)
				line.setPosition(line.getPosition().x, 0);
			if (line.getPosition().y >= 900 - 150)
				line.setPosition(line.getPosition().x, 900 - 150);
		}
		catch (std::exception e)
		{
			std::cout << "なぜこんなことになったのか？";
		}
	}
	return 0;
}

DWORD WINAPI movement_Handler_2(LPVOID parameter)
{
	while (true)
	{
		if (GetKeyState(0x57) & 0x8000)
		{
			Sleep(20);
			line2.setPosition(line2.getPosition().x, line2.getPosition().y - movement);
		}
		if (GetKeyState(0x53) & 0x8000)
		{
			Sleep(20);
			line2.setPosition(line2.getPosition().x, line2.getPosition().y + movement);
		}

		try {
			if (line2.getPosition().y <= 0)
				line2.setPosition(line2.getPosition().x, 0);
			if (line2.getPosition().y >= 900 - 150)
				line2.setPosition(line2.getPosition().x, 900 - 150);
		}
		catch (std::exception e)
		{
		}
	}
	return 0;
}

DWORD WINAPI ball_Handler(LPVOID parameter)
{
	bool up = false;
	bool right = true;
	Sleep(3000);
	while (true)
	{
		if (ball.getPosition().y <= 0)
		{
			up = false;
			Sleep(20);
		}
		if (ball.getPosition().y >= 900 - 35)
		{
			up = true;
			Sleep(20);
		}

		if (ball.getGlobalBounds().intersects(line.getGlobalBounds()))
		{
			right = true;
			ball.setPosition(ball.getPosition().x + velocity, ball.getPosition().y);
			velocity += random() % 2;
			movement += 1;
		}

		if (ball.getGlobalBounds().intersects(line2.getGlobalBounds()))
		{
			right = false;
			ball.setPosition(ball.getPosition().x - velocity, ball.getPosition().y);
			velocity += random() % -2;
			movement += 1;
		}
		switch (right)
		{
			case true:
				ball.setPosition(ball.getPosition().x + velocity, ball.getPosition().y);
					break;
			case false:
				ball.setPosition(ball.getPosition().x - velocity, ball.getPosition().y);
					break;
		}
		switch (up)
		{
			case true:
				ball.setPosition(ball.getPosition().x, ball.getPosition().y - 5);
				break;
			case false:
				ball.setPosition(ball.getPosition().x, ball.getPosition().y + 5);
				break;
		}
		Sleep(10);

	}
	return 0;
}	

DWORD WINAPI game_Handler(LPVOID parameter)
{
	while (true)
	{
		if (ball.getPosition().x <= line.getPosition().x - 100)
		{
			velocity = 0;
			ball.setPosition(600, 450);
			score_p2++;
			score2.setString(std::to_string(score_p2));
			Sleep(3000);
			velocity = 5;
			movement = 20;
		}
		if (ball.getPosition().x >= line2.getPosition().x + 100)
		{
			velocity = 0;
			ball.setPosition(600, 450);
			score_p1++;
			score1.setString(std::to_string(score_p1));
			Sleep(3000);
			velocity = 5;
			movement = 20;
		}
	}
	return 0;
}

int main()
{
	// load font
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	score1.setFont(font);
	score2.setFont(font);

	// Window information
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Unloved ");

	// Render properties
	line.setRotation(90);
	line.setPosition(100, 100);
	line2.setRotation(90);
	line2.setPosition(1000, 100);
	ball.setPosition(600, 450);

	// Score1
	score1.setPosition(500, 0);
	score1.setCharacterSize(50);
	score1.setFillColor(sf::Color::Red);
	score1.setString(std::to_string(score_p1));

	// Score2
	score2.setPosition(700, 0);
	score2.setCharacterSize(50);
	score2.setFillColor(sf::Color::Red);
	score2.setString(std::to_string(score_p2));

	CreateThread(NULL, 0, movement_Handler, NULL, 0, NULL); // Create thread for movement_Handler function
	CreateThread(NULL, 0, movement_Handler_2, NULL, 0, NULL); // Create thread for movement_Handler2 function
	CreateThread(NULL, 0, ball_Handler, NULL, 0, NULL); // Create thread for ball_Handler function
	CreateThread(NULL, 0, game_Handler, NULL, 0, NULL); // Create thread for game_Handler function


	// Start the Window
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Players
		window.draw(line);
		window.draw(line2);

		// Ball
		window.draw(ball);

		// Score
		window.draw(score1);
		window.draw(score2);
		window.display();
	}

	return 0;
}