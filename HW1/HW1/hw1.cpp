#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
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
	vector<edge> *successor ;
    node *predecessor;
	int step;
public:

	node(pair<int,int> state){
		s=state;
		successor= new vector<edge>();
		predecessor=NULL;
		step = 0;
	};
	~node(){
		delete [] this->successor;
	}
	state getState(){
	return this->s; 
	}
	void addedge(node *dest){
	edge e ;
	e.org = this;
	e.dest = dest;
	
	this->successor->push_back(e);
	dest->setPredecessor(this);
	}
	void setPredecessor(node *p){
		this->predecessor = p;
	}
	int getStep(){
	return this->step;
	}
	void setStep(int x){
		this->step = x;
	}
};

vector<int> applicableRule(state s,int a,int b);
state applyRuleS1(vector<int> rules,int a,int b,state in);
vector<state> applyRuleS2(vector<int> rules,int a,int b,state in);
bool unique(state s,vector<node*> nodes);


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
		if(pos==3){initS.first=found;}
		if(pos==4){initS.second=found;}
		if(pos==5){golS.first=found;}
		if(pos==6){golS.second=found;}
	
      }
	}

	vector<int> rules;
	cout<<"Strategy A initial state("<<initS.first<<","<<initS.second<<")"<<endl;
	
	int count = 0;
	state currentState = initS;
	
	bool flag = false;
	while(count<250){
     rules = applicableRule(currentState,CA,CB);
	 currentState = applyRuleS1(rules,CA,CB,currentState);
	 if(golS.first<0&&golS.second>=0){
		 if(currentState.second == golS.second){
       flag = true;	 
		 break;
	 }
	 }
	 else if(golS.second<0&&golS.first>=0){
		 if(currentState.first == golS.first){
       flag = true;	 
		 break;
	 }
	 }
	 else if (golS.second<0&&golS.first<0){
       flag = true;	 
		 break;
	 }
	 else{
		if(currentState == golS)
	   {
		   flag = true;	 
		break;
		}
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
	vector<node*> existState;
	vector<state> expendState;
	queue<node*> Nodes;
	node head(initS);
	node *curr;
	Nodes.push(&head);
	existState.push_back(&head);
	
	while(!Nodes.empty()){
		curr = Nodes.front();
		rules = applicableRule(curr->getState(),CA,CB);
		expendState = applyRuleS2(rules,CA,CB,curr->getState());
		Nodes.pop();
		node *temp;
		for(int i = 0;i<expendState.size();i++){
			if(unique(expendState[i],existState)){
			temp =new node(expendState[i]);
			Nodes.push(temp);
			existState.push_back(temp);
			curr->addedge(temp);
			}
		}
	}
	

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
		cout<<"Fill the "<<a<<"-gallon jug\t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 2:
		out.first=in.first;
		out.second=b;
		cout<<"Fill the "<<b<<"-gallon jug\t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 3:
		out.first=0;
		out.second=in.second;
		cout<<"Empty the "<<a<<"-gallon jug\t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 4:
		out.first=in.first;
		out.second=0;
		cout<<"Empty the "<<b<<"-gallon jug\t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 5:
		out.first = a;
		out.second = in.second -(a-in.first);
		cout<<"Pour water from "<<b<<"-gallon jug into "<<a<<"-gallon jug untill full \t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	case 6:
		out.first = in.first-(b-in.second);
		out.second = b;
		cout<<"Pour water from "<<a<<"-gallon jug into "<<b<<"-gallon jug untill full \t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 7:
		out.first=in.first+in.second;
		out.second=0;
		cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug \t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
    case 8:
		out.first=0;
		out.second=in.first+in.second;
		cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug \t->state("<<out.first<<","<<out.second<<")"<<endl;
		break;
	}
	return out;
}


vector<state> applyRuleS2(vector<int> rules,int a,int b,state in){
	    vector<state> res;
		state out; 
		int key = 0;
		for(int i = 0;i<rules.size();i++){
		key = rules[i];
	    if(key==1){
		out.first=a;
		out.second=in.second;
		//cout<<"Fill the "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
	    else if(key==2){
		out.first=in.first;
		out.second=b;
		//cout<<"Fill the "<<b<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
	    else if(key==3){
		out.first=0;
		out.second=in.second;
		//cout<<"Empty the "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		else if(key==4){
		out.first=in.first;
		out.second=0;
		//cout<<"Empty the "<<b<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		else if(key==5){
		out.first = a;
		out.second = in.second -(a-in.first);
		//cout<<"Pour water from "<<b<<"-gallon jug into "<<a<<"-gallon jug untill full ->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		else if(key==6){
		out.first = in.first-(b-in.second);
		out.second = b;
		//cout<<"Pour water from "<<a<<"-gallon jug into "<<b<<"-gallon jug untill full ->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		else if(key==7){
		out.first=in.first+in.second;
		out.second=0;
		//cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		else if(key==8){
		out.first=0;
		out.second=in.first+in.second;
		//cout<<"Pour all the water from "<<b<<"-gallon jug into "<<a<<"-gallon jug->state("<<out.first<<","<<out.second<<")"<<endl;
		}
		res.push_back(out);
	}
		return res;

}

bool unique(state s,vector<node*> nodes){
	for(int i = 0; i<nodes.size();i++){
		if(nodes[i]->getState() == s)
	    return false;
	}
	return true;
}