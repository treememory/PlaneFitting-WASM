#include "PlaneFitting.h"
#include <iostream>
#include "GRANSAC.hpp"
#include "PlaneModel.hpp"
#include <chrono>
#include <random>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#ifdef __cplusplus
extern "C"
{
#endif


    EMSCRIPTEN_KEEPALIVE int add(int a, int b)
    {
        return a + b;
    }
    EMSCRIPTEN_KEEPALIVE int sub(int a, int b)
    {
        return a - b;
    }

EMSCRIPTEN_KEEPALIVE bool PlaneFitting(const float* points_input, int length, float threash, int maxIterations, float* Return)
{
    // int length = 0;
    // float* points_input = nullptr;
    // float threash = 0.1;
    // int maxIterations = 0;
    // float Return[] = {0.f,0.f,0.f,0.f,0.f,0.f}; 
    if(length%3!=0) {
        std::cout << "PlaneFitting: input point length err = " << length << std::endl;
        return false;
    }
	int Num = length/3;
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter> > CandPoints;
	CandPoints.resize(Num);
	for (int i = 0; i <Num; ++i)
	{
		Vector3VP p = {points_input[3*i], points_input[3*i+1], points_input[3*i+2]};
		std::shared_ptr<GRANSAC::AbstractParameter> CandPt = std::make_shared<Point3D>(p[0], p[1],p[2]);
		CandPoints[i]=CandPt;
	}
	
	GRANSAC::RANSAC<PlaneModel, 3> Estimator;
    Estimator.Initialize(threash, maxIterations); // Threshold, iterations

    auto start = std::chrono::high_resolution_clock::now();
	Estimator.Estimate(CandPoints);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "RANSAC took: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms." << std::endl;
	
	auto BestPlane = Estimator.GetBestModel();
	if (BestPlane == nullptr)
	{
        Return[0] = Return[1] = Return[2] = Return[3] = Return[4] = Return[5] = 0;
		return false;
	}
    
    float nx = BestPlane->m_PlaneCoefs[0];
    float ny = BestPlane->m_PlaneCoefs[1];
    float nz = BestPlane->m_PlaneCoefs[2];
    float norm = sqrt(nx*nx + ny*ny + nz*nz);
    if(norm < 1e-5){
        std::cout << "PlaneFitting: norm(sqrt(nx*nx+ny*ny+nz*nz)) is too small = " << norm << std::endl;
        Return[0] = Return[1] = Return[2] = Return[3] = Return[4] = Return[5] = 0;
		return false;
    }

    Return[0] = BestPlane->m_PointCenter[0];
    Return[1] = BestPlane->m_PointCenter[1];
    Return[2] = BestPlane->m_PointCenter[2];
    Return[3] = nx/norm;
    Return[4] = ny/norm;
    Return[5] = nz/norm;
    
	return true;
}

#ifdef __cplusplus
}
#endif