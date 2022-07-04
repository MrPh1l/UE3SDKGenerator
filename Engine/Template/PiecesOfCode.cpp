#include "PiecesOfCode.hpp"

/*
# ========================================================================================= #
# Pieces Of Code
# ========================================================================================= #
*/

namespace PiecesOfCode
{
	const std::string TArray_Iterator =
		"template<typename TArray>\n"
		"class TIterator\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = typename TArray::ElementType;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\tusing ElementReference = ElementType&;\n"
		"\tusing ElementConstReference = const ElementType&;\n"
		"\n"
		"private:\n"
		"\tElementPointer IteratorData;\n"
		"\n"
		"public:\n"
		"\tTIterator(ElementPointer inElementPointer)\n"
		"\t{\n"
		"\t\tIteratorData = inElementPointer;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tTIterator& operator++()\n"
		"\t{\n"
		"\t\tIteratorData++;\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"\tTIterator operator++(int32_t)\n"
		"\t{\n"
		"\t\tTIterator iteratorCopy = *this;\n"
		"\t\t++(*this);\n"
		"\t\treturn iteratorCopy;\n"
		"\t}\n"
		"\n"
		"\tTIterator& operator--()\n"
		"\t{\n"
		"\t\tIteratorData--;\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"\tTIterator operator--(int32_t)\n"
		"\t{\n"
		"\t\tTIterator iteratorCopy = *this;\n"
		"\t\t--(*this);\n"
		"\t\treturn iteratorCopy;\n"
		"\t}\n"
		"\n"
		"\tElementReference operator[](int32_t index)\n"
		"\t{\n"
		"\t\treturn *(IteratorData[index]);\n"
		"\t}\n"
		"\n"
		"\tElementPointer operator->()\n"
		"\t{\n"
		"\t\treturn IteratorData;\n"
		"\t}\n"
		"\n"
		"\tElementReference operator*()\n"
		"\t{\n"
		"\t\treturn *IteratorData;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tbool operator==(const TIterator& other) const\n"
		"\t{\n"
		"\t\treturn (IteratorData == other.IteratorData);\n"
		"\t}\n"
		"\n"
		"\tbool operator!=(const TIterator& other) const\n"
		"\t{\n"
		"\t\treturn !(*this == other);\n"
		"\t}\n"
		"};\n";

	const std::string TArray_Class =
		"template<typename InElementType>\n"
		"class TArray\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = InElementType;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\tusing ElementReference = ElementType&;\n"
		"\tusing ElementConstReference = const ElementType&;\n"
		"\tusing Iterator = TIterator<TArray<ElementType>>;\n"
		"\n"
		"private:\n"
		"\tElementPointer ArrayData;\n"
		"\tint32_t ArrayCount;\n"
		"\tint32_t ArrayMax;\n"
		"\n"
		"public:\n"
		"\tTArray() : ArrayData(nullptr), ArrayCount(0), ArrayMax(0)\n"
		"\t{\n"
		"\t\t//ReAllocate(sizeof(ElementType));\n"
		"\t}\n"
		"\n"
		"\t~TArray()\n"
		"\t{\n"
		"\t\t//Clear();\n"
		"\t\t//::operator delete(ArrayData, ArrayMax * sizeof(ElementType));\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tElementConstReference operator[](int32_t index) const\n"
		"\t{\n"
		"\t\treturn ArrayData[index];\n"
		"\t}\n"
		"\n"
		"\tElementReference operator[](int32_t index)\n"
		"\t{\n"
		"\t\treturn ArrayData[index];\n"
		"\t}\n"
		"\n"
		"\tElementConstReference At(int32_t index) const\n"
		"\t{\n"
		"\t\treturn ArrayData[index];\n"
		"\t}\n"
		"\n"
		"\tElementReference At(int32_t index)\n"
		"\t{\n"
		"\t\treturn ArrayData[index];\n"
		"\t}\n"
		"\n"
		"\tvoid Add(ElementConstReference newElement)\n"
		"\t{\n"
		"\t\tif (ArrayCount >= ArrayMax)\n"
		"\t\t{\n"
		"\t\t\tReAllocate(sizeof(ElementType) * (ArrayCount + 1));\n"
		"\t\t}\n"
		"\n"
		"\t\tnew(&ArrayData[ArrayCount]) ElementType(newElement);\n"
		"\t\tArrayCount++;\n"
		"\t}\n"
		"\n"
		"\tvoid Add(ElementReference& newElement)\n"
		"\t{\n"
		"\t\tif (ArrayCount >= ArrayMax)\n"
		"\t\t{\n"
		"\t\t\tReAllocate(sizeof(ElementType) * (ArrayCount + 1));\n"
		"\t\t}\n"
		"\n"
		"\t\tnew(&ArrayData[ArrayCount]) ElementType(newElement);\n"
		"\t\tArrayCount++;\n"
		"\t}\n"
		"\n"
		"\tvoid PopBack()\n"
		"\t{\n"
		"\t\tif (ArrayCount > 0)\n"
		"\t\t{\n"
		"\t\t\tArrayCount--;\n"
		"\t\t\tArrayData[ArrayCount].~ElementType();\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\tvoid Clear()\n"
		"\t{\n"
		"\t\tfor (int32_t i = 0; i < ArrayCount; i++)\n"
		"\t\t{\n"
		"\t\t\tArrayData[i].~ElementType();\n"
		"\t\t}\n"
		"\n"
		"\t\tArrayCount = 0;\n"
		"\t}\n"
		"\n"
		"\tint32_t Num() const\n"
		"\t{\n"
		"\t\treturn ArrayCount;\n"
		"\t}\n"
		"\n"
		"\tint32_t Max() const\n"
		"\t{\n"
		"\t\treturn ArrayMax;\n"
		"\t}\n"
		"\n"
		"\tIterator begin()\n"
		"\t{\n"
		"\t\treturn Iterator(ArrayData);\n"
		"\t}\n"
		"\n"
		"\tIterator end()\n"
		"\t{\n"
		"\t\treturn Iterator(ArrayData + ArrayCount);\n"
		"\t}\n"
		"\n"
		"private:\n"
		"\tvoid ReAllocate(int32_t newArrayMax)\n"
		"\t{\n"
		"\t\tElementPointer newArrayData = (ElementPointer)::operator new(newArrayMax * sizeof(ElementType));\n"
		"\t\tint32_t newNum = ArrayCount;\n"
		"\n"
		"\t\tif (newArrayMax < newNum)\n"
		"\t\t{\n"
		"\t\t\tnewNum = newArrayMax;\n"
		"\t\t}\n"
		"\n"
		"\t\tfor (int32_t i = 0; i < newNum; i++)\n"
		"\t\t{\n"
		"\t\t\tnew(newArrayData + i) ElementType(std::move(ArrayData[i]));\n"
		"\t\t}\n"
		"\n"
		"\t\tfor (int32_t i = 0; i < ArrayCount; i++)\n"
		"\t\t{\n"
		"\t\t\tArrayData[i].~ElementType();\n"
		"\t\t}\n"
		"\n"
		"\t\t::operator delete(ArrayData, ArrayMax * sizeof(ElementType));\n"
		"\t\tArrayData = newArrayData;\n"
		"\t\tArrayMax = newArrayMax;\n"
		"\t}\n"
		"};\n";

		const std::string TMap_Class =
			"template<typename TKey, typename TValue>\n"
			"class TMap\n"
			"{\n"
			"private:\n"
			"\tstruct TPair\n"
			"\t{\n"
			"\t\tTKey Key;\n"
			"\t\tTValue Value;\n"
			"\t};\n"
			"\n"
			"public:\n"
			"\tusing ElementType = TPair;\n"
			"\tusing ElementPointer = ElementType*;\n"
			"\tusing ElementReference = ElementType&;\n"
			"\tusing ElementConstReference = const ElementType&;\n"
			"\tusing Iterator = TIterator<TArray<ElementType>>;\n"
			"\n"
			"public:\n"
			"\tTArray<ElementType> Elements;\t\t\t\t\t\t\t\t\t// 0x0000 (0x0010)\n"
			"\tuintptr_t IndirectData;\t\t\t\t\t\t\t\t\t\t\t// 0x0010 (0x0008)\n"
			"\tint32_t InlineData[0x4];\t\t\t\t\t\t\t\t\t\t// 0x0018 (0x0010)\n"
			"\tint32_t NumBits;\t\t\t\t\t\t\t\t\t\t\t\t// 0x0028 (0x0004)\n"
			"\tint32_t MaxBits;\t\t\t\t\t\t\t\t\t\t\t\t// 0x002C (0x0004)\n"
			"\tint32_t FirstFreeIndex;\t\t\t\t\t\t\t\t\t\t\t// 0x0030 (0x0004)\n"
			"\tint32_t NumFreeIndices;\t\t\t\t\t\t\t\t\t\t\t// 0x0034 (0x0004)\n"
			"\tint64_t InlineHash;\t\t\t\t\t\t\t\t\t\t\t\t// 0x0038 (0x0008)\n"
			"\tint32_t* Hash;\t\t\t\t\t\t\t\t\t\t\t\t\t// 0x0040 (0x0008)\n"
			"\tint32_t HashCount;\t\t\t\t\t\t\t\t\t\t\t\t// 0x0048 (0x0004)\n"
			"\n"
			"public:\n"
			"\tTMap() :\n"
			"\t\tIndirectData(NULL),\n"
			"\t\tNumBits(0),\n"
			"\t\tMaxBits(0),\n"
			"\t\tFirstFreeIndex(0),\n"
			"\t\tNumFreeIndices(0),\n"
			"\t\tInlineHash(0),\n"
			"\t\tHash(nullptr),\n"
			"\t\tHashCount(0)\n"
			"\t{\n"
			"\n"
			"\t}\n"
			"\n"
			"\tTMap(struct FMap_Mirror& unrealMap) :\n"
			"\t\tIndirectData(NULL),\n"
			"\t\tNumBits(0),\n"
			"\t\tMaxBits(0),\n"
			"\t\tFirstFreeIndex(0),\n"
			"\t\tNumFreeIndices(0),\n"
			"\t\tInlineHash(0),\n"
			"\t\tHash(nullptr),\n"
			"\t\tHashCount(0)\n"
			"\t{\n"
			"\t\t*this = *reinterpret_cast<TMap<TKey, TValue>*>(&unrealMap);\n"
			"\t}\n"
			"\n"
			"\t~TMap() {}\n"
			"\n"
			"public:\n"
			"\tint32_t Num() const\n"
			"\t{\n"
			"\t\treturn Elements.Num();\n"
			"\t}\n"
			"\n"
			"\tint32_t Max() const\n"
			"\t{\n"
			"\t\treturn Elements.Max();\n"
			"\t}\n"
			"\n"
			"\tElementConstReference At(int32_t index) const\n"
			"\t{\n"
			"\t\treturn Elements[index];\n"
			"\t}\n"
			"\n"
			"\tElementReference At(int32_t index)\n"
			"\t{\n"
			"\t\treturn Elements[index];\n"
			"\t}\n"
			"\n"
			"\tIterator begin()\n"
			"\t{\n"
			"\t\treturn Elements.begin();\n"
			"\t}\n"
			"\n"
			"\tIterator end()\n"
			"\t{\n"
			"\t\treturn Elements.end();\n"
			"\t}\n"
			"\n"
			"public:\n"
			"\tElementConstReference operator[](int32_t index) const\n"
			"\t{\n"
			"\t\treturn Elements[index];\n"
			"\t}\n"
			"\n"
			"\tElementReference operator[](int32_t index)\n"
			"\t{\n"
			"\t\treturn Elements[index];\n"
			"\t}\n"
			"\n"
			"\tconst TValue& operator[](const TKey& key) const\n"
			"\t{\n"
			"\t\tfor (const TPair& pair : Elements)\n"
			"\t\t{\n"
			"\t\t\tif (pair.Key == key)\n"
			"\t\t\t{\n"
			"\t\t\t\treturn pair.Value;\n"
			"\t\t\t}\n"
			"\t\t}\n"
			"\t}\n"
			"\n"
			"\tTValue& operator[](const TKey& key)\n"
			"\t{\n"
			"\t\tfor (TPair& pair : Elements)\n"
			"\t\t{\n"
			"\t\t\tif (pair.Key == key)\n"
			"\t\t\t{\n"
			"\t\t\t\treturn pair.Value;\n"
			"\t\t\t}\n"
			"\t\t}\n"
			"\t}\n"
			"\n"
			"\tTMap<TKey, TValue>& operator=(const struct FMap_Mirror& fMap)\n"
			"\t{\n"
			"\t\t*this = *reinterpret_cast<TMap<TKey, TValue>*>(&fMap);\n"
			"\t\treturn *this;\n"
			"\t}\n"
			"};\n";

	const std::string FNameEntry_UPPER =
		"struct FNameEntry\n"
		"{\n"
		"public:\n";

	const std::string FNameEntry_UTF16 =
		"\n"
		"public:\n"
		"\tFNameEntry() : Index(-1) {}\n"
		"\t~FNameEntry() {}\n\n"
		"public:\n"
		"\tint32_t GetIndex() const\n"
		"\t{\n"
		"\t\treturn Index;\n"
		"\t}\n"
		"\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\tstd::wstring ws(Name);\n"
		"\t\tstd::string str(ws.begin(), ws.end());\n"
		"\t\treturn str;\n"
		"\t}\n"
		"\n"
		"\tconst wchar_t* GetWideName() const\n"
		"\t{\n"
		"\t\treturn Name;\n"
		"\t}\n"
		"};\n";

	const std::string FNameEntry_UTF8 =
		"\n"
		"public:\n"
		"\tFNameEntry() : Index(-1) {}\n"
		"\t~FNameEntry() {}\n\n"
		"public:\n"
		"\tint32_t GetIndex() const\n"
		"\t{\n"
		"\t\treturn Index;\n"
		"\t}\n"
		"\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\treturn std::string(Name);\n"
		"\t}\n"
		"\n"
		"\tconst char* GetAnsiName() const\n"
		"\t{\n"
		"\t\treturn Name;\n"
		"\t}\n";

	const std::string FName_UTF16 =
		"struct FName\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = const wchar_t;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\n"
		"private:\n"
		"\tint32_t\t\t\tFNameEntryId;\t\t\t\t\t\t\t\t\t// 0x0000 (0x04)\n"
		"\tint32_t\t\t\tInstanceNumber;\t\t\t\t\t\t\t\t\t// 0x0004 (0x04)\n"
		"\n"
		"public:\n"
		"\tFName() : FNameEntryId(0), InstanceNumber(0) {}\n"
		"\n"
		"\tFName(int32_t id) : FNameEntryId(id), InstanceNumber(0) {}\n"
		"\n"
		"\tFName(const ElementPointer nameToFind) : FNameEntryId(0), InstanceNumber(0)\n"
		"\t{\n"
		"\t\tstatic std::vector<int32_t> nameCache{};\n"
		"\n"
		"\t\tfor (int32_t entryId : nameCache)\n"
		"\t\t{\n"
		"\t\t\tif (Names()->At(entryId))\n"
		"\t\t\t{\n"
		"\t\t\t\tif (!wcscmp(Names()->At(entryId)->Name, nameToFind))\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tFNameEntryId = entryId;\n"
		"\t\t\t\t\treturn;\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\tfor (int32_t i = 0; i < Names()->Num(); i++)\n"
		"\t\t{\n"
		"\t\t\tif (Names()->At(i))\n"
		"\t\t\t{\n"
		"\t\t\t\tif (!wcscmp(Names()->At(i)->Name, nameToFind))\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tnameCache.push_back(i);\n"
		"\t\t\t\t\tFNameEntryId = i;\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\t~FName() {}\n"
		"\n"
		"public:\n"
		"\tstatic class TArray<struct FNameEntry*>* Names()\n"
		"\t{\n"
		"\t\tTArray<FNameEntry*>* GNamesArray = reinterpret_cast<TArray<FNameEntry*>*>(GNames);\n"
		"\t\treturn GNamesArray;\n"
		"\t}\n"
		"\n"
		"\tint32_t GetDisplayIndex() const\n"
		"\t{\n"
		"\t\treturn FNameEntryId;\n"
		"\t}\n"
		"\n"
		"\tconst struct FNameEntry GetDisplayNameEntry() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn *Names()->At(FNameEntryId);\n"
		"\t\t}\n"
		"\n"
		"\t\treturn FNameEntry();\n"
		"\t}\n"
		"\n"
		"\tstruct FNameEntry* GetEntry()\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn Names()->At(FNameEntryId);\n"
		"\t\t}\n"
		"\n"
		"\t\treturn nullptr;\n"
		"\t}\n"
		"\n"
		"\tint32_t GetNumber() const\n"
		"\t{\n"
		"\t\treturn InstanceNumber;\n"
		"\t}\n"
		"\n"
		"\tvoid SetNumber(int32_t newNumber)\n"
		"\t{\n"
		"\t\tInstanceNumber = newNumber;\n"
		"\t}\n"
		"\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn GetDisplayNameEntry().ToString();\n"
		"\t\t}\n"
		"\n"
		"\t\treturn std::string(\"UnknownName\");\n"
		"\t}\n"
		"\n"
		"\tbool IsValid() const\n"
		"\t{\n"
		"\t\tif (FNameEntryId < 0 || FNameEntryId > Names()->Num())\n"
		"\t\t{\n"
		"\t\t\treturn false;\n"
		"\t\t}\n"
		"\n"
		"\t\treturn true;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tstruct FName& operator=(const struct FName& other)\n"
		"\t{\n"
		"\t\tFNameEntryId = other.FNameEntryId;\n"
		"\t\tInstanceNumber = other.InstanceNumber;\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"\tbool operator==(const struct FName& other) const\n"
		"\t{\n"
		"\t\treturn (FNameEntryId == other.FNameEntryId);\n"
		"\t}\n"
		"\n"
		"\tbool operator!=(const struct FName& other) const\n"
		"\t{\n"
		"\t\treturn (FNameEntryId != other.FNameEntryId);\n"
		"\t}\n"
		"};\n";

	const std::string FName_UTF8 =
		"struct FName\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = const char;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\n"
		"private:\n"
		"\tint32_t\t\t\tFNameEntryId;\t\t\t\t\t\t\t\t\t// 0x0000 (0x04)\n"
		"\tint32_t\t\t\tInstanceNumber;\t\t\t\t\t\t\t\t\t// 0x0004 (0x04)\n"
		"\n"
		"public:\n"
		"\tFName() : FNameEntryId(-1), InstanceNumber(0) {}\n"
		"\n"
		"\tFName(int32_t id) : FNameEntryId(id), InstanceNumber(0) {}\n"
		"\n"
		"\tFName(ElementPointer nameToFind) : FNameEntryId(0), InstanceNumber(0)\n"
		"\t{\n"
		"\t\tstatic std::vector<int32_t> nameCache{};\n"
		"\n"
		"\t\tfor (int32_t entryId : nameCache)\n"
		"\t\t{\n"
		"\t\t\tif (Names()->At(entryId))\n"
		"\t\t\t{\n"
		"\t\t\t\tif (!strcmp(Names()->At(entryId)->Name, nameToFind))\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tFNameEntryId = entryId;\n"
		"\t\t\t\t\treturn;\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\tfor (int32_t i = 0; i < Names()->Num(); i++)\n"
		"\t\t{\n"
		"\t\t\tif (Names()->At(i))\n"
		"\t\t\t{\n"
		"\t\t\t\tif (!strcmp(Names()->At(i)->Name, nameToFind))\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tnameCache.push_back(i);\n"
		"\t\t\t\t\tFNameEntryId = i;\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\t~FName() {}\n"
		"\n"
		"public:\n"
		"\tstatic class TArray<struct FNameEntry*>* Names()\n"
		"\t{\n"
		"\t\tTArray<FNameEntry*>* GNamesArray = reinterpret_cast<TArray<FNameEntry*>*>(GNames);\n"
		"\t\treturn GNamesArray;\n"
		"\t}\n"
		"\n"
		"\tint32_t GetDisplayIndex() const\n"
		"\t{\n"
		"\t\treturn FNameEntryId;\n"
		"\t}\n"
		"\n"
		"\tconst struct FNameEntry GetDisplayNameEntry() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn *Names()->At(FNameEntryId);\n"
		"\t\t}\n"
		"\n"
		"\t\treturn FNameEntry();\n"
		"\t}\n"
		"\n"
		"\tstruct FNameEntry* GetEntry()\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn Names()->At(FNameEntryId);\n"
		"\t\t}\n"
		"\n"
		"\t\treturn nullptr;\n"
		"\t}\n"
		"\n"
		"\tint32_t GetNumber() const\n"
		"\t{\n"
		"\t\treturn InstanceNumber;\n"
		"\t}\n"
		"\n"
		"\tvoid SetNumber(int32_t newNumber)\n"
		"\t{\n"
		"\t\tInstanceNumber = newNumber;\n"
		"\t}\n"
		"\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn GetDisplayNameEntry().ToString();\n"
		"\t\t}\n"
		"\n"
		"\t\treturn std::string(\"UnknownName\");\n"
		"\t}\n"
		"\n"
		"\tbool IsValid() const\n"
		"\t{\n"
		"\t\tif (FNameEntryId < 0 || FNameEntryId > Names()->Num())\n"
		"\t\t{\n"
		"\t\t\treturn false;\n"
		"\t\t}\n"
		"\n"
		"\t\treturn true;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tstruct FName& operator=(const struct FName& other)\n"
		"\t{\n"
		"\t\tFNameEntryId = other.FNameEntryId;\n"
		"\t\tInstanceNumber = other.InstanceNumber;\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"\tbool operator==(const struct FName& other) const\n"
		"\t{\n"
		"\t\treturn (FNameEntryId == other.FNameEntryId);\n"
		"\t}\n"
		"\n"
		"\tbool operator!=(const struct FName& other) const\n"
		"\t{\n"
		"\t\treturn (FNameEntryId != other.FNameEntryId);\n"
		"\t}\n"
		"};\n";

	const std::string FString_UTF16 =
		"class FString\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = const wchar_t;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\n"
		"private:\n"
		"\tElementPointer\tArrayData;\t\t\t\t\t\t\t\t\t\t// 0x0000 (0x08)\n"
		"\tint32_t\t\t\tArrayCount;\t\t\t\t\t\t\t\t\t\t// 0x0008 (0x04)\n"
		"\tint32_t\t\t\tArrayMax;\t\t\t\t\t\t\t\t\t\t// 0x000C (0x04)\n"
		"\n"
		"public:\n"
		"\tFString() : ArrayData(nullptr), ArrayCount(0), ArrayMax(0) {}\n"
		"\n"
		"\tFString(ElementPointer other) : ArrayData(nullptr), ArrayCount(0), ArrayMax(0)\n"
		"\t{\n"
		"\t\tArrayMax = ArrayCount = *other ? (wcslen(other) + 1) : 0;\n"
		"\n"
		"\t\tif (ArrayCount > 0)\n"
		"\t\t{\n"
		"\t\t\tArrayData = other;\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\t~FString() {}\n"
		"\n"
		"public:\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\tstd::wstring wideStr(ArrayData);\n"
		"\t\t\tstd::string str(wideStr.begin(), wideStr.end());\n"
		"\t\t\treturn str;\n"
		"\t\t}\n"
		"\n"
		"\t\treturn std::string(\"null\");\n"
		"\t}\n"
		"\n"
		"\tbool IsValid() const\n"
		"\t{\n"
		"\t\treturn (!!ArrayData);\n"
		"\t}\n"
		"\n"
		"\tclass FString& operator=(ElementPointer other)\n"
		"\t{\n"
		"\t\tif (ArrayData != other)\n"
		"\t\t{\n"
		"\t\t\tArrayMax = ArrayCount = *other ? (wcslen(other) + 1) : 0;\n"
		"\n"
		"\t\t\tif (ArrayCount > 0)\n"
		"\t\t\t{\n"
		"\t\t\t\tArrayData = other;\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tbool operator==(const class FString& other)\n"
		"\t{\n"
		"\t\treturn (!wcscmp(ArrayData, other.ArrayData));\n"
		"\t}\n"
		"\n"
		"\tbool operator!=(const class FString& other)\n"
		"\t{\n"
		"\t\treturn (wcscmp(ArrayData, other.ArrayData));\n"
		"\t}\n"
		"};\n";

	const std::string FString_UTF8 =
		"class FString\n"
		"{\n"
		"public:\n"
		"\tusing ElementType = const char;\n"
		"\tusing ElementPointer = ElementType*;\n"
		"\n"
		"private:\n"
		"\tElementPointer\tArrayData;\t\t\t\t\t\t\t\t\t\t// 0x0000 (0x08)\n"
		"\tint32_t\t\t\tArrayCount;\t\t\t\t\t\t\t\t\t\t// 0x0008 (0x04)\n"
		"\tint32_t\t\t\tArrayMax;\t\t\t\t\t\t\t\t\t\t// 0x000C (0x04)\n"
		"\n"
		"public:\n"
		"\tFString() : ArrayData(nullptr), ArrayCount(0), ArrayMax(0) {}\n"
		"\n"
		"\tFString(ElementPointer other) : ArrayData(nullptr), ArrayCount(0), ArrayMax(0)\n"
		"\t{\n"
		"\t\tArrayMax = ArrayCount = *other ? (strlen(other) + 1) : 0;\n"
		"\n"
		"\t\tif (ArrayCount > 0)\n"
		"\t\t{\n"
		"\t\t\tArrayData = other;\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\t~FString() {}\n"
		"\n"
		"public:\n"
		"\tstd::string ToString() const\n"
		"\t{\n"
		"\t\tif (IsValid())\n"
		"\t\t{\n"
		"\t\t\treturn std::string(ArrayData);\n"
		"\t\t}\n"
		"\n"
		"\t\treturn std::string(\"null\");\n"
		"\t}\n"
		"\n"
		"\tbool IsValid() const\n"
		"\t{\n"
		"\t\treturn (!!ArrayData);\n"
		"\t}\n"
		"\n"
		"\tclass FString& operator=(ElementPointer other)\n"
		"\t{\n"
		"\t\tif (ArrayData != other)\n"
		"\t\t{\n"
		"\t\t\tArrayMax = ArrayCount = *other ? (strlen(other) + 1) : 0;\n"
		"\n"
		"\t\t\tif (ArrayCount > 0)\n"
		"\t\t\t{\n"
		"\t\t\t\tArrayData = other;\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\treturn *this;\n"
		"\t}\n"
		"\n"
		"public:\n"
		"\tbool operator==(const class FString& other)\n"
		"\t{\n"
		"\t\treturn (!strcmp(ArrayData, other.ArrayData));\n"
		"\t}\n"
		"\n"
		"\tbool operator!=(const class FString& other)\n"
		"\t{\n"
		"\t\treturn (strcmp(ArrayData, other.ArrayData));\n"
		"\t}\n"
		"};\n";

	const std::string FPointer_Struct =
		"struct FPointer\n"
		"{\n"
		"\tuintptr_t Dummy;\n"
		"};\n";

	const std::string FQWord_Struct =
		"struct FQWord\n"
		"{\n"
		"\tint32_t A;\n"
		"\tint32_t B;\n"
		"};\n";

	const std::string UObject_FunctionDescriptions =
		"\tstatic TArray<class UObject*>* GObjObjects();\n"
		"\n"
		"\tstd::string GetName();\n"
		"\tstd::string GetNameCPP();\n"
		"\tstd::string GetFullName();\n"
		"\tclass UObject* GetPackageObj();\n"
		"\ttemplate<typename T> static T* FindObject(const std::string& objectFullName)\n"
		"\t{\n"
		"\t\tfor (UObject* uObject : *UObject::GObjObjects())\n"
		"\t\t{\n"
		"\t\t\tif (uObject && uObject->IsA(T::StaticClass()))\n"
		"\t\t\t{\n"
		"\t\t\t\tif (uObject->GetFullName() == objectFullName)\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\treturn static_cast<T*>(uObject);\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\treturn nullptr;\n"
		"\t}\n"
		"\ttemplate<typename T> static uint32_t CountObject(const std::string& objectName)\n"
		"\t{\n"
		"\t\tstatic std::map<std::string, int32_t> countCache;\n"
		"\n"
		"\t\tif (countCache.find(objectName) == countCache.end())\n"
		"\t\t{\n"
		"\t\t\tcountCache[objectName] = 0;\n"
		"\n"
		"\t\t\tfor (UObject* uObject : *UObject::GObjObjects())\n"
		"\t\t\t{\n"
		"\t\t\t\tif (uObject && uObject->IsA(T::StaticClass()))\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tif (uObject->GetName() == objectName)\n"
		"\t\t\t\t\t{\n"
		"\t\t\t\t\t\tcountCache[uObject->GetName()]++;\n"
		"\t\t\t\t\t}\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\treturn countCache[objectName];\n"
		"\t}\n"
		"\tstatic class UClass* FindClass(const std::string& classFullName);\n"
		"\ttemplate<typename T> bool IsA()\n"
		"\t{\n"
		"\t\tif (std::is_base_of<UObject, T>::value)\n"
		"\t\t{\n"
		"\t\t\treturn IsA(T::StaticClass());\n"
		"\t\t}\n"
		"\t}\n"
		"\tbool IsA(class UClass* uClass);\n"
		"\tbool IsA(int32_t objInternalInteger);\n\n";

	const std::string UObject_Functions =
		"TArray<class UObject*>* UObject::GObjObjects()\n"
		"{\n"
		"\tTArray<UObject*>* objectArray = reinterpret_cast<TArray<UObject*>*>(GObjects);\n"
		"\treturn objectArray;\n"
		"}\n"
		"\n"
		"std::string UObject::GetName()\n"
		"{\n"
		"\treturn this->Name.ToString();\n"
		"}\n"
		"\n"
		"std::string UObject::GetNameCPP()\n"
		"{\n"
		"\tstd::string nameCPP;\n"
		"\n"
		"\tif (this->IsA(UClass::StaticClass()))\n"
		"\t{\n"
		"\t\tUClass* uClass = static_cast<UClass*>(this);\n"
		"\n"
		"\t\twhile (uClass)\n"
		"\t\t{\n"
		"\t\t\tstd::string className = uClass->GetName();\n"
		"\n"
		"\t\t\tif (className == \"Actor\")\n"
		"\t\t\t{\n"
		"\t\t\t\tnameCPP += \"A\";\n"
		"\t\t\t\tbreak;\n"
		"\t\t\t}\n"
		"\t\t\telse if (className == \"Object\")\n"
		"\t\t\t{\n"
		"\t\t\t\tnameCPP += \"U\";\n"
		"\t\t\t\tbreak;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tuClass = static_cast<UClass*>(uClass->SuperField);\n"
		"\t\t}\n"
		"\t}\n"
		"\telse\n"
		"\t{\n"
		"\t\tnameCPP += \"F\";\n"
		"\t}\n"
		"\n"
		"\tnameCPP += this->GetName();\n"
		"\n"
		"\treturn nameCPP;\n"
		"}\n"
		"\n"
		"std::string UObject::GetFullName()\n"
		"{\n"
		"\tstd::string fullName = this->GetName();\n"
		"\n"
		"\tfor (UObject* uOuter = this->Outer; uOuter; uOuter = uOuter->Outer)\n"
		"\t{\n"
		"\t\tfullName = uOuter->GetName() + \".\" + fullName;\n"
		"\t}\n"
		"\n"
		"\tfullName = this->Class->GetName() + \" \" + fullName;\n"
		"\n"
		"\treturn fullName;\n"
		"}\n"
		"\n"
		"UObject* UObject::GetPackageObj()\n"
		"{\n"
		"\tUObject* uPackage = nullptr;\n"
		"\n"
		"\tfor (UObject* uOuter = this->Outer; uOuter; uOuter = uOuter->Outer)\n"
		"\t{\n"
		"\t\tuPackage = uOuter;\n"
		"\t}\n"
		"\n"
		"\treturn uPackage;\n"
		"}\n"
		"\n"
		"UClass* UObject::FindClass(const const std::string& classFullName)\n"
		"{\n"
		"\tstatic bool initialized = false;\n"
		"\tstatic std::map<const std::string, UClass*> foundClasses{};\n"
		"\n"
		"\tif (!initialized)\n"
		"\t{\n"
		"\t\tfor (UObject* uObject : *UObject::GObjObjects())\n"
		"\t\t{\n"
		"\t\t\tif (uObject)\n"
		"\t\t\t{\n"
		"\t\t\t\tconst std::string objectFullName = uObject->GetFullName();\n"
		"\n"
		"\t\t\t\tif (objectFullName.find(\"Class\") == 0)\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tfoundClasses[objectFullName] = static_cast<UClass*>(uObject);\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\tinitialized = true;\n"
		"\t}\n"
		"\n"
		"\tif (foundClasses.find(classFullName) != foundClasses.end())\n"
		"\t{\n"
		"\t\treturn foundClasses[classFullName];\n"
		"\t}\n"
		"\n"
		"\treturn nullptr;\n"
		"}\n"
		"\n"
		"bool UObject::IsA(class UClass* uClass)\n"
		"{\n"
		"\tfor (UClass* uSuperClass = this->Class; uSuperClass; uSuperClass = static_cast<UClass*>(uSuperClass->SuperField))\n"
		"\t{\n"
		"\t\tif (uSuperClass == uClass)\n"
		"\t\t{\n"
		"\t\t\treturn true;\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\treturn false;\n"
		"}\n"
		"\n"
		"bool UObject::IsA(int32_t objInternalInteger)\n"
		"{\n"
		"\tUClass* uClass = UObject::GObjObjects()->At(objInternalInteger)->Class;\n"
		"\n"
		"\tif (uClass)\n"
		"\t{\n"
		"\t\treturn this->IsA(uClass);\n"
		"\t}\n"
		"\n"
		"\treturn false;\n"
		"}\n\n";

	const std::string UFunction_Functions =
		"UFunction* UFunction::FindFunction(const const std::string& functionFullName)\n"
		"{\n"
		"\tstatic bool initialized = false;\n"
		"\tstatic std::map<const std::string, UFunction*> foundFunctions{};\n"
		"\n"
		"\tif (!initialized)\n"
		"\t{\n"
		"\t\tfor (UObject* uObject : *UObject::GObjObjects())\n"
		"\t\t{\n"
		"\t\t\tif (uObject)\n"
		"\t\t\t{\n"
		"\t\t\t\tconst std::string objectFullName = uObject->GetFullName();\n"
		"\n"
		"\t\t\t\tif (objectFullName.find(\"Function\") == 0)\n"
		"\t\t\t\t{\n"
		"\t\t\t\t\tfoundFunctions[objectFullName] = static_cast<UFunction*>(uObject);\n"
		"\t\t\t\t}\n"
		"\t\t\t}\n"
		"\t\t}\n"
		"\n"
		"\t\tinitialized = true;\n"
		"\t}\n"
		"\n"
		"\tif (foundFunctions.find(functionFullName) != foundFunctions.end())\n"
		"\t{\n"
		"\t\treturn foundFunctions[functionFullName];\n"
		"\t}\n"
		"\n"
		"\treturn nullptr;\n"
		"}\n\n";

	const std::string EEnumFlags =
		"// Function Flags\n"
		"// https://docs.unrealengine.com/en-US/API/Runtime/CoreUObject/UObject/EFunctionFlags/index.html\n"
		"enum EFunctionFlags\n"
		"{\n"
		"\tFUNC_None =                             0x00000000,\n"
		"\tFUNC_Final =                            0x00000001,\n"
		"\tFUNC_RequiredAPI =                      0x00000002,\n"
		"\tFUNC_BlueprintAuthorityOnly =           0x00000004,\n"
		"\tFUNC_BlueprintCosmetic =                0x00000008,\n"
		"\tFUNC_Net =                              0x00000040,\n"
		"\tFUNC_NetReliable =                      0x00000080,\n"
		"\tFUNC_NetRequest =                       0x00000100,\n"
		"\tFUNC_Exec =                             0x00000200,\n"
		"\tFUNC_Native =                           0x00000400,\n"
		"\tFUNC_Event =                            0x00000800,\n"
		"\tFUNC_NetResponse =                      0x00001000,\n"
		"\tFUNC_Static =                           0x00002000,\n"
		"\tFUNC_NetMulticast =                     0x00004000,\n"
		"\tFUNC_UbergraphFunction =                0x00008000,\n"
		"\tFUNC_MulticastDelegate =                0x00010000,\n"
		"\tFUNC_Public =                           0x00020000,\n"
		"\tFUNC_Private =                          0x00040000,\n"
		"\tFUNC_Protected =                        0x00080000,\n"
		"\tFUNC_Delegate =                         0x00100000,\n"
		"\tFUNC_NetServer =                        0x00200000,\n"
		"\tFUNC_HasOutParms =                      0x00400000,\n"
		"\tFUNC_HasDefaults =                      0x00800000,\n"
		"\tFUNC_NetClient =                        0x01000000,\n"
		"\tFUNC_DLLImport =                        0x02000000,\n"
		"\tFUNC_BlueprintCallable =                0x04000000,\n"
		"\tFUNC_BlueprintEvent =                   0x08000000,\n"
		"\tFUNC_BlueprintPure =                    0x10000000,\n"
		"\tFUNC_EditorOnly =                       0x20000000,\n"
		"\tFUNC_Const =                            0x40000000,\n"
		"\tFUNC_NetValidate =                      0x80000000,\n"
		"\tFUNC_AllFlags =                         0xFFFFFFFF\n"
		"};\n"
		"\n"
		"// Proprerty Flags\n"
		"// https://docs.unrealengine.com/en-US/API/Runtime/CoreUObject/UObject/EPropertyFlags/index.html (The ones in this link are UE4 specific, so I had to modify accordingly here.)\n"
		"enum EPropertyFlags\n"
		"{\n"
		"\tCPF_Edit =\t\t\t\t\t\t\t\t0x0000000000000001,\t// Property is user-settable in the editor.\n"
		"\tCPF_Const =\t\t\t\t\t\t\t\t0x0000000000000002,\t// Actor\'s property always matches class\'s default actor property.\n"
		"\tCPF_Input =\t\t\t\t\t\t\t    0x0000000000000004,\t// Variable is writable by the input system.\n"
		"\tCPF_ExportObject =\t\t\t\t\t\t0x0000000000000008,\t// Object can be exported with actor.\n"
		"\tCPF_OptionalParm =\t\t\t\t\t\t0x0000000000000010,\t// Optional parameter (if CPF_Param is set).\n"
		"\tCPF_Net =\t\t\t\t\t\t\t\t0x0000000000000020,\t// Property is relevant to network replication.\n"
		"\tCPF_EditConstArray =\t\t\t\t\t0x0000000000000040,\t// Prevent adding/removing of items from dynamic a array in the editor.\n"
		"\tCPF_Parm =\t\t\t\t\t\t\t\t0x0000000000000080,\t// Function/When call parameter.\n"
		"\tCPF_OutParm =\t\t\t\t\t\t\t0x0000000000000100,\t// Value is copied out after function call.\n"
		"\tCPF_SkipParm =\t\t\t\t\t\t\t0x0000000000000200,\t// Property is a short-circuitable evaluation function parm.\n"
		"\tCPF_ReturnParm =\t\t\t\t\t\t0x0000000000000400,\t// Return value.\n"
		"\tCPF_CoerceParm =\t\t\t\t\t\t0x0000000000000800,\t// Coerce args into this function parameter.\n"
		"\tCPF_Native =\t\t\t\t\t\t\t0x0000000000001000,\t// Property is native: C++ code is responsible for serializing it.\n"
		"\tCPF_Transient =\t\t\t\t\t\t\t0x0000000000002000,\t// Property is transient: shouldn\'t be saved, zero-filled at load time.\n"
		"\tCPF_Config =\t\t\t\t\t\t\t0x0000000000004000,\t// Property should be loaded/saved as permanent profile.\n"
		"\tCPF_Localized =\t\t\t\t\t\t\t0x0000000000008000,\t// Property should be loaded as localizable text.\n"
		"\tCPF_Travel =\t\t\t\t\t\t\t0x0000000000010000,\t// Property travels across levels/servers.\n"
		"\tCPF_EditConst =\t\t\t\t\t\t\t0x0000000000020000,\t// Property is uneditable in the editor.\n"
		"\tCPF_GlobalConfig =\t\t\t\t\t\t0x0000000000040000,\t// Load config from base class, not subclass.\n"
		"\tCPF_Component =\t\t\t\t\t\t\t0x0000000000080000,\t// Property containts component references.\n"
		"\tCPF_NeedCtorLink =\t\t\t\t\t\t0x0000000000400000,\t// Fields need construction/destruction.\n"
		"\tCPF_NoExport =\t\t\t\t\t\t\t0x0000000000800000,\t// Property should not be exported to the native class header file.\n"
		"\tCPF_NoClear =\t\t\t\t\t\t\t0x0000000002000000,\t// Hide clear (and browse) button.\n"
		"\tCPF_EditInline =\t\t\t\t\t\t0x0000000004000000,\t// Edit this object reference inline.\n"
		"\tCPF_EdFindable =\t\t\t\t\t\t0x0000000008000000,\t// References are set by clicking on actors in the editor viewports.\n"
		"\tCPF_EditInlineUse =\t\t\t\t\t\t0x0000000010000000,\t// EditInline with Use button.\n"
		"\tCPF_Deprecated =\t\t\t\t\t\t0x0000000020000000,\t// Property is deprecated.  Read it from an archive, but don\'t save it.\n"
		"\tCPF_EditInlineNotify =\t\t\t\t\t0x0000000040000000,\t// EditInline, notify outer object on editor change.\n"
		"\tCPF_RepNotify =\t\t\t\t\t\t\t0x0000000100000000,\t// Notify actors when a property is replicated\n"
		"\tCPF_Interp =\t\t\t\t\t\t\t0x0000000200000000,\t// interpolatable property for use with matinee\n"
		"\tCPF_NonTransactional =\t\t\t\t\t0x0000000400000000,\t// Property isn\'t transacted\n"
		"\tCPF_EditorOnly =\t\t\t\t\t\t0x0000000800000000,\t// Property should only be loaded in the editor.\n"
		"\tCPF_NoDestructor =\t\t\t\t\t\t0x0000001000000000,\t// No destructor.\n"
		"\tCPF_AutoWeak =\t\t\t\t\t\t\t0x0000004000000000,\t// CPF_ = 0x0000002000000000, ///<.\n"
		"\tCPF_ContainsInstancedReference =        0x0000008000000000,\t// Property contains component refuerences.\n"
		"\tCPF_AssetRegistrySearchable =           0x0000010000000000,\t// Asset instances will add properties with this flag to the asset registry automatically\n"
		"\tCPF_SimpleDisplay =\t\t\t\t\t\t0x0000020000000000,\t// The property is visible by default in the editor details view.\n"
		"\tCPF_AdvancedDisplay =\t\t\t\t\t0x0000040000000000,\t// The property is advanced and not visible by default in the editor details view.\n"
		"\tCPF_Protected =\t\t\t\t\t\t\t0x0000080000000000,\t// Property is protected from the perspective of scrip\n"
		"\tCPF_BlueprintCallable =\t\t\t\t\t0x0000100000000000,\t// MC Delegates only. Property should be exposed for calling in blueprint code.\n"
		"\tCPF_BlueprintAuthorityOnly =\t\t\t0x0000200000000000,\t// MC Delegates only. This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.\n"
		"\tCPF_TextExportTransient =\t\t\t\t0x0000400000000000,\t// Property shouldn\'t be exported to text format (e.g. copy/paste)\n"
		"\tCPF_NonPIEDuplicateTransient =\t\t\t0x0000800000000000,\t// Property should only be copied in PIE.\n"
		"\tCPF_ExposeOnSpawn =\t\t\t\t\t\t0x0001000000000000,\t// Property is exposed on spawn.\n"
		"\tCPF_PersistentInstance =\t\t\t\t0x0002000000000000,\t// A object referenced by the property is duplicated like a component. (Each actor should have an own instance.)\n"
		"\tCPF_UObjectWrapper =\t\t\t\t\t0x0004000000000000,\t// Property was parsed as a wrapper class like TSubclassOf , FScriptInterface etc., rather than a USomething*.\n"
		"\tCPF_HasGetValueTypeHash =\t\t\t\t0x0008000000000000,\t// This property can generate a meaningful hash value.\n"
		"\tCPF_NativeAccessSpecifierPublic =\t\t0x0010000000000000,\t// Public native access specifier.\n"
		"\tCPF_NativeAccessSpecifierProtected =\t0x0020000000000000,\t// Protected native access specifier.\n"
		"\tCPF_NativeAccessSpecifierPrivate =\t\t0x0040000000000000,\t// Private native access specifier.\n"
		"\tCPF_SkipSerialization =\t\t\t\t\t0x0080000000000000\t// Property shouldn\'t be serialized, can still be exported to text.\n"
		"};\n"
		"\n"
		"// https://docs.unrealengine.com/4.26/en-US/API/Runtime/CoreUObject/UObject/EObjectFlags/\n"
		"// Object Flags\n"
		"enum EObjectFlags\n"
		"{\n"
		"\tRF_NoFlags = 0x00000000,\n"
		"\tRF_Public = 0x00000001,\n"
		"\tRF_Standalone = 0x00000002,\n"
		"\tRF_MarkAsNative = 0x00000004,\n"
		"\tRF_Transactional = 0x00000008,\n"
		"\tRF_ClassDefaultObject = 0x00000010,\n"
		"\tRF_ArchetypeObject = 0x00000020,\n"
		"\tRF_Transient = 0x00000040,\n"
		"\tRF_MarkAsRootSet = 0x00000080,\n"
		"\tRF_TagGarbageTemp = 0x00000100,\n"
		"\tRF_NeedInitialization = 0x00000200,\n"
		"\tRF_NeedLoad = 0x00000400,\n"
		"\tRF_KeepForCooker = 0x00000800,\n"
		"\tRF_NeedPostLoad = 0x00001000,\n"
		"\tRF_NeedPostLoadSubobjects = 0x00002000,\n"
		"\tRF_NewerVersionExists = 0x00004000,\n"
		"\tRF_BeginDestroyed = 0x00008000,\n"
		"\tRF_FinishDestroyed = 0x00010000,\n"
		"\tRF_BeingRegenerated = 0x00020000,\n"
		"\tRF_DefaultSubObject = 0x00040000,\n"
		"\tRF_WasLoaded = 0x00080000,\n"
		"\tRF_TextExportTransient = 0x00100000,\n"
		"\tRF_LoadCompleted = 0x00200000,\n"
		"\tRF_InheritableComponentTemplate = 0x00400000,\n"
		"\tRF_DuplicateTransient = 0x00800000,\n"
		"\tRF_StrongRefOnFrame = 0x01000000,\n"
		"\tRF_NonPIEDuplicateTransient = 0x02000000,\n"
		"\tRF_Dynamic = 0x04000000,\n"
		"\tRF_WillBeLoaded = 0x08000000,\n"
		"};\n";
}

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/