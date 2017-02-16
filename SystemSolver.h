#ifndef SYSTEMSOLVER_H
#define SYSTEMSOLVER_H

#include <memory>
using std::shared_ptr;

#include "SystemMaker.h"

class SystemSolver
{
public:
	SystemSolver();
	void setSystemMaker(shared_ptr<SystemMaker> systemMaker);
	void setTimeStep (double timeStep);
	void solveOneTriangle (Triangle & origTriangle, Triangle & newTriangle);
private:
	shared_ptr <SystemMaker> systemMaker;
	double timeStep;
};

#endif // SYSTEMSOLVER_H
