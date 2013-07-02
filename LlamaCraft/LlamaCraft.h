#pragma once

#include "pch.h"
#include "CubeRenderer.h"
#include "MoveLookController.h"




ref class LlamaCraft sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
public:
	LlamaCraft();
	
	// IFrameworkView Methods.
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
	virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
	virtual void Load(Platform::String^ entryPoint);
	virtual void Run();
	virtual void Uninitialize();


protected:
	// Event Handlers.
	void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
	void OnLogicalDpiChanged(Platform::Object^ sender);
	void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args);
	void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
	void OnResuming(Platform::Object^ sender, Platform::Object^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	// Methods to get input from the UI pointers
    void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args);

    void OnPointerMoved(
        Windows::UI::Core::CoreWindow^ sender,
        Windows::UI::Core::PointerEventArgs^ args
        );

    void OnPointerReleased(
        Windows::UI::Core::CoreWindow^ sender,
        Windows::UI::Core::PointerEventArgs^ args
        );

    void OnKeyDown(
         Windows::UI::Core::CoreWindow^ sender,
         Windows::UI::Core::KeyEventArgs^ args
        );

    void OnKeyUp(
         Windows::UI::Core::CoreWindow^ sender,
         Windows::UI::Core::KeyEventArgs^ args
        );

private:
	CubeRenderer^ m_renderer;
	MoveLookController m_controller;
	bool m_windowClosed;
	bool m_windowVisible;
};

ref class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};
