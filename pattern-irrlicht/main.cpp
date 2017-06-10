#include <irrlicht.h>
//#include <SIrrCreationParameters.h>

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "pugixml.hpp"

using namespace std;
using namespace chrono;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//This is the main method. We can now use main() on every platform.

void savetex(ITexture *texture, std::string filename, IVideoDriver* videoDriver) {

	// void* imageData = texture->lock(true);
	video::IImage* image = videoDriver->createImageFromData (
		texture->getColorFormat(),
		texture->getSize(),
		texture->lock( irr::video::E_TEXTURE_LOCK_MODE::ETLM_READ_WRITE),
		true  //copy mem
	);

	videoDriver->writeImageToFile(image, path(filename.c_str()));
	texture->unlock();
}


int main(int argc, char* argv[])
{
	bool isTesting = false;
	bool isFrame = false;
	int widthOfDisplayZone = 800;
	int heightOfDisplayZone = 600;
	int widthOfSubimage = 20;
	int heightOfSubimage = 20;
	int widthOfHole = 2;
	int heightOfHole = 2;

	int widthOfFrameExternal = 20;
	int heightOfFrameExternal = 20;
	int widthOfFrameInner = 18;
	int heightOfFrameInner = 18;

	int xOffset = 0;
	int yOffset = 0;

	pugi::xml_document doc;
	pugi::xml_parse_result resultConfigfile = doc.load_file("config.xml");
	if (!resultConfigfile)
	{
		// add node with some name
		pugi::xml_node nodeSetting = doc.append_child("Settings");
		nodeSetting.append_child("isTesting").append_attribute("value") = isTesting;
		nodeSetting.append_child("isFrame").append_attribute("value") = isFrame;
		nodeSetting.append_child("widthOfDisplayZone").append_attribute("value") = widthOfDisplayZone;
		nodeSetting.append_child("heightOfDisplayZone").append_attribute("value") = heightOfDisplayZone;
		nodeSetting.append_child("widthOfSubimage").append_attribute("value") = widthOfSubimage;
		nodeSetting.append_child("heightOfSubimage").append_attribute("value") = heightOfSubimage;
		nodeSetting.append_child("widthOfHole").append_attribute("value") = widthOfHole;
		nodeSetting.append_child("heightOfHole").append_attribute("value") = heightOfHole;

		nodeSetting.append_child("widthOfFrameExternal").append_attribute("value") = widthOfFrameExternal;
		nodeSetting.append_child("heightOfFrameExternal").append_attribute("value") = heightOfFrameExternal;
		nodeSetting.append_child("widthOfFrameInner").append_attribute("value") = widthOfFrameInner;
		nodeSetting.append_child("heightOfFrameInner").append_attribute("value") = heightOfFrameInner;

		nodeSetting.append_child("xOffset").append_attribute("value") = xOffset;
		nodeSetting.append_child("yOffset").append_attribute("value") = yOffset;


		doc.save_file("config.xml");
	}
	else
	{
		isTesting = doc.child("Settings").child("isTesting").attribute("value").as_bool();
		isFrame = doc.child("Settings").child("isFrame").attribute("value").as_bool();
		widthOfDisplayZone = doc.child("Settings").child("widthOfDisplayZone").attribute("value").as_int();
		heightOfDisplayZone = doc.child("Settings").child("heightOfDisplayZone").attribute("value").as_int();
		widthOfSubimage = doc.child("Settings").child("widthOfSubimage").attribute("value").as_int();
		heightOfSubimage = doc.child("Settings").child("heightOfSubimage").attribute("value").as_int();
		widthOfHole = doc.child("Settings").child("widthOfHole").attribute("value").as_int();
		heightOfHole = doc.child("Settings").child("heightOfHole").attribute("value").as_int();

		widthOfFrameExternal = doc.child("Settings").child("widthOfFrameExternal").attribute("value").as_int();
		heightOfFrameExternal = doc.child("Settings").child("heightOfFrameExternal").attribute("value").as_int();
		widthOfFrameInner = doc.child("Settings").child("widthOfFrameInner").attribute("value").as_int();
		heightOfFrameInner = doc.child("Settings").child("heightOfFrameInner").attribute("value").as_int();

		xOffset = doc.child("Settings").child("xOffset").attribute("value").as_int();
		yOffset = doc.child("Settings").child("yOffset").attribute("value").as_int();
	}

	video::SColor backgroundColor;
	video::SColor dotColor;
	std::string filename;

	if(isTesting)
	{
		backgroundColor = SColor(255,230,230,230);
		dotColor = SColor(255,0,0,0);
	}
	else
	{
		backgroundColor = SColor(255,0,0,0);
		dotColor = SColor(255,255,255,255);
		if (isFrame)
		{
			backgroundColor = SColor(255, 255, 255, 255);
			dotColor = SColor(255, 0, 0, 0);
		}
	}

	IrrlichtDevice *device =
		createDevice(
			video::EDT_OPENGL,				//- deviceType: Type of the device. This can currently be the Null-device,one of the two software renderers, D3D8, D3D9, or OpenGL.In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			//video::EDT_DIRECT3D9,
			dimension2d<u32>(widthOfDisplayZone, heightOfDisplayZone),
											//- windowSize: Size of the Window or screen in FullScreenMode to be created.
			16,								//- bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			false,//- fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			true,							//- stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			true,							//- vsync: Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0								//- eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.
			);


	device->setWindowCaption(L"Light field display");

	IVideoDriver* videoDriver = device->getVideoDriver();
	ISceneManager* sceneManager = device->getSceneManager();
	IGUIEnvironment* guiEnvironment = device->getGUIEnvironment();

	video::IRenderTarget* simulatorRenderTarget = 0;
	video::ITexture* renderTargetTex = 0;
	scene::ICameraSceneNode* fixedCam = 0;
	renderTargetTex = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(widthOfDisplayZone,heightOfDisplayZone), "RTT1", video::ECF_A8R8G8B8);
	video::ITexture* renderTargetDepth = videoDriver->addRenderTargetTexture(core::dimension2d<u32>(widthOfDisplayZone,heightOfDisplayZone), "DepthStencil", video::ECF_D24S8);
	simulatorRenderTarget = videoDriver->addRenderTarget();
	simulatorRenderTarget->setTexture(renderTargetTex, renderTargetDepth);
	videoDriver->setRenderTargetEx(simulatorRenderTarget, video::ECBF_COLOR | video::ECBF_DEPTH, SColor(0));


	if(isTesting)
	{
		IGUIStaticText* informationTextBox = guiEnvironment->addStaticText(L"this is text", rect<s32>(15,15,260,30), true);
		core::stringw displayStr = L"Width = ";
		displayStr += widthOfDisplayZone;
		displayStr += " Height = ";
		displayStr += heightOfDisplayZone;
		informationTextBox->setText(displayStr.c_str());

		videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, backgroundColor);
		for (int xSubimageCount = 0; xSubimageCount < widthOfDisplayZone / widthOfSubimage; xSubimageCount++)
		{
			for (int ySubimageCount = 0; ySubimageCount < heightOfDisplayZone / heightOfSubimage; ySubimageCount++)
			{
				videoDriver->draw2DRectangle(
					dotColor,
					core::rect<s32>(
						(xSubimageCount + 0.5) * widthOfSubimage - widthOfHole / 2 + xOffset,
						(ySubimageCount + 0.5) * heightOfSubimage - heightOfHole / 2 + yOffset,
						(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole / 2 + xOffset,
						(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole / 2 + yOffset
						)
					);

				if (xSubimageCount % 5 == 0 && ySubimageCount % 5 == 0)
				{
					IGUIStaticText* coordinatesInformationTextBox = guiEnvironment->addStaticText(
						L"this is text",
						rect<s32>(xSubimageCount * widthOfSubimage, ySubimageCount * heightOfSubimage, (xSubimageCount + 3) * widthOfSubimage, (ySubimageCount + 3) * heightOfSubimage), true);
					core::stringw displayStr = L"(";
					displayStr += xSubimageCount * widthOfSubimage;
					displayStr += ", ";
					displayStr += ySubimageCount * heightOfSubimage;
					displayStr += ")";
					coordinatesInformationTextBox->setText(displayStr.c_str());
				}
			}
		}
	}
	else {
		if (!isFrame) {
			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, backgroundColor);
			if (widthOfHole > 1 && heightOfHole > 1) {
				for (int xSubimageCount = 0; xSubimageCount < (widthOfDisplayZone - xOffset) / widthOfSubimage; xSubimageCount++)
				{
					for (int ySubimageCount = 0; ySubimageCount < (heightOfDisplayZone - yOffset) / heightOfSubimage; ySubimageCount++)
					{
						videoDriver->draw2DRectangle(
							dotColor,
							core::rect<s32>(
								(xSubimageCount + 0.5) * widthOfSubimage - widthOfHole / 2 + xOffset,
								(ySubimageCount + 0.5) * heightOfSubimage - heightOfHole / 2 + yOffset,
								(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole / 2 + xOffset,
								(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole / 2 + yOffset
								)
							);
					}
				}
			}
			else {
				for (int xSubimageCount = 0; xSubimageCount < (widthOfDisplayZone - xOffset) / widthOfSubimage; xSubimageCount++)
				{
					for (int ySubimageCount = 0; ySubimageCount < (heightOfDisplayZone - yOffset) / heightOfSubimage; ySubimageCount++)
					{
						videoDriver->draw2DRectangle(
							dotColor,
							core::rect<s32>(
								(xSubimageCount + 0.5) * widthOfSubimage + xOffset,
								(ySubimageCount + 0.5) * heightOfSubimage + yOffset,
								(xSubimageCount + 0.5) * widthOfSubimage + widthOfHole + xOffset,
								(ySubimageCount + 0.5) * heightOfSubimage + heightOfHole + yOffset
								)
							);
					}
				}
			}
			
		}
		else {
			videoDriver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, backgroundColor);
			for (int xSubimageCount = 0; xSubimageCount < (widthOfDisplayZone - xOffset) / widthOfSubimage; xSubimageCount++)
			{
				for (int ySubimageCount = 0; ySubimageCount < (heightOfDisplayZone - yOffset) / heightOfSubimage; ySubimageCount++)
				{
					videoDriver->draw2DRectangle(
						dotColor,
						core::rect<s32>(
							(xSubimageCount + 0.5) * widthOfSubimage - widthOfFrameExternal / 2 + xOffset,
							(ySubimageCount + 0.5) * heightOfSubimage - heightOfFrameExternal / 2 + yOffset,
							(xSubimageCount + 0.5) * widthOfSubimage + widthOfFrameExternal / 2 + xOffset,
							(ySubimageCount + 0.5) * heightOfSubimage + heightOfFrameExternal / 2 + yOffset
							)
						);
					videoDriver->draw2DRectangle(
						backgroundColor,
						core::rect<s32>(
							(xSubimageCount + 0.5) * widthOfSubimage - widthOfFrameInner / 2 + xOffset,
							(ySubimageCount + 0.5) * heightOfSubimage - heightOfFrameInner / 2 + yOffset,
							(xSubimageCount + 0.5) * widthOfSubimage + widthOfFrameInner / 2 + xOffset,
							(ySubimageCount + 0.5) * heightOfSubimage + heightOfFrameInner / 2 + yOffset
							)
						);
				}
			}
		}
		
	}


	guiEnvironment->drawAll();	

	videoDriver->setRenderTargetEx(0, 0, SColor(0));
	videoDriver->draw2DImage(renderTargetTex,	core::position2d< s32 >(100,100));
	videoDriver->endScene();

	filename = "LB-";
	if(isTesting)
	{
		filename = "LB-testing-";
	}
	if(isFrame)
	{
		filename = "LB-Frame-";
	}
	filename += to_string(widthOfDisplayZone) + "-" + to_string(heightOfDisplayZone) + "-" + to_string(widthOfSubimage) + "-" + to_string(heightOfSubimage) + "-" + to_string(widthOfHole) + "-" + to_string(heightOfHole) + ".png";
	savetex(renderTargetTex,filename,videoDriver);
  //while(device->run());
}
