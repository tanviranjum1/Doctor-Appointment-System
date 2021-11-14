#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define pb push_back

string names[13];
vector <int> bookings[6];


string departmentFinder(int ch)
{
    switch(ch)
    {
        case 1:
            return "Neurology";
        case 2:
            return "Pediatric";
        case 3:
            return "Internal Medicine";
        case 4:
            return "Psychiatric";
        case 5:
            return "E.N.T";
        case 6:
            return "Emergency";
    }
}

void fixBooking(int ch)
{
    char confirm='N';
    int fl=0;
    string days[]= {"Sun","Mon","Tues","Wed","Thurs"};
    string time="@";
    char ok;
    string deptname;
    while(confirm=='N' || confirm=='n')
    {
        system("cls");
        deptname=departmentFinder(ch);
        cout << "\n**** "<<deptname<< " Department ****"<<endl;
        cout << "\n Make your appointment: "<<endl<<endl<<endl;;
        char i='A';
        string name=names[(ch*2)-1];
        printf("  MENU:       DAY                    NAME         PRE-BOOKED            STATUS\n");
        while(i<='E')
        {
            if (i>='D')
                name=names[ch*2];
            cout <<setw(5) << i<< "  =>"<< setw(8)<<days[(int)i-65] <<setw(24)<<name<< setw(13)<<bookings[ch-1][(int)i-65]<< "/20"<< setw(22);
            if (bookings[ch-1][(int)i-65]==20)
                cout <<  "Unavailable"<<endl;
            else
                cout << "Available" <<endl;
            i++;
        }


        char choice;
        cout<<"\n\n Input (A-E) and F to Go Back : ";
        cin>>choice;
        choice=toupper(choice);

        //considering 15 mins for each patient
        string str2="";
        if (choice>='A' && choice<='E')
        {
            int booked=bookings[ch-1][(int)choice-65];
            if (booked<20)
            {
                ok=choice;
                double calc=(booked*15.0)/60.0;
                int hr=(int)calc+5;
                int mins=(calc-(int)calc)*60;
                stringstream ss,ob;
                ss << hr;
                ss >> time;
                time+=":";
                ob << mins;
                ob >> str2;
                time+=str2;
                if (time[2]=='0')
                {
                    time+="0";
                }
                cout << "\n Appointment Arranged at " << time << " p.m."<<endl;
                cout << "\n\n Do you wish to confirm it? Y|N "<<endl;
                cout <<" ";
                cin >> confirm;
            }
            else
            {
                cout<<"\n Error : All Appointments had been booked";
                cout<<"\n Please select different day !!";
                cout<<"\n Press any key to continue!!";
                getchar();
                getchar();
            }
        }
        else if (choice=='F')
        {
            fl=1;
            break;

        }
        else
        {
            cout<<"\n Error: Invalid Selection";
            cout<<"\n Please select correct value from menu A-E";
            cout << "\n Press any key to continue";
            getchar();
            getchar();
        }
    }
    if (fl==0)
    {
        ofstream out;
        out.open("app.txt",ios::app);

        string pname,dname;
        int phone;
        cout <<endl<< " Enter your first name: ";
        cin>> pname;
        cout << " Enter your phone number: ";
        cin >> phone;
        while(cin.fail())
        {
            cout<<" Phone number is in integer form,sire!";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> phone;
        }

        dname=names[ch*2-1];

        if (out)
        {
            if (ok=='D' || ok=='E')
                dname=names[ch*2];
            out << "entry" <<endl;
            out << pname << "(0" << phone << ")"<<endl;
            out << "with, " << dname << " [" << deptname<<"]"<<endl;
            out << "at " << time<< " pm, ";
            out << days[(int)ok-65]<<endl;
            out << "-----------------------------------" <<endl;
        }
        else
        {
            cout <<"\n Error while saving booking"<<endl;
        }
        out.close();
        bookings[ch-1][(int)ok-65]++;

        cout <<endl<<" Congratulations, booking successful!!" <<endl;
    }

    cout << "\n Going to the main menu." <<endl;
    Sleep(2000);
}



void useBookings()
{
    ifstream read_file;
    read_file.open("total.txt");
    int i=0;
    while(i<=5)
    {
        int x;
        for (int j=0; j<5; j++)
        {
            read_file>>x;
            bookings[i].pb(x);
        }
        i++;
    }
    i=1;
    int j=0,x;
    while(i<=12)
    {
        read_file>> x;
        read_file.ignore();
        string name,dept;
        getline(read_file,name,',');
        getline(read_file,dept,',');
        names[++j]=name;
        i++;
    }
    read_file.close();
}


void storeBookings()
{
    ifstream read_file;
    read_file.open("total.txt");
    ofstream out;
    out.open("new.txt");
    int i=0;
    while(i<=5)
    {
        int x;
        read_file>>x;
        for (int j=0; j<5; j++)
        {
            out << bookings[i][j] << " ";
        }
        i++;
    }
    i=1;
    string line;
    getline(read_file,line);
    out <<endl;
    while(!read_file.eof())
    {
        getline(read_file,line);
        out << line <<endl;
    }
    read_file.close();
    out.close();
    remove("total.txt");
    rename("new.txt","total.txt");
}




int setDept()
{
    int choice;
    cout<<"\n\t\t\t\tChoose Department:"<<endl;
    cout<<"\n\t\t\t\t1)Neurology \n\t\t\t\t2)Pediatric \n\t\t\t\t3)Internal Medicine \n\t\t\t\t4)Phsychiatric \n\t\t\t\t5)E.N.T \n\t\t\t\t6)Emergency \n\n\n\t\t\tYour Choice:";
    cin>>choice;
    if (choice>=1 && choice<=6)
    {
        fixBooking(choice);
    }
    else if (cin.fail() || choice>6)
    {
        cin.clear();
        cout << "\n\n\t\t\t\tInvalid choice!!"<<endl;
        getchar();
        getchar();
    }

}


void allRec()
{
    system("cls");
    cout << "\n All Bookings Made: "<<endl<<endl;
    ifstream read_file;
    read_file.open("app.txt");
    if (!read_file)
    {
        cout << "error reading file" <<endl;
    }
    string str;
    int num=1;
    cout << "-----------------------------------" ;
    while(!read_file.eof())
    {
        getline(read_file,str);
        if (str=="entry")
        {
            cout <<endl<<str <<" "<<  num <<endl;
            ++num;
        }
        else{
            cout <<str <<endl;
        }
    }
    read_file.close();
    cout << "Hit a key to return . . .";
    system("pause >nul");

}
void oneRec()
{
    system("cls");
    cout << "\n**** Searching your Appointment ****\n"<<endl;
    string x="";
    string name,phone;
    cout << "\n Patient name: ";
    cin>>name;
    cout << "\n Patient number: ";
    cin>>phone;
    x+=name;
    x+="("+phone+")";
    ifstream read_file;
    read_file.open("app.txt");
    if (!read_file)
    {
        cout << "error reading file" <<endl;
    }
    string str;
    int fl=0;

    while(!read_file.eof())
    {
        getline(read_file,str);
        if (str==x)
        {
            fl=1;
            cout <<endl<<" Match Found!"<<endl;
            string str2,str3;
            getline(read_file,str2);
            getline(read_file,str3);
            cout << " Name: "<<name<<", phone number: "<< phone<<endl;
            cout << " appointment "<< str2<<endl;
            cout << " Scheduled "<< str3 <<endl<<endl<<endl;
        }
    }
    if (fl==0)
    {
        cout <<endl<<" Sorry, no Matches!"<<endl<<endl;
    }
    read_file.close();
    cout << " Hit a key to return . . .";
    system("pause >nul");
}



void showDoctors()
{
    system("cls");
    cout << "\n";
    ifstream a;
    a.open("total.txt");
    if (!a)
    {
        cout << "error opening the file" <<endl;
    }
    string line;
    getline(a,line);
    int x,i=1;
    printf("       ******** All Doctors ********\n\n");
    cout << " ID:           NAME                WORKING DAYS                DEPARTMENT" <<endl;
    cout<<" ------------------------------------------------------------------------"<<endl<<endl;
    while(i<=12)
    {
        a>>x;
        a.ignore();
        string name,dept;
        getline(a,name,',');
        getline(a,dept,',');
        if (i%2!=0)
        {
            cout << setw(4) << x << setw(20)<< name << setw(20) << "SUN-TUE" << setw(28) << dept<<endl;
        }
        else
        {
            cout << setw(4) << x << setw(20)<< name << setw(20) << "WED-THU" << setw(28) << dept<<endl;
        }
        i++;
    }
    a.close();
    cout << endl <<endl;
    cout << " Hit a key to return . . .";
    system("pause >nul");
}



void changeDoctor()
{
    cout << "\n";
    ifstream read_file;
    read_file.open("total.txt");
    ofstream out;
    out.open("temp.txt");

    string line;
    getline(read_file,line);
    out<<line<<endl;

    int ID,x;
    cout << "  Enter the ID of doctor to be removed: " ;
    cin>> ID;
    cin.ignore();
    int i=1,fl=0;

    while(i<=12)
    {
        read_file>> x;
        read_file.ignore();
        string name,dept;
        getline(read_file,name,',');
        getline(read_file,dept,',');
        if (x==ID)
        {
            fl=1;
            cout << "\n  Enter the name of doctor to be added: ";
            getline(cin,name);
            names[ID]=name;
        }
        out << x<< ","<< name << "," << dept <<","<<endl;
        i++;
    }
    if (fl==0)
    {
        cout << " Doctor ID, not found!" <<endl<<endl<<endl;
        cout << " Hit a key to return . . ." <<endl;
        system("pause >nul");
    }
    read_file.close();
    out.close();
    remove("total.txt");
    rename("temp.txt","total.txt");
}

bool check()
{
    string username;
    cout<<"\n\t\t\t\tEnter username:";
    string pass;
    cin>> username;
    cout<<"\n\t\t\t\tEnter pass:";
    cin>> pass;
    if (username=="admin" && pass=="admin123")
    {
        cout<<"\n\n\t\t\t\tAccess granted."<<endl;
        return 1;
    }
    else{

           cout<<"\n\n\t\t\t\tAccess denied.";
            getchar();
            getchar();
            return 0;
    }


}

int main()
{
    useBookings();
    while(1)
    {
        system("cls");
        cout<<setw(30)<<"\n\n\t\t\t      Doctor Appointment System "<<endl;
        cout<<setw(30)<<"  \t\t=================================================="<<endl<<endl;
        cout<<setw(30)<<"  \t\t--------------------------------------------------"<<endl;
        cout<<"\t\t||\t   1. View Doctors Available"<<"            ||"<<endl;
        cout<<"\t\t||\t   2. Go To Appointment Section"<<"         ||"<<endl;
        cout<<"\t\t||\t   3. Booking Records"<<"                   ||"<<endl;
        cout<<"\t\t||\t   4. Save and Exit"<<"                     ||"<<endl;
        cout <<setw(30)<<"  \t\t--------------------------------------------------"<<endl;
        cout<<"\t\t||\t   Administration Panel"<<"                 ||"<<endl;
        cout<<"\t\t||\t   5. Update Doctor"<<"                     ||"<<endl;
        cout <<setw(30)<<"  \t\t--------------------------------------------------"<<endl;
        cout<<"\t\tEnter Choice: ";
        char n;
        cin >> n;
        switch(n)
        {
        default:
            cout<<"\n\n\t\t\t\tInvalid choice!!";
            getchar();
            getchar();
            break;
        case '1':
            showDoctors();
            break;
        case '2':
            setDept();
            break;
        case '3':
            cout <<endl;
            cout <<"\n\n\t\t\tShow Booking Records"<<endl;
            //for patient
            cout <<"\n\t\t\t\t1. Yours Only"<<endl;
            //for administrator
            cout <<"\t\t\t\t2. All "<<endl;
            cout << "\n\t\t\tChoice: ";
            char ch;
            cin>>ch;
            if (ch=='1'){
                oneRec();
            }
            else if (ch=='2'){
                allRec();
            }
            break;
        case '4':
            storeBookings();
            cout <<endl<<endl;
            cout << "Thank you!";
            exit(0);
        case '5':
            if (check())
            {
                changeDoctor();
            }
            break;
        }
    }


    return 0;
}
