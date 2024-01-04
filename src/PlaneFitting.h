#ifndef SeegetXR_PlaneFitting
#define SeegetXR_PlaneFitting

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    bool PlaneFitting(const float* points_input, int length, float threash, int maxIterations, float* Return);
    int add(int a, int b);
    int sub(int a, int b);

#ifdef __cplusplus
}
#endif

#endif