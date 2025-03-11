//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2025
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <fstream>
#include <iomanip>

#include <Vcl.Dialogs.hpp>

#include "Formatting.h"
#include "PaletteHandler.h"
#include "ProjectIO.h"

extern PaletteHandler *GPaletteHandler;


ProjectIO::ProjectIO()
{
}


bool ProjectIO::Load(const std::wstring file_name, PCProject &project, Animation &animation)
{
	std::wifstream file(file_name);

	if (file)
	{
		project.ProjectFileName = file_name;

		std::wstring s(L"");

		animation.Configured = false;

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
						//ShowMessage(key.c_str());
						break;
					case FileProperty::Name:
						project.Name = value;
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
					case FileProperty::var_a:
						project.var_a = stod(value);
						break;
					case FileProperty::var_b:
						project.var_b = stod(value);
						break;
					case FileProperty::var_c:
						project.var_c = stod(value);
						break;
					case FileProperty::var_d:
						project.var_d = stod(value);
						break;

					case FileProperty::Steps:
						animation.Configured = true;
						animation.Steps = stoi(value);
						break;
					case FileProperty::DeltaA:
						animation.DeltaA = stod(value);
						break;
					case FileProperty::DeltaB:
						animation.DeltaB = stod(value);
						break;
					case FileProperty::DeltaC:
						animation.DeltaC = stod(value);
						break;
					case FileProperty::DeltaD:
						animation.DeltaD = stod(value);
						break;
					case FileProperty::Parameters:
						animation.Parameters = stoi(value);
						break;
					case FileProperty::Zoom:
						animation.Zoom = stoi(value);
						break;
					case FileProperty::Prefix:
						animation.Prefix = value;
						break;

					case FileProperty::PaletteFileName:
                        project.PaletteFileName = value;
						break;

					case FileProperty::SuperSampling:
						project.SuperSampling = stoi(value);
						break;

					case FileProperty::SuperSamplingLevel:
						project.SuperSamplingLevel = stoi(value);
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


ProjectIO::FileProperty ProjectIO::GetInputProperty(const std::wstring input)
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


bool ProjectIO::Save(const std::wstring file_name, PCProject &project, Animation &animation)
{
	std::ofstream file(file_name);

	if (file)
	{
		project.ProjectFileName = file_name;

		file << Formatting::to_utf8(L"[\n");

		file << Formatting::to_utf8(L"Name=" + project.Name + L"\n");
		file << Formatting::to_utf8(L"Width=" + std::to_wstring(project.Width) + L"\n");
		file << Formatting::to_utf8(L"Height=" + std::to_wstring(project.Height) + L"\n");

		file << Formatting::to_utf8(L"RenderMode=" + std::to_wstring(project.RenderMode) + L"\n");
		file << Formatting::to_utf8(L"nCoeff=" + std::to_wstring(project.nCoeff) + L"\n");
		file << Formatting::to_utf8(L"MaxIterations=" + std::to_wstring(project.MaxIterations) + L"\n");
		file << Formatting::to_utf8(L"BailoutRadius=" + std::to_wstring(project.BailoutRadius) + L"\n");

		file << Formatting::to_utf8(L"SS=" + std::to_wstring(project.SuperSampling) + L"\n");
		file << Formatting::to_utf8(L"SSLevel=" + std::to_wstring(project.SuperSamplingLevel) + L"\n");

		if (!GPaletteHandler->FileName.empty())
		{
			file << Formatting::to_utf8(L"Palette=" + GPaletteHandler->FileName + L"\n");
		}

		file << Formatting::to_utf8(L"xmin=" + Formatting::LDToStr(project.xmin) + L"\n");
		file << Formatting::to_utf8(L"xmax=" + Formatting::LDToStr(project.xmax) + L"\n");
		file << Formatting::to_utf8(L"ymin=" + Formatting::LDToStr(project.ymin) + L"\n");
		file << Formatting::to_utf8(L"ymax=" + Formatting::LDToStr(project.ymax) + L"\n");

		file << Formatting::to_utf8(L"var_a=" + Formatting::LDToStr(project.var_a) + L"\n");
		file << Formatting::to_utf8(L"var_b=" + Formatting::LDToStr(project.var_b) + L"\n");
		file << Formatting::to_utf8(L"var_c=" + Formatting::LDToStr(project.var_c) + L"\n");
		file << Formatting::to_utf8(L"var_d=" + Formatting::LDToStr(project.var_d) + L"\n");

		file << Formatting::to_utf8(L"]\n");

		if (animation.Configured)
		{
			file << Formatting::to_utf8(L"{\n");

			file << Formatting::to_utf8(L"Steps=" + std::to_wstring(animation.Steps) + L"\n");

			file << Formatting::to_utf8(L"DeltaA=" + std::to_wstring(animation.DeltaA) + L"\n");
			file << Formatting::to_utf8(L"DeltaB=" + std::to_wstring(animation.DeltaB) + L"\n");
			file << Formatting::to_utf8(L"DeltaC=" + std::to_wstring(animation.DeltaC) + L"\n");
			file << Formatting::to_utf8(L"DeltaD=" + std::to_wstring(animation.DeltaD) + L"\n");

			file << Formatting::to_utf8(L"Parameters=" + std::to_wstring(animation.Parameters) + L"\n");
			file << Formatting::to_utf8(L"Zoom=" + std::to_wstring(animation.Zoom) + L"\n");

			file << Formatting::to_utf8(L"Prefix=" + animation.Prefix + L"\n");

			file << Formatting::to_utf8(L"}\n");
		}

		file.close();

		return true;
	}

	return false;
}
