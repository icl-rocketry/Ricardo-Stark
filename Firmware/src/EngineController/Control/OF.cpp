#include "OF.h"
#include "EngineController/StateMachine/Controlled.h"


OF::OF(EngineController& Engine):
_engine(Engine),
m_CstarTable({0.1,0.22041,0.34082,0.46122,0.58163,0.70204,
        0.82245,0.94286,1.0633,1.1837,1.3041,1.4245,1.5449,1.6653,
        1.7857,1.9061,2.0265,2.1469,2.2673,2.3878,2.5082,2.6286,
        2.749,2.8694,2.9898,3.1102,3.2306,3.351,3.4714,3.5918,
        3.7122,3.8327,3.9531,4.0735,4.1939,4.3143,4.4347,4.5551,
        4.6755,4.7959,4.9163,5.0367,5.1571,5.2776,5.398,5.5184,
        5.6388,5.7592,5.8796,6.0},{892.7,950.82,995.01,1029.1,
        1056.1,1078.2,1096.9,1113.2,1128.0,1141.7,1154.8,1167.7
        ,1176.2,1212.7,1259.9,1300.9,1336.3,1367.2,1394.4,1418.5
        ,1440.0,1459.2,1476.3,1491.5,1505.0,1516.8,1527.3,1536.3
        ,1544.0,1550.6,1556.0,1560.4,1563.8,1566.2,1567.7,1568.5
        ,1568.6,1568.1,1567.2,1565.8,1564.1,1562.1,1559.9,1557.6
        ,1555.2,1552.6,1550.0,1547.3,1544.6,1541.9}) //OF C to C* LUT
{};   


void OF::setup(){

    setupPts();

    _currPc = _engine._sensorHandler.getPressure(SensorID::ChamberPt);
    _WarmFuelInjP = _engine._sensorHandler.getPressure(SensorID::WarmFuelInjPt);

    m_currOF = m_startOF;

}

void OF::update(){

    updateOF();

}

void OF::setupPts(){

    

}

void OF::updateOF(){


    for (int i=0; i < N; i++){

        

        m_mdotTotal = m_throatA*_currPc/ m_CstarTable.get(m_startOF);
        m_mdotFuel = m_CdaFuel*sqrt(2*m_fuelrho*(_WarmFuelInjP-_currPc));
        m_mdotOx = m_mdotTotal-m_mdotFuel;

        m_loopOF = m_mdotOx/m_mdotFuel;

    }

    m_currOF = m_loopOF;


}

