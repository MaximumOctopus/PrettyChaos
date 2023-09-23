//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>

#include "Formatting.h"
#include "ProjectIO.h"


ProjectIO::ProjectIO()
{

}


bool ProjectIO::Load(std::wstring file_name, PCProject &project)
{
	std::wifstream file(file_name);

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
					FileProperty PropertyName = FileProperty::None;

					std::wstring key = s.substr(0, equals);
					std::wstring value = s.substr(equals + 1);

					if (equals == std::wstring::npos)
					{
						key = s;
					}

					PropertyName = GetInputProperty(key);

					switch (PropertyName)
					{
					case FileProperty::None:
						break;
					case FileProperty::Width:
						project.Width = stoi(value);
						break;
					case FileProperty::Height:
						project.Height = stoi(value);
						break;
					case FileProperty::RenderMode:
						project.RenderMode = stoi(value);
						break;
					case FileProperty::nCoeff:
						project.nCoeff = stod(value);
						break;
					case FileProperty::MaxIterations:
						project.MaxIterations = stoi(value);
						break;
					case FileProperty::BailoutRadius:
						project.BailoutRadius = stoi(value);
						break;
					case FileProperty::xmin:
						project.xmin = stod(value);
						break;
					case FileProperty::xmax:
						project.xmax = stod(value);
						break;
					case FileProperty::ymin:
						project.ymin = stod(value);
						break;
					case FileProperty::ymax:
                        project.ymax = stod(value);
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


ProjectIO::FileProperty ProjectIO::GetInputProperty(std::wstring input)
{
	for (int t = 0; t < kPropertyListCount; t++)
	{
		if (input == FilePropertyList[t])
		{
			return FilePropertyReference[t];
		}
	}

	return FileProperty::None;
}


bool ProjectIO::Save(std::wstring file_name, PCProject &project)
{
	std::ofstream file(file_name);

	if (file)
	{
		file << Formatting::to_utf8(L"[\n");

		file << Formatting::to_utf8(L"Width=" + std::to_wstring(project.Width) + L"\n");
		file << Formatting::to_utf8(L"Height=" + std::to_wstring(project.Width) + L"\n");

		file << Formatting::to_utf8(L"RenderMode=" + std::to_wstring(project.RenderMode) + L"\n");
		file << Formatting::to_utf8(L"nCoeff=" + std::to_wstring(project.nCoeff) + L"\n");
		file << Formatting::to_utf8(L"MaxIterations=" + std::to_wstring(project.MaxIterations) + L"\n");
		file << Formatting::to_utf8(L"BailoutRadius=" + std::to_wstring(project.BailoutRadius) + L"\n");

		file << Formatting::to_utf8(L"xmin=" + std::to_wstring(project.xmin) + L"\n");
		file << Formatting::to_utf8(L"xmax=" + std::to_wstring(project.xmax) + L"\n");
		file << Formatting::to_utf8(L"ymin=" + std::to_wstring(project.ymin) + L"\n");
		file << Formatting::to_utf8(L"ymax=" + std::to_wstring(project.ymax) + L"\n");

		file << Formatting::to_utf8(L"]\n");

		file.close();

		return true;
	}

	return false;
}
