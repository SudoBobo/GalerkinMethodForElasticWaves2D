//#include "Solver.h"

//Solver::Solver(SystemMaker systemMaker, SystemSolver systemSolver)
//{
//	this->systemSolver = systemSolver;
//	systemSolver.setSystemMaker(systemMaker);
//}

//void Solver::solveAll(Mesh & mesh, double timeStep,
//						double fullTime)
//{
//	systemSolver.setTimeStep(timeStep);
//	double time;
//	const int timeSteps = fullTime / timeStep;

//	// ?
//	Mesh & origState = mesh;
//	//make mesh class
//	for (int t = 0; t <= timeSteps; t++)
//	{
//		time = (t+1) * timeStep;
//		solveOneStep(origState, time);
//	// write somehow
//	}
//}



//void Solver::solveOneStep(Mesh & mesh, double time)
//{
//	static tempMesh();
//	if(tempMesh.getGeometryId() == mesh.getGeometryId()){}
//		// позже следует заменить на изменение размеров и всего такого
//		else tempMesh = mesh;
//	for (int numberOfTriangle = 0; numberOfTriangle <= maxNumberOfTriangle;
//			 numberOfTriangle++)
//	{
//		this->systemSolver.solveOneTriangle(mesh.getTriangle(numberOfTriangle),
//						 tempMesh.getTriangle(numberOfTriangle), time);
//	}
//	mesh = tempMesh;
//	// пройтись по всем треугольникам, каждый посчитать
//}

