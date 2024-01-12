#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include <vector>
#include <algorithm>

using namespace std;
void Admin();
void BookList();
void User(string studentNo);
void ReturnBook();


struct Book{
	string name,author,isItActive,application;

};
struct Users{
	string name,password,studentNo;
	char auth;
};
void AddBook(){

 Book newBook; 
string book,empity="-";
	cout<<"\t\tKITAP EKLE\n\n";
cout<<"Kitap adini giriniz:";
cin.ignore();
getline(cin,newBook.name);
cin.ignore();
cout<<"Yazarini giriniz:";
getline(cin,newBook.author);
newBook.isItActive="Aktif";
book=newBook.name+empity+newBook.author+empity+newBook.isItActive+"-()\n";


   ofstream dosya("kitaplar.txt",ios::app);
    if (dosya.is_open()) {
        dosya << book;
        dosya.close();
        cout << "\nBasariyla Kaydedildi !" << endl;
    Admin();
    } 
	else {
        cout << "Bir Hata Olustu !" << endl;
    }	
	
	
}
vector<Book> bookList4;
void DeleteBook(){
	Book book;
	int selection;


	
    ifstream mainFile("kitaplar.txt");
   

	if (mainFile.is_open()) {
        string line1;
        while (getline(mainFile, line1)) {
           
            book.name = line1.substr(0, line1.find("-"));         
		   line1 = line1.substr(line1.find("-") + 1);
            book.author = line1.substr(0, line1.find("-"));
		    line1 = line1.substr(line1.find("-") + 1);
            book.isItActive = line1.substr(0, line1.find("-"));
            line1 = line1.substr(line1.find("(") + 1);
            book.application = line1.substr(0, line1.find(")"));
			bookList4.push_back(book);
        
		}
        
 
    } else {
        cout << "Dosya acilamadi" << endl;
    }


   for (int i = 0; i < bookList4.size(); i++) {
    
	   
		
				cout << i+1 << ". " << bookList4[i].name+" - " << bookList4[i].author+" - " << bookList4[i].isItActive <<endl;
		
        		
		}	
  bool control=false;
    while(!control){
	
	
		cout<<"\n\nSilmek istediginiz kitabi secin :";
	  cin>>selection;
	if(bookList4[selection-1].application!="" && bookList4[selection-1].isItActive=="Pasif"){
	if(bookList4[selection-1].application!="Iade Edildi"){
		
	
		cout<<"\n Hata: Bu kitap su an "+bookList4[selection-1].application+" numarali ogrencide !";
		Admin();
		continue;
	}
}
 ofstream tempFile("temp.txt"); 
	string line;
    int lineNumber = 1;
   mainFile.clear();
   mainFile.seekg(0, ios::beg);
    while (getline(mainFile, line)) {
        if (lineNumber != selection) { 
            tempFile << line << endl;
        }
        lineNumber++;
    }

   
    mainFile.close();
    tempFile.close();
    remove("kitaplar.txt");
    rename("temp.txt", "kitaplar.txt");
    cout<<"\nKitap Basariyla Silindi !\n";
   control=true;
    Admin();
}


}

vector<Book> bookList3;


void StudentsBooks(string studentNo1){
	
	Book book;
string studentNo;
	vector<string> studentsNo;
		ifstream dosya("kitap_ogrenci.txt");   
	if (dosya.is_open()) {
        string line;
        while (getline(dosya, line)) {
           
		    studentNo=line.substr(0, line.find("(")); 
		    
			 line = line.substr(line.find("-") + 1);
            book.name = line.substr(0, line.find("("));         
		   line = line.substr(line.find("(") + 1);
            book.author = line.substr(0, line.find(")"));
		    bookList3.push_back(book);
        studentsNo.push_back(studentNo);
		}
        dosya.close();
 
    } else {
        cout << "Dosya acilamadi" << endl;
    }

	vector<int> myIndex;
 
	 for(int j=0;j<bookList3.size();j++){		
	if(studentsNo[j]==studentNo1)	
    myIndex.push_back(j);
	
	}
	
	cout<<"\nKitap Listesi : \n\n";
		for (int i = 0; i < bookList3.size(); i++) {
    
	    if(find(myIndex.begin(),myIndex.end(), i) != myIndex.end()){
		
			cout << i+1 << ". " << bookList3[i].name+" - " << bookList3[i].author << endl;
		}
        		
		}	
	
int selection;
   cout << "\nIade etmek istediginiz kitabi seciniz: ";
   cin>> selection;
   
   
    ofstream dosya1("kitaplar.txt");
    if (dosya1.is_open()) {
        for (int i = 0; i < bookList3.size(); i++) {
          if(find(myIndex.begin(),myIndex.end(), i) != myIndex.end()){
		  if((selection-1)==i){
          	  dosya1 << bookList3[i].name+"-"<<bookList3[i].author+"-"<<"Pasif-(Iade Edildi)" << endl;
          	  continue;
		  }
		  dosya1 << bookList3[i].name+"-"<<bookList3[i].author+"-"<<"Pasif" << endl;
}
}
cout<<"\n"+bookList3[selection-1].name+"("+bookList3[selection-1].author +") Basariyla Iade Edildi !";
dosya1.close();
 
int selection1=0;

while(selection1!=1 && selection1!=2){	
cout<<"\n\n\n1-Ana Menu\n0-Cikis Yap\n:";
cin>>selection1;
	if(selection1==1) User(studentNo1);
	else if(selection1==0)break;
	else cout<<"\nHatali bir secim yaptiniz !";	
	
	}

}



}

vector<Book> bookList2;

void BookListForStudent(string studentNo){
		 Book book;	
	
	ifstream dosya("kitaplar.txt");   
	if (dosya.is_open()) {
        string line;
        while (getline(dosya, line)) {
           
            book.name = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.author = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.isItActive = line.substr(0, line.find("-"));
            bookList2.push_back(book);
        }
        dosya.close();
  
    } else {
        cout << "Dosya acilamadi" << endl;
    }
 

     cout<<"\n";
   
    vector<int> activeIndex;
	
	for(int j=0;j<bookList2.size();j++){		
	if(bookList2[j].isItActive=="Aktif")	
 activeIndex.push_back(j);
	
	}
        cout<<"\nKitap Listesi : \n\n";
		for (int i = 0; i < bookList2.size(); i++) {
    
	    if(find(activeIndex.begin(),activeIndex.end(), i) != activeIndex.end()){
		
			cout << i+1 << ". " << bookList2[i].name+" - " << bookList2[i].author+" - " << bookList2[i].isItActive << endl;
		}
        
 
		
		}	
	int selection;
	cout<<"\nBasvurmak istediginiz kitabi seciniz: ";
	cin>>selection;
	cout<<"\nSectiginiz Kitap: "+bookList2[selection-1].name+"("+bookList2[selection-1].author+")";
	
	  ofstream dosya1("kitaplar.txt");
    if (dosya1.is_open()) {
        for (int i = 0; i < bookList2.size(); i++) {
         if( bookList2[i].name==bookList2[selection-1].name){
         	dosya1 << bookList2[i].name+"-"<<bookList2[i].author+"-"<<bookList2[i].isItActive+"-("+studentNo+")" << endl;
         	continue;
		 }
		  dosya1 << bookList2[i].name+"-"<<bookList2[i].author+"-"<<bookList2[i].isItActive << endl;
}
dosya1.close();

int selection1=0;
while(selection1!=1 && selection1!=2){	
cout<<"\n\n\n1-Ana Menu\n0-Cikis Yap\n:";
cin>>selection1;
	if(selection1==1) User(studentNo);
	else if(selection1==0)break;
	else cout<<"\nHatali bir secim yaptiniz !";	
	
	}

}

	
	
}
void BookList(){
		ifstream file("kitaplar.txt");
    vector<string> data;

    if (file.is_open()) {
        string line;
        cout<<"\n";
		while (getline(file, line)) {
            data.push_back(line);
        }

        file.close();

     
        sort(data.begin(), data.end());

     
        for (int i = 0; i < data.size(); i++) {
            cout << i + 1 << ". " << data[i] << endl;
        }
    } 
int selection=0;

while(selection!=1 && selection!=2){	
cout<<"\n\n1-Ana Menu\n0-Cikis Yap\n:";
cin>>selection;
	if(selection==1) Admin();
	else if(selection==0)break;
	else cout<<"\nHatali bir secim yaptiniz !";	
	
	}
	


	
}
vector<Book> bookList1;
void AssingBook(){

	Users user;
	vector<Users> users;
	int selection,selection1;
	string assignment;
		
 Book book;		
	ifstream dosya("kitaplar.txt");   
	if (dosya.is_open()) {
        string line;
        while (getline(dosya, line)) {
           
            book.name = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.author = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.isItActive = line.substr(0, line.find("("));
            line=line.substr(line.find("(") + 1);
			book.application=line.substr(0, line.find(")"));
			bookList1.push_back(book);
        }
        dosya.close();
  
    } else {
        cout << "Dosya acilamadi" << endl;
    }
 

     cout<<"\n";
   
    vector<int> passiveIndex;
	    for(int j=0;j<bookList1.size();j++){
		
	if(bookList1[j].isItActive=="Pasif")	
 passiveIndex.push_back(j);
	
	}
        cout<<"\n\t\tKitap Listesi  \n\n";
		for (int i = 0; i < bookList1.size(); i++) {
    
	    if(find(passiveIndex.begin(),passiveIndex.end(), i) == passiveIndex.end()){
	
			cout << i+1 << ". " << bookList1[i].name+" - " << bookList1[i].author+" - " << bookList1[i].isItActive << "   | Basvuranlar: "+bookList1[i].application <<endl;
		}
        		
		}	
 cout << "\n\nAtamak istediginiz kitabi seciniz: ";
   cin>> selection1;
   cout<< "\nSecilen Kitap : "+bookList1[selection1-1].name+" - "+bookList1[selection1-1].author; 

 
 
 	
 
	ifstream file("ogrenciler.txt");
    if (file.is_open()) {
        string line;
        cout<<"\n";
		while (getline(file, line)) {
             if (!line.empty()) {			
    }
	user.studentNo=line.substr(0,line.find(":")); 
	line=line.substr(line.find(":")+1);
	user.password=line.substr(0,line.find("-"));
	line=line.substr(line.find("-")+1);
	user.name=line.substr(0,line.find("-"));	
	
	users.push_back(user);
	}

        file.close();
}
  bool control=false;
   while(!control){
   	
   
    cout<<"\n\t\tOgrenci Listesi  \n\n";
        for (int i = 0; i < users.size(); i++) {
            cout << i + 1 << ". " << users[i].name+" - "+users[i].studentNo << endl;
        
    } 


   cout << "\nKitap atamak istediginiz ogrenciyi seciniz: ";
   cin>> selection;
 if(bookList1[selection1-1].application!=users[selection-1].studentNo){
 	cout<<"\n'"+users[selection-1].studentNo+"' Ogrencisi bu kitap icin basvuruda bulunmamis !\n";
 	continue;
 }
   cout<< "\nSecilen ogrenci : "+users[selection-1].name+" - "+users[selection-1].studentNo; 
 
  assignment=users[selection-1].studentNo+"("+users[selection-1].name+")"+"-"+ bookList1[selection1-1].name+"("+bookList1[selection1-1].author+")\n";
  cout<< "\n\n"+bookList1[selection1-1].name+"("+bookList1[selection1-1].author+")"+" basariyla "+users[selection-1].name+" kisine atandi !\n"; 
   ofstream file1("kitap_ogrenci.txt",ios::app);
    if (file1.is_open()) {
        file1 << assignment;
        file1.close();
      bookList1[selection1-1].isItActive="Pasif"; 
 	  ofstream dosya1("kitaplar.txt");
    if (dosya1.is_open()) {
        for (int i = 0; i < bookList1.size(); i++) {
          dosya1 << bookList1[i].name+"-"<<bookList1[i].author+"-"<<bookList1[i].isItActive <<"-("+bookList1[i].application+")" <<endl;
 control=true;
}
}
dosya1.close();
	int selection2=0;

while(selection2!=1 && selection2!=2){	
cout<<"\n\n\n1-Ana Menu\n0-Cikis Yap\n:";
cin>>selection2;
	if(selection2==1) Admin();
	else if(selection2==0)break;
	else cout<<"\nHatali bir secim yaptiniz !";	
	
	}
    } 


	else {
        cout << "Bir Hata Olustu !" << endl;
    }	
}




}

vector<Book> bookList;


void ReturnBook(){
	
	 Book book;	
	
	ifstream dosya("kitaplar.txt");   
	if (dosya.is_open()) {
        string line;
        while (getline(dosya, line)) {
           
            book.name = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.author = line.substr(0, line.find("-"));
            line = line.substr(line.find("-") + 1);
            book.isItActive = line.substr(0, line.find("-"));
            line=line.substr(line.find("(") + 1);
			book.application=line.substr(0, line.find(")"));
		   
			bookList.push_back(book);
        }
        dosya.close();
  
    } else {
        cout << "Dosya acilamadi" << endl;
    }
    
 

     cout<<"\n";
   
    vector<int> activeIndex;
	    for(int j=0;j<bookList.size();j++){
		
	if(bookList[j].isItActive=="Aktif")	
 activeIndex.push_back(j);
	
	}
        cout<<"\nKitap Listesi : \n\n";
		for (int i = 0; i < bookList.size(); i++) {
    
	    if(find(activeIndex.begin(),activeIndex.end(), i) == activeIndex.end()){
		
			cout << i+1 << ". " << bookList[i].name+" - " << bookList[i].author+" - " << bookList[i].isItActive <<" -("+bookList[i].application+")" <<endl;
		}
        
 
		
		}	
  bool control=false;
  while(!control){
  
   int selection;
   cout << "\nTekrar yayinlamak istediginiz kitabi seciniz: ";
   cin>> selection;
   if(bookList[selection-1].application!="Iade Edildi"){
   	cout<<"\nHATA: Bu kitap '"+bookList[selection-1].application+"' numarali ogrencide !\n";
   	continue;
   }
    bookList[selection-1].isItActive ="Aktif";
   control=true;
    ofstream dosya1("kitaplar.txt");
    if (dosya1.is_open()) {
        for (int i = 0; i < bookList.size(); i++) {
          dosya1 << bookList[i].name+"-"<<bookList[i].author+"-"<<bookList[i].isItActive <<"-()" <<endl;
}
dosya1.close();
 

 ifstream inputFile("kitap_ogrenci.txt");
 
if (!inputFile) {
        cout << "Dosya acilamadi" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cout << "Gecici dosya olusturulamadi" << endl;
        inputFile.close();
        return;
    }


	string word= bookList[selection-1].name+"("+bookList[selection-1].author+")";
	string line1;
    while (getline(inputFile, line1)) {
        if (line1.find(word) == string::npos) {
            tempFile << line1 << endl;
        }
    }	




 inputFile.close();
 tempFile.close();

 remove("kitap_ogrenci.txt");
rename("temp.txt", "kitap_ogrenci.txt");

cout<<"\nKitap Basariyla Aktiflestirildi !";











int selection1=0;

while(selection1!=1 && selection1!=2){	
cout<<"\n\n\n1-Ana Menu\n0-Cikis Yap\n:";
cin>>selection1;
	if(selection1==1) Admin();
	else if(selection1==0)break;
	else cout<<"\nHatali bir secim yaptiniz !";	
	
	}

}

}
}
void AdminLogin(char auth){
	
	string username,password,empity=":";
	bool control=false;

cout<<"\t\tGIRIS EKRANI\n\n";

while(!control){
	
cout<<"Kullanici adini giriniz:";
cin>>username;
cout<<"Sifreyi giriniz:";
cin>>password;

string controlStr=username+empity+password+empity+auth;
	 
    bool control1 = false;


		ifstream dosya("yoneticiler.txt");
	if (dosya.is_open()) {
        string satir="";
        while (getline(dosya, satir)) {
            if (satir.find(controlStr) != string::npos) {
                control1 = true;
                break;
            }
        }
        dosya.close();
    } else {
        cout << "Dosya acilamadi." << endl;
       
    }
	
	 if (control1) {
       control=true;
	    cout << "\nBasariyla Giris Yapildi !" << endl;
        
        if(auth=='1'){ Admin(); }
        break;
    } else {
        cout << "\nKullanici Bilgileri Yanlis !\n" << endl;
    }
	
	
	
	

	
} 

	
	

}
void UserLogin(char auth){
	
	string studentNo,password,empity=":";
	bool control=false;

cout<<"\t\tGIRIS EKRANI\n\n";

while(!control){
	cout<<"Okul No: ";
cin>>studentNo;
cout<<"Sifre: ";
cin>>password;

string control=studentNo+empity+password;
	 
    bool control1 = false;
	
	

		ifstream dosya("ogrenciler.txt");
	if (dosya.is_open()) {
        string satir="";
        while (getline(dosya, satir)) {
            if (satir.find(control) != string::npos) {
                control1 = true;
                break;
            }
        }
        dosya.close();
    } else {
        cout << "Dosya acilamadi." << endl;
       return;
    }
	
	 if (control1) {
       control=true;
	    cout << "\nBasariyla Giris Yapildi !" << endl;
        
        if(auth=='2'){ User(studentNo); }
        break;
    } else {
        cout << "\nKullici Bilgileri Yanlis !\n" << endl;
    }
	
	
	
	
	

	
} 
	
}
void User(string studentNo){   
   int selection;
   bool control=false;

	while(!control){
	
cout<<"\n\t\tOGRENCI PANELI\n";
cout<<"\n1-Kitap Listesi";
cout<<"\n2-Kitaplarim";
cout<<"\n\n0-Cikis Yap\n\n:";

cin>>selection;
switch(selection){
	
	case 1:BookListForStudent(studentNo);control=true;break;
	case 2:StudentsBooks(studentNo);control=true;break;
	
	case 0:control=true;break;
	
	default:break;
}
}
	
	
}
void Admin(){
	int selection;
	bool control=false;

while(!control){
	
	cout<<"\n\t\tYONETICI PANELI";
cout<<"\n1-Kitap Ekle";
cout<<"\n2-Kitap Sil";
cout<<"\n3-Kitap Listesini Goster";
cout<<"\n4-Ogrencilere Kitap Ata";
cout<<"\n5-Kitap Yayinla";
cout<<"\n\n0-Cikis Yap\n\n:";
cin>>selection;
switch(selection){
	
	case 1:AddBook();control=true;break;
	case 2:DeleteBook();control=true;break;
	case 3:BookList();control=true;break;
	case 4:AssingBook();control=true;break;
	case 5:ReturnBook();control=true;break;
	case 0:control=true;break;
	
	default:break;
}
}

}
void Login(char auth){
	if(auth=='1'){
		AdminLogin(auth);
	}
else if(auth=='2'){
	
	UserLogin(auth);
}
	
	
	
}

void SignUp(char auth){
	struct Users newUser;
		string empity=":",user;
		
cout<<"\t\tKAYIT EKRANI\n\n";
cout<<"Ad Soyad: ";
cin.ignore();
getline(cin,newUser.name);
cout<<"Okul No: ";
cin>>newUser.studentNo;
cout<<"Sifre: ";
cin>>newUser.password;
newUser.auth='2';

user= newUser.studentNo+empity+newUser.password+"-"+newUser.name+"\n";

   ofstream dosya("ogrenciler.txt",ios::app);
    if (dosya.is_open()) {
        dosya << user;
        dosya.close();
        cout << "\nBasariyla Kaydedildi !" << endl;
    } 
	else {
        cout << "Bir Hata Olustu !" << endl;
    }	
	
	int input=0;
	cout<<"\n\tYapmak Istediginiz Islemi Seciniz ";
  	while(input!=1 && input!=2){
		cout<<"\n\n  [1] Giris Yap     [0] Cikis Yap\n\n:";
	    cin>>input;
		if(input==1){
		Login(auth);
		}
		else if(input==0){
			return;
		}
		else {
			cout<<"\nHatali bir secim yaptiniz !";
		}
		
	}
	
	
	
}
void UserPanel(){
	int input=0;
	 char auth='2';
	cout<<"\n\t\tOGRENCI PANELI ";
  	while(input!=1 && input!=2){
		cout<<"\n\n  [1] Giris Yap     [2] Kayit Ol\n\n:";
	    cin>>input;
		if(input==1){
		Login(auth);
		}
		else if(input==2){
			SignUp(auth);
		}
		else {
			cout<<"\nHatali bir secim yaptiniz !";
		}
		
	}
	
	
}

int main()
{
	
   int  input=0;
   char auth='1';
   
 
 
   cout<<"\n\tKUTUPHANE SISTEMINE HOSGELDINIZ";

	while(input!=1 && input!=2  ){
		cout<<"\n\n  [1] Yonetici Giris     [2] Ogrenci Islemleri\n\n:";
	    cin>>input;
		if(input==1){
		Login(auth);
		}
		else if(input==2){
			UserPanel();
		}
		else {
			cout<<"\nHatali bir secim yaptiniz !";
		}
		
	}
	
	
	
	
}
