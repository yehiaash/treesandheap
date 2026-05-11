#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Patient {
    int id;
    string name;
    int severity;
    int arrivalTime;

    Patient(int pid, string pname, int pseverity, int parrivaltime) {
        id = pid;
        name = pname;
        severity = pseverity;
        arrivalTime = parrivaltime;
    }

    bool operator<(const Patient& other) const {
        if (severity != other.severity)
            return severity < other.severity;          
        return arrivalTime > other.arrivalTime;        
    }
};
vector <Patient> heap;

bool higherPriority(Patient newpatient, Patient oldpatient) {
    if (newpatient.severity > oldpatient.severity || 
       (newpatient.severity == oldpatient.severity && newpatient.arrivalTime < oldpatient.arrivalTime)) return true;
    else return false ;
}

void heepfy_up(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (higherPriority(heap[i], heap[parent])) {
            swap(heap[i], heap[parent]);
            i = parent;
        }
        else {
            break;
        }
    }
}

void insert_patient(Patient p) {
    heap.push_back(p);
    heepfy_up((int)heap.size() - 1);
}

void Heapfy_down(int i) {
    int n = heap.size();
    while (true) { 
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;
        int best = i;

        if (left < n && higherPriority(heap[left], heap[best])) {
            best = left;
        }
       
        if (right < n && higherPriority(heap[right], heap[best])) {
               best = right;
        }

        if (best != i) {
            swap(heap[i], heap[best]);
            i = best;
        }
        else {
            break;
        }          
    }
}

void Treat_Next_Patient() {
    if (heap.empty()) return;

    heap[0] = heap.back();
    heap.pop_back();
    if(!heap.empty()) Heapfy_down(0);

}

void View_Next_Patient() {
    if (!heap.empty()) {
        cout << "  [ID=" << heap[0].id
            << " \"" << heap[0].name << "\""
            << " Sev=" << heap[0].severity
            << " T=" << heap[0].arrivalTime << "]" << endl;
    }
    else {
        cout << "There is no patient";
    }
}

void Update_Severity(int id , int newseverity){
    for (int i = 0; i < (int)heap.size(); i++) {
        if (heap[i].id == id) {
            int old = heap[i].severity;
            heap[i].severity = newseverity;
            if (newseverity > old) heepfy_up(i);
            else if (newseverity < old)
            {
                Heapfy_down(i);
            }
            return;
        }
    }
}

void Display_All_Patients_By_Level() {
    if (heap.empty()) return;
    int level_limit = 1; 
    int count = 0;       

    for (int i = 0; i < (int)heap.size(); i++) {
        cout << "  [ID=" << heap[i].id
            << " \"" << heap[i].name << "\""
            << " Sev=" << heap[i].severity
            << " T=" << heap[i].arrivalTime << "]";
        count++;
        if (count == level_limit) { 
            cout << endl;          
            level_limit *= 2;      
            count = 0;             
        }
    }
    cout << endl;
}

//STLS
priority_queue<Patient> pq;
void insetTOqueue(Patient p) {
    pq.push(p);
}

void Treat_Next_Patient_STLS() {
    if (pq.empty()) return;
    pq.pop();
}

void View_Next_Patient_STLS() {
    if (!pq.empty()) {
        cout << "  [ID=" << pq.top().id
            << " \"" << pq.top().name << "\""
            << " Sev=" << pq.top().severity
            << " T=" << pq.top().arrivalTime << "]" << endl;
    }
    else {
        cout << "There is no patient";
    }
}


void Display_All_STL_PQ() {
    priority_queue<Patient> temp_pq = pq; 
    cout << "STL Priority Queue:" << endl;
    while (!temp_pq.empty()) {
        Patient p = temp_pq.top();
        cout << "  [ID=" << p.id << " \"" << p.name << "\" Sev=" << p.severity << " T=" << p.arrivalTime << "]" << endl;
        temp_pq.pop();
    }
}

void line() {
    cout << "-----------------------------------------------------------------------------"<<endl;
}

int main() {
    Patient allp[] = {
    Patient(1, "Shimaa", 9, 12),
    Patient(2, "Fatma", 10, 5),
    Patient(3, "Manal", 7, 2),
    Patient(4, "Alaa", 10, 15),
    Patient(5, "Ahmed", 5, 10),
    Patient(6, "Sara", 8, 5),
    Patient(7, "Omar", 8, 3),
    Patient(8, "Mona", 4, 1),
    Patient(9, "Youssef", 3, 20),
    Patient(10, "Zain", 7, 8),
    Patient(11, "Karem", 5, 2),
    Patient(12, "Amal", 6, 11),
    Patient(13, "Samy", 1, 30),
    Patient(14, "Dina", 9, 4),
    Patient(15, "Nader", 2, 25),
    Patient(16, "Ali", 4, 18),
    Patient(17, "Tarek", 8, 22),
    Patient(18, "Fady", 5, 9),
    Patient(19, "Rana", 6, 14),
    Patient(20, "Mostafa", 3, 6),
    Patient(21, "Hend", 9, 21),
    };

    for (Patient p : allp) {
        insert_patient(p);
        insetTOqueue(p);
    }


    Display_All_Patients_By_Level();
    line();
    Display_All_STL_PQ();
    line();

    View_Next_Patient();
    line();
    View_Next_Patient_STLS();
    line();

    Update_Severity(4, 10);
    Update_Severity(5, 2); 

    Display_All_Patients_By_Level();
    line();
    Display_All_STL_PQ();
    line();
    Treat_Next_Patient();
    Treat_Next_Patient_STLS();
    Display_All_Patients_By_Level();
    line();
    Display_All_STL_PQ();
    line();
    return 0;
}