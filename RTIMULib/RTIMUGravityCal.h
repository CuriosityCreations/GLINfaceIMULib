#ifndef _RTIMUGRAVITYCAL_H
#define	_RTIMUGRAVITYCAL_H

#include "RTFusion.h"
#include <vector>
using namespace std;

class RTIMUGravityCal
{
public:
    //--get original fusion acceleration value
	RTVector3 getFusionAccel() {return m_fusion->getAccel();}

	//--get Gravity
	double GetGravity() {return m_fusion->getGsense();}

    //--gravity quaternion
	void setGravityQuaternion();

    //--getAccelResiduals() gets the residual after subtracting gravity
    RTVector3 getAccelResiduals();

    RTVector3 WorldAccelResiduals();

protected:
	RTFusion *m_fusion;                                  // the fusion algorithm
    RTQuaternion m_gravity;                              // gravity Quaternion
    RTVector3 m_accel;                                   //
	vector<double> Gstastic;

};

#endif // _RTIMUGRAVITYCAL_H
