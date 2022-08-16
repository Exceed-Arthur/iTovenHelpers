#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;


const string ogFileName = "itoven_file_list_one.txt";
const string newFileName = "itoven_file_list_NEW.txt";


string lower(string S) {
	string s;
	for (int i=0; i < S.length(); i++) {
		s[i] = tolower(S[i]);
	}
  cout << s << endl;
	return s;

}

void SplitString(string s, vector<string> &v){
	string temp = "";
	for(int i=0;i<s.length()-1;++i){
    int j = i + 1;
		if (s[i] == ',' && s[j] == ' ') {
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}

	}
	v.push_back(temp);
}

void PrintVector(vector<string> v){
	for(int i=0;i<v.size();++i)
		cout<<v[i]<<endl;
	cout<<"\n";
}

bool StringContains(string s, string t) {
	if (s.find(t) != std::string::npos) {
    std::cout << "found!" << '\n';
		return true;
	}
	return false;
}

void FilterVector(vector<string> &v, string filterPhrase){
  vector<string> heapVector;
  for(int i=0;i<v.size();++i) {
		if (StringContains(v.at(i), filterPhrase)) {
      //v.erase(std::next(v.begin(), i), std::next(v.begin(), i+1));
      heapVector.push_back(v.at(i));
      cout << v.at(i) << endl;
    }
  }
  v = heapVector;
}

void FilterVectorPhrases(vector<string> &v, string filterPhrases[3]){
  vector<string> heapVector;
  for(int i=0;i<v.size();++i) {
		if (StringContains(v.at(i), filterPhrases[0])) {
      //v.erase(std::next(v.begin(), i), std::next(v.begin(), i+1));
      heapVector.push_back(v.at(i));
      cout << v.at(i) << endl;
    }
		else if (StringContains(v.at(i), filterPhrases[1])) {
			//v.erase(std::next(v.begin(), i), std::next(v.begin(), i+1));
			heapVector.push_back(v.at(i));
			cout << v.at(i) << endl;
		}
		else if (StringContains(v.at(i), filterPhrases[2])) {
			//v.erase(std::next(v.begin(), i), std::next(v.begin(), i+1));
			heapVector.push_back(v.at(i));
			cout << v.at(i) << endl;
		}
  }
  v = heapVector;
}


string trimmedString(string s) { //Remove 1 leading whitespace
	vector<char> v;
	for (int i=0; i<s.size(); i++) {
		if (i==0) {
			if (s[i] != ' ') {
				v.push_back(s[i]);
			}
		}
		else if (i == s.size()-1) {
			if (s[i] != ' ' && s[i] != ',') {
				v.push_back(s[i]);
			}
		}
		else {
			v.push_back(s[i]);
		}
	}
	string builtString = "";
	for (const auto &e : v) builtString+=e;
	cout << endl << builtString;
	return builtString;
}




void WriteVectorToFile(vector<string> v, string newFileName) {
	// Create and open a text file
	/*
  ofstream newFile(newFileName);
	string additionToFile;
	for(int i=0;i<v.size();++i) {
    additionToFile = additionToFile + "'" + v.at(i) + "', ";
	}
	newFile << "[" << additionToFile << "]";
	cout << "Wote to file!";
	*/
	std::ofstream outFile(newFileName);
// the important part
	outFile << "[";

	for (const auto &e : v) outFile << "'" << trimmedString(e) << "', ";
	outFile << "]";
}

int main()
{
  // Initialize array of pointer
  string scaleNames[7] = { "Phrygian", "Dorian", "Lydian", "Locrian",
                            "Harmonic Minor", "Natural Minor", "Melodic Minor"};
  string keyNames[23] = { "A ", "Ab ", "A#","B ", "Bb", "B#","C ", "Cb", "C#",
               "D ", "Db", "D#","E ", "Eb", "E#","F ", "Fb", "F#","G ", "Gb", "G#"};
  string signatureNames[8] = { "Two Two", "Two Four","Three Four", "Four Two", "Four Four","Four Eight", "Five Four",
                            "Five Eight"};
	string lengthNames[2] = { "Fragment", "Grand"};
	string typeNames[2] = { "Natural", "Melodical"};


  std::ifstream ifs(ogFileName); // Incoming File Stream
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) ); // Copy to std::string
  vector<string> iTovenObjectList;
  SplitString(content, iTovenObjectList); // Split after delimiter to std::vector<int> v;

	for (int i=0; i<7; i++){
		vector<string> scaleVector = iTovenObjectList;
		cout<< scaleVector.size() << " ";
		string fileName = scaleNames[i] + "Literal.py";
		FilterVector(scaleVector, scaleNames[i]);
		if (scaleVector.size() > 0)
			WriteVectorToFile(scaleVector, fileName);
	}
	for (int i=0; i<20; i++){
		vector<string> keyVector = iTovenObjectList;
		FilterVector(keyVector, keyNames[i]);
		PrintVector(keyVector);
		if (keyNames[i][1] == '#') {
			char character = keyNames[i][0];
			keyNames[i] = string(1, character) + "Sharp";
		}
		if (keyVector.size() > 0)
			WriteVectorToFile(keyVector, keyNames[i] + "Literal.py");
	}

	for (int i=0; i<2; i++){
		vector<string> keyVector = iTovenObjectList;
		FilterVector(keyVector, typeNames[i]);
		PrintVector(keyVector);
		if (keyNames[i][1] == '#') {
			char character = typeNames[i][0];
			typeNames[i] = string(1, character) + "Sharp";
		}
		if (keyVector.size() > 0)
			WriteVectorToFile(keyVector, typeNames[i] + "Literal.py");
	}


  return 0;
}
