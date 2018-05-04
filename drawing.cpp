#include "drawing.h"

//--------------------------------------------------------------------------------
// Drawing implementation
//--------------------------------------------------------------------------------

Drawing::Drawing() :
	mWindow(sf::VideoMode(1920, 1200), "Evolution"),
	mDrawFlag(true)
{
	if (!mFont.loadFromFile("font.ttf"))
	{
		cout << "Font load error!\n";
	}
	mText.setFont(mFont);
	mText.setFillColor(sf::Color::White);
	//mText.setColor(sf::Color(250, 250, 250));
	mText.setStyle(sf::Text::Bold | sf::Text::Underlined);
}
//--------------------------------------------------------------------------------
void 
Drawing::checkEvents()
{
	while (mWindow.pollEvent(mEvent))
	{
		if (mEvent.type == sf::Event::Closed) mWindow.close();

		if (mEvent.type == sf::Event::KeyReleased)
		{
			if (mEvent.key.code == sf::Keyboard::Tab)
			{
				cout << "Tab";
				mDrawFlag = !mDrawFlag;
			}
			if (mEvent.key.code == sf::Keyboard::Num1)
			{
				cout << "1";
				mDrawState = DrawingState::NONE;
			}
			if (mEvent.key.code == sf::Keyboard::Num2)
			{
				cout << "2";
				mDrawState = DrawingState::GENERATION;
			}
			if (mEvent.key.code == sf::Keyboard::Num3)
			{
				cout << "3";
				mDrawState = DrawingState::TURN;
			}
			if (mEvent.key.code == sf::Keyboard::Num4)
			{
				cout << "4";
				mDrawState = DrawingState::STEP;
			}
			if (mEvent.key.code == sf::Keyboard::X)
			{
				mWindow.close();
			}
		}
	}
}
//--------------------------------------------------------------------------------
void 
Drawing::draw(const std::vector<std::vector<CeilType>>& aField, 
	uint_16 aPopulatioAge, uint_16 aPopulationTurnCount)
{
	mWindow.clear();



	if (mDrawFlag)
	{
		drawField(aField);
	}

	mText.setCharacterSize(50);
	mText.setPosition(1650, 50);
	mText.setString(std::to_string(aPopulatioAge));
	mWindow.draw(mText);

	mText.setCharacterSize(18);
	mText.setPosition(1685, 40);
	mText.setString(std::to_string(aPopulationTurnCount));
	mWindow.draw(mText);

	mWindow.display();
}
//--------------------------------------------------------------------------------
bool
Drawing::isActive()
{
	return mWindow.isOpen();
}
//--------------------------------------------------------------------------------
void 
Drawing::drawField(const std::vector<std::vector<CeilType>>& aField)
{
	sf::RectangleShape rectangle(sf::Vector2f(DRAW_SQUARE_SIZE, DRAW_SQUARE_SIZE));
	//sf::RectangleShape rectangle(sf::Vector2f(0, 0));
	//rectangle.setSize(sf::Vector2f(DRAW_SQUARE_SIZE, DRAW_SQUARE_SIZE));

	for (uint_8 i = 0; i < aField.size(); ++i)
	{
		for (uint_8 j = 0; j < aField[i].size(); ++j)
		{
			rectangle.setPosition(sf::Vector2f
			(i * DRAW_SQUARE_SIZE, j * DRAW_SQUARE_SIZE));

			if (aField[i][j] == EMPTY)
			{
				rectangle.setFillColor(sf::Color::Black);
			}
			else if (aField[i][j] == FOOD)
			{
				rectangle.setFillColor(sf::Color::Green);
			}
			else if (aField[i][j] == POISON)
			{
				rectangle.setFillColor(sf::Color::Red);
			}
			else if (aField[i][j] == WALL)
			{
				rectangle.setFillColor(sf::Color::White);
			}
			else if (aField[i][j] == CREATURE)
			{
				rectangle.setFillColor(sf::Color::Blue);
			}

			mWindow.draw(rectangle);
		}
	}
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