#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<queue>
#include<vector>
#include<map>
#include<iostream>
#include<fstream>  
#include<streambuf>
#define maxn 0x7fffffff
#define minn 0xcf
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
struct ss{
	int number;
	char ass;
};
ss sum[1001];
map<char,int> File;
struct po{
	int value,left,right,fa;
	char cun;
	vector<bool> code;
}point[1001];
inline bool cmp(ss x,ss y){
	return x.number<y.number;
}
inline bool cp(po x,po y){
	return x.cun<y.cun;
}
bool codei[10001];
ll wpl=0;
string reduce;
int tot=0;
vector<bool> haffFile;
string ending;
bool treemove(int cnt){
	int num1=maxn,num2=maxn,tree1=-1,tree2=-1;//maxn=0x7fffffff
	for(int i=0;i<cnt;i++){
		if(point[i].fa==i){
			if(point[i].value<num1) num2=num1,num1=point[i].value,tree2=tree1,tree1=i;
			else if(point[i].value>=num1&&point[i].value<num2) num2=point[i].value,tree2=i;
		} 
	}
	if(tree1<0||tree2<0) return false;
	point[cnt].value=num1+num2;
	point[tree1].fa=cnt;
	point[tree2].fa=cnt;
	point[cnt].left=tree1;
	point[cnt].right=tree2;
	point[cnt].fa=cnt;
	return true;
}

void dfs(int lim,int step){
	if(point[lim].left<0){
		if(point[lim].right<0){
			for(int i=0;i<step;i++) point[lim].code.push_back(codei[i]);
			wpl+=step*point[lim].value;
			return;
		}else{
			codei[step]=true;
			dfs(point[lim].right,step+1);
		}
	}else{
		if(point[lim].right<0){
			codei[step]=false;
			dfs(point[lim].left,step+1);
		}else{
			codei[step]=false;
			dfs(point[lim].left,step+1);
			codei[step]=true;
			dfs(point[lim].right,step+1);
		}
	}
}

void haffchange(int cnt){
	int n=0;
	if (point[cnt].left>=0&&reduce[tot]=='0') tot++,haffchange(point[cnt].left);
	else if(point[cnt].right>=0&&reduce[tot]=='1') tot++,haffchange(point[cnt].right);
	else ending.push_back(sum[cnt].ass);
}

int main(){
	
	ifstream file("file.in");
	if(!file.is_open()) return NULL; 
	string content;
	content.assign(istreambuf_iterator<char>(file),istreambuf_iterator<char>());
	
	for(int i=0;i<content.size();i++) File[content[i]]++;//计算每种字符出现的数量 
	for(int i=0;i<26;i++){
		sum[i].number=File[i+'a'];//a~z
		sum[i].ass=i+'a';
	}
	for(int i=0;i<26;i++){
		sum[i+26].number=File[i+'A'];//A~Z
		sum[i+26].ass=i+'A';
	}
	for(int i=52;i<62;i++){
		sum[i].number=File[(i-52)+'0'];//0~9
		sum[i].ass=(i-52)+'0';
	}
	sum[62].number=File[' '],sum[62].ass=' ';//空格 
	sum[63].number=File[','],sum[63].ass=',';//逗号
	sum[64].number=File['.'],sum[64].ass='.';//句号 
	sum[65].number=File[':'],sum[65].ass=':';//冒号
	sum[66].number=File['('],sum[66].ass='(';
	sum[67].number=File[')'],sum[67].ass=')';
	sum[68].number=File['\n'],sum[68].ass='\n';
	sum[69].number=File[';'],sum[69].ass=';';
	sum[70].number=File['"'],sum[70].ass='"';
	sum[71].number=File['?'],sum[71].ass='?';
	sum[72].number=File['!'],sum[72].ass='!';
	for(int i=0;i<=72;i++){
		point[i].cun=sum[i].ass;
		point[i].value=sum[i].number;
		point[i].right=-1;
		point[i].left=-1;
	}
	
	for(int i=0;i<=72;i++){
		point[i].fa=i;
	}
	
	for(int i=0;i<=72;i++){
		point[i].fa=i;
	}
	int cnt=72;
	while(treemove(++cnt));
	memset(codei,0,sizeof(codei));
	dfs(cnt-1,0);
	
	freopen("code.ans","w",stdout);
	
	for(int i=72;i>=0;i--){
		cout<<point[i].cun<<" code is:";
		for(int j=0;j<point[i].code.size();j++) cout<<point[i].code[j]<<" ";
		cout<<endl;
	}
	
	printf("-----------------------------------------------------------------------------\n");	
	sort(point,point+73,cp);
	for(int i=0;i<73;i++){
		cout<<point[i].cun<<" code is:";
		for(int j=0;j<point[i].code.size();j++) cout<<point[i].code[j]<<" ";
		cout<<endl;
	}
	cout<<endl;
	cout<<"treeWPL is:"<<wpl<<endl;
	fclose(stdout);
	freopen("file.out","w",stdout);
	
	for(int i=0;i<content.size();i++){ 
		if(content[i]=='\n'){
			for(int j=0;j<point[0].code.size();j++)
				haffFile.push_back(point[0].code[j]);
		}
		else if(content[i]==' '){
			for(int j=0;j<point[1].code.size();j++)
				haffFile.push_back(point[1].code[j]);
		}
		else if(content[i]=='!'){
			for(int j=0;j<point[2].code.size();j++)
				haffFile.push_back(point[2].code[j]);
		}
		else if(content[i]=='"'){
			for(int j=0;j<point[3].code.size();j++)
				haffFile.push_back(point[3].code[j]);
		}
		else if(content[i]=='('){
			for(int j=0;j<point[4].code.size();j++)
				haffFile.push_back(point[4].code[j]);
		}
		else if(content[i]==')'){
			for(int j=0;j<point[5].code.size();j++)
				haffFile.push_back(point[5].code[j]);
		}
		else if(content[i]==','){
			for(int j=0;j<point[6].code.size();j++)
				haffFile.push_back(point[6].code[j]);
		}
		else if(content[i]=='.'){
			for(int j=0;j<point[7].code.size();j++) 
				haffFile.push_back(point[7].code[j]);
		} 
		else if(content[i]>='0'&&content[i]<='9'){
			for(int j=0;j<point[content[i]-'0'+8].code.size();j++)
				haffFile.push_back(point[content[i]-'0'+8].code[j]);
		} 
		else if(content[i]==':'){
			for(int j=0;j<point[18].code.size();j++)
				haffFile.push_back(point[18].code[j]);
		}  
		else if(content[i]==';'){
			for(int j=0;j<point[19].code.size();j++)
				haffFile.push_back(point[19].code[j]);
		} 
		else if(content[i]=='?'){
			for(int j=0;j<point[20].code.size();j++)
				haffFile.push_back(point[20].code[j]);
		} 
		else if(content[i]>='A'&&content[i]<='Z'){
			for(int j=0;j<point[content[i]-'A'+21].code.size();j++)
				haffFile.push_back(point[content[i]-'A'+21].code[j]);
		}  
		else if(content[i]>='a'&&content[i]<='z'){
			for(int j=0;j<point[content[i]-'a'+47].code.size();j++)
				haffFile.push_back(point[content[i]-'a'+47].code[j]);
		}  
	}

	for(int i=0;i<haffFile.size();i++) cout<<haffFile[i];
	
	fclose(stdout);
	freopen("file.ans","w",stdout);
	ofstream fout("reduce.out",ios::binary);
	vector<bool>::size_type n=haffFile.size();
	fout.write((const char*)&n, sizeof(std::vector<bool>::size_type));
	for (std::vector<bool>::size_type i = 0; i < n;){
		unsigned char aggr = 0;
		for (unsigned char mask=1;mask>0&&i<n;++i,mask<<=1)
	    if (haffFile.at(i))
	    	aggr |= mask;
		fout.write((const char*)&aggr, sizeof(unsigned char));
	}
	fout.close();

	// 从文件读取数据到x中
	std::vector<bool> x;
	std::ifstream fin("flie.out", ios::binary);
	fin.read((char*)&n, sizeof(std::vector<bool>::size_type));
	x.resize(n);
	for (std::vector<bool>::size_type i=0;i<n;){
		unsigned char aggr;
		fin.read((char*)&aggr,sizeof(unsigned char));
		for (unsigned char mask=1;mask>0&&i<n;++i,mask<<=1)
			x.at(i)=aggr&mask;
	}

	// 将x中的数据转化为“010101”格式的字符串
	n = x.size();
	reduce.reserve(n);
	for(std::vector<bool>::size_type i = 0; i < n; i++){
		reduce+=haffFile.at(i)?'1':'0';
	}
	while(tot<reduce.size()){
		haffchange(cnt-1);
	}
	
	for(int i=0;i<ending.size();i++) cout<<ending[i];
	return 0;
}
