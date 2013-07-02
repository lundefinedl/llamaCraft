#include "pch.h"
#include "MoveLookController.h"
#include "XMFloatMath.h"

void MoveLookController::OnPointerPressed(
 DirectX::XMFLOAT2& position,PointerDeviceType& type)
{
    if ( type == PointerDeviceType::Mouse )
    {
        // Action, Jump, or Fire
    }

}

float maxt(float a, float b) {
	return (a>b) ? a :b;

}

float mint(float a, float b) {
	return (a<b) ? a : b;
}


void MoveLookController::OnPointerMoved(DirectX::XMFLOAT2& position)
{
    
         DirectX::XMFLOAT2 pointerDelta;
		 pointerDelta = XMFloatMath::subtract(position, m_lookLastPoint);		// how far did pointer move

         DirectX::XMFLOAT2 rotationDelta;
		 rotationDelta = XMFloatMath::multiply(pointerDelta,ROTATION_GAIN);	// scale for control sensitivity
        m_lookLastPoint = position;			 			// save for next time through

        // update our orientation based on the command
        m_pitch -= rotationDelta.y;						// mouse y increases down, but pitch increases up
        m_yaw   -= rotationDelta.x;						// yaw defined as CCW around y-axis

        // Limit pitch to straight up or straight down
	    m_pitch = maxt( -((3.145f)/2.0f), m_pitch );
        m_pitch = mint((3.145f/2.0f), m_pitch );
    
}

void MoveLookController::OnPointerReleased(DirectX::XMFLOAT2& position)
{
    
}

void MoveLookController::OnKeyDown(Windows::System::VirtualKey& Key)
{
    
    // figure out the command from the keyboard
    if ( Key == VirtualKey::W )		// forward
        m_forward = true;
    if ( Key == VirtualKey::S )		// back
        m_back = true;
    if ( Key == VirtualKey::A )		// left
        m_left = true;
    if ( Key == VirtualKey::D )		// right
        m_right = true;
}


void MoveLookController::OnKeyUp(Windows::System::VirtualKey& Key)
{
    
    // figure out the command from the keyboard
    if ( Key == VirtualKey::W )		// forward
        m_forward = false;
    if ( Key == VirtualKey::S )		// back
        m_back = false;
    if ( Key == VirtualKey::A )		// left
        m_left = false;
    if ( Key == VirtualKey::D )		// right
        m_right = false;
}


void MoveLookController::Initialize( )
{

  
  
    //	need to init this as it is reset every frame
    m_moveCommand = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );

    SetOrientation( 0, 0 );				// look straight ahead when the app starts

}


void MoveLookController::SetPosition(DirectX::XMFLOAT3 pos )
{
    m_position = pos;
}

// accessor to set position of controller
void MoveLookController::SetOrientation(  float pitch,  float yaw )
{
    m_pitch = pitch;
    m_yaw = yaw;
}

// returns the position of the controller object
DirectX::XMFLOAT3 MoveLookController::get_Position()
{
    return m_position;
}

// returns the point at which the camera controller is facing
DirectX::XMFLOAT3 MoveLookController::get_LookPoint()
{
    float y = sinf( m_pitch );		// vertical
    float r = cosf( m_pitch );		// in the plane
    float z = r*cosf( m_yaw );		// fwd-back
    float x = r*sinf( m_yaw );		// left-right

	m_position.x=m_position.x+x;
	m_position.y=m_position.y+y;
	m_position.z=m_position.z+z;

    return m_position;
}

void MoveLookController::Update( )
{
    // check for input from the Move control
    if ( m_moveInUse )
    {
		DirectX::XMFLOAT2 pointerDelta = XMFloatMath::subtract(m_movePointerPosition, m_moveFirstDown);

        // figure out the command from the touch-based virtual joystick
        if ( pointerDelta.x > 16.0f )		// leave 32 pixel-wide dead spot for being still
            m_moveCommand.x =  1.0f;
        else
            if ( pointerDelta.x < -16.0f )
                m_moveCommand.x = -1.0f;

        if ( pointerDelta.y > 16.0f )		// joystick y is up so change sign
            m_moveCommand.y = -1.0f;
        else
            if (pointerDelta.y < -16.0f )
                m_moveCommand.y =  1.0f;
    }

    // poll our state bits set by the keyboard input events
    if ( m_forward )
        m_moveCommand.y += 1.0f;
    if ( m_back )
        m_moveCommand.y -= 1.0f;

    if ( m_left )
        m_moveCommand.x -= 1.0f;
    if ( m_right )
        m_moveCommand.x += 1.0f;

    if ( m_up )
        m_moveCommand.z += 1.0f;
    if ( m_down )
        m_moveCommand.z -= 1.0f;

    // make sure that 45  degree cases are not faster
    DirectX::XMFLOAT3 command = m_moveCommand;
    if ( fabsf(command.x) > 0.1f || fabsf(command.y) > 0.1f || fabsf(command.z) > 0.1f )
		XMStoreFloat3(&command, DirectX::XMVector3Normalize(XMLoadFloat3(&command)));

	

    // rotate command to align with our direction (world coordinates)
    DirectX::XMFLOAT3 wCommand;
    wCommand.x = command.x*cosf( m_yaw ) - command.y*sinf( m_yaw );
    wCommand.y = command.x*sinf( m_yaw ) + command.y*cosf( m_yaw );
    wCommand.z = command.z;

    // scale for sensitivity adjustment
	wCommand = XMFloatMath::multiply(wCommand,MOVEMENT_GAIN);

    // our velocity is based on the command,
    // also note that y is the up-down axis 
    DirectX::XMFLOAT3  Velocity;
    Velocity.x = -wCommand.x;
    Velocity.z =  wCommand.y;
    Velocity.y =  wCommand.z;

    // integrate
    m_position = XMFloatMath::add(m_position, Velocity);

    // clear movement input accumulator for use during next frame
    m_moveCommand = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );

}



