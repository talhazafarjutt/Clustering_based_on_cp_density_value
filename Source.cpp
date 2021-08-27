#include<iostream>
#include<fstream>
using namespace std;
#define max 99999
struct linked
{
	int from = max, to = max, w8 = 0;
	linked* struct_NEXT = NULL;
};
class arr_list
{
public:
	int nod_id, vertex_w8;
	linked* class_NEXT;
	bool visit = true;
	void insertion(int a, int b);
	arr_list();
	~arr_list();
private:

}arr[1004];
//void arr_func(int n)
//{
//	arr = new arr_list[n];
//}
arr_list::arr_list()
{
	nod_id = max;
	vertex_w8 = 0;
	class_NEXT = NULL;
}
void arr_list::insertion(int a, int b)
{
	if (arr[a].nod_id == max)
	{
		arr[a].nod_id = a;
		goto make_nod;
	}
	else if (arr[a].nod_id != max)
	{
	make_nod:
		linked* p = new linked;
		p->from = a;
		p->to = b;
		if (arr[a].class_NEXT == NULL)
		{
			arr[a].class_NEXT = p;
		}
		else
		{
			p->struct_NEXT = arr[a].class_NEXT;
			arr[a].class_NEXT = p;
		}
	}
	else
	{
		cout << "nod not inserted" << endl;
	}
}
void assign_weight()
{
	linked* p1, * p2, * p3;
	int sum = 0;
	for (int i = 0; i < 1004; i++)
	{
		p1 = arr[i].class_NEXT;
		while (p1 != NULL)
		{
			p3 = arr[i].class_NEXT;
			while (p3 != NULL)
			{
				p2 = arr[p1->to].class_NEXT;
				while (p2 != NULL)
				{
					if (p2->to == p3->to)
					{
						++sum;
					}
					p2 = p2->struct_NEXT;
				}
				p3 = p3->struct_NEXT;
			}
			p1->w8 = sum;
			sum = 0;
			p1 = p1->struct_NEXT;
		}
	}
	p1 = NULL;
	for (int i = 0; i < 1004; i++)
	{
		p1 = arr[i].class_NEXT;
		while (p1 != NULL)
		{
			arr[i].vertex_w8 += p1->w8;
			p1 = p1->struct_NEXT;
		}
	}
}
linked* merge_linked_List(linked* p1, linked* p2)
{
	linked* merged = NULL;
	if (p1 == NULL)
	{
		return (p2);
	}
	else if (p2 == NULL)
	{
		return (p1);
	}
	if (p1->w8 >= p2->w8)
	{
		merged = p1;
		merged->struct_NEXT = merge_linked_List(p1->struct_NEXT, p2);
	}
	else {
		merged = p2;
		merged->struct_NEXT = merge_linked_List(p1, p2->struct_NEXT);
	}
	return merged;
}
void split(linked* sorce, linked** list_1, linked** list_2)
{
	linked* p1;
	linked* p2;
	p2 = sorce;
	p1 = sorce->struct_NEXT;
	while (p1 != NULL)
	{
		p1 = p1->struct_NEXT;
		if (p1 != NULL) {
			p2 = p2->struct_NEXT;
			p1 = p1->struct_NEXT;
		}
	}
	*list_1 = sorce;
	*list_2 = p2->struct_NEXT;
	p2->struct_NEXT = NULL;
}
void sort_merge_linked_list(linked** p)
{
	linked* head = *p;
	linked* a;
	linked* b;
	if ((head == NULL) || (head->struct_NEXT == NULL))
	{
		return;
	}
	split(head, &a, &b);
	sort_merge_linked_list(&a);
	sort_merge_linked_list(&b);
	*p = merge_linked_List(a, b);
}
void perculations(int arr_size, int i)
{
	int maximum = i;
	int left_Child = 2 * i + 1;
	int right_Child = 2 * i + 2;
	if (left_Child < arr_size && arr[left_Child].vertex_w8 < arr[maximum].vertex_w8)
	{
		maximum = left_Child;
	}
	if (right_Child < arr_size && arr[right_Child].vertex_w8 < arr[maximum].vertex_w8)
	{
		maximum = right_Child;
	}
	if (maximum != i)
	{
		swap(arr[i], arr[maximum]);
		perculations(arr_size, maximum);
	}
}

void tree_heap_sort(int arr_size)
{
	for (int i = arr_size / 2 - 1; i >= 0; i--)
		perculations(arr_size, i);

	for (int i = arr_size - 1; i >= 0; i--)
	{
		swap(arr[0].vertex_w8, arr[i].vertex_w8);
		swap(arr[0].nod_id, arr[i].nod_id);
		swap(arr[0].class_NEXT, arr[i].class_NEXT);
		perculations(i, 0);
	}
}
float density(int edge, int nod)
{
	return (2 * edge) / (nod * (nod - 1));
}
float cp(int edge, int nod)
{
	return edge / (density(edge, nod) * nod);
}
void display()
{
	linked* p1;
	for (int i = 0; i < 1004; i++)
	{
		cout << "w8=" << arr[i].vertex_w8 << "|" << " visited " << arr[i].visit << " | " << "Nod id " << arr[i].nod_id << "->";
		p1 = arr[i].class_NEXT;
		while (p1 != NULL)
		{
			cout << "[" << p1->from << "," << p1->to << "(" << p1->w8 << ")" << "]";
			p1 = p1->struct_NEXT;
		}cout << endl;
	}
}
void linked_list(linked* p)
{
	linked* head = NULL;
	while (p != NULL)
	{
		linked* p1 = new linked;
		p1->from = p->from;
		p1->to = p->to;
		p1->struct_NEXT = p->struct_NEXT;
		if (head == NULL)
		{
			head = p1;
		}
		else
		{
			p1->struct_NEXT = head->struct_NEXT;
			head = p1;
		}

	}

}
arr_list::~arr_list()
{
}
int main()
{
	int maximum_size = 0, get;
	ifstream high("email_data_set.txt");
	while (!high.eof())
	{
		high >> get;
		if (get > maximum_size)
		{
			maximum_size = get;
		}
	}
	high.close();
	cout << "maximum no. of nodes " << maximum_size << endl;
	int a1, b2, count = 0;
	float cluster_p;
	ifstream out;
	out.open("facebook_combined.txt");
	while (!out.eof())
	{
		out >> a1;
		out >> b2;
		arr[a1].insertion(a1, b2);
	}
	out.close();
	assign_weight();
	/*for (int i = 0; i < 1004; i++)
	{
		sort_merge_linked_list(&arr[i].class_NEXT);
	}*/
	tree_heap_sort(7);
	float a, b, n = 1, c = 0, cluster_edge = arr[0].vertex_w8, temp_edge = arr[0].vertex_w8, temp_nod = 1;
	//display();
	cout << "enter the values of density and cp: ";
	cin >> a >> b;
	linked* p;
	ofstream in("clusters.txt");
	for (int i = 0; i < 1004; i++)
	{
		if (arr[i].visit && arr[i].nod_id != 99999)
		{
			in << "cluster no: " << ++count << endl;
			in << arr[i].nod_id << "  " << arr[i].vertex_w8 << endl;
			p = arr[i].class_NEXT;
			while (p != nullptr)
			{
				if ((arr[p->to].visit) && (arr[p->to].nod_id != 99999))
				{
					temp_edge += arr[p->to].vertex_w8;
					++temp_nod;
					if ((density(temp_edge, temp_nod) >= a) && (cp(temp_edge, temp_nod) >= b))
					{
						in << arr[p->to].nod_id << "  " << arr[p->to].vertex_w8 << endl;
						arr[p->to].visit = false;
					}
					else
					{
						temp_edge -= arr[p->to].vertex_w8;
						--temp_nod;
					}
				}
				p = p->struct_NEXT;
			}
		}
	}
	cout << "total no. of clusters are " << count << endl;
	in.close();
}