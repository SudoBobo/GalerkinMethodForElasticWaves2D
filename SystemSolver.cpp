#include "SystemSolver.h"

SystemSolver::SystemSolver()
{

}

void SystemSolver::setSystemMaker(shared_ptr<SystemMaker> systemMaker)
{
	this->systemMaker = systemMaker;
}

void SystemSolver::setTimeStep(double timeStep)
{
	this->timeStep = timeStep;
}

void SystemSolver::solveOneTriangle(Triangle & origTriangle, Triangle & newTriangle)
{
	static matrix<double> U;
	//не по ссылке ли передаётся?
	U = origTriangle.getU();
	// Euler method
	 // this->getTimeStep() * this->systemMaker.dU();
	newTriangle.setU(U);
}
