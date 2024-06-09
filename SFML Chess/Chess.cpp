

#include<string>
#include<time.h>
#include<iostream>
using namespace std;
#include"Chess.h"
#include "Chess.h" 
#include"Players.h"
#include"Board.h"
#include<iostream>
#include"Utility.h"
#include "Piece.h"
#include"ChessGameState.h"
#include<vector>
#include"Bishop.h"
#include"King.h"
#include"Knight.h"
#include"Pawn.h"
#include"Queen.h"
#include"Rook.h"
#include"Piece.h"
#include<fstream>



Chess::Chess()
{
	timer = false;
	Load = false;

	turn = 0;
	rows = 8;
	cols = 8;
	boxSize = 60;
	Position Null(0, 0);
	sourcePos = Null;
	destPos = Null;
	B = new Board(60);
	players[0] = new Players("Player1", White);
	players[1] = new Players("Player2", Black);
	window=new RenderWindow(sf::VideoMode(1200, 600), "Chess", sf::Style::Default);
	renderHiglight=false;
	selectDest=false;
	isCheck = false, isCheckMate = false, isStaleMate = false;
	Copy = B->clone();
	shift_X = 400;
	shift_Y = 60;
	p1Time = 30;
	p2Time = 30;
}
void Chess::InputNames()
{
	sf::RenderWindow window(sf::VideoMode(600, 200), "Enter Names");
	
	sf::Font font;
	if (!font.loadFromFile("Fonts/phantomstormwide.ttf")) // Load a font to display text
	{
		std::cout << "Error loading font" << std::endl;
	}
	sf::Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		// Error handling code here

	}
	// Set the icon for the window
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.jpg"))
	{
		cout << " not laod" << endl;
	}
	sf::Sprite backgroundSprite(backgroundTexture);
	// get the size of the window
	sf::Vector2u windowSize = window.getSize();
	
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	// set the scale of the sprite to match the window size
	backgroundSprite.setScale(
		(float(windowSize.x) / backgroundTexture.getSize().x),
		(float(windowSize.y) / backgroundTexture.getSize().y)
	);
	sf::Text player1_text;
	player1_text.setFont(font);
	player1_text.setString("Player 1 Name: ");
	player1_text.setCharacterSize(20);
	player1_text.setPosition(200, 50);

	sf::Text player2_text;
	player2_text.setFont(font);
	player2_text.setString("Player 2 Name: ");
	player2_text.setCharacterSize(20);
	player2_text.setPosition(200, 100);

	sf::Text input_text;
	input_text.setFont(font);
	input_text.setString("");
	input_text.setCharacterSize(20);
	input_text.setPosition(360, 50);

	std::string player1_name;
	std::string player2_name;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
	
			else if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == '\b' && input_text.getString().getSize() > 0) // Handle backspace
				{
					input_text.setString(input_text.getString().substring(0, input_text.getString().getSize() - 1));
				}
				else if (event.text.unicode < 128 && input_text.getString().getSize() < 10) // Handle valid characters
				{
					input_text.setString(input_text.getString() + static_cast<char>(event.text.unicode));
				}
				
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) // Handle enter key
			{
				if (player1_name.empty())
				{
					input_text.setPosition(360, 100);
					player1_name = input_text.getString();
					input_text.setString("");
					player1_text.setString("Player 1 Name: " + player1_name);

				}
				else if (player2_name.empty())
				{
					player2_name = input_text.getString();
					input_text.setString("");
					player2_text.setString("Player 2 Name: " + player2_name);

				}

				if (player1_name.size() >= 10 || player2_name.size() >= 10) // Check name length
				{
				
					std::cout << "Error: Names must be shorter than 10 characters" << std::endl;
					player1_name = "";
					player2_name = "";
					player1_text.setString("Player 1 Name: ");
					player2_text.setString("Player 2 Name: ");
					input_text.setPosition(360, 50);
				}
				else if (!player1_name.empty() && !player2_name.empty()) // Both names have been entered
				{
					std::cout << "Player 1 Name: " << player1_name << std::endl;
					std::cout << "Player 2 Name: " << player2_name << std::endl;
					window.close();
				}
			}
		}

		window.clear();
		window.draw(backgroundSprite);
		window.draw(input_text);
		window.draw(player1_text);
		window.draw(player2_text);

		window.display();
	}
	string enter = "\r";
	if(player1_name!=enter)
	players[0]->SetName(player1_name);
	if (player2_name != enter)
	players[1]->SetName(player2_name);

}
void Chess::safe(vector<ChessGameState> gameHistory)
{
	write(gameHistory[gameHistory.size() - 1]);
}
bool  isUndoPosition(int x, int y)
{
	if((y>= 500 && y<=547 )&&(x>=1020 && x<=1050))
		return true;
	return false;
}
bool  isRedoPosition(int x, int y)
{
	if ((y >= 500 && y <= 547) && (x >= 1080 && x <= 1130))
		return true;
	return false;
}
void Chess::undoGame(vector<ChessGameState>& gameHistory,int index)
{
	if (index < 0 || index >= gameHistory.size())
		return;
	Board* copy2 = B->clone();
	if (gameHistory.size() > 1) {
		// Remove the last game state from the vector
		ChessGameState prevGameState = gameHistory[index];
		// Get the previous game state
		B = new Board(prevGameState.board);
		// Update the board and player information to the previous state
		turn = prevGameState.turn;
		*players[0] = prevGameState.player1;
		*players[1] = prevGameState.player2;
		sourcePos = prevGameState.dest;
		destPos = prevGameState.source;
		isCheck = prevGameState.isCheck;
		isCheckMate = prevGameState.isCheckMate;
		isStaleMate = prevGameState.isStaleMate;
		B->enableCastling = prevGameState.enableCastling;
	}
	
}


bool Chess::isPromotion(Position pos)
{
	Piece* pawn = B->getPiece(pos);
	if (pawn != nullptr && pawn->getType() == PieceType::PAWN) {
		pColor color = pawn->getColor();
		int row = pos.rpos;

		// Check if the pawn has reached the end of the board
		if ((color == Black && row == 7) || (color == White && row == 0)) {
			return true;
		}
	}
	return false;
}
void Chess::promotion(Position pos)
{
	int choice = 0;
	Piece* pawn = B->getPiece(pos);
	if (pawn != nullptr && pawn->getType() == PieceType::PAWN) {
		{
			Texture queen,rook,bishop,knight;
			pColor color = pawn->getColor();
			if (color == Black)
			{
				queen.loadFromFile("images\\black-queen.png");
				rook.loadFromFile("images\\black-rook.png");
				bishop.loadFromFile("images\\black-bishop.png");
				knight.loadFromFile("images\\black-knight.png");
			}
			else
			{
				
				queen.loadFromFile("images\\white-queen.png");
				rook.loadFromFile("images\\white-rook.png");
				bishop.loadFromFile("images\\white-bishop.png");
				knight.loadFromFile("images\\white-knight.png");
			}
			


			sf::RenderWindow Window(sf::VideoMode(134, 134), "Promotion", sf::Style::Default);
			sf::Event ev;


			sf::Sprite Piece1;
			sf::Sprite Piece2;
			sf::Sprite Piece3;
			sf::Sprite Piece4;

			Piece1.setTexture(queen);
			Piece1.setPosition(sf::Vector2f(0, 0));


			Piece2.setTexture(rook);
			Piece2.setPosition(sf::Vector2f(76, 0));



			Piece3.setTexture(bishop);
			Piece3.setPosition(sf::Vector2f(3, 71));



			Piece4.setTexture(knight);
			Piece4.setPosition(sf::Vector2f(71, 71));
			sf::Image icon;
			if (!icon.loadFromFile("icon.png"))
			{
				cout << "icon not loaded";
			}
			Window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
			while (Window.isOpen())
			{
				sf::Event ev;
				while (Window.pollEvent(ev))
				{
					switch (ev.type)
					{
					case sf::Event::MouseButtonPressed:
						if (ev.mouseButton.button == sf::Mouse::Left)
						{
							if ((ev.mouseButton.x >= 0) && (ev.mouseButton.x <= 62) && (ev.mouseButton.y >= 0) && (ev.mouseButton.y <= 62))
							{
								choice = 1;
								Window.close();
							}
							else if ((ev.mouseButton.x >= 72) && (ev.mouseButton.x <= 134) && (ev.mouseButton.y >= 0) && (ev.mouseButton.y <= 62))
							{
								choice = 2;
								Window.close();
							}

							else if ((ev.mouseButton.x >= 0) && (ev.mouseButton.x <= 62) && (ev.mouseButton.y >= 71) && (ev.mouseButton.y <= 134))
							{
								choice = 3;
								Window.close();
							}
							else if ((ev.mouseButton.x >= 72) && (ev.mouseButton.x <= 134) && (ev.mouseButton.y >= 71) && (ev.mouseButton.y <= 134))
							{
								choice = 4;
								Window.close();
							}
						}
					}
				}

				Window.clear();

				Window.draw(Piece1);
				Window.draw(Piece2);
				Window.draw(Piece3);
				Window.draw(Piece4);
				Window.display();


			}
			B->promote(choice, pos, color);
		}
	}
}

void Delete(bool**& Map)
{
	for (int i = 0; i < 8; i++)
	{
		delete Map[i];
	}
	delete[]Map;
	Map = nullptr;
}

void Chess::Play()
{
	int startTime = time(0);
	bool** Map=nullptr;
	vector<ChessGameState> gameHistory;
	int Undocount = 0;
	int RedoCount = 0;
	bool isUndo = false,isRedo=false;
	Piece* check = B->getPiece(sourcePos);
	
	ChessGameState gameState(*B, sourcePos, turn, destPos, *players[0], *players[1], isCheck, isCheckMate, isStaleMate, B->enableCastling,this->timer);
	gameHistory.push_back(gameState);


	SoundBuffer moveBuff;
	if (!moveBuff.loadFromFile("Audio/select.wav"))
		std::cout << "Error in opening movesound" << std::endl;




	bool bar_Display = false;
	bool bar1_Display = false;
	bool gameOver = false;
	bool g = true, l = true;
	//bool change = false;
	sf::Text tx;
	sf::Text text1, simple, timeb,clock1,clock2;
	Font home_font,timer_font;
	home_font.loadFromFile("Fonts/phantomstormwide.ttf");
	timer_font.loadFromFile("Fonts/digital-7 (mono).ttf");
	sf::Texture homeTexture;

	if (!homeTexture.loadFromFile("images\\front (5).jpg"))
	{
		cout << " not laod" << endl;
	}
	sf::Sprite homeSprite(homeTexture);
	// get the size of the window
	sf::Vector2u windowSize = window->getSize();

	// set the scale of the sprite to match the window size
	homeSprite.setScale(
		(float(windowSize.x) / homeTexture.getSize().x),
		(float(windowSize.y) / homeTexture.getSize().y));
	tx.setFont(home_font);
	tx.setString("new game");
	tx.setPosition(200, 250);


	text1.setFont(home_font);
	text1.setString("load game");
	text1.setPosition(200, 300);


	simple.setFont(home_font);
	simple.setString("simple mode");
	simple.setPosition(200, 250);


	timeb.setFont(home_font);
	timeb.setString("time based");
	timeb.setPosition(200, 300);
	
	clock1.setFont(timer_font);
	clock1.setString("30");
	clock1.setPosition(1070, 130);

	clock2.setFont(timer_font);
	clock2.setString("30");
	clock2.setPosition(1070, 430);



	//////////////////////////////////////////////////////

	sf::RectangleShape bar;
	sf::RectangleShape bar1;
	bar.setFillColor(sf::Color(128, 128, 128));
	bar.setSize(sf::Vector2f(180.f, 40.f));
	bar1.setFillColor(sf::Color(128, 128, 128));
	bar1.setSize(sf::Vector2f(165.f, 40.f));
	bool play = false, playCheckmate = false,playStalemate=false,gameoverplay=true;
	bool start = false;
	bool home = true;
	// Arp sound used in the background (will probably change in the future)
	SoundBuffer buffer;
	if (!buffer.loadFromFile("Audio/Chess.wav"))
		std::cout << "Error" << std::endl;
	Sound sound;
	sound.setLoop(true);
	sound.setVolume(10.0f);
	sound.setBuffer(buffer);
	// Font used in the game
	Font game_font;
	game_font.loadFromFile("Fonts/phantomstorm.ttf");
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	
	window->setVerticalSyncEnabled(true);
	// Limiting the framerate to 60 to decrease the load from GPU
	window->setFramerateLimit(60);
	

	sf::Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		// Error handling code here

	}
	// Set the icon for the window
	sf::Texture backgroundTexture;
	Texture turnTexture;
	turnTexture.loadFromFile("images\\arrow.png");
	Texture b_king;
	b_king.loadFromFile("images\\black-pawn.png");
	Texture w_king;
	w_king.loadFromFile("images\\white-pawn.png");
	Texture undo, redo;
	undo.loadFromFile("images\\undo.png");
	redo.loadFromFile("images\\redo.png");
	if (!backgroundTexture.loadFromFile("background.jpg"))
	{
		cout << " not laod" << endl;
	}
	sf::Sprite backgroundSprite(backgroundTexture);
	// get the size of the window

	// set the scale of the sprite to match the window size
	backgroundSprite.setScale(
		float(windowSize.x) / backgroundTexture.getSize().x,
		float(windowSize.y) / backgroundTexture.getSize().y
	);

	window->draw(backgroundSprite);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	drawBoard(*window, rows, cols, boxSize, shift_X, shift_Y);
	B->printBoard(*window, boxSize, shift_X, shift_Y);
	window->display();
	sound.play();
	while (window->isOpen())
	{
		
		if (start&&!this->Load)
		{
			InputNames();
			gameState.player1.SetName(players[0]->getName());
			gameState.player2.SetName(players[1]->getName());
	       gameHistory[0].player1.SetName(players[0]->getName());
		   gameHistory[0].player2.SetName(players[1]->getName());
			start = false;
			startTime = time(0);
		}
	
		//////////////////////
		//events
		
		Event event;
		while (window->pollEvent(event))
		{
	
			switch (event.type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window->close();
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					if (inRange(event.mouseButton.x, event.mouseButton.y)&&!this->selectDest&&!isCheckMate&&!home&&!gameOver)
					{
						sourcePos.rpos = (event.mouseButton.y-shift_Y)/boxSize ;
						sourcePos.cpos = (event.mouseButton.x-shift_X)/boxSize ;
						if (B->isValidSource(sourcePos, turn))
						{
						 Map = B->getPiece(sourcePos)->HighlightLoc(B, sourcePos, turn);
						renderHiglight = true;
						
						}
					}
					if (event.mouseButton.button == Mouse::Left&&this->selectDest&&!isCheckMate && !home&&!gameOver)
					{
						if (inRange(event.mouseButton.x, event.mouseButton.y) && selectDest)
						{
							destPos.rpos = (event.mouseButton.y - shift_Y) / boxSize;
							destPos.cpos = (event.mouseButton.x - shift_X) / boxSize;
							if (B->isValidDest(destPos, turn))
							{
								check = B->getPiece(sourcePos);
								if (check->legalMove(B, sourcePos, destPos))
								{
									Copy->movePiece(sourcePos, destPos);
									if (!Copy->selfCheck(turn))
									{
										action();
										if (isCheck)
											play = true;
										if (isCheckMate)
											playCheckmate = true;
										if (isStaleMate)
											playStalemate = true;
										startTime = time(0);
										if (isUndo)
										{
											for (int i = 1; i < Undocount; i++)
											{
												gameHistory.pop_back();
											}
											Undocount = 0;
											RedoCount = 0;
											isUndo = false;
											isRedo = false;
										}
										else {
											
											gameState.Update(*B, sourcePos, turn, destPos,isCheck,isCheckMate,isStaleMate,B->enableCastling,timer);
											gameHistory.push_back(gameState);
										}
									
										   
											safe(gameHistory);
										
									}
									this->selectDest = false;
									this->renderHiglight = false;
								}
								
							}
							this -> selectDest = false;
							this->renderHiglight = false;


						}
					}
					else if (isUndoPosition (event.mouseButton.x,event.mouseButton.y) && !home&&!gameOver)
					{
						if (Undocount == gameHistory.size() - 1)
							Undocount = 0;
						undoGame(gameHistory, gameHistory.size()-Undocount - 2);
						if(gameHistory.size()>1)
						Undocount++;
						isUndo = true;
					}
					else if (isRedoPosition(event.mouseButton.x, event.mouseButton.y)&&isUndo && !home&&!gameOver)
					{
						if (Undocount + RedoCount <= gameHistory.size() - 1)
							RedoCount = 0;
						undoGame(gameHistory, gameHistory.size() - Undocount+RedoCount);
						if (gameHistory.size() > 1)
							RedoCount++;
						isRedo = true;
							
					}
					if (event.mouseButton.x > 200 && event.mouseButton.x <= 343 && event.mouseButton.y >= 250 && event.mouseButton.y <= 277&&home&&!gameOver)
					{
						if (g)
						{
							g = false;
							l = false;
						}
						else
						{
							home = false;
							start = true;
						}
					}
					if (event.mouseButton.x >= 200 && event.mouseButton.x <= 343 && event.mouseButton.y >= 300 && event.mouseButton.y <= 327&&home&&!gameOver)
					{

						if (l)
						{
							Load = true;
						    load();
							
							home = false;
							start = true;
						}
						else
						{
							this->timer = true;
							home = false;
							start = true;
						}
					}
				}
				break;
			default:
				break;
			}
	

		}
		/////////////////



		////Player2 Name/////////
		sf::Sprite wking;
		sf::Text p1;
		p1.setFont(game_font);
		p1.setString(players[0]->getName());
		p1.setPosition(1050, 400);
		wking.setTexture(w_king);
		wking.setScale(sf::Vector2f(0.7f, 0.7f));
		wking.setPosition((1015), (400));
	

		////Player2 Name/////////

		sf::Sprite bking;
		sf::Text p2;
		p2.setFont(game_font);
		p2.setString(players[1]->getName());
		p2.setPosition(1050, 100);
		bking.setTexture(b_king);
		bking.setScale(sf::Vector2f(0.7f, 0.7f));
		bking.setPosition((1015), (100));

		
		Sprite indicate;
		indicate.setTexture(turnTexture);
		indicate.setColor(Color::Green);
		indicate.setScale(sf::Vector2f(0.03f, 0.03f));
		if (turn == 0)
			indicate.setPosition(990, 410);
		else
			indicate.setPosition(990, 110);

		Sprite Undo;
		Undo.setTexture(undo);
		Undo.setPosition(1020, 500);
		Undo.setScale(0.08f, 0.08f);

		Sprite Redo;
		Redo.setTexture(redo);
		Redo.setPosition(1080, 500);
		Redo.setScale(0.08f, 0.08f);
		bar_Display = false;
		bar1_Display = false;

		window->clear();

     ////////////home page/////////////////
		

		if (home)
		{
			
			int c, r;
			c = sf::Mouse::getPosition(*window).x;
			r = sf::Mouse::getPosition(*window).y;

			if (r > 307 && r <= 326 && c >= 200 && c <= 350)
			{

				bar_Display = true;

				bar.setPosition(190, 300);
			}
			else if (r > 256 && r <= 277 && c >= 200 && c <= 344)
			{

				bar1_Display = true;

				bar1.setPosition(190, 250);
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			
			if (!l)
				bar1.setSize(sf::Vector2f(204.f, 40.f));
			window->draw(homeSprite);
			if (bar_Display == true)
			{
				window->draw(bar);


			}
			if (bar1_Display == true)
			{
				window->draw(bar1);
			}
			if (g)
				window->draw(tx);
			else
				window->draw(simple);
			if (l)
				window->draw(text1);
			else
				window->draw(timeb);
		}

		////////////////////////
		//Renderring area
		
		
		else {
			window->draw(backgroundSprite);
			this->window->draw(p1);
			this->window->draw(p2);
			window->draw(wking);
			window->draw(bking);
			window->draw(indicate);
			window->draw(Undo);
			window->draw(Redo);
			
			drawBoard(*window, rows, cols, boxSize, shift_X, shift_Y);
			if (isCheck)
			{
				sf::Text checkMessage;
				checkMessage.setFont(game_font);
				checkMessage.setString("Check");
				checkMessage.setPosition(1050, 300);
				window->draw(checkMessage);
				Position kingPos = B->findKing(turn);
				sf::RectangleShape redBox(Vector2f(boxSize, boxSize));
				redBox.setFillColor(Color(255, 0, 0));
				redBox.setPosition(kingPos.cpos * boxSize + shift_X, kingPos.rpos * boxSize + shift_Y);
				window->draw(redBox);
				if (turn == 0)
				{
					Sprite whiteP(wking);
					whiteP.setPosition(1110, 300);
					window->draw(whiteP);

				}
				else
				{
					Sprite blackP(bking);
					blackP.setPosition(1110, 300);
					window->draw(blackP);

				}
				


			}
			
			B->printBoard(*window, boxSize, shift_X, shift_Y);
			if (isCheckMate)
			{

				sf::Text checkmateMessage;
				checkmateMessage.setFont(game_font);
				checkmateMessage.setString("Checkmate");
				checkmateMessage.setPosition(600, 300);
				checkmateMessage.scale(1, 1.5);
				checkmateMessage.setFillColor(Color(255, 0, 0));
				window->draw(checkmateMessage);
				if (turn == 0)
				{

					Sprite blackP(bking);
					blackP.setPosition(1030, 300);
					window->draw(blackP);
					sf::Text checkMessage;
					checkMessage.setFont(game_font);
					checkMessage.setString("wins");
					checkMessage.setPosition(1060, 300);
					window->draw(checkMessage);


				}
				else
				{
					Sprite blackP(wking);
					blackP.setPosition(1030, 300);
					window->draw(blackP);
					sf::Text checkMessage;
					checkMessage.setFont(game_font);
					checkMessage.setString("wins");
					checkMessage.setPosition(1060, 300);
					window->draw(checkMessage);


				}
			}
			else if (isStaleMate)
			{
				sf::Text checkmateMessage;
				checkmateMessage.setFont(game_font);
				checkmateMessage.setString("stalemate");
				checkmateMessage.setPosition(600, 300);
				checkmateMessage.scale(1, 1.5);
				checkmateMessage.setFillColor(Color(255, 0, 0));
				window->draw(checkmateMessage);
				sf::Text checkMessage;
				checkMessage.setFont(game_font);
				checkMessage.setString("DRAW");
				checkMessage.setPosition(1060, 300);
				window->draw(checkMessage);
			}
			if (timer)
			{
				if (turn == 0)
				{
					int diff = 0;
					int end = time(0);
					diff = end - startTime;
					int display = 30 - diff;
					if (display > 0)
					{
						this->p2Time = 30;
						if (display < 10) {
							clock2.setString("0" + std::to_string(display));
						}
						else 
							clock2.setString(std::to_string(display));
						clock1.setString(std::to_string(this->p2Time));
					}
					else 
					{
						gameOver = true;
						clock2.setString("00");
						sf::Text checkmateMessage;
						checkmateMessage.setFont(game_font);
						checkmateMessage.setString("gameover");
						checkmateMessage.setPosition(600, 300);
						checkmateMessage.scale(1, 1.5);
						checkmateMessage.setFillColor(Color(255, 0, 0));
						window->draw(checkmateMessage);
						if (turn == 0)
						{

							Sprite blackP(bking);
							blackP.setPosition(1030, 300);
							window->draw(blackP);
							sf::Text checkMessage;
							checkMessage.setFont(game_font);
							checkMessage.setString("wins");
							checkMessage.setPosition(1060, 300);
							window->draw(checkMessage);


						}
						else
						{
							Sprite blackP(wking);
							blackP.setPosition(1030, 300);
							window->draw(blackP);
							sf::Text checkMessage;
							checkMessage.setFont(game_font);
							checkMessage.setString("wins");
							checkMessage.setPosition(1060, 300);
							window->draw(checkMessage);


						}
					}
				}
				if (turn == 1)
				{
					int end = time(0);
					int diff = 0;
					diff = end - startTime;
					int display = 30 - diff;
					if (display > 0)
					{


						this->p1Time = 30;
						if (display < 10) {
							clock1.setString("0" + std::to_string(display));
						}
						else
							clock1.setString(std::to_string(display));
						clock2.setString(std::to_string(p1Time));
						
					}
					else
					{
						gameOver = true;
						clock1.setString("00");
						sf::Text checkmateMessage;
						checkmateMessage.setFont(game_font);
						checkmateMessage.setString("gameover");
						checkmateMessage.setPosition(600, 300);
						checkmateMessage.scale(1, 1.5);
						checkmateMessage.setFillColor(Color(255, 0, 0));
						window->draw(checkmateMessage);
						if (turn == 0)
						{

							Sprite blackP(bking);
							blackP.setPosition(1030, 300);
							window->draw(blackP);
							sf::Text checkMessage;
							checkMessage.setFont(game_font);
							checkMessage.setString("wins");
							checkMessage.setPosition(1060, 300);
							window->draw(checkMessage);


						}
						else
						{
							Sprite blackP(wking);
							blackP.setPosition(1030, 300);
							window->draw(blackP);
							sf::Text checkMessage;
							checkMessage.setFont(game_font);
							checkMessage.setString("wins");
							checkMessage.setPosition(1060, 300);
							window->draw(checkMessage);


						}
					}
				}

			}
			if (timer)
			{
				window->draw(clock1);
				window->draw(clock2);
			}
			if (renderHiglight)
			{
				Highlight(*window, rows, boxSize, boxSize, Map, shift_X, shift_Y);
				this->selectDest = true;
			}
		}
			window->display();
			
			



			if (bar1_Display || bar_Display&&home)
			{

				Sound moveS;
				moveS.setVolume(20.0f);
				moveS.setBuffer(moveBuff);
				moveS.play(); // play the sound
				while (moveS.getStatus() == Sound::Playing) // wait until the sound has finished playing
				{
					// do nothing
				}
				moveS.stop(); // stop the sound

			}

			if (isCheck&&play)
			{
				SoundBuffer checkbuff;
				if (!checkbuff.loadFromFile("Audio/check.wav"))
					std::cout << "Error in opening movesound" << std::endl;
				else
				{
					Sound checkS;
					checkS.setVolume(50.0f);
					checkS.setBuffer(checkbuff);
					checkS.play(); // play the sound
					while (checkS.getStatus() == Sound::Playing) // wait until the sound has finished playing
					{
						// do nothing
					}
					checkS.stop(); // stop the sound
					play = false;
				}
			}
			if (isCheckMate && playCheckmate)
			{
				SoundBuffer checkbuff;
				if (!checkbuff.loadFromFile("Audio/checkmate.wav"))
					std::cout << "Error in opening movesound" << std::endl;
				else
				{
					Sound checkS;
					checkS.setVolume(50.0f);
					checkS.setBuffer(checkbuff);
					checkS.play(); // play the sound
					while (checkS.getStatus() == Sound::Playing) // wait until the sound has finished playing
					{
						// do nothing
					}
					checkS.stop(); // stop the sound
					playCheckmate = false;
				}
			}
			if (isStaleMate && playStalemate)
			{
				SoundBuffer checkbuff;
				if (!checkbuff.loadFromFile("Audio/stalemate.wav"))
					std::cout << "Error in opening movesound" << std::endl;
				else
				{
					Sound checkS;
					checkS.setVolume(50.0f);
					checkS.setBuffer(checkbuff);
					checkS.play(); // play the sound
					while (checkS.getStatus() == Sound::Playing) // wait until the sound has finished playing
					{
						// do nothing
					}
					checkS.stop(); // stop the sound
					playStalemate = false;
				}
			}
			if (gameOver&& gameoverplay)
			{
				SoundBuffer checkbuff;
				if (!checkbuff.loadFromFile("Audio/gameover.wav"))
					std::cout << "Error in opening movesound" << std::endl;
				else
				{
					Sound checkS;
					checkS.setVolume(50.0f);
					checkS.setBuffer(checkbuff);
					checkS.play(); // play the sound
					while (checkS.getStatus() == Sound::Playing) // wait until the sound has finished playing
					{
						// do nothing
					}
					checkS.stop(); // stop the sound
					gameoverplay = false;
				}
			}
		
		//////////////////////////

	}
}

void Chess:: action()
{

	// castling
	B->getPiece(sourcePos)->move(destPos);
	if (B->enableCastling)
	{
		Position RookSource, RooKDest;
		RookSource.rpos = sourcePos.rpos;
		RookSource.cpos = destPos.cpos + 1;

		if (B->getPiece(RookSource) != nullptr && B->getPiece(RookSource)->getType() == ROOK)
		{
			RooKDest.rpos = destPos.rpos;
			RooKDest.cpos = destPos.cpos - 1;
			B->movePiece(RookSource, RooKDest);
		}
		RookSource.rpos = sourcePos.rpos;
		RookSource.cpos = destPos.cpos - 2;
		if (B->getPiece(RookSource) != nullptr && B->getPiece(RookSource)->getType() == ROOK)
		{
			RooKDest.rpos = destPos.rpos;
			RooKDest.cpos = destPos.cpos + 1;
			B->movePiece(RookSource, RooKDest);

		}
		B->enableCastling = false;
	}

	B->movePiece(sourcePos, destPos);
	SoundBuffer moveBuff;
	if (!moveBuff.loadFromFile("Audio/move.wav"))
		std::cout << "Error in opening movesound" << std::endl;
	else
	{
		Sound moveS;
		moveS.setVolume(20.0f);
		moveS.setBuffer(moveBuff);
		moveS.play(); // play the sound
		while (moveS.getStatus() == Sound::Playing) // wait until the sound has finished playing
		{
			// do nothing
		}
		moveS.stop(); // stop the sound
	}


	*Copy = *B;
	if (isPromotion(destPos))
		promotion(destPos);

	
	if (B->check(turn))
	{
		if (B->checkmate(turn))
		{
			isCheckMate = true;
		}
		else
			isCheck = true;
	}
	else if (B->stalemate(turn))
	{
		isStaleMate = true;
	}
	else {
		isCheckMate = false;
		isCheck = false;
		isStaleMate = false;
	}
	B->changeTurn(turn);

}
bool Chess::inRange(int x, int y)
{
	return (x >= 0+shift_X && x <= rows*boxSize+shift_X) && (y >= 0+shift_Y && y <= cols*boxSize+shift_X);
				
}
void Chess::write(ChessGameState last)
{
	ofstream write("load.txt");
	write << last.player1.getName() << endl;
	write << last.player2.getName() << endl;
	write << last.turn << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Position p(i, j);
			Piece* print = B->getPiece(p);
			if (print == nullptr)
				write << "-";
			else {
				switch (print->getType())
				{
				case PAWN:
					if (print->getColor() == Black)
						write << "p";
					else
						write << "P";
					break;
				case KING:
					if (print->getColor() == Black)
						write << "k";
					else
						write << "K";
					break;
				case QUEEN:
					if (print->getColor() == Black)
						write << "q";
					else
						write << "Q";
					break;
				case ROOK:
					if (print->getColor() == Black)
						write << "r";
					else
						write << "R";
					break;
				case KNIGHT:
					if (print->getColor() == Black)
						write << "n";
					else
						write << "N";
					break;
				case BISHOP:
					if (print->getColor() == Black)
						write << "b";
					else
						write << "B";
					break;
				default:
					write << "-";
					break;
				}
			}
		}
		write << endl;
	}
	write << last.isCheck << " " << last.isCheckMate << " " << last.isStaleMate << " " << last.enableCastling<<" "<<timer;

}
void Chess::load()
{

	ifstream read("load.txt");
	if (!read.is_open())
	{
		cout << "File not found!" << endl;
		return;
	}

	string p1name, p2name;
	int turn;
	getline(read, p1name);
	getline(read, p2name);
	getline(read, p2name);

	read >> turn;
	players[0]->SetName(p1name);
	players[1]->SetName(p2name);

	B->clearBoard();
	// read the board state from the file
	B->load(read);

	read >> this->isCheck >> isCheckMate >> isStaleMate >> B->enableCastling>>timer;

	// restore the game state

	this->turn = turn;
	this->sourcePos = Position(0, 0);
	this->destPos = Position(0, 0);

}



