#include "SystemSolver.h"

using std::cout;
using std::endl;

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
	matrix<double> U;
	//не по ссылке ли передаётся?
//	U = origTriangle.getU();
	// Euler method
	 // this->getTimeStep() * this->systemMaker.dU();
	U = origTriangle.getU();
	matrix <double> dU = this->systemMaker->dU(origTriangle);
	matrix <double> dUt = dU * this->timeStep;

//	cout << U << endl;
//	cout << dU << endl;
//	cout << dUt << endl;
	U += dUt;
//	U += this->timeStep * this->systemMaker->dU(origTriangle);
	newTriangle.setU(U);
}
