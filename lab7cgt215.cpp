// Lab_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 200));
	ball.setRadius(20);
	ball.setVelocity(Vector2f(-0.5, 0.7));
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Left Wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 560));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	// Right Wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 560));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	// Obstacle
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(80, 80));
	obstacle.setCenter(Vector2f(400, 350));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	int thudCount(0);
	// Thud Count for Floor
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Thud Count for Ceiling
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Thud Count for Left Wall
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Thud Count for Right Wall
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	int bangCount(0);
	// Bang Count for Obstacle
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;

		int strikeCount = 3;
		if (bangCount >= strikeCount) {
			cout << "Game Over! Ball hit the obstacle three times." << endl;
			exit(0);
		}
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(obstacle);
		window.display();
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file