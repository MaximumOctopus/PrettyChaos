//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023-2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once


#include <string>


namespace Utility
{
	[[nodiscard]] std::wstring GetOpenFileName(int, std::wstring);
	[[nodiscard]] std::wstring GetSaveFileName(int, std::wstring);

	[[nodiscard]] int CurrentYear();

	[[nodiscard]] std::wstring GetFileExtension(const std::wstring&);
	[[nodiscard]] std::wstring ProcessFileName(const std::wstring&);

	[[nodiscard]] std::wstring ReplaceString(const std::wstring, const std::wstring&, const std::wstring&);
}