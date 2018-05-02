#include "drawing.h"

//--------------------------------------------------------------------------------
// Drawing implementation
//--------------------------------------------------------------------------------

void 
Drawing::drawField(sf::RenderWindow& aWindow, Environment& aEnvironment) const
{
	const std::vector<std::vector<CeilType>>& field = aEnvironment.getField();

	sf::RectangleShape rectangle(sf::Vector2f(DRAW_SQUARE_SIZE, DRAW_SQUARE_SIZE));
	//sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	//rectangle.setSize(sf::Vector2f(DRAW_SQUARE_SIZE, DRAW_SQUARE_SIZE));

	for (uint_8 i = 0; i < field.size(); ++i)
	{
		for (uint_8 j = 0; j < field[i].size(); ++j)
		{
			rectangle.setPosition(sf::Vector2f
			(i * DRAW_SQUARE_SIZE, j * DRAW_SQUARE_SIZE));

			if (field[i][j] == EMPTY)
			{
				rectangle.setFillColor(sf::Color::Black);
			}
			else if (field[i][j] == FOOD)
			{
				rectangle.setFillColor(sf::Color::Green);
			}
			else if (field[i][j] == POISON)
			{
				rectangle.setFillColor(sf::Color::Red);
			}
			else if (field[i][j] == WALL)
			{
				rectangle.setFillColor(sf::Color::White);
			}
			else if (field[i][j] == CREATURE)
			{
				rectangle.setFillColor(sf::Color::Blue);
			}

			aWindow.draw(rectangle);
		}
	}

	//		text.setCharacterSize(10);
	//		//text.setColor(sf::Color::White);
	//		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	//
	//		for (std::map<uint_8, Creature*> ::iterator it = mCreatures.begin();
	//			it != mCreatures.end(); ++it)
	//		{
	//			text.setString(std::to_string(it->second->getLife()));
	//			text.setPosition(sf::Vector2f(it->second->getX() *
	//				DRAW_SQUARE_SIZE + 1, it->second->getY() * DRAW_SQUARE_SIZE));
	//			mWindow->draw(text);
	//		}
}
//--------------------------------------------------------------------------------
void 
Drawing::drawCreatures(sf::RenderWindow& aWindow,
	Environment& aEnvironment, Population& aPopulation) const
{
	//text.setCharacterSize(25);

	//text.setString(std::to_string(globalCycleCount));
	//text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 100));
	//mWindow->draw(text);

	//text.setString(std::to_string(cycleCount));
	//text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 250));
	//mWindow->draw(text);

	//for (uint_8 i = 0; i < oldCycleCount.size(); ++i)
	//{
	//	text.setString(std::to_string(oldCycleCount[i]));
	//	text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 300 + 50 * i));
	//	mWindow->draw(text);
	//}
}
//--------------------------------------------------------------------------------
void 
Drawing::drawHistory(sf::RenderWindow& aWindow, std::vector<uint_32> aHistory) const
{
	//text.setCharacterSize(25);

	//text.setString(std::to_string(globalCycleCount));
	//text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 100));
	//mWindow->draw(text);

	//text.setString(std::to_string(cycleCount));
	//text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 250));
	//mWindow->draw(text);

	//for (uint_8 i = 0; i < oldCycleCount.size(); ++i)
	//{
	//	text.setString(std::to_string(oldCycleCount[i]));
	//	text.setPosition(sf::Vector2f(DRAW_SQUARE_SIZE *(N + 7), 300 + 50 * i));
	//	mWindow->draw(text);
	//}
}
//--------------------------------------------------------------------------------