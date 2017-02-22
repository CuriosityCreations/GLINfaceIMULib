#ifndef _RTIMUGRAVITYCAL_H
#define	_RTIMUGRAVITYCAL_H

#include "RTFusion.h"
#include <vector>
using namespace std;

class RTIMUGravityCal
{
public:
	//--Get Gravity
	double GetGravity() {return m_fusion->getGsense();}
	RTVector3 getFusionAccel() {return m_fusion->getAccel();}
	

protected:
	RTFusion *m_fusion;                                  // the fusion algorithm
	vector<double> Gstastic;

};

#endif // _RTIMUGRAVITYCAL_H
