#include "Boid.h"
#include "Flock.h"
#include "game.h"

using namespace std;

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize()
{
	return flock.size();
}

Boid* Flock::getBoid(int i)
{
	return &flock[i];
}

void Flock::addBoid(Boid b)
{
	flock.push_back(b);
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].run(flock);
	}
}

// Runs the swarm function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::swarming()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].swarm(flock);
	}
}

//Runs the formation algorithm which updates the positions based on the position of the leader and 
//relative position in the formation pattern of the other NPCs.
void Flock::cFormation(int fLeader)
{
	float pi = 3.141592653589793;
	int fSize = flock.size();
	for (int i = 0; i < fSize; i++)
	{
		Pvector	sub(0, 0);
		Pvector sum(0, 0);
		int npcRadius = 10;
		int closeEnough = 10;
		float angleAroundCircle = 0.0;
		Pvector targetSlot(0, 0);
		Boid target = flock[fLeader]; // Our designated leader

		if (i == fLeader) {		//Deal with our leader here
			// Any changes to velocity will be done in the steering function
			flock[i].update("cFormation");
			flock[i].borders();
		}
		else {    //Find our position in the circle
			angleAroundCircle = (float)i / (fSize - 1);
			angleAroundCircle = angleAroundCircle * pi * 2;
			float radius = npcRadius / sin(pi / (fSize));

			targetSlot = target.location;
			targetSlot.x = targetSlot.x + radius * cos(angleAroundCircle);
			targetSlot.y = targetSlot.y + radius * sin(angleAroundCircle);
			sub = sub.subTwoVector(targetSlot, flock[i].location);
			float D = sub.magnitude();
			if (D > closeEnough)	// Are we close enough to our slot position, if so just match the leader's velocity.
			{
//				std::cout << "NOT close enough" << std::endl;
				sum = sub;
				sum.normalize();
				sum.mulScalar(flock[i].maxSpeed);
				flock[i].applyForce(sum);
				flock[i].update("cFormation");
				flock[i].borders();
			}
			else 
			{
				flock[i].velocity = flock[fLeader].velocity; //Match the leader's velocity if we are close enough
				flock[i].borders();
				//				std::cout << "Close enough" << flock[fLeader].velocity.magnitude() << std::endl;
			}
		}
	}
}

void Flock::dFormation(int fLeader)
{
	if (flock.size() > 0)
	{
		int pointCount = 4;
		int fSize = flock.size();
		float droidPerSide = std::ceil((flock.size() - 5.0f) / 4.0f);
		float lengthOfLine = std::ceil((droidPerSide * 3) + (fSize * 0.5f));
		float distanceFromLeader = sqrt((lengthOfLine * lengthOfLine) / 2);
		Boid target = flock[fLeader]; // Our designated leader

		Pvector points[4] = { {target.location.x + distanceFromLeader, target.location.y} , {target.location.x, target.location.y + distanceFromLeader},
			{target.location.x - distanceFromLeader, target.location.y},{target.location.x, target.location.y - distanceFromLeader} };

		int closeEnough = 10;

		for (int i = 0; i < fSize; i++)
		{
			Pvector targetSlot(0, 0);
			Pvector	sub(0, 0);
			Pvector sum(0, 0);

			targetSlot = { 500,500 };
			int lineCount = 0;
			Pvector line;
			if(i <= pointCount && i != fLeader)
			{
				targetSlot = points[i - 1];
			}
			else if(i != fLeader)
			{
				for (int i = 0; i < pointCount; i++)
				{
					if (i != pointCount - 1)
					{
						line.x = points[i + 1].x - points[i].x;
						line.y = points[i + 1].y - points[i].y;
					}
					else
					{
						line.x = points[0].x - points[i].x;
						line.y = points[0].y - points[i].y;
					}

					Pvector norm = line;
					norm.normalize();
					targetSlot.x = points[i].x + (line.x * norm.x);
					targetSlot.y = points[i].y + (line.y * norm.y);
				}
			}

			flock[i].location = targetSlot;


			//sub = sub.subTwoVector(targetSlot, flock[i].location);
			//float D = sub.magnitude();
			//if (D > closeEnough)	// Are we close enough to our slot position, if so just match the leader's velocity.
			//{
			//	//				std::cout << "NOT close enough" << std::endl;
			//	sum = sub;
			//	sum.normalize();
			//	sum.mulScalar(flock[i].maxSpeed);
			//	flock[i].applyForce(sum);
			//	flock[i].update("cFormation");
			//	flock[i].borders();
			//}
			//else
			//{
			//	flock[i].velocity = flock[fLeader].velocity; //Match the leader's velocity if we are close enough
			//	flock[i].borders();
			//	//				std::cout << "Close enough" << flock[fLeader].velocity.magnitude() << std::endl;
			//}
		}
	}
}