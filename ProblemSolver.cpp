#include "ProblemSolver.h"
#include "RectangleMesh.h"

#include "FileWriter.h"


using std::swap;
using std::make_shared;

ProblemSolver::ProblemSolver(shared_ptr<SystemMaker> systemMaker,
							 shared_ptr<SystemSolver>systemSolver)
	: systemMaker(systemMaker), systemSolver(systemSolver)
{
	systemSolver->setSystemMaker(systemMaker);
}


void ProblemSolver::solve (double realFullTime, double timeStep,
						   shared_ptr<TriangleMesh> initialMesh, std::vector <int> gridSize)
{
	// ?
	this->gridSize = gridSize;
	systemSolver->setTimeStep(timeStep);
	const int timeSteps = realFullTime / timeStep;

	shared_ptr<TriangleMesh> currentState = initialMesh;
	// initialize with initialMesh just to make right size
	shared_ptr <TriangleMesh> nextState = make_shared<TriangleMesh>(*(initialMesh.get()));
	for (int t = 0; t < timeSteps; t++)
	{
		// using currentState data fills nexState
		this->writeOneStep(currentState, t);
		this->solveOneStep(currentState, nextState);
		swap(currentState, nextState);
	}
}

void ProblemSolver::solveOneStep(shared_ptr <TriangleMesh> currentState,
				  shared_ptr <TriangleMesh> nextState)
{
		int maxNumberOfTriangle = currentState->getMesh().size();
		for (int numberOfTriangle = 0; numberOfTriangle < maxNumberOfTriangle;
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

	FileWriter fileWriter(source, "part0_","file",
							  "/home/bobo/aData/", 6, gridSize);
	if (numberOfStep == 0)
		fileWriter.clean();
	fileWriter.write(numberOfStep);
}


