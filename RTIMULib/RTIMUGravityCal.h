#ifndef _RTIMUGRAVITYCAL_H
#define	_RTIMUGRAVITYCAL_H

#include "RTFusion.h"
#include <vector>
using namespace std;

class RTIMUGravityCal
{
public:
    RTIMUGravityCal();
    ~RTIMUGravityCal();

    void newIMUData(RTIMU_DATA& data, const RTIMUSettings *settings);
	void reset();

    //--getAccel() gets the G sensor value
	RTVector3 getAccel();

	//--getGravity() gets G sensor magnitude
	double  getGsense();
    
protected:
    bool m_firsttime;                                  // first time execute flag
    RTQuaternion m_gravity;                            // gravity Quaternion
    RTVector3 m_accel;                                 // get the acceleration
	vector<double> Gstastic;

};

#endif // _RTIMUGRAVITYCAL_H
