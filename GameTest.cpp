#include <iostream>
#include <list>
#include <sys/stat.h>
#include <memory>
#include <cmath>
#include <cfloat>
#include <stack>
#include <stdio.h>

struct ListNode
{
	ListNode *prev;
	ListNode *next;
	ListNode *rand;
	std::string data;
};

// Task 1
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
			strNode.data = "data " + std::to_string(i + 1);
			strNode.next = NULL;

			// Рандомный указатель
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

	void Serialize(FILE *file)
	{
		std::string emptyStr("0\n");
		const char *EndStr = "\n";
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

	void Deserialize(FILE *file)
	{
		struct stat fi;
		stat("text.txt", &fi);

		char *data = new char[fi.st_size];
		if (data)
		{

			fread(data, sizeof(char), fi.st_size, file);

			char *pos(nullptr);
			pos = data;
			char *cursor(nullptr);
			cursor = data;

			auto shift = [&]() {
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
				//***************************
				pos = strstr(cursor, "\n");
				if (!pos)
					break;

				strNew.data.resize((pos - cursor));
				memcpy(&strNew.data[0], cursor, (pos - cursor) * sizeof(char));
				//***************************

				//***************************
				shift();
				if (!pos)
					break;

				strForSearchNext.resize((pos - cursor));
				memcpy(&strForSearchNext[0], cursor, (pos - cursor) * sizeof(char));

				if (strForSearchNext == "0")
					strNew.next = NULL;
				else if (strForRemberNextStruct.empty())
					strForRemberNextStruct = strForSearchNext;
				//***************************

				//***************************
				shift();
				if (!pos)
					break;

				strForSearch.resize((pos - cursor));
				memcpy(&strForSearch[0], cursor, (pos - cursor) * sizeof(char));
				if (strForSearch == "0")
					strNew.prev = NULL;
				else if (strForSearch == ListStrNew.back().data)
					strNew.prev = &ListStrNew.back();
				//***************************

				// ListNode * rand ���������;
				//***************************
				shift();
				if (!pos)
					break;

				strForSearch.resize((pos - cursor));
				memcpy(&strForSearch[0], cursor, (pos - cursor) * sizeof(char));
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
	}

private:
	std::list<ListNode> ListStrNew;
	std::list<ListNode> list;
	int count;
};

// Task 2
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

	char *ret = new char[x + 1];
	if (ret)
	{
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
	}
	return;
}
// ***

// Task 3
void RemoveDups(char *str)
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
// ***

// Task 4
struct list
{
	struct list *next = nullptr;
};

void funcReverse(list *_l)
{
	if (_l == nullptr)
		return;

	struct list *curElement = _l, *nextElement = nullptr, *prevElement = nullptr;

	while (curElement)
	{
		nextElement = curElement->next;
		curElement->next = prevElement;
		prevElement = curElement;
		curElement = nextElement;
	}
}
//****

// Task 5
void findMissNum(int *arr, int size)
{
	if (arr == nullptr || size <= 0)
		return;

	// Сумма/произведение массива
	double sum = 0;
	double multi = 1;

	// Сумма/произведение чисел от 0 до n
	double countSum = (size + 1) * ((size + 1) + 1) / 2;
	double countMulti = 1;

	for (long i = 1; i <= size + 1; ++i)
		countMulti = countMulti * i;

	for (long i = 0; i < size; ++i)
		sum += arr[i];

	bool bflag = false;
	for (long i = 0; i < size; ++i)
	{
		if (arr[i] < 0)
		{
			bflag = true;
			break;
		}

		if (arr[i] != 0)
			multi *= arr[i];
	}

	if (bflag)
		return;

	countSum -= sum;
	countMulti /= multi;

	double diff = sqrt(pow(countSum, 2) - 4 * (countMulti));

	// первое пропущенное
	if (std::isnan(diff)) // Добавил проверку на size=1
		diff = 0;
	else
		diff = (countSum + diff) / 2;
	// второе пропущенное
	countSum = countSum - diff;
}
//***

// Task 6
bool CorrectFunc(const char *str)
{
	if (str == nullptr)
		return false;

	bool ret(true);

	long left = 0, right = strlen(str);

	std::stack<char> sSymbol;

	while (left < right)
	{
		switch (str[left])
		{
		case '{':
			sSymbol.push('{');
			break;
		case '(':
			sSymbol.push('(');
			break;
		case '}':
			if (sSymbol.empty() || sSymbol.top() != '{')
				ret = false;
			else
				sSymbol.pop();
			break;
		case ')':
			if (sSymbol.empty() || sSymbol.top() != '(')
				ret = false;
			else
				sSymbol.pop();
			break;
		default:
			break;
		}

		if (!ret)
			break;

		++left;
	}

	if (sSymbol.empty() && ret)
		return true;
	else
		return false;
}

// Task 7
bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) 
{
    if(!root) 
        return true;
		
    if((minNode && root->val <= minNode->val) ||
	   (maxNode && root->val >= maxNode->val))
   		return false;
   
    return isValidBST(root->left, minNode, root) && 
      	   isValidBST(root->right, root, maxNode);
}
//***
    
bool isValidBST(TreeNode* root) 
{    
    return isValidBST(root, nullptr, nullptr);
}

int main()
{
	std::cout << "Task1 Input integer Number: ";
	std::string strtmp;

	std::getline(std::cin, strtmp);
	ConvertToBin(atoi(strtmp.c_str()));

	std::cout << "\nTask2 Input String: ";
	getline(std::cin, strtmp);
	char *str = const_cast<char *>(strtmp.c_str());
	RemoveDups(str);
	std::cout << "Output String: " << str;
	std::cout << "\n";

	std::unique_ptr<List> Clist(new List);
	if (Clist)
	{
		Clist->SetCount(8);
		Clist->InsertStruct();
	}

	FILE *file(nullptr);
	if (file)
	{
		file = fopen("text.txt", "wb");
		Clist->Serialize(file);

		file = fopen("text.txt", "rb");
		Clist->Deserialize(file);
		file = nullptr;
	}

	// Task4
	list node[10];
	int size = sizeof(node) / sizeof(list);

	for (long i = size - 2; i >= 0; --i)
		node[i].next = &node[i + 1];

	funcReverse(node);

	// Task5
	int arr[9] = {0, 1, 2, 3, 5, 6, 7, 8, 9};
	findMissNum(arr, 9);

	// Task6
	const char *Str = "hello (7*9) * {ss()} ";
	std::cout << CorrectFunc(Str) << std::endl;

	system("pause");
	return 0;
}