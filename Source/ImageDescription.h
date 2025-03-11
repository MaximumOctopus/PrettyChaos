//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <string>


class ImageDescription
{

private:

	static const int kIDPropertyListCount = 6;

	enum class IDProperty {
		None = 0, Active = 1, Font = 2, Size = 3, PositionX = 4, PositionY = 5, Location = 6
	};

	const std::wstring IDPropertyList[kIDPropertyListCount] = {
		L"active", L"font", L"size", L"positionx", L"positiony",
		L"location"
	};

	const IDProperty IDPropertyReference[kIDPropertyListCount] = {
		IDProperty::Active, IDProperty::Font, IDProperty::Size, IDProperty::PositionX, IDProperty::PositionY, IDProperty::Location
	};

	std::wstring FileName = L"";

	ImageDescription::IDProperty GetInputProperty(const std::wstring);

public:

	bool Active = false;

	std::wstring FontName = L"Courier New";
	int FontSize = 12;

	int PositionX = 10;
	int PositionY = 10;

	int Location = 0;               // 0 = bottom left, 1 = top left

    bool Valid = false;

	ImageDescription(const std::wstring);

	bool Load();
	bool Save();
};
