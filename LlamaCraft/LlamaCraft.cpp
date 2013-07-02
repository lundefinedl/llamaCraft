#include "pch.h"
#include "LlamaCraft.h"
#include "BasicTimer.h"


using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace concurrency;

LlamaCraft::LlamaCraft() :
	m_windowClosed(false),
	m_windowVisible(true)
{
	m_controller.Initialize();
}

void LlamaCraft::Initialize(CoreApplicationView^ applicationView)
{
	applicationView->Activated +=
        ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &LlamaCraft::OnActivated);

	CoreApplication::Suspending +=
        ref new EventHandler<SuspendingEventArgs^>(this, &LlamaCraft::OnSuspending);

	CoreApplication::Resuming +=
        ref new EventHandler<Platform::Object^>(this, &LlamaCraft::OnResuming);

	m_renderer = ref new CubeRenderer();
}

void LlamaCraft::SetWindow(CoreWindow^ window)
{
	window->SizeChanged += 
        ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &LlamaCraft::OnWindowSizeChanged);

	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &LlamaCraft::OnVisibilityChanged);

	window->Closed += 
        ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &LlamaCraft::OnWindowClosed);

	window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

	window->PointerPressed +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &LlamaCraft::OnPointerPressed);

	window->PointerMoved +=
		ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &LlamaCraft::OnPointerMoved);

    window->PointerReleased += 
    ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &LlamaCraft::OnPointerReleased);

  //  window->CharacterReceived +=
  //  ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &LlamaCraft::OnCharacterReceived);

    window->KeyDown += 
    ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &LlamaCraft::OnKeyDown);

    window->KeyUp += 
    ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &LlamaCraft::OnKeyUp);

	m_renderer->Initialize(CoreWindow::GetForCurrentThread());
}

void LlamaCraft::Load(Platform::String^ entryPoint)
{
	


}

void LlamaCraft::Run()
{
	BasicTimer^ timer = ref new BasicTimer();

	while (!m_windowClosed)
	{
		if (m_windowVisible)
		{
			timer->Update();
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
			m_renderer->Update(timer->Total, timer->Delta);
			m_renderer->Render();
			m_renderer->Present(); // This call is synchronized to the display frame rate.
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
		}
	}
}

void LlamaCraft::Uninitialize()
{
}

void LlamaCraft::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args)
{
	m_renderer->UpdateForWindowSizeChange();
}

void LlamaCraft::OnVisibilityChanged(CoreWindow^ sender, VisibilityChangedEventArgs^ args)
{
	m_windowVisible = args->Visible;
}

void LlamaCraft::OnWindowClosed(CoreWindow^ sender, CoreWindowEventArgs^ args)
{
	m_windowClosed = true;
}


void LlamaCraft::OnPointerPressed(
 CoreWindow^ sender,
 PointerEventArgs^ args)
{
    // get the current pointer position
    uint32 pointerID = args->CurrentPoint->PointerId;
    DirectX::XMFLOAT2 position = DirectX::XMFLOAT2( args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y );
	auto device = args->CurrentPoint->PointerDevice;
    auto deviceType = device->PointerDeviceType;
	m_controller.OnPointerPressed(position, deviceType);
    
    if ( deviceType == PointerDeviceType::Mouse )
    {
        // Action, Jump, or Fire
    }


}



void LlamaCraft::OnPointerMoved(
                                         CoreWindow ^sender,
                                         PointerEventArgs ^args)
{
    
     DirectX::XMFLOAT2 position =  DirectX::XMFLOAT2( args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y );
    m_controller.OnPointerMoved(position);
    }

void LlamaCraft::OnPointerReleased(
 CoreWindow ^sender,
 PointerEventArgs ^args)
{
   
       DirectX::XMFLOAT2 position =    DirectX::XMFLOAT2( args->CurrentPoint->Position.X, args->CurrentPoint->Position.Y );
	   m_controller.OnPointerReleased(position);

}

void LlamaCraft::OnKeyDown(
                                    CoreWindow^ sender,
                                    KeyEventArgs^ args )
{
    Windows::System::VirtualKey Key;
    Key = args->VirtualKey;
	m_controller.OnKeyDown(Key);

  
}


void LlamaCraft::OnKeyUp(
                                  CoreWindow^ sender,
                                  KeyEventArgs^ args)
{
    Windows::System::VirtualKey Key;
    Key = args->VirtualKey;

    m_controller.OnKeyDown(Key);
}


void LlamaCraft::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
{
	CoreWindow::GetForCurrentThread()->Activate();
}

void LlamaCraft::OnSuspending(Platform::Object^ sender, SuspendingEventArgs^ args)
{
	// Save app state asynchronously after requesting a deferral. Holding a deferral
	// indicates that the application is busy performing suspending operations. Be
	// aware that a deferral may not be held indefinitely. After about five seconds,
	// the app will be forced to exit.
	SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

	create_task([this, deferral]()
	{
		// Insert your code here.

		deferral->Complete();
	});
}
 
void LlamaCraft::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Restore any data or state that was unloaded on suspend. By default, data
	// and state are persisted when resuming from suspend. Note that this event
	// does not occur if the app was previously terminated.
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
    return ref new LlamaCraft();
}

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);
	return 0;
}
