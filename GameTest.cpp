#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <sys/stat.h>
#include <memory>
struct ListNode 
{
	ListNode * prev;
	ListNode * next;
	ListNode * rand;
	std::string data;
};

class List 
{
public:
	void SetCount(const int count)
	{
		this->count = count;
	}
	
	void InsertStruct()
	{
		ListNode strNode;
		strNode.data = "data 0";
		strNode.prev = NULL;
		strNode.next = NULL;
		strNode.rand = NULL;
		list.push_back(strNode);

		for (long i = 0; i < count; ++i)
		{
			strNode.prev = &list.back();
			strNode.data = "data " + std::to_string(i+1);
			strNode.next = NULL;

			// Рандомный элемент
			if (i == 4)
			{
				auto itt = list.begin();
				std::advance(itt, 3);
				strNode.rand = itt->prev;
			}
			else
				strNode.rand = NULL;

			list.push_back(strNode);
			auto itt = list.begin();
			std::advance(itt, i);
			itt->next = &list.back();
		}
	}

	void Serialize(FILE * file) 
	{
		std::string emptyStr("0\n");
		const char* EndStr = "\n";
		for (auto &itt : list)
		{
			fwrite(itt.data.c_str(), itt.data.size(), sizeof(char), file);
			fwrite(EndStr, strlen(EndStr), sizeof(char), file);

			if (itt.next != nullptr)
			{
				fwrite(itt.next->data.c_str(), itt.next->data.size(), sizeof(char), file);
				fwrite(EndStr, strlen(EndStr), sizeof(char), file);
			}
			else
				fwrite(emptyStr.c_str(), emptyStr.size(), sizeof(char), file);

			if (itt.prev != nullptr)
			{
				fwrite(itt.prev->data.c_str(), itt.prev->data.size(), sizeof(char), file);
				fwrite(EndStr, strlen(EndStr), sizeof(char), file);
			}
			else
				fwrite(emptyStr.c_str(), emptyStr.size(), sizeof(char), file);

			if (itt.rand != nullptr)
			{
				fwrite(itt.rand->data.c_str(), itt.rand->data.size(), sizeof(char), file);
				fwrite(EndStr, strlen(EndStr), sizeof(char), file);
			}
			else
				fwrite(emptyStr.c_str(), emptyStr.size(), sizeof(char), file);
		}
		fclose(file);
	}

	void Deserialize(FILE * file) 
	{
		// Определили размер
		struct stat fi;
		stat("text.txt", &fi);
		fi.st_size;
		char* data = new char[fi.st_size];

		// Считали файл
		fread(data, sizeof(char), fi.st_size, file);

		char* pos(nullptr);
		pos = data;
		char* cursor(nullptr);
		cursor = data;

		// Сдвиг по файлу
		auto shift = [&]()
		{
			cursor = pos + 1;
			pos = strstr(cursor, "\n");
		};

		ListNode strNew;
		std::string strForSearch;
		std::string strForSearchNext;
		std::string strForRemberNextStruct;
		long iShift(0);

		while (pos != NULL || (cursor - data) >= fi.st_size)
		{
			// ListNode data заполняем;
			//***************************	
			pos = strstr(cursor, "\n");
			if (!pos)
				break;

			strNew.data.resize((pos - cursor));
			memcpy_s(&strNew.data[0], (pos - cursor) * sizeof(char), cursor, (pos - cursor) * sizeof(char));
			//***************************

			// ListNode * next заполняем;
			//***************************
			shift();
			if (!pos)
				break;

			strForSearchNext.resize((pos - cursor));
			memcpy_s(&strForSearchNext[0], (pos - cursor) * sizeof(char), cursor, (pos - cursor) * sizeof(char));

			if (strForSearchNext == "0")
				strNew.next = NULL;
			else if (strForRemberNextStruct.empty())
				strForRemberNextStruct = strForSearchNext;// Заполним позже
			//***************************

			// ListNode * prev заполняем;
			//***************************
			shift();
			if (!pos)
				break;

			strForSearch.resize((pos - cursor));
			memcpy_s(&strForSearch[0], (pos - cursor) * sizeof(char), cursor, (pos - cursor) * sizeof(char));
			if (strForSearch == "0")
				strNew.prev = NULL;
			else if (strForSearch == ListStrNew.back().data)
				strNew.prev = &ListStrNew.back();
			//***************************

			// ListNode * rand заполняем;
			//***************************
			shift();
			if (!pos)
				break;

			strForSearch.resize((pos - cursor));
			memcpy_s(&strForSearch[0], (pos - cursor) * sizeof(char), cursor, (pos - cursor) * sizeof(char));
			if (strForSearch == "0")
				strNew.rand = NULL;
			else
			{
				for (auto &itt : ListStrNew)
				{
					if (strForSearch == itt.data)
						strNew.rand = &itt;
				}
			}
			//***************************
			ListStrNew.push_back(strNew);

			// Вернулись, чтобы next, предыдущей итерации ссылался на текущую
			if (strNew.data == strForRemberNextStruct)
			{
				auto itt = ListStrNew.begin();
				std::advance(itt, iShift);
				itt->next = &ListStrNew.back();
				strForRemberNextStruct = strForSearchNext;
				++iShift;
			}
			cursor = pos + 1;
		}

		fclose(file);
		delete[] data;
		data = nullptr;
	}
private:
	std::list<ListNode> ListStrNew;
	std::list<ListNode> list;
	int count;
};


void ConvertToBin(long num)
{
	bool m_bCountNegative(false);

	if (num < 0)
	{
		m_bCountNegative = true;
		num = -num;
	}
	else if (num == 0)
	{
		std::cout << "Incorrect Count";
		return;
	}

	long x = (long)trunc(log2(num)) + 1;
	x = m_bCountNegative ? x + 1 : x;

	char* ret = new char[x + 1];
	ret[x] = '\0';

	while (num != 0)
	{
		if (x < 0)
			break;

		if (num % 2 == 1)
			ret[x - 1] = '1';
		else
			ret[x - 1] = '0';

		--x;
		num /= 2;
	}

	if (m_bCountNegative)
		ret[0] = '-';

	//printf("%s", ret);
	std::cout << "Output integer Number: " << ret;

	delete[] ret;
	ret = nullptr;

	return;
}

void RemoveDups(char* str)
{
	for (long i = 1; i < (long)strlen(str); ++i)
	{
		if (str[i - 1] == str[i])
		{
			memmove(&str[i - 1], &str[i], strlen(str) - (i - 1));
			--i;
		}
	}
	//printf("%s", str);
}

int main()
{
	std::cout << "Task1 Input integer Number: ";
	std::string strtmp;

	std::getline(std::cin, strtmp);
	ConvertToBin(atoi(strtmp.c_str()));

	std::cout << "\nTask2 Input String: ";
	getline(std::cin, strtmp);
	char* str = const_cast<char*>(strtmp.c_str());
	RemoveDups(str);
	std::cout << "Output String: " << str;
	std::cout << "\n";

	std::unique_ptr <List> Clist(new List);
	Clist->SetCount(8);
	Clist->InsertStruct();

	FILE * file(nullptr);
	// Сериализация
	fopen_s(&file, "text.txt", "wb");
	Clist->Serialize(file);

	// Десериализация
	fopen_s(&file, "text.txt", "rb");
	Clist->Deserialize(file);

	file = nullptr;

	system("pause");
	return 0;
}