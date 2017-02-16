#include "ProblemSolver.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "Rectangle.h"
#include "RectangleMesh.h"

#include "Support.h"
#include "FileWriter.h"

#include <algorithm>

using std::swap;
using std::make_shared;

ProblemSolver::ProblemSolver(shared_ptr<SystemMaker> systemMaker,
							 shared_ptr<SystemSolver>systemSolver)
	: systemMaker(systemMaker), systemSolver(systemSolver)
{
	systemSolver->setSystemMaker(systemMaker);
}


void ProblemSolver::solve (double realFullTime, double timeStep,
						   shared_ptr<TriangleMesh> initialMesh)
{
	// ?
	systemSolver->setTimeStep(timeStep);
	const int timeSteps = realFullTime / timeStep;

	shared_ptr<TriangleMesh> currentState = initialMesh;
	// initialize with initialMesh just to make right size
	TriangleMesh nextStateMesh (*(initialMesh.get()));
	shared_ptr <TriangleMesh> nextState = make_shared<TriangleMesh>(*(initialMesh.get()));
	for (int t = 0; t < timeSteps; t++)
	{
		// using currentState data fills nexState
		this->solveOneStep(currentState, nextState);
		swap(currentState, nextState);
		this->writeOneStep(currentState, t);
	}
}

void ProblemSolver::solveOneStep(shared_ptr <TriangleMesh> currentState,
				  shared_ptr <TriangleMesh> nextState)
{
		int maxNumberOfTriangle = currentState->getMesh().size();
		for (int numberOfTriangle = 0; numberOfTriangle <= maxNumberOfTriangle;
				 numberOfTriangle++)
		{
			this->systemSolver->solveOneTriangle(currentState->getMesh()[numberOfTriangle],
							 nextState->getMesh()[numberOfTriangle]);
		}
}

void ProblemSolver::writeOneStep(shared_ptr <TriangleMesh> triangleMesh,
								 int numberOfStep)
{

	RectangleMesh rectangleMesh(*triangleMesh.get());
	SourceWrapper wrappedSource = rectangleMesh.makeSourceWrapper();
	auto source = wrappedSource.getSource();
	//remove this hardcode, please
	int xSize = 100;
	int ySize = 100;
	int xGrid = (xSize / 25) * 3;
	int yGrid = (ySize / 25) * 3;

	std::vector <int> gridSize = {xGrid, yGrid, 0};

	FileWriter fileWriter(source, "part0_","file",
							  "/home/bobo/aData/", 6, gridSize);
	static bool isFirstCall = false;
	if (isFirstCall == false)
		fileWriter.clean();
	isFirstCall = true;
	fileWriter.write(numberOfStep);
}


