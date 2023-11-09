//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#include <vector>

#include "PaletteKey.h"


class PaletteHandler
{

	int PaletteR[500];
	int PaletteG[500];
	int PaletteB[500];

    int GradientKeyAt(int);
	int GetNextGradientKey(int);
	int GetKeyType(const std::wstring);

public:

    std::wstring FileName = L"";        // file name of last load/save

	bool IsRendering = false;

	bool Interleve = false;
	bool InterleveReverse = false;
	int InterleveMode = 0;

	int Steps = 1;
	double Log = 1;
	bool ColourSpace = true;            // false is b/w

	int Palette[501];

	int SelectedKey = 0;

	TBitmap* Gradient;

	std::vector<PaletteKey> Keys;

	PaletteHandler();
	~PaletteHandler();

	void Clear(bool);

	void Render();

	void CopyPublic();

	bool Align();

	bool Load(const std::wstring);
	bool Save(const std::wstring);

	int AddNewKey(int, int, int, bool);
};
