#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H

#include <SystemMaker.h>
#include <SystemSolver.h>
#include <TriangleMesh.h>

#include <memory>
using std::shared_ptr;

class ProblemSolver
{
public:
	// may be lot of mistakes because all the classes below don't have
	// copy constructors
	ProblemSolver(shared_ptr<SystemMaker> systemMaker,
				  shared_ptr<SystemSolver> systemSolver);
	void solve(double realFullTime, double timeStep,
			   shared_ptr<TriangleMesh> initialMesh);
	void solveOneStep(shared_ptr <TriangleMesh> currentState,
					  shared_ptr <TriangleMesh> nextState);
	void writeOneStep(shared_ptr <TriangleMesh> triangleMesh,
									 int numberOfStep);
private:
	shared_ptr<SystemMaker>  systemMaker;
	shared_ptr<SystemSolver> systemSolver;
};

#endif // PROBLEMSOLVER_H
