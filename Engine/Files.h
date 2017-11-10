#pragma once
#include <fstream>
#include <string>

using namespace std;
class FileDump {
public:
	bool Exists(const char *fileName);
	bool Exists(const std::string fileName);
	bool Create(const char *fileName);
	bool Create(const std::string fileName);
	bool Open(const char *fileName);
	bool Open(const std::string fileName);
	void Close();
	template <typename T>
	void DumpArray(T *arr, int nElements);
	template <typename T>
	void FillArray(T * arr, int nElements);
private:
	std::fstream file;
};


inline bool FileDump::Exists(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

inline bool FileDump::Exists(const std::string fileName)
{
	return Exists(fileName.c_str());
}

inline bool FileDump::Create(const char * fileName)
{
	std::ifstream infile;
	infile.open(fileName, std::ios::out);
	return infile.is_open();
}

inline bool FileDump::Create(const std::string fileName)
{
	return Create(fileName.c_str());
}

inline bool FileDump::Open(const char * fileName)
{
	file.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
	return file.is_open();
}

inline bool FileDump::Open(const std::string fileName)
{
	return Open(fileName.c_str());
}

inline void FileDump::Close()
{
	file.close();
}

template<typename T>
inline void FileDump::DumpArray(T *arr, int nElements)
{
	int scale = sizeof(T) / sizeof(char);
	for (int i = 0; i < nElements * scale; i++) {
		file.put((reinterpret_cast<char *>(arr))[i]);
	}
}

template<typename T>
inline void FileDump::FillArray(T * arr, int nElements)
{
	int scale = sizeof(T) / sizeof(char);
	for (int i = 0; i < nElements * scale; i++) {
		file.get((reinterpret_cast<char *>(arr))[i]);
	}
}
