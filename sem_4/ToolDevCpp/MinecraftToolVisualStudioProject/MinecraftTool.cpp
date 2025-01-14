﻿// MinecraftTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <direct.h> // _getwcwd
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <codecvt>
#include "rapidjson.h"
#include "document.h"
#include "stream.h"
#include "filereadstream.h"
#include "istreamwrapper.h"
#include "MinecraftTool.h"

int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	if (argc != 3 && argc != 5)
	{
		std::wcout << "wrong amount of arguments\n";
		PrintInstructions();
	}

	std::ifstream is{ argv[2] };

	if (!is)
	{
		std::wcout << L"Couldn't find inputFile\n";
		PrintInstructions();
		return -1;
	}

	if (std::wstring(argv[1]) != L"-i")
	{
		std::wcout << L"Wrong 2nd argument\n";
		PrintInstructions();
	}

	std::wstring inputFile{ std::wstring(argv[2]) };
	if (std::wstring(inputFile).find(L".json") == 0)
	{
		std::wcout << L"InputFile must be a json file.\n";
		PrintInstructions();
	}

	FILE* pOFile = nullptr;
	std::wstring outputFile{};

	if (argc == 5)
	{
		if (std::wstring(argv[3]) != L"-o")
		{
			std::wcout << L"Wrong 4rd argument\n";
			PrintInstructions();
		}

		outputFile = argv[4];
	}
	else
	{
		outputFile = inputFile.erase(inputFile.find(L"json")).append(L"obj");
	}

	if (outputFile == L"")
		return -1;

	if (outputFile.find(L".obj") == 0)
	{
		std::wcout << L"OutputFile must be an obj file\n";
	}

	_wfopen_s(&pOFile, outputFile.c_str(), L"w+,ccs=UTF-8");

	if (pOFile == nullptr)
		return -1;
	
	if (outputFile.find(L".obj") == 0)
	{
		std::wcout << L"OutputFile must be an obj file.\n";
		PrintInstructions();
	}

	// it was possible to create the file for writing.
	const wchar_t* text = L"#∂ is the symbol for partial derivative.\n";
	fwrite(text, wcslen(text) * sizeof(wchar_t), 1, pOFile);

	text = L"mtllib minecraftMats.mtl\n";
	fwrite(text, wcslen(text) * sizeof(wchar_t), 1, pOFile);

	using namespace rapidjson;
	IStreamWrapper isw{ is };
	Document jsonDoc;
	jsonDoc.ParseStream(isw);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter{};

	int amountOfCubes{};

	if (jsonDoc.IsArray())
	{
		std::vector<Cube> cubes{};

		for (Value::ConstValueIterator it = jsonDoc.Begin(); it != jsonDoc.End(); ++it)
		{
			const Value& newCubes{ *it };

			std::wstring newCubesLayer{};
			if (newCubes.HasMember("layer"))
			{
				const Value& layer{ newCubes["layer"] };

				if (layer.IsString())
				{
					newCubesLayer = converter.from_bytes(layer.GetString());
					//make the first letter capitilized
					newCubesLayer[0] = std::toupper(newCubesLayer[0]);
				}				
			}

			bool areNewCubesOpaque{};
			if (newCubes.HasMember("opaque"))
			{
				const Value& isOpaque{ newCubes["opaque"] };

				if(isOpaque.IsBool())
					areNewCubesOpaque = isOpaque.GetBool();
			}

			if (newCubes.HasMember("positions"))
			{
				const Value& positions{ newCubes["positions"] };

				for (int index{}; index < static_cast<int>(positions.Size()); ++index)
				{
					const Value& pos{ positions[index] };

					if (pos.Size() == 3 && pos[0].IsInt() && pos[1].IsInt() && pos[2].IsInt())
					{
						CreateCube(newCubesLayer, Position(pos[0].GetInt(), pos[1].GetInt(), pos[2].GetInt()), areNewCubesOpaque, cubes);
						++amountOfCubes;
					}
				}
			}
		}
		CalculateCubesNeigbors(cubes);
		WriteCubesToFile(pOFile, cubes);
	}

	fclose(pOFile);

	std::cout << "Convertion completed\n";

	return 0;
}

std::wstring Replace(const std::wstring& str, const std::wstring& subStrToReplace, const std::wstring& strToReplaceSubStringWith)
{
	size_t start_pos = str.find(subStrToReplace);

	std::wstring result{ str };

	if (start_pos == std::string::npos)
		result.replace(start_pos, subStrToReplace.length(), strToReplaceSubStringWith);

	return result;
}

void CreateCube(const std::wstring& layer, const Position& pos, bool isOpaque, std::vector<Cube>& cubes)
{
	Cube newCube{};

	newCube.p1 = Position(0 + pos.x, 0 + pos.z, 0 + pos.y);
	newCube.p2 = Position(0 + pos.x, 0 + pos.z, 1 + pos.y);
	newCube.p3 = Position(0 + pos.x, 1 + pos.z, 0 + pos.y);
	newCube.p4 = Position(0 + pos.x, 1 + pos.z, 1 + pos.y);
	newCube.p5 = Position(1 + pos.x, 0 + pos.z, 0 + pos.y);
	newCube.p6 = Position(1 + pos.x, 0 + pos.z, 1 + pos.y);
	newCube.p7 = Position(1 + pos.x, 1 + pos.z, 0 + pos.y);
	newCube.p8 = Position(1 + pos.x, 1 + pos.z, 1 + pos.y);
	newCube.layer = layer;
	newCube.isOpaque = isOpaque;

	cubes.push_back(newCube);
}

void WriteCubesToFile(FILE* pOFile, const std::vector<Cube>& cubes)
{
	for (auto& cube : cubes)
	{
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p1.x, cube.p1.y, cube.p1.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p2.x, cube.p2.y, cube.p2.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p3.x, cube.p3.y, cube.p3.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p4.x, cube.p4.y, cube.p4.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p5.x, cube.p5.y, cube.p5.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p6.x, cube.p6.y, cube.p6.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p7.x, cube.p7.y, cube.p7.z);
		fwprintf_s(pOFile, L"v %i %i %i\n", cube.p8.x, cube.p8.y, cube.p8.z);
	}

	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.f, 0.f, 1.f);
	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.f, 0.f, -1.f);
	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.f, 1.f, 0.f);
	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 0.f, -1.f, 0.f);
	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", 1.f, 0.f, 0.f);
	fwprintf_s(pOFile, L"vn %.4f %.4f %.4f\n", -1.f, 0.f, 0.f);

	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 0.f);
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 0.f);
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 0.f, 1.f);
	fwprintf_s(pOFile, L"vt %.4f %.4f\n", 1.f, 1.f);

	std::wstring currentLayer{};
	for (int cubeNr{}; cubeNr < static_cast<int>(cubes.size()); ++cubeNr)
	{
		if (currentLayer.find(cubes[cubeNr].layer) == std::wstring::npos) //check if a new layer was started
		{
			currentLayer = L"usemtl " + cubes[cubeNr].layer + L'\n';
			fwrite(currentLayer.c_str(), wcslen(currentLayer.c_str()) * sizeof(wchar_t), 1, pOFile);
		}

		if (!cubes[cubeNr].hasRightNeighbor)
		{
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 1, 2, 7 + 8 * cubeNr, 4, 2, 5 + 8 * cubeNr, 2, 2);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 1, 2, 3 + 8 * cubeNr, 3, 2, 7 + 8 * cubeNr, 4, 2);
		}

		if (!cubes[cubeNr].hasBackNeighbor)
		{

			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 2, 6, 4 + 8 * cubeNr, 3, 6, 3 + 8 * cubeNr, 4, 6);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 2, 6, 2 + 8 * cubeNr, 1, 6, 4 + 8 * cubeNr, 3, 6);
		}

		if (!cubes[cubeNr].hasTopNeighbor)
		{
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 3 + 8 * cubeNr, 2, 3, 8 + 8 * cubeNr, 3, 3, 7 + 8 * cubeNr, 1, 3);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 3 + 8 * cubeNr, 2, 3, 4 + 8 * cubeNr, 4, 3, 8 + 8 * cubeNr, 3, 3);
		}
		
		if (!cubes[cubeNr].hasFrontNeighbor)
		{
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 5 + 8 * cubeNr, 1, 5, 7 + 8 * cubeNr, 3, 5, 8 + 8 * cubeNr, 4, 5);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 5 + 8 * cubeNr, 1, 5, 8 + 8 * cubeNr, 4, 5, 6 + 8 * cubeNr, 2, 5);
		}
		
		if (!cubes[cubeNr].hasBottomNeighbor)
		{
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 4, 4, 5 + 8 * cubeNr, 3, 4, 6 + 8 * cubeNr, 1, 4);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 1 + 8 * cubeNr, 4, 4, 6 + 8 * cubeNr, 1, 4, 2 + 8 * cubeNr, 2, 4);
		}
		
		if (!cubes[cubeNr].hasLeftNeighbor)
		{
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 2 + 8 * cubeNr, 1, 1, 6 + 8 * cubeNr, 2, 1, 8 + 8 * cubeNr, 4, 1);
			fwprintf_s(pOFile, L"f %d/%d/%d %d/%d/%d %d/%d/%d\n", 2 + 8 * cubeNr, 1, 1, 8 + 8 * cubeNr, 4, 1, 4 + 8 * cubeNr, 3, 1);
		}
	}
}

void CalculateCubesNeigbors(std::vector<Cube>& cubes)
{
	for (auto& cube : cubes)
	{
		for (auto& otherCube : cubes)
		{
			//make sure cube is not the same as otherCube
			if (cube == otherCube || !cube.isOpaque || !otherCube.isOpaque)
				continue;

			//check if otherCube is a rightNeighbor for cube
			if (	cube.p3 == otherCube.p1 && cube.p4 == otherCube.p2
				 && cube.p7 == otherCube.p5 && cube.p8 == otherCube.p6)
			{
				cube.hasTopNeighbor = true;
				otherCube.hasBottomNeighbor = true;
			}

			//check if otherCube is a topNeighbor for cube
			if (	cube.p1 == otherCube.p2 && cube.p3 == otherCube.p4
				 && cube.p5 == otherCube.p6 && cube.p7 == otherCube.p8)
			{
				cube.hasRightNeighbor = true;
				otherCube.hasLeftNeighbor = true;
			}

			//check if otherCube is a backNeighbor for cube
			if (cube.p1 == otherCube.p5 && cube.p2 == otherCube.p6
				&& cube.p3 == otherCube.p7 && cube.p4 == otherCube.p8)
			{
				cube.hasBackNeighbor = true;
				otherCube.hasFrontNeighbor = true;
			}
		}
	}
}

void PrintInstructions()
{
	std::wcout << L"Possible arguments:\n\tMinecraftTool -i (inputFileName).json\n\tMinecraftTool -i inputFile.json -o outputFile.obj\n";
}