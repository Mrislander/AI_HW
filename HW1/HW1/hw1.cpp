#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)

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
state applyRuleS1(vector<int> rules,int a,int b,state in);




int main(int argc,char *argv[]){

	if(argc!=3){
	cout<<"\nUsage: "<<argv[0]<<" inputfile outputfile\n"<<endl; 
	}
	ifstream infile(argv[1]);
	freopen(argv[2],"w",stdout);
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
		if(pos==3){initS.first=found>0?found:0;}
		if(pos==4){initS.second=found>0?found:0;}
		if(pos==5){golS.first=found>0?found:0;}
		if(pos==6){golS.second=found>0?found:0;}
	
      }
	}

	node head(initS);
	vector<int> roles;
	cout<<"Strategy A initial state("<<initS.first<<","<<initS.second<<")"<<endl;
	int count = 0;
	state currentState = initS;
	bool flag = false;
	while(count<250){
     roles = applicableRule(currentState,CA,CB);
	 currentState = applyRuleS1(roles,CA,CB,currentState);
	 if(currentState == golS){
       flag = true;	 
		 break;
	 } 
	 cout<<"step"<<count+1<<endl;
	 count++;
	  
	}
	if(!flag)
	cout<<"Strategy A failed"<<endl;
	else 
    cout<<"Find Solution"<<endl;
	cout<<endl<<endl<<endl;
	cout<<"Strategy B initial state("<<initS.first<<","<<initS.second<<")"<<endl;


infile.close();
fclose (stdout);
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
state applyRuleS1(vector<int> rules,int a,int b,state in){
	int key = 0;
	int index = rand()%rules.size();
	key = rules[index];
	state out;
	switch(key){
	case 1:
		out.first=a;
		out.second=in.second;
		cout<<"Fill the "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 2:
		out.first=in.first;
		out.second=b;
		cout<<"Fill the "<<b<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 3:
		out.first=0;
		out.second=in.second;
		cout<<"Empty the "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 4:
		out.first=in.first;
		out.second=0;
		cout<<"Empty the "<<b<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 5:
		out.first = a;
		out.second = in.second -(a-in.first);
		cout<<"Pour water from "<<b<<"-gallon jug into "<<a<<"-gallon jug untill full ->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 6:
		out.first = in.first-(b-in.second);
		out.second = b;
		cout<<"Pour water from "<<a<<"-gallon jug into "<<b<<"-gallon jug untill full ->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 7:
		out.first=in.first+in.second;
		out.second=0;
		cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 8:
		out.first=0;
		out.second=in.first+in.second;
		cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	}
	return out;
}