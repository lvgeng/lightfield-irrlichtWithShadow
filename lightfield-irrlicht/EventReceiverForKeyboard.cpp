#include "EventReceiverForKeyboard.h"

bool EventReceiverForKeyboard::OnEvent(const SEvent & event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown)
	{
		deviceInner->closeDevice();
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_1  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		savetex(renderTargetTexInner,"renderingResult1.png",videoDriver);
		// videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot1.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_2  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		savetex(renderTargetTexInner,"renderingResult2.png",videoDriver);
		// videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot2.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_3  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		savetex(renderTargetTexInner,"renderingResult3.png",videoDriver);
		// videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot3.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_4  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot1.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_5  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot2.png");
		return true;
	}
	else if (event.EventType == irr::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_KEY_6  && event.KeyInput.PressedDown)
	{
		IVideoDriver* videoDriver = deviceInner->getVideoDriver();
		videoDriver->writeImageToFile(videoDriver->createScreenShot(), "screenshot3.png");
		return true;
	}
}

void EventReceiverForKeyboard::savetex(ITexture *texture, std::string filename, IVideoDriver* videoDriver) {
	video::IImage* image = videoDriver->createImageFromData (
		texture->getColorFormat(),
		texture->getSize(),
		texture->lock( irr::video::E_TEXTURE_LOCK_MODE::ETLM_READ_WRITE),
		true  //copy mem
	);
	videoDriver->writeImageToFile(image, path(filename.c_str()));
	texture->unlock();
}

EventReceiverForKeyboard::EventReceiverForKeyboard(IrrlichtDevice* device, video::ITexture* renderTargetTex)
{
	deviceInner = device;
	renderTargetTexInner = renderTargetTex;
}


EventReceiverForKeyboard::~EventReceiverForKeyboard()
{
}
