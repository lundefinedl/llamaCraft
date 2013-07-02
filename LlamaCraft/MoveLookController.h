#include "pch.h"
#include "Direct3DBase.h"

using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Devices::Input;



#define ROTATION_GAIN 0.004f	// sensitivity adjustment for look controller
#define MOVEMENT_GAIN 0.1f		// sensitivity adjustment for move controller
#define M_PI 3.14596f;

class MoveLookController
{
private:

	



	
	// properties of the controller object
    DirectX::XMFLOAT3 m_position;			    // the position of the controller
    float m_pitch, m_yaw;			// orientation euler angles in radians

    // properties of the Move control
    bool m_moveInUse;			    // specifies whether the move control is in use
    uint32 m_movePointerID;		    // id of the pointer in this control
    DirectX::XMFLOAT2 m_moveFirstDown;		    // point where initial contact occurred
    DirectX::XMFLOAT2 m_movePointerPosition;   // point where the move pointer is currently located
    DirectX::XMFLOAT3 m_moveCommand;		    // the net command from the move control

    // properties of the Look control
    bool m_lookInUse;			    // specifies whether the look control is in use
    uint32 m_lookPointerID;		    // id of the pointer in this control
    DirectX::XMFLOAT2 m_lookLastPoint;		    // last point (from last frame)
    DirectX::XMFLOAT2 m_lookLastDelta;		    // for smoothing

    bool m_forward, m_back;			// states for movement
    bool m_left, m_right;
    bool m_up, m_down;


public:

    
    void OnPointerPressed(DirectX::XMFLOAT2& position,PointerDeviceType& type);

    void OnPointerMoved(DirectX::XMFLOAT2& position);

    void OnPointerReleased(DirectX::XMFLOAT2& position);

    void OnKeyDown(Windows::System::VirtualKey& Key);

    void OnKeyUp(Windows::System::VirtualKey& Key);

    // set up the Controls that this controller supports
    void Initialize();

    // accessor to set position of controller
    void SetPosition(DirectX::XMFLOAT3 pos );

    // accessor to set position of controller
    void SetOrientation(  float pitch,  float yaw );

    // returns the position of the controller object
    DirectX::XMFLOAT3 get_Position();

    // returns the point  which the controller is facing
    DirectX::XMFLOAT3 get_LookPoint();

    void Update( );

};  // class MoveLookController


