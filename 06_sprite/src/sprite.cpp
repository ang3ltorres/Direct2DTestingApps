#include "sprite.hpp"

Sprite::Sprite(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;
	this->bmp = nullptr;

	IWICImagingFactory* wicFactory = nullptr;
	CoCreateInstance
	(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory
	);

	IWICBitmapDecoder* wicDecoder = nullptr;
	wicFactory->CreateDecoderFromFilename
	(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder
	);

	IWICBitmapFrameDecode* wicFrame = nullptr;
	wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter* wicConverter = nullptr;
	wicFactory->CreateFormatConverter(&wicConverter);

	wicConverter->Initialize
	(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	gfx->renderTarget->CreateBitmapFromWicBitmap
	(
		wicConverter,
		nullptr,
		&bmp
	);

	wicConverter->Release();
	wicFrame->Release();
	wicDecoder->Release();
	wicFactory->Release();
}

Sprite::~Sprite()
{
	bmp->Release();
}

void Sprite::draw()
{
	gfx->renderTarget->DrawBitmap
	(
		bmp,
		D2D1::RectF
		(
			0.0f,
			0.0f,
			bmp->GetSize().width,
			bmp->GetSize().height
		),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF
		(
			0.0f,
			0.0f,
			bmp->GetSize().width,
			bmp->GetSize().height
		)
	);
}

