#pragma once
#include <fstream>
#include <string>

using namespace std;
class FileDump {
public:
	bool Exists(const char *fileName);
	bool Create(const char *fileName);
	bool Open(const char *fileName);
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

inline bool FileDump::Create(const char * fileName)
{
	std::ofstream outfile;
	outfile.open(fileName, std::ios_base::out);
	return outfile.is_open();
}

inline bool FileDump::Open(const char * fileName)
{
	file.open(fileName, std::ios::binary | std::ios::in | std::ios::out);
	return file.is_open();
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
