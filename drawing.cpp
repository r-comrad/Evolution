#include "drawing.h"

//--------------------------------------------------------------------------------
// Drawing implementation
//--------------------------------------------------------------------------------

Drawing::Drawing() :
	mWindow(sf::VideoMode(1920, 1200), "Evolution"),
	mDrawFlag(true),
	nextStep(false),
	stepByStepFlag(false)
{
	if (!mFont.loadFromFile("font.ttf"))
	{
		cout << "Font load error!\n";
	}
	mText.setFont(mFont);
	mText.setFillColor(sf::Color::White);
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
			if (mEvent.key.code == sf::Keyboard::LShift)
			{

				cout << "LShift";
				stepByStepFlag = !stepByStepFlag;
			}
			if (mEvent.key.code == sf::Keyboard::Q)
			{
				cout << "Q";
				nextStep = true;
			}
			if (mEvent.key.code == sf::Keyboard::X)
			{
				mWindow.close();
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		cout << "W";
		nextStep = true;
	}
}
//--------------------------------------------------------------------------------
//void
//Drawing::draw(const std::vector<std::vector<CeilType>>& aField,
//	CreaturesLifeList& aList, const PopulationStatistic& aPopStatistic)
//{
//	mWindow.clear();
//
//	if (mDrawFlag)
//	{
//		drawField(aField, aList);
//	}
//
//	mText.setCharacterSize(50);
//	mText.setPosition(1650, 50);
//	mText.setString(std::to_string(aPopStatistic.getPopulationAge()));
//	mWindow.draw(mText);
//
//	mText.setCharacterSize(18);
//	mText.setPosition(1685, 40);
//	mText.setString(std::to_string(aPopStatistic.getCreatureCount()));
//	mWindow.draw(mText);
//
//	mWindow.display();
//}
//--------------------------------------------------------------------------------
bool
Drawing::isActive()
{
	return mWindow.isOpen();
}
//--------------------------------------------------------------------------------
bool
Drawing::isDraw()
{
	return mDrawFlag;
}
//--------------------------------------------------------------------------------
void
Drawing::clear()
{
	mWindow.clear();
}
//--------------------------------------------------------------------------------
void
Drawing::display()
{
	mWindow.display();
}
//--------------------------------------------------------------------------------
void 
Drawing::drawField(const std::vector<std::vector<CeilType>>& aField)
{
	if (mDrawFlag == false) return;

	sf::RectangleShape rectangle(sf::Vector2f(DRAW_SQUARE_SIZE, DRAW_SQUARE_SIZE));

	for (uint_8 i = 0; i < aField.size(); ++i)
	{
		for (uint_8 j = 0; j < aField[i].size(); ++j)
		{
			rectangle.setPosition(sf::Vector2f
				(30 + i * DRAW_SQUARE_SIZE, 30 + j * DRAW_SQUARE_SIZE));

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

	mText.setCharacterSize(10);
	for (uint_8 i = 0; i < aField.size(); ++i)
	{
		mText.setPosition(35 + i * (DRAW_SQUARE_SIZE), 15);
		mText.setString(std::to_string(i));
		mWindow.draw(mText);
	}
	for (uint_8 i = 0; i < aField[0].size(); ++i)
	{
		mText.setPosition(15, 30 + i * (DRAW_SQUARE_SIZE));
		mText.setString(std::to_string(i));
		mWindow.draw(mText);
	}
}
//--------------------------------------------------------------------------------
void 
Drawing::drawCreaturesLifes(CreaturesLifeList& aList)
{
	if (mDrawFlag == false) return;

	for (uint_16 i = 0; i < aList.size(); ++i)
	{
		std::pair<Point, sint_16> cur = aList.getNextValue();
		Point coord = cur.first;
		sint_16 life = cur.second;

		mText.setCharacterSize(12);
		mText.setPosition(sf::Vector2f
		(30 + coord.mX * DRAW_SQUARE_SIZE + 1, 30 + coord.mY * DRAW_SQUARE_SIZE));
		mText.setString(std::to_string(life));
		mWindow.draw(mText);
	}
}
//--------------------------------------------------------------------------------
void
Drawing::drawStatistic(const PopulationStatistic& aPopStatistic)
{
	mText.setCharacterSize(18);
	mText.setPosition(1685, 40);
	mText.setString(std::to_string(aPopStatistic.getCreatureCount()));
	mWindow.draw(mText);

	const std::list<uint_16>& ages = aPopStatistic.getAllAges();
	uint_16 num = 0;
	for (auto& i : ages)
	{
		mText.setCharacterSize(50);
		mText.setPosition(1650, 50 + num * 50);
		mText.setString(std::to_string(i));
		mWindow.draw(mText);
		num++;
	}
}
//--------------------------------------------------------------------------------
bool 
Drawing::pressedN()
{
	if (nextStep == true)
	{
		nextStep = false;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------
bool 
Drawing::stepByStep()
{
	return stepByStepFlag;
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