#include "iostream"
#include "fstream"
#include <queue>
using namespace std;
const int maxDinh = 20;
bool visited[maxDinh] = { false };

struct node {
	int dinhKe;
	int trongSo;
	node* link;
};

struct danhSachKe {
	node* dsk[maxDinh];
	int soDinh; // số đỉnh của graph
};

void readFile(danhSachKe& list) {
	ifstream inFile("AdjacencyList.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep.";
		return;
	}
	// cho danh sách = null hết
	for (int i = 0; i < maxDinh; i++)
		list.dsk[i] = NULL;
	// Nhap số đỉnh tổng
	inFile >> list.soDinh;
	for (int i = 0; i < list.soDinh; i++) {
		int soDinhKe;
		inFile >> soDinhKe;
		for (int j = 0; j < soDinhKe; j++) {
			node* newNode = new node();
			inFile >> newNode->dinhKe;
			inFile >> newNode->trongSo;
			newNode->link = NULL;
			// Thêm vào single list theo đỉnh tương ứng 
			if (list.dsk[i] == NULL)  // chưa có đỉnh kề nào hết 
				list.dsk[i] = newNode;
			else { // đã có đỉnh kề trước đó thêm vào cuối single list 
				node* temp = list.dsk[i];
				while (temp->link != NULL)
					temp = temp->link;
				temp->link = newNode;
			}
		}
	}
}

void xuatDanhSachKe(danhSachKe list) {
	cout << "GRAPH";
	for (int i = 0; i < list.soDinh; i++) {
		cout << "\n(" << i << "): ";
		node* pointer = list.dsk[i];
		while (pointer) {
			cout << "(" << pointer->dinhKe << "," << pointer->trongSo << ") ";
			pointer = pointer->link;
		}
	}
}

void BFS(int u, danhSachKe list) {
	// Tạo hàng đợi 
	queue <int> hangDoi;
	hangDoi.push(u);
	visited[u] = true;
	while (hangDoi.empty() == false)
	{
		int v = hangDoi.front(); // Lấy đỉnh ở đầu hàng đợi 
		hangDoi.pop();
		cout << v << " ";

		// Duyệt qua tất cả các đỉnh kề của v
		node* temp = list.dsk[v];
		while (temp != NULL) {
			int checkDinh = temp->dinhKe;
			// Nếu chưa thăm thì đẩy x vào hàng đợi 
			if (visited[checkDinh] == false) {
				hangDoi.push(checkDinh);
				visited[checkDinh] = true;
			}
			temp = temp->link;
		}
	}
}

void DFS(int u, danhSachKe list) {
	cout << u << " ";
	visited[u] = true; // đánh dấu đỉnh u đã được thăm 

	// Duyệt qua tất cả các đỉnh kề của u
	node* temp = list.dsk[u];
	while (temp != NULL) {
		int v = temp->dinhKe;
		if (!visited[v])
			DFS(v, list);
		temp = temp->link;
	}
}

int main() {
	danhSachKe list;
	readFile(list);
	xuatDanhSachKe(list);

	cout << "\nBFS Traversal: ";
	BFS(0, list);

	// Reset mảng visited ( mảng viếng thăm )
	for (int i = 0; i < maxDinh; i++) {
		visited[i] = false;
	}

	cout << "\nDFS Traversal: ";
	DFS(0, list);
}
