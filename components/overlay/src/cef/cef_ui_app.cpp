#include "std_include.hpp"

#include "cef/cef_ui.hpp"
#include "cef/cef_ui_app.hpp"
#include "cef/cef_ui_handler.hpp"

namespace gameoverlay
{
	cef_ui_app::cef_ui_app()
	{
		this->client = new cef_ui_handler(this);
	}

	CefRefPtr<cef_ui_handler> cef_ui_app::get_client()
	{
		return this->client;
	}

	void cef_ui_app::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
	{

	}

	void cef_ui_app::OnContextInitialized()
	{
		CEF_REQUIRE_UI_THREAD();

		CefBrowserSettings browserSettings;
		browserSettings.windowless_frame_rate = 60;
		browserSettings.web_security = STATE_DISABLED;

		std::string url = "http://google.com";

		CefWindowInfo windowInfo;
		windowInfo.SetAsWindowless(GetDesktopWindow());
		windowInfo.windowless_rendering_enabled = TRUE;

		CefBrowserHost::CreateBrowser(windowInfo, this->get_client(), url, browserSettings, NULL);
	}

	void cef_ui_app::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
	{

	}

	void cef_ui_app::OnBeforeCommandLineProcessing(const CefString& /*process_type*/, CefRefPtr<CefCommandLine> command_line)
	{
		command_line->AppendSwitch("enable-experimental-web-platform-features");
		command_line->AppendSwitch("in-process-gpu");
		command_line->AppendSwitch("enable-media-stream");
		command_line->AppendSwitch("use-fake-ui-for-media-stream");
		command_line->AppendSwitch("enable-speech-input");
		command_line->AppendSwitch("ignore-gpu-blacklist");
		command_line->AppendSwitch("enable-usermedia-screen-capture");
		command_line->AppendSwitchWithValue("default-encoding", "utf-8");

		/*if (IsWindows10OrGreater())
		{
			command_line->AppendSwitch("force-gpu-rasterization");
		}*/

		command_line->AppendSwitch("disable-gpu");
		command_line->AppendSwitch("disable-gpu-compositing");
		command_line->AppendSwitch("enable-begin-frame-scheduling");
	}

	bool cef_ui_app::OnProcessMessageReceived(CefRefPtr<CefBrowser> /*browser*/, CefProcessId /*sourceProcess*/, CefRefPtr<CefProcessMessage> /*message*/)
	{
		return false;
	}
}
