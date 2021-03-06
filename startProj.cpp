#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
#define NUM_LINES_FOR_TICKET 15

//Struct decleration
struct Contact
{
	string name;
	long id;
	string phone;
	string email;
};
struct Date
{
	int day;
	int month;
	int year;
};
struct Ticket
{
	Contact contact;
	Date date;
	string ProblemCategory;
	string SubCategory;
	string description;
	string status;
	string StakeHolder;
	int TicketNumber;
	string comments;
	string severity;
};
struct ContactCounter
{
	Contact contact;
	int counter;
};

//Copy Functions
void copyContacts(Contact &c1, const Contact c2)
//"Function copy c2 to c1"
{
	c1.email = c2.email;
	c1.id = c2.id;
	c1.name = c2.name;
	c1.phone = c2.phone;
}
void copyDate(Date &d1, const Date d2)
{
	d1.day = d2.day;
	d1.month = d2.month;
	d1.year = d2.year;
}
void copyTickets(Ticket &t1, const Ticket t2)
{
	copyContacts(t1.contact, t2.contact);
	copyDate(t1.date, t2.date);
	t1.comments = t2.comments;
	t1.description = t2.description;
	t1.ProblemCategory = t2.ProblemCategory;
	t1.severity = t2.severity;
	t1.StakeHolder = t2.StakeHolder;
	t1.status = t2.status;
	t1.SubCategory = t2.SubCategory;
	t1.TicketNumber = t2.TicketNumber;
}

//Count Functions
int countTickets(const string fileName)
{
	int count = 0;
	string line;
	ifstream fs(fileName);
	if (!fs.is_open())
		return 0;
	while (!fs.eof())
	{
		getline(fs,line);
		++count;
	}
	return count / NUM_LINES_FOR_TICKET; //every 15 lines is 1 ticket
}

//Change functions
void ChangeTicketStatus(Ticket *arr, int size, int i)
{
	int choose;
	cout << "\n\nWitch status do u want do change?\n1) Open\t2) In handling\t3) Close\n";
	cin >> choose;
	if (choose == 1)
		arr[i].status = "Open";
	else if (choose == 2)
		arr[i].status = "In handling";
	else if (choose == 3)
		arr[i].status = "Close";
	else
		cout << "Invalid input\n";
	if(choose==1 || choose ==2 || choose==3)
		cout<<"Status changed successfully\n\n";
}

//Print Functions
void printContact(const Contact c)
{
	cout << "Name: " << c.name << "                 ID: " << c.id << endl
		<< "Phone number: " << c.phone << "\tEmail: " << c.email << endl;
}
void printDate(const Date d)
{
	cout << "Date: " << d.day << "/" << d.month << "/" << d.year << endl;
}
void printTicket(const Ticket t)
{
	printContact(t.contact);
	cout << "Problem category: " << t.ProblemCategory << ", " << t.SubCategory << endl
		<< "Problem description: " << t.description << endl;
	printDate(t.date);
	cout << "Status: " << t.status << "\nStakeholder: " << t.StakeHolder << "\nTicket number: " << t.TicketNumber <<
		"\nComments: " << t.comments << "\nSeverity: " << t.severity << endl << endl;
}
void printTicketNoContact(const Ticket t)
{
	cout << "Problem category: " << t.ProblemCategory << ", " << t.SubCategory << endl
		<< "Problem description: " << t.description << endl;
	printDate(t.date);
	cout << "Status: " << t.status << "\nStakeholder: " << t.StakeHolder << "\nTicket number: " << t.TicketNumber <<
		"\nComments: " << t.comments << "\nSeverity: " << t.severity << endl << endl;
}
bool CheckLogin(string userName, string passWord, const string fileName)
{
	string line1, line2;
	ifstream fs(fileName);
	while (!fs.eof())
	{
		getline(fs, line1);
		getline(fs, line2);
		if (line1 == userName && line2 == passWord)
		{
			fs.close();
			return true;
		}
	}
	fs.close();
	return false;
}
void Login(const string fileName)
{
	string userName, passWord;
	cout << "\t--Please Log in the System -\n\n";
	do
	{
		cout << "Username:  ";
		cin >> userName;
		cout << "Password:  ";
		cin >> passWord;
	} while (!CheckLogin(userName,passWord,fileName));
	
}
void printMenu()
{
	cout << "\t--==== \"Suppurt My Phone\" Menu ====--\n\n1) New ticket\t        2) Sort ticket\n3) Analysis system\t4) Show all contact previous tickets\n";
	cout << "5) Change ticket's status\n0) Exit\n\n";
		
}
void printProblemCategories()
{
	cout << "1) Internet\t2) Hardware\n3) Calls\t4) Massages\n";
}

//Get Functions
Contact getContact()
{
	string temp;
	Contact newContact;
	cout << "Enter contact name: ";
	getline(cin, newContact.name);
	getline(cin, newContact.name);
	cout << "Enter "<<newContact.name<< "'s ID: ";
	getline(cin, temp);
	// This code converts from string to number.
	stringstream myStream(temp);
	myStream >> newContact.id;
	
	cout << "Enter " << newContact.name << "'s phone number: ";
	getline(cin, newContact.phone);
	cout << "Enter " << newContact.name << "'s email: ";
	getline(cin, newContact.email);
	return newContact;
}
Date getDate()
{
	Date date;
	cout << "Enter day: ";
	cin >> date.day;
	cout << "Enter month: ";
	cin >> date.month;
	cout << "Enter year: ";
	cin >> date.year;
	return date;
}
Ticket getFullTicket(int tickNumber,bool ContExist,Contact contact)
{
	Ticket ticket;
	ticket.TicketNumber = tickNumber;
	int choose,subchoose;
	if(ContExist==false)
		copyContacts(ticket.contact, getContact());
	else
		copyContacts(ticket.contact, contact);

	copyDate(ticket.date, getDate());
	cout << "Choose problem category:" << endl;
	printProblemCategories();
	cin >> choose;
	cout << "Choose sub category:" << endl;
	switch (choose)
	{
		case(1):
		{
			ticket.ProblemCategory = "Internet";
			cout << "1) Slow connection\n2) Capasity connection\n3) Inappropriate content\n";
			cin >> subchoose;
			if (subchoose == 1)
				ticket.SubCategory = "Slow connection";
			else if (subchoose == 2)
				ticket.SubCategory = "Capasity connection";
			else
				ticket.SubCategory = "Inappropriate content";
			break;
		}
		case(2):
		{
			ticket.ProblemCategory = "Hardware";
			cout << "1) Battery problem\n2) Broken device\n3) Camera problem\n";
			cin >> subchoose;
			if (subchoose == 1)
				ticket.SubCategory = "Battery problem";
			else if (subchoose == 2)
				ticket.SubCategory = "Broken device";
			else
				ticket.SubCategory = "Camera problem";
			break;
		}
		case(3):
		{
			ticket.ProblemCategory = "Calls";
			cout << "1) Signal problem\n2) Travel package\n";
			cin >> subchoose;
			if (subchoose == 1)
				ticket.SubCategory = "Signal problem";
			else
				ticket.SubCategory = "Travel package";
			break;
		}
		case(4):
		{
			ticket.ProblemCategory = "Massages";
			cout << "1) MMS problems\n2) SMS problems\n";
			cin >> subchoose;
			ticket.SubCategory = subchoose == 1 ? "MMS problems" : "SMS problems";
			break;
		}
		default:
			cout << "Invalid input\n";
	}

	cout << "Enter description of the problem\n";
	getline(cin, ticket.description);//get the \n from prev input
	getline(cin, ticket.description);
	cout << "Enter Status\n1)Open\n2)In handling\n3)Close\n";
	cin >> choose;
	if (choose == 1)
		ticket.status = "Open";
	else
		ticket.status = choose == 2 ? "In handling" : "Close";
	
	cout << "Enter StakeHolder\n1)Contact service \n2)Technical support\n";
	cin >> choose;
	ticket.StakeHolder = choose == 1 ? "Contact service" : "Technical support";
	cout << "Enter comments\n";
	getline(cin ,ticket.comments);//get the \n from prev input
	getline(cin, ticket.comments);
	cout << "Enter Severity\n1)Urgent\n2)Not urgent\n";
	cin >> choose;
	ticket.severity = choose == 1 ? "Urgent" : "Not urgent";

	return ticket;
}

//Get Exist
bool IsContactExist(const Ticket *arr, int size, int id)
{
	for (int i = 0; i < size; ++i)
		if (arr[i].contact.id == id)
			return true;
	return false;
}
Contact GetContactExist(const Ticket *arr, int size, int id)
{
	int i;
	for (i = 0; i < size; ++i)
		if (arr[i].contact.id == id)
			return arr[i].contact;
	return arr[i - 1].contact;
}
void printPrevioustickets(const Ticket *arr, int size, Contact contact)
{
	int count = 0, i;
	cout << "\t--== Previous tickets for the following contact ==--\n\n";
	printContact(contact);
	cout << endl << endl;
	for (i = 0; i < size; ++i)
	{
		if (arr[i].contact.id == contact.id)
		{
			cout << "\t--=== Ticket number " << count+1 << " ===--\n";
			printTicketNoContact(arr[i]);
			++count;
		}
		if (!count)
			cout << "No previous tickets\n";
	}
}
int IndexTicketNumberExist(const Ticket *arr, int size, int num)
{
	//Function returns the index of the ticket in arr, if doesnt exist returns -1
	for (int i = 0; i < size; ++i)
		if (arr[i].TicketNumber == num)
			return i;
	return -1;
}
bool IsContExist(const ContactCounter *arr, int size, int id)
{
	if (size == 0)
		return false;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i].contact.id == id)
			return true;
	}
	return false;
}

//Init Functions
void InitArr(Ticket *&arr,int size,const string fileName)
{
	if (!size)
		return;
	arr = new Ticket[size];
	string line;
	ifstream fs(fileName);
	for (int i = 0; i < size; ++i)
	{
		getline(fs, line);
		arr[i].contact.name = line;
		getline(fs, line);
		arr[i].contact.id = atoi(line.c_str());
		getline(fs, line);
		arr[i].contact.phone= line;
		getline(fs, line);
		arr[i].contact.email = line;
		getline(fs, line);
		arr[i].ProblemCategory = line;
		getline(fs, line);
		arr[i].SubCategory = line;
		getline(fs, line);
		arr[i].description = line;
		getline(fs, line);
		arr[i].date.day = atoi(line.c_str());
		getline(fs, line);
		arr[i].date.month = atoi(line.c_str());
		getline(fs, line);
		arr[i].date.year = atoi(line.c_str());
		getline(fs, line);
		arr[i].status = line;
		getline(fs, line);
		arr[i].StakeHolder = line;
		getline(fs, line);
		arr[i].comments = line;
		getline(fs, line);
		arr[i].severity = line;
		getline(fs, line);
		arr[i].TicketNumber = atoi(line.c_str());
	}
	fs.close();
}
void AddNewTicket(Ticket *&arr, int &size,const Ticket ticket)
{
	Ticket *temp = new Ticket[size + 1];
	for (int i = 0; i < size; ++i)
		copyTickets(temp[i], arr[i]);
	copyTickets(temp[size], ticket);
	++size;
	arr = temp;
}
void WriteToFile(const Ticket *arr, int size, const string FileName)
{
	ofstream of;
	of.open(FileName);
	for (int i = 0; i < size; ++i)
	{
		of << arr[i].contact.name << endl;
		of << arr[i].contact.id << endl;
		of << arr[i].contact.phone << endl;
		of << arr[i].contact.email << endl;
		of << arr[i].ProblemCategory << endl;
		of << arr[i].SubCategory << endl;
		of << arr[i].description << endl;
		of << arr[i].date.day << endl;
		of << arr[i].date.month << endl;
		of << arr[i].date.year << endl;
		of << arr[i].status << endl;
		of << arr[i].StakeHolder << endl;
		of << arr[i].comments << endl;
		of << arr[i].severity << endl;
		of << arr[i].TicketNumber << endl;
	}
	of.close();
}
void AddNewContact(ContactCounter *&arr, int &size, const Contact contact)
{
	ContactCounter *temp = new ContactCounter[size + 1];
	for (int i = 0; i < size; ++i)
		copyContacts(temp[i].contact, arr[i].contact);
	copyContacts(temp[size].contact, contact);
	++size;
	arr = temp;
}
void InitContactsArr(ContactCounter *&Carr,int &Csize, const Ticket *Tarr, const int size)
{
	if (!size)
		return;
	int i;
	ContactCounter *temp = NULL;
	for (i = 0; i < size; ++i)
		if (!IsContExist(temp, Csize, Tarr[i].contact.id))
		{
			AddNewContact(temp, Csize, Tarr[i].contact);
			temp[i].counter = 0;
		}		
	Carr = temp;
}

//Sort Functions
void SortByStatus(const Ticket *arr, int size) 
{
	if (size == 0)
	{
		cout << "No Tickets to show\n";
		return;
	}
	for (int i = 0; i < size; i++) 
	{
		if (arr[i].status == "Open")
			printTicket(arr[i]);
	}
	for (int i = 0; i < size; i++) {
		if (arr[i].status == "In handling")
			printTicket(arr[i]);
	}
	for (int i = 0; i < size; i++) {
		if (arr[i].status == "Close")
			printTicket(arr[i]);
	}
}
void SortBySeverity(const Ticket *arr, int size) 
{
	if (size == 0)
	{
		cout << "No Tickets to show\n";
		return;
	}
	for (int i = 0; i < size; i++) {
		if (arr[i].severity == "Urgent")
			printTicket(arr[i]);
	}
	for (int i = 0; i < size; i++) {
		if (arr[i].severity == "Not urgent")
			printTicket(arr[i]);
	}
}
void SortByID(const Ticket *arr, int size) {
	if (size == 0)
	{
		cout << "No Tickets to show\n";
		return;
	}
	Ticket *tmpArr = new Ticket[size];
	Ticket topTicket;
	int tmpSize = size;
	for (int i = 0; i<size; i++)
		copyTickets(tmpArr[i], arr[i]);
	for (int i = 0; i<size; i++) {
		topTicket = tmpArr[0];
		for (int j = 0; j<tmpSize; j++)
			topTicket = topTicket.contact.id<tmpArr[j].contact.id ? topTicket : tmpArr[j];
		printTicket(topTicket);
		Ticket *copyArr = new Ticket[tmpSize];
		for (int j = 0; j<tmpSize; j++)
			copyTickets(copyArr[j], tmpArr[j]);
		delete[](tmpArr);
		tmpArr = new Ticket[--tmpSize];
		for (int j = 0, tmpIndex = 0; j<tmpSize + 1; j++) {
			if (copyArr[j].contact.id != topTicket.contact.id)
				copyTickets(tmpArr[tmpIndex++], copyArr[j]);
		}
	}
}
void SortByNumber(const Ticket *arr, int size) 
{
	if (size == 0)
	{
		cout << "No Tickets to show\n";
		return;
	}
	Ticket *tmpArr = new Ticket[size];
	Ticket topTicket;
	int tmpSize = size;
	for (int i = 0; i<size; i++)
		copyTickets(tmpArr[i], arr[i]);
	for (int i = 0; i<size; i++) {
		topTicket = tmpArr[0];
		for (int j = 0; j<tmpSize; j++)
			topTicket = topTicket.TicketNumber<tmpArr[j].TicketNumber ? topTicket : tmpArr[j];
		printTicket(topTicket);
		Ticket *copyArr = new Ticket[tmpSize];
		for (int j = 0; j<tmpSize; j++)
			copyTickets(copyArr[j], tmpArr[j]);
		delete[](tmpArr);
		tmpArr = new Ticket[--tmpSize];
		for (int j = 0, tmpIndex = 0; j<tmpSize + 1; j++) {
			if (copyArr[j].TicketNumber != topTicket.TicketNumber)
				copyTickets(tmpArr[tmpIndex++], copyArr[j]);
		}
	}
}
Ticket NewestTicket(const Ticket t1, const Ticket t2) {
	if (t1.date.year>t2.date.year) {
		return t1;
	}
	else if (t2.date.year>t1.date.year) {
		return t2;
	}
	else {
		if (t1.date.month>t2.date.month) {
			return t1;
		}
		else if (t2.date.month>t1.date.month) {
			return t2;
		}
		else {
			if (t1.date.day>t2.date.day) {
				return t1;
			}
			else if (t2.date.day>t1.date.day) {
				return t2;
			}
		}
	}
	return t1;
}
void SortByDate(const Ticket *arr, int size) 
{
	if (size == 0)
	{
		cout << "No Tickets to show\n";
		return;
	}
	Ticket *tmpArr = new Ticket[size];
	Ticket topTicket;
	int tmpSize = size;
	for (int i = 0; i<size; i++)
		copyTickets(tmpArr[i], arr[i]);
	for (int i = 0; i<size; i++) {
		topTicket = tmpArr[0];
		for (int j = 0; j<tmpSize; j++)
			topTicket = NewestTicket(topTicket, tmpArr[j]);
		printTicket(topTicket);
		Ticket *copyArr = new Ticket[tmpSize];
		for (int j = 0; j<tmpSize; j++)
			copyTickets(copyArr[j], tmpArr[j]);
		delete[](tmpArr);
		tmpArr = new Ticket[--tmpSize];
		for (int j = 0, tmpIndex = 0; j<tmpSize + 1; j++) {
			if (copyArr[j].TicketNumber != topTicket.TicketNumber)
				copyTickets(tmpArr[tmpIndex++], copyArr[j]);
		}
	}
}


//Ganarate reports
void print_common_problems(const Ticket* AllTickets, const int size, int index) {
	string problem;
	if (index == 0)
		problem = "Slow connection";
	if (index == 1)
		problem = "Capacity connection";
	if (index == 2)
		problem = "Inappropriate content";
	if (index == 3)
		problem = "Battery problem";
	if (index == 4)
		problem = "Broken device";
	if (index == 5)
		problem = "Camera problem";
	if (index == 6)
		problem = "Signal problems";
	if (index == 7)
		problem = "Travel package";
	if (index == 8)
		problem = "MMS problems";
	if (index == 9)
		problem = "SMS problems";
	cout << problem << ": " << endl;
	for (int i = 0; i < size; ++i) {
		if (AllTickets[i].SubCategory == problem)
			printTicket(AllTickets[i]);
	}
}
void Report_common_problems(const Ticket* AllTickets, const int size) {
	int i,j, arr[10] = { 0 };
	for (i = 0; i < size; ++i) {
		if (AllTickets[i].SubCategory == "Slow connection")
			arr[0]++;
		if (AllTickets[i].SubCategory == "Capacity connection")
			arr[1]++;
		if (AllTickets[i].SubCategory == "Inappropriate content")
			arr[2]++;
		if (AllTickets[i].SubCategory == "Battery problem")
			arr[3]++;
		if (AllTickets[i].SubCategory == "Broken device")
			arr[4]++;
		if (AllTickets[i].SubCategory == "Camera problem")
			arr[5]++;
		if (AllTickets[i].SubCategory == "Signal problems")
			arr[6]++;
		if (AllTickets[i].SubCategory == "Travel package")
			arr[7]++;
		if (AllTickets[i].SubCategory == "MMS problems")
			arr[8]++;
		if (AllTickets[i].SubCategory == "SMS problems")
			arr[9]++;
	}
	for (i = 0; i < 10; ++i)
	{
		int max = arr[0];
		int index = 0;
		for (j = 1; j < 10; ++j)
		{
			if (arr[j] > max)
			{
				max = arr[j];
				index = j;
			}
		}
		arr[index] = 0;
		if(max>0)
			print_common_problems(AllTickets,  size, index);
	}
}
void swapCarr(ContactCounter &a, ContactCounter &b)
{
	ContactCounter temp;
	copyContacts(temp.contact, a.contact);
	temp.counter = a.counter;

	copyContacts(a.contact, b.contact);
	a.counter = b.counter;

	copyContacts(b.contact, temp.contact);
	b.counter = temp.counter;
}
void most_active_contacts_report(const Ticket* AllTickets, const int size, const string problem) 
{
	ContactCounter *Carr = NULL;
	int i,j ,Csize = 0;
	InitContactsArr(Carr, Csize, AllTickets, size);
	for (i = 0; i < Csize; ++i)
		for (j = 0; j < size; ++j)
			if (AllTickets[j].contact.id == Carr[i].contact.id)
				if (AllTickets[j].SubCategory == problem)
					Carr[i].counter++;
			
	//Sort the Carr from biggest to lowest
	for (i = 0; i < Csize - 1; ++i)
		for (j = 0; j < Csize - i - 1; ++j)
			if (Carr[j].counter < Carr[j + 1].counter)
				swapCarr(Carr[j], Carr[j + 1]);
	//Print most active
	cout << "--Most actice contact for: " << problem <<"--"<< endl << endl;
	bool flag = false;
	for(i=0;i<Csize;++i)
		if (Carr[i].counter != 0)
		{
			printContact(Carr[i].contact);
			cout << endl;
			flag = true;
		}
	if (!flag)
		cout << "No contacts with this problem: " << problem << endl;
}


int main()
{
	const string LoginFileName="LoginDatabase.txt", TicketsFileName = "TicketsDatabase.txt";
	Ticket *AllTickets = NULL;
	int choose,TicketNumber,size = countTickets(TicketsFileName);
	TicketNumber = size + 1;
	InitArr(AllTickets, size,TicketsFileName);
	
	Login(LoginFileName);
	do
	{
		printMenu();
		cin >> choose;
		switch (choose)
		{
		case(1): //Add New Ticket
		{
			Contact c;
			Ticket t;
			int exist,id;
			cout << "1) New contact\t2) Exist contact\n";
			cin >> exist;
			if (exist == 1)
				copyTickets(t, getFullTicket(TicketNumber, false, c));
			else
			{
				cout << "Enter contact ID:  ";
				cin >> id;
				if (!IsContactExist(AllTickets, size, id))
				{
					cout << "No contact found\n";
					break;
				}
				copyContacts(c, GetContactExist(AllTickets, size, id));
				copyTickets(t, getFullTicket(TicketNumber, true, c));
			}
			AddNewTicket(AllTickets, size, t);
			cout << "Ticket added successfully\n\n";
			break;
		}
		case(2): //Sort tickets
		{
			int sortParameter;
			cout << "1) Sort by Status\t2) Sort by Date\n3) Sort by severity\t4) Sort by contact ID\n5) Sort by ticket number\n";
			cin >> sortParameter;
			if (sortParameter == 1)
				SortByStatus(AllTickets, size);
			else if (sortParameter == 2)
				SortByDate(AllTickets, size);
			else if (sortParameter == 3)
				SortBySeverity(AllTickets, size);
			else if (sortParameter == 4)
				SortByID(AllTickets, size);
			else
				SortByNumber(AllTickets, size);
			break;
		}
		case(3): //Ganarate reports
		{
			int reportType, sub;
			cout << "1) Ganarate most common problems report\n2) Ganarate most active contacts report\n\n";
			cin >> reportType;
			if (reportType == 1)
				Report_common_problems(AllTickets, size);
			else if (reportType == 2)
			{
				cout << "1) Most active contacts for travel package\n2) Most active contacts for capacity connection\n";
				cin >> sub;
				if (sub == 1)
					most_active_contacts_report(AllTickets, size, "Travel package");
				else
					most_active_contacts_report(AllTickets, size, "Capacity connection");
			}

			break;
		}
		case(4):// Print previous contact's tickets
		{
			int id;
			cout << "Enter contact ID:  ";
			cin >> id;
			if (!IsContactExist(AllTickets, size, id))
			{
				cout << "No contact found\n";
				break;
			}
			printPrevioustickets(AllTickets, size, GetContactExist(AllTickets, size, id));
			break;
		}
		case(5)://Change ticket's status
		{
			int num;
			SortByNumber(AllTickets, size);
			cout << "\n\nEnter ticket's number: ";
			cin >> num;
			int j = IndexTicketNumberExist(AllTickets, size, num);
			if (j == -1)
			{
				cout << "Ticket number does not exist\n";
				break;
			}
			printTicket(AllTickets[j]);
			ChangeTicketStatus(AllTickets, size, j);
			break;
		}
		case(0)://Save to database and exit
		{
			WriteToFile(AllTickets, size, TicketsFileName);
			cout << "Have a good day =)\n";
			break;
		}	
		default:
			cout << "Invalid input try again\n";
		}
	} while (choose != 0);

	return 0;
}