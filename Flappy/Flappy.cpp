#include <iostream>
#include <SFML/Graphics.hpp> // Header File for GUI
#include <SFML/Audio.hpp> // For Handeling Audio
#include <SFML/Window/Keyboard.hpp> // For Handeling Keyboard
#include <fstream> // For File Handeling
#include <string>
using namespace std;
using namespace sf; // For not writing sf:: every time



// Resolution 
const int ResolutionX = 600;
const int ResolutionY = 700;



// Grounds Y-axis position
int groundY = 580;



// Grounds X-Axis
int groundx = 0;
int ground2x = 600;



// Ground Moving Speed
const float groundSpeed = 1;



// Player x,y Position
const int x = 0;
const int y = 1;



// Gravity Acting on Bird
float Gravity = 5.0;



// All Pipe Sets Y-Axis
float AllPipeY = 300;



// All  Pipe Sets x-axis initial Position
float pipe_x_axis[3] = { 620,920,1220 };



// Pipes Distance
float PipeDist = 150;



// Hit Enter to Run Game
bool run = false;
bool collide = false; // For Collision
bool gameOver = false;// For Game Over Sprite



// Function Declerations or ProtoTypes

void moveGrounds(Sprite& g1, Sprite& g2);// Function That Moves Grounds


void moveUpBird(float player[]);// Function that moves player Up


void movePipes(Sprite& p1, Sprite& p1d, Sprite& p2, Sprite& p2d, Sprite& p3, Sprite& p3d, float x_axis[]);// Moving Pipes


int randomHeightGenerator();// To Generate Random Height of Pipes


bool collisionWithPipes(Sprite& p1, Sprite& p1d, Sprite& p2, Sprite& p2d, Sprite& p3, Sprite& p3d, Sprite& player);// To check Collision with Pipes



int main()
{


	// Creating Window
	RenderWindow window(VideoMode(ResolutionX, ResolutionY), "Project 1st Sem");
	window.setFramerateLimit(50);   // Setting Frames Per Seconds



	// Setting Background
	Texture Background;
	Background.loadFromFile("assets/bg.png");
	Sprite BackgroundSprite;
	BackgroundSprite.setTexture(Background);
	BackgroundSprite.scale(1.5, 1); // Scaling Background to fit it on Window



	// Setting Ground1
	Texture Ground;
	Ground.loadFromFile("assets/ground.png");
	Sprite GroundSprite;
	GroundSprite.setTexture(Ground);
	GroundSprite.scale(1.5, 1); // Scaling to make it fit on x-axis of Window
	GroundSprite.setPosition(0, groundY); // Setting position on x-axis = 0 and y-axis = 600



	// Setting Ground2
	Texture Ground2;
	Ground2.loadFromFile("assets/ground.png");
	Sprite GroundSprite2;
	GroundSprite2.setTexture(Ground2);
	GroundSprite2.scale(1.5, 1); // Scaling to make it fit on x-axis of Window
	GroundSprite2.setPosition(ground2x, groundY); // Setting position on x-axis = 0 and y-axis = 600



	// Setting Player
	Texture PlayerTexture;
	PlayerTexture.loadFromFile("assets/birdup.png");
	Sprite PlayerSprite;
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.scale(1.2, 1.2); // Scaling Bird to make its look a bit Bigger
	float player[2];
	player[x] = 70;
	player[y] = 70;
	PlayerSprite.setPosition(player[x], player[y]);// Setting Position
	int animCount = 0;



	// Pipes Set1
	int randomHeight1 = randomHeightGenerator();
	Texture pipe1;
	pipe1.loadFromFile("assets/pipedown.png");
	Sprite spritepipe1;
	spritepipe1.setTexture(pipe1);
	spritepipe1.setPosition(pipe_x_axis[0], randomHeight1);

	Texture pipe1down;  // Down means lower pipe
	pipe1down.loadFromFile("assets/pipe.png");
	Sprite spritepipe1down;
	spritepipe1down.setTexture(pipe1down);
	spritepipe1down.setPosition(pipe_x_axis[0], randomHeight1 + PipeDist + AllPipeY);



	// Pipes Set2
	int randomHeight2 = randomHeightGenerator();
	Sprite spritepipe2;
	spritepipe2.setTexture(pipe1);
	spritepipe2.setPosition(pipe_x_axis[1], randomHeight2);

	Sprite spritepipe2down; // Downs means lower
	spritepipe2down.setTexture(pipe1down);
	spritepipe2down.setPosition(pipe_x_axis[1], randomHeight2 + PipeDist + AllPipeY);



	// Pipes Set3
	int randomHeight3 = randomHeightGenerator();
	Sprite spritepipe3;
	spritepipe3.setTexture(pipe1);
	spritepipe3.setPosition(pipe_x_axis[2], randomHeight3);

	Sprite spritepipe3down; // Downs means lower
	spritepipe3down.setTexture(pipe1down);
	spritepipe3down.setPosition(pipe_x_axis[2], randomHeight3 + PipeDist + AllPipeY);



	// Game Over Sprite
	Texture Gover;
	Gover.loadFromFile("assets/gameover.png");
	Sprite GameoverSprite;
	GameoverSprite.setTexture(Gover);
	GameoverSprite.setPosition(175, 450);
	GameoverSprite.scale(1.3, 1.3);



	// Start Game Mssg
	Texture startMssg;
	startMssg.loadFromFile("assets/message.png");
	Sprite mssgSprite;
	mssgSprite.setTexture(startMssg);
	mssgSprite.scale(2, 2);
	mssgSprite.setPosition(110, 100);



	// Texts
	


	// Hit enter to Start
	Font Arialfont;
	Arialfont.loadFromFile("assets/arial.ttf");
	Text Txt;
	Txt.setString(" Hit Enter to Start!\nHold space to Flap");
	Txt.setFont(Arialfont);
	Txt.setFillColor(sf::Color::White);
	Txt.setPosition(205, 530);
	Txt.scale(0.7, 0.7);



	// Hit enter to restart
	Text restartTxt;
	restartTxt.setString("Hit Enter to Restart!");
	restartTxt.setFont(Arialfont);
	restartTxt.setFillColor(sf::Color::White);
	restartTxt.setPosition(205, 530);
	restartTxt.scale(0.7, 0.7);



	// Scores and High Score
	scores scoreCount = { 0,0 };



	// Audios

	// Flap Sound
	Music flapSound;
	flapSound.openFromFile("assets/sfx/flap.wav");



	// Game Loop
	while (window.isOpen())
	{



		// Display Window
		window.display();



		// Drawing Background
		window.draw(BackgroundSprite);



		// Drawing Pipes
		window.draw(spritepipe1);
		window.draw(spritepipe1down);
		window.draw(spritepipe2);
		window.draw(spritepipe2down);
		window.draw(spritepipe3);
		window.draw(spritepipe3down);



		// Drawing Ground
		window.draw(GroundSprite);
		window.draw(GroundSprite2);



		// Drawing Bird
		window.draw(PlayerSprite);



		// Hit Enter to Run Game
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			run = true;
		}



		// Start Game
		if (run == true)
		{



			// Moving Ground
			moveGrounds(GroundSprite, GroundSprite2);



			// Moving Pipes
			movePipes(spritepipe1, spritepipe1down, spritepipe2, spritepipe2down, spritepipe3, spritepipe3down, pipe_x_axis);



			// Flapping Wings
			animCount++;
			if (animCount == 8)
			{
				PlayerTexture.loadFromFile("assets/birddown.png");
				animCount = 0;
			}
			else
			{
				PlayerTexture.loadFromFile("assets/birdup.png");
			}



			// Gravity Acting on Bird

			if (player[y] <= (groundY - 35))
			{
				player[y] += Gravity;
				PlayerSprite.setPosition(player[x], player[y]);
			}



			// Moving Bird Up on Pressing Space Bar
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				moveUpBird(player);
				flapSound.play();
			}



			// Collision with Pipes
			run = collisionWithPipes(spritepipe1, spritepipe1down, spritepipe2, spritepipe2down, spritepipe3, spritepipe3down, PlayerSprite);



			// Collisions
			if (player[y] >= (groundY - 30))  // Collision for Bird Hitting Ground
			{
				run = false;
				gameOver = true;
				collide = true;
			}

		}



		// If Collison Occurs for Resetting Game
		if (run == false)
		{

			// Draw Game Over
			if (gameOver == true)
			{
				window.draw(GameoverSprite);
				window.draw(restartTxt);
			}


			// Resetting Player Position
			player[x] = 70;
			player[y] = 70;


			// Resetting Ground Position
			groundx = 0;
			ground2x = 0;


			// Resetting Pipes Position
			pipe_x_axis[0] = 620;
			pipe_x_axis[1] = 920;
			pipe_x_axis[2] = 1220;

		}



		// Event to Close Window
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close(); // Close Window
			}
		}



		// Drawing Startup Mssg
		if (run == false && collide == false)
		{
			window.draw(mssgSprite);
			PlayerSprite.setPosition(-20, -30);
			window.draw(Txt);
		}


	}

}


// Function Definations


// Moving Grounds
void moveGrounds(Sprite& g1, Sprite& g2)
{
	g1.setPosition(groundx -= groundSpeed, groundY);
	g2.setPosition(ground2x -= groundSpeed, groundY);

	if (ground2x <= 0)
	{
		groundx = 0;
		ground2x = 600;
	}
}


// Moving Player Up
void moveUpBird(float player[])
{
	if (player[y] > 10)
	{
		player[y] -= (Gravity * 2);
	}
}


// For moving Pipes
void movePipes(Sprite& p1, Sprite& p1d, Sprite& p2, Sprite& p2d, Sprite& p3, Sprite& p3d, float x_axis[])
{


	p1.setPosition(x_axis[0] -= 0.5, p1.getPosition().y);
	p1d.setPosition(x_axis[0] -= 0.5, p1d.getPosition().y);
	;
	p2.setPosition(x_axis[1] -= 0.5, p2.getPosition().y);
	p2d.setPosition(x_axis[1] -= 0.5, p2d.getPosition().y);

	p3.setPosition(x_axis[2] -= 0.5, p3.getPosition().y);
	p3d.setPosition(x_axis[2] -= 0.5, p3d.getPosition().y);

	for (int i = 0; i < 3; i++)
	{
		if (x_axis[i] <= -300)
		{

			x_axis[i] = 620;
			int randH = randomHeightGenerator();
			int height = randH + PipeDist + AllPipeY;

			if (i == 0)
			{
				p1.setPosition(x_axis[i] -= 0.5, randH);
				p1d.setPosition(x_axis[i] -= 0.5, height);
			}
			else if (i == 1)
			{
				p2.setPosition(x_axis[i] -= 0.5, randH);
				p2d.setPosition(x_axis[i] -= 0.5, height);
			}
			else
			{
				p3.setPosition(x_axis[i] -= 0.5, randH);
				p3d.setPosition(x_axis[i] -= 0.5, height);
			}
		}
	}
}


// For Generating Random Height
int randomHeightGenerator()
{
	return rand() % 200 - 200; // Generates Random Number Between -200 - 0
}


// For Collision Detection With Pipes
bool collisionWithPipes(Sprite& p1, Sprite& p1d, Sprite& p2, Sprite& p2d, Sprite& p3, Sprite& p3d, Sprite& player)
{
	if (p1.getGlobalBounds().intersects(player.getGlobalBounds()) || p1d.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		gameOver = true;
		collide = true;
		return false;
	}
	else if (p2.getGlobalBounds().intersects(player.getGlobalBounds()) || p2d.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		gameOver = true;
		collide = true;
		return false;
	}
	else if (p3.getGlobalBounds().intersects(player.getGlobalBounds()) || p3d.getGlobalBounds().intersects(player.getGlobalBounds()))
	{
		gameOver = true;
		collide = true;
		return false;
	}
	else
	{
		return true;
	}
}