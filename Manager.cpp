#include "Manager.h"


Manager::Manager() = default;
void Manager::addStore(Store store, bool new_time) {
	if (new_time) {
		current_time++;
		this->timeline.addTime({ branch_name,current_time });


	}


	try {
		if (store.get_is_original()) {

			auto node = stores_hash.getIf(convertToInt(store.get_name()),
				[store](Node<Store>*& target_store) {
					return
						target_store->get_data().get_name() == store.get_name();


				});
		cout << "there is a main branch with that name"<<endl;
		return;//if there was on we cant add any more
		}
	}
	catch (const char* err) {
		//pass
	}
	if (!store.get_is_original()) {
		try {
			auto node = stores_hash.getIf(convertToInt(store.get_name()),
				[store](Node<Store>*& target_store) {
					return
						target_store->get_data().get_name() == store.get_name();


				});
		}
		catch (const char* err) {
			cout << "no main branch with that name"<<endl;
			return;
		}
		try {
			auto node = stores_hash.getIf(convertToInt(store.get_name()),
				[store](Node<Store>*& target_store) {
					return
						target_store->get_data().get_name() == store.get_name() && target_store->get_data().get_individualName() == store.get_individualName();


				});
			cout << "there is an store with an identical main brancch  and individual name " << endl;
			return;//we dont want two branches with the same name and main branch name
		}

		catch(const char* err){
			//pass

		}
	}



	

	
	auto node=stores.push(store);
	stores_hash.add(node,convertToInt(store));
	kdtree.push(node);
	string name = store.get_name();
	try {
		Pair<string, KDTree>& p= kdrees.getIf(convertToInt(name), [name](const Pair<string, KDTree>& p) {return (p.first == name); });
		p.second.push(node);
	}
	catch(const char* err){
		KDTree tree;
		tree.push(node);
		kdrees.add(Pair<string, KDTree>(name, tree), convertToInt(name));
	}
	timeline.addSubTime(current_time, branch_name, this->stores, this->neighbors);

	
	

}
int Manager::convertToInt(const Store& store) const {
	return convertToInt(store.get_name());

}
int Manager::convertToInt(string name) const {
	int result=0;
	for (auto i : name) {
		result += i;
	}
	return result;

}
void Manager::addNeighborhood(Neighborhood neighborhood,  bool new_time) {
	if (new_time) {
		current_time++;
		this->timeline.addTime({ branch_name,current_time });


	}
	auto node=this->neighbors.push(neighborhood);
	this->neighborhoods_hash.add(node, convertToInt(neighborhood.getName()));
	timeline.addSubTime(current_time, branch_name, this->stores, this->neighbors);

	
}
void Manager::printLargest() {
	if (stores.get_size() == 0) {
		cout << "there is no store" << endl;
		return;
	}

	string* arr = new string[stores.get_size()];
	int cnt = 0;
	for (auto i : stores) {
		arr[cnt] = i->get_data().get_name();
		cnt++;

	}
	mergeSort(arr, stores.get_size(), [](string s) {return s; });

	Pair<string, int>* result = new Pair<string, int>[stores.get_size()];
	string prev = "";
	cnt = -1;
	for (int i = 0; i < stores.get_size(); i++) {
		if (prev != arr[i]) {
			cnt++;
			result[cnt] = { arr[i],1 };
			prev = arr[i];

		}
		else {
			result[cnt].second++;

		}
	}
	cnt++;
	mergeSort(result, cnt, [](Pair<string, int> p) {return p.second; });

	cout << result[cnt-1].first<<endl;
	


}
void Manager::printCooByName(string name) {
	LinkedList<Node<Store>*> result=stores_hash.get(convertToInt(name));  
	for (auto i : result) {
		if (i->get_data()->get_data().get_name() == name) {
			cout << "( "<<i->get_data()->get_data().get_x()<<" , " <<i->get_data()->get_data().get_y()<<" )"<<endl;
		}
	}

}
void Manager::printKDTree_DEBUG() {
	this->kdtree.BFSPrint();
}
void Manager::deleteByCoo(int x, int y,  bool new_time) {
	if (new_time) {
		current_time++;
		this->timeline.addTime({ branch_name,current_time });


	}
	Node<Store>* node=kdtree.deleteByCoo(x, y);
	string name = node->get_data().get_name();
	Pair<string, KDTree>& p =kdrees.getIf(convertToInt(name), [name](Pair<string, KDTree>& p) {return (p.first == name); });
	p.second.deleteByCoo(x, y);
	stores.deleteByAdr(node);
	stores_hash.deleteIf(convertToInt(node->get_data().get_name()),
		[x, y](Node<Store>* node){
			return node->get_data().get_x() == x && node->get_data().get_y() == y; 
		});
	deleted_stores.pushByAdr(node);
	timeline.addSubTime(current_time, branch_name, this->stores, this->neighbors);

	




}
void Manager::printAllBranches(string name) {
	LinkedList<Node<Store>*> list = stores_hash.get(convertToInt(name));

	auto node = stores_hash.getIf(convertToInt(name),
		[name](Node<Store>*& store) {
			return store->get_data().get_individualName() == name;

		});
	string main_branch_name = node->get_data().get_name();
	for (auto i : list) {
		if (i->get_data()->get_data().get_name() == name) {
			cout << i->get_data()->get_data() << endl;
		}
	}
}
void Manager::printNearestBranch(string name, int x, int y) {
	try {
		Node<Store>* res=kdrees.getIf(convertToInt(name), [name](const Pair<string, KDTree>& p) {return (p.first == name); }).second.findTheClosestPoint(x, y);
		cout << res->get_data()<<endl;

	}
	catch (const char * error) {
		cout << error;
		
	}

}
void Manager::printInNeighbor(string name) {
	auto node = neighborhoods_hash.getIf(convertToInt(name),
		[name](Node<Neighborhood>*& neighbor) {
			return neighbor->get_data().getName() == name;

		});
	kdtree.searchNeighborhood(node->get_data());

}
void Manager::printAllInRange(int x, int y, float R) {
	kdtree.printAllNodesInRange(x, y, R);
}
void Manager::readFromFile(string path) {
	/*FILE* file = fopen((path + "//stores.txt").c_str(), "r+");

	int x, y;
	char name[100];
	char individual_name[100];
	while (!feof(file)) {
		fscanf_s(file,"%s %s %d %d", name, individual_name, &x, &y);


		Store store({ x,y },string( name), string(individual_name), individual_name == name);
		this->addStore(store, false);


	}

	fclose(file);

	FILE* file_n = fopen((path + "//neighbores.txt").c_str(), "r+");

	int left,top,right,bottom;
	
	while (!feof(file_n)) {
		fscanf_s(file, "%s %d %d %d %d", name, &left,&top,&right,&bottom);



	
		this->addNeighborhood(Neighborhood(string(name),left,right,bottom,top), false);


	}

	fclose(file_n);*/
	ifstream file(path+"//stores.txt",ios::in);
	string line;
    if (!file.is_open()) {
		ofstream file(path + "//stores.txt");
		file.close();
	}
	string name;
	string individual_name;
	int x, y;
	while (!file.eof()) {

		getline(file, line);
		if (line == "")
			break;
		stringstream s(line);

		s >> name>>individual_name>>x>>y;
		
		Store store({ x,y }, name, individual_name, individual_name == name);
		this->addStore(store,false);
		

	}
	file.close();
	int left, top, right, bottom;
	ifstream file_neighbor(path + "//neighbors.txt",ios::in);


	if (!file_neighbor.is_open()) {
		ofstream file_neighbor(path + "//stores.txt");
		file_neighbor.close();
	}

	while (!file_neighbor.eof()) {
		getline(file_neighbor, line);
		if (line == "")
			break;
		stringstream s(line);

		s >> name >> left >> top >> right >> bottom;
		this->addNeighborhood(Neighborhood(name, left, right, bottom, top),false);

	}
	file_neighbor.close();

}
void Manager::writeInFile(string path) {
	ofstream file(path + "//stores.txt");
	for (auto i : stores) {
		auto store = i->get_data();
		file << store.get_name() << ' ' << store.get_individualName() << ' ' << store.get_x() << ' ' << store.get_y()<<endl;
	}
	file.close();
	ofstream file_neighbor(path + "//neighbors.txt");
	for (auto n : neighbors) {
		auto neighbor = n->get_data();
		auto coo = neighbor.getCoo();
		file_neighbor << neighbor.getName() << ' ' << coo.first.first << ' ' << coo.second.second << ' ' << coo.first.second << ' ' << coo.second.first<<endl;
	}
	file_neighbor.close();
}