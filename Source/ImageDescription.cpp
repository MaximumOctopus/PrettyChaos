//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>

#include "Formatting.h"
#include "ImageDescription.h"


ImageDescription::ImageDescription(const std::wstring path)
{
	FileName = path + L"pcot.txt";
}


bool ImageDescription::Load()
{
	std::wifstream file(FileName);

	if (file)
	{
		std::wstring s(L"");

		while (std::getline(file, s))
		{
			if (s != L"")
			{
				if (s[0] == L'/' || s[0] == L'#')
				{
					// comment, do nothing
				}
				else
				{
					auto equals = s.find(L'=');
					IDProperty PropertyName = IDProperty::None;

					std::wstring key = s.substr(0, equals);
					std::wstring value = s.substr(equals + 1);

					if (equals == std::wstring::npos)
					{
						key = s;
					}

					PropertyName = GetInputProperty(key);

					switch (PropertyName)
					{
					case IDProperty::None:
						break;
					case IDProperty::Active:
						Active = stoi(value);
						break;
					case IDProperty::Font:
						FontName = value;
						break;
					case IDProperty::Size:
						FontSize = stoi(value);
						break;
					case IDProperty::PositionX:
						PositionX = stoi(value);
						break;
					case IDProperty::PositionY:
						PositionY = stod(value);
						break;
					case IDProperty::Location:
						Location = stoi(value);
						break;
                    }
				}
			}
		}

		file.close();

		return true;
    }

    return false;
}


ImageDescription::IDProperty ImageDescription::GetInputProperty(const std::wstring input)
{
	for (int t = 0; t < kIDPropertyListCount; t++)
	{
		if (input == IDPropertyList[t])
		{
			return IDPropertyReference[t];
		}
	}

	return IDProperty::None;
}


bool ImageDescription::Save()
{
	std::ofstream ofile(FileName);

	if (ofile)
	{
		ofile << Formatting::to_utf8(L"{\n");
		ofile << Formatting::to_utf8(L"active=" + std::to_wstring(Active) + L"\n");
		ofile << Formatting::to_utf8(L"font=" + FontName + L"\n");
		ofile << Formatting::to_utf8(L"size=" + std::to_wstring(FontSize) + L"\n");
		ofile << Formatting::to_utf8(L"positionx=" + std::to_wstring(PositionX) + L"\n");
		ofile << Formatting::to_utf8(L"positiony=" + std::to_wstring(PositionY) + L"\n");
		ofile << Formatting::to_utf8(L"location=" + std::to_wstring(Location) + L"\n");
		ofile << Formatting::to_utf8(L"}\n");

		ofile.close();

		return true;
	}

	return false;
}
