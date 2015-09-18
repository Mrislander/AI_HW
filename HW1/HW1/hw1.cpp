#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int,int> state;


class node;

class edge{
private:
	node *org;
	node *dest;
	
public:
	edge(){
	org=NULL;
	dest=NULL;
	}
	
	friend class node;
};
class node{

private:
	state s;
	vector<edge> *successor;
    edge *predecessor;
public:
	node(pair<int,int> state){
		s=state;
		successor=NULL;
		predecessor=NULL;
	};
	void addedge(node *dest){
	edge e ;
	e.org = this;
	e.dest = dest;
	this->successor->push_back(e);
	dest->addedge(this); 
	}

};

vector<int> applicableRule(state s,int a,int b);
state applyRuleS1(vector<int> rules);



int main(int argc,char *argv[]){

	if(argc!=3){
	cout<<"\nUsage: "<<argv[0]<<" input\n"<<endl; 
	}
	ifstream infile(argv[1]);
	if(!infile.is_open()) cout<<"Could not open file\n"<<endl;
	string line;
	int CA,CB,found;
	
	state initS,golS;
	int pos = 0;
	while(getline(infile,line, ' ')){
	 if(stringstream(line)>>found)
     {
		pos++;
		if(pos==1){CA=found;}
		if(pos==2){CB=found;}
		if(pos==3){initS.first=found;}
		if(pos==4){initS.second=found;}
		if(pos==5){golS.first=found;}
		if(pos==6){golS.second=found;}
	
      }
	}

	node head(initS);
	vector<int> ans = applicableRule(initS,CA,CB);
	cout<<"Strategy A"<<endl;





return 0;
}


vector<int> applicableRule(state s,int a,int b){
	vector<int> ans;
	if(s.first<a)  ans.push_back(1);
	if(s.second<b) ans.push_back(2);
	if(s.first>0)  ans.push_back(3);
	if(s.second>0) ans.push_back(4);
	if(s.first+s.second>=a && s.second>0)  ans.push_back(5);
	if(s.first+s.second>=b && s.first>0)   ans.push_back(6);
	if(s.first+s.second<=a && s.second>0)  ans.push_back(7);
	if(s.first+s.second<=b && s.first>0)  ans.push_back(8);
	return ans;
}
state applyRuleS1(vector<int> rules){
	int key = 0;
	switch(key){
	case 1:

	case 2:

	case 3:
    case 4:
	case 5:
	case 6:
    case 7:
    case 8:
	}
}