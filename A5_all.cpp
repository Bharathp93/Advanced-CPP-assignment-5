#include<iostream>
#include<string>
#include<locale>
#include<vector>
#include<algorithm>
#include<functional>
#include<map>
#include<iterator>
#include<set>
using namespace std;


bool is_palindrome(const string & phrase);
bool Isnotalpha(char i);
void test_is_palindrome();
void test_second_max(std::vector<int> vec);
int countStringLambda(std::vector<std::string>& vec, int n);
int countStringFreeFun(std::vector<std::string>& vec, int n);
int countStringFunctor(std::vector<std::string>& vec, int n);
bool isLessThan(string s, int n);
void charFrequency();
void multisetUsingDefaultComparator();



/*
		1
*/

/*
* passing the strings to be checked if they are palindrome

*/
void test_is_palindrome()
{
	string str_i = string("Was it a car or a cat I saw?");
	string str_u = string("Was it a car or a cat U saw?");
	cout << "the phrase \"" + str_i + "\" is " + (is_palindrome(str_i) ? "" : "not ") + "a palindrome\n";
	cout << "the phrase \"" + str_u + "\" is " + (is_palindrome(str_u) ? "" : "not ") + "a palindrome\n";
}

/*
* to check if character is not alpha

* @param  a char that has to be checked

* @return a boolean value if it a character or not
*/
bool Isnotalpha(char i)
{
	if (!isalpha(i))
		return true;
	return false;
}

/*
* to check if the string is a palindrome or not

* @param  a referrence to a string to be checked

* @return a boolean value if it is a palindrome or not
*/
bool is_palindrome(const string & phrase)
{
	string temp;
	std::remove_copy_if(phrase.begin(), phrase.end(), std::back_inserter(temp), Isnotalpha);
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

	if (std::equal(temp.rbegin(), temp.rend(), temp.begin()))
	{
		return true;
	}
	
	return false;
}

/*
		2
*/

/*
* a function template called second_max to find the second maximum number between start and finish

@param two Iterator type parameters start and finish

@return returns a pair<Iterator, bool>
				pair<finish, false> if empty
				pair<start, false> if all elements are equal
				pair<Iter, true> where Iter points to the element which is second maximum
*/
template <class Iterator>
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish)
{
	Iterator iter;
	Iterator iter1 = start;
	Iterator temp = start;
	if (start == finish)
	{
		return std::make_pair(finish, false);
	}
	else
	{
		while (start != finish)
		{
			if (*start > *iter1)
			{
				iter = iter1;
				iter1 = start;
			}
			start++;
		}
		if (iter1 == temp)
		{
			return std::make_pair(iter1, false);
		}
		else
			return std::make_pair(iter, true);
	}
}

/*
* a function that specifies if the vector has equal elements, no elements or gives the secon 
	maximum in the vector

@param the vector to be checked

*/
void test_second_max(std::vector<int> vec)
{
	auto retval = second_max(vec.begin(), vec.end());
	if (retval.second)
	{
		cout << "The second largest element in vec is " << *retval.first << endl;
	}
	else
	{
		if (retval.first == vec.end())
			cout << "List empty, no elements\n";
		else
			cout << "Container's elements are all equal to " << *retval.first << endl;
	}
}




/*
		3
*/


/*
* to check how many strings in the vector are lesser than the value n in length using a lambda function in count_if

* @param  a vector of strings to be checked
*@param an integer n with which the string lengths have to be compared

* @return a integer value of the number strings that satisfy the condition
*/

int countStringLambda(std::vector<std::string>& vec, int n)
{
	int count = std::count_if(vec.begin(), vec.end(), [&](string& s)->bool
	{
		if ((int)s.length() < n)
			return true;
		else
			return false;
	});
	return count;
}

/*
* to check how many strings in the vector are lesser than the value n in length using a function in count_if

* @param  a vector of strings to be checked
*@param an integer n with which the string lengths have to be compared

* @return a integer value of the number strings that satisfy the condition
*/
int countStringFreeFun(std::vector<std::string>& vec, int n)
{
	int count = std::count_if(vec.begin(), vec.end(), std::bind(isLessThan, std::placeholders::_1, n));
	return count;
}

/*
* to check if the length of the string is less than n

* @param  the string to be checked
*@param an integer n with which the string lengths have to be compared

* @return a boolean value that tells if it is less or not
*/
bool isLessThan(string s, int n)
{
	if ((int)s.length() < n)
		return true;
	else
		return false;
}


/*
* a struct to check if the incoming string is lesser that a perticular value in length

@param n is the value that is passed through a constructor
@param string is the string to be checked

@return boolean value that specifes if the string's length is less than n
*/
struct lessthan {
public:
	int n;
	lessthan(int n) : n(n) {};
	bool operator()(string s) {
		if ((int)s.length() < n)
			return true;
		else
			return false;
	}
};


/*
* to check how many strings in the vector are lesser than the value n in length using a functor in count_if

* @param  a vector of strings to be checked
*@param an integer n with which the string lengths have to be compared

* @return a integer value of the number strings that satisfy the condition
*/
int countStringFunctor(std::vector<std::string>& vec, int n)
{
	int count = std::count_if(vec.begin(), vec.end(), lessthan(n));
	return count;
}


/*
		4
*/


/*
* to compute the frequency of characters in a user input and store it in a map and display

*/
void charFrequency()
{
	string input;
	cout << "Enter one or more lines of text" << endl;
	cout << "To end input press Ctrl-Z in Windows and Ctrl-D in Linux" << endl;
	while (!cin.eof())
	{
		string line;
		getline(cin, line);
		input = input + " " + line;
	}
	string temp;
	std::remove_copy_if(input.begin(), input.end(), std::back_inserter(temp), isspace);
	std::transform(temp.begin(), temp.end(), temp.begin(), tolower);

	std::map<char, int> mymap;
	for_each(temp.begin(), temp.end(), [&](char c)
	{
		if (mymap.find(c) != mymap.end())
			mymap.find(c)->second = mymap.find(c)->second + 1;
		else
			mymap.insert(std::pair<char, int>(c, 1));

	});

	for_each(mymap.begin(), mymap.end(), [](pair<char, int> p)
	{
		cout << p.first << " " << p.second << endl;
	});


}

/*
		5
*/


/*
* a struct to specify the "compare" attribute of the multiset<> on what has to be done with the data order

* @param  two strings lhs and rhs to be compared

* @return a boolean value that specifies if lhs comes before rhs or not
*/
struct compare {
	bool operator()(std::string lhs,
		std::string rhs) const {
		if (lhs.length() < rhs.length())
			return true;
		else if (lhs.length() == rhs.length())
		{
			for (int i = 0; i < (int)lhs.length(); i++)
			{
				if (lhs[i] < rhs[i])
					return true;
				if (lhs[i] > rhs[i])
					return false;
			}
			return false;
		}
		else
			return false;
	}
};

/*
* to arrange the strings in a vector in lexological order and in the increasing order of lengths at the same time
	using multiset<>
*/
void multisetUsingDefaultComparator()
{
	std::multiset<string, compare> gibberish;
	vector<string> vec = { "C","BB","A","CC","A","B","BB","A","D","CC","DDD","AAA" };
	copy(vec.begin(), vec.end(), std::inserter(gibberish, gibberish.begin()));
	ostream_iterator<string> out(std::cout, " ");
	copy(gibberish.begin(), gibberish.end(), out);
}



int main()
{
	//problem 1
	test_is_palindrome();
	cout << "\n";

	//problem 2
	std::vector<int> v1{ 1 };
	test_second_max(v1);

	std::vector<int> v2{ 1,1};
	test_second_max(v2);

	std::vector<int> v3{ 1,1,3,3,7,7 };
	test_second_max(v3);
	cout << "\n";

	//problem 3
	std::vector<std::string> vecstr
	{
		"count_if" , "Returns", "the", "number", "of", "elements", "in", "the",
		"range", "[first", "last)", "for", "which", "pred", "is", "true."
	};
	cout << countStringLambda(vecstr, 5) << endl;
	cout << countStringFreeFun(vecstr, 5) << endl;
	cout << countStringFunctor(vecstr, 5) << endl;
	cout << "\n";

	//problem 4
	charFrequency();
	cout << "\n";

	//problem 5
	multisetUsingDefaultComparator();
	cout << "\n";
	system("pause");
	return 0;

}