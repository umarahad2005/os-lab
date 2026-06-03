#include <iostream>
using namespace std;

struct queue {
    int arr[200];
    int front;
    int rear;

    queue() { front = rear = -1; }

    void enqueue(int x) {
        if (rear == 199) { cout << "Queue is full" << endl; return; }
        if (front == -1) front = 0;
        rear++;
        arr[rear] = x;
    }

    void dequeue() {
        if (front == -1 || front > rear) { cout << "Queue is empty" << endl; return; }
        front++;
    }

    bool isempty() { return (front == -1 || front > rear); }
};

int main() {
    cout << "Welcome to Round Robin - Umar Ahad Usmani SAP: 60199" << endl;

    int n, quatum_time;
    cout << "Kindly enter the number of processes: ";
    cin >> n;
    cout << "Kindly enter the quantum time: ";
    cin >> quatum_time;
    cout << "\n";

    int arival_time[n], burst_time[n], remaining_burst_time[n];
    int waiting_time[n], turnaround_time[n];
    bool inQueue[n];  
    for (int i = 0; i < n; i++) {
        cout << "Kindly enter the arrival time of process " << i+1 << ": ";
        cin >> arival_time[i];
        cout << "Kindly enter the burst time of process  " << i+1 << ": ";
        cin >> burst_time[i];
        remaining_burst_time[i] = burst_time[i];
        inQueue[i] = false;
    }

    queue q;
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        if (arival_time[i] <= time) {
            q.enqueue(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {

        if (q.isempty()) {
            time++;
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && arival_time[i] <= time && remaining_burst_time[i] > 0) {
                    q.enqueue(i);
                    inQueue[i] = true;
                }
            continue;
        }

        int process_index = q.arr[q.front];
        q.dequeue();

        if (remaining_burst_time[process_index] > quatum_time) {
            time += quatum_time;
            remaining_burst_time[process_index] -= quatum_time;

            for (int j = 0; j < n; j++)
                if (!inQueue[j] && arival_time[j] <= time && remaining_burst_time[j] > 0) {
                    q.enqueue(j);
                    inQueue[j] = true;
                }

            q.enqueue(process_index);

        } else {
            time += remaining_burst_time[process_index];
            remaining_burst_time[process_index] = 0;
            waiting_time[process_index]     = time - arival_time[process_index] - burst_time[process_index];
            turnaround_time[process_index]  = time - arival_time[process_index];
            completed++;

            for (int j = 0; j < n; j++)
                if (!inQueue[j] && arival_time[j] <= time && remaining_burst_time[j] > 0) {
                    q.enqueue(j);
                    inQueue[j] = true;
                }
        }
    }

    
    cout << "\nProcess\tAT\tBT\tWT\tTAT\n";
    cout << "------------------------------------\n";
    float sumWT = 0, sumTAT = 0;
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1     << "\t"
             << arival_time[i] << "\t"
             << burst_time[i]  << "\t"
             << waiting_time[i] << "\t"
             << turnaround_time[i] << "\n";
        sumWT  += waiting_time[i];
        sumTAT += turnaround_time[i];
    }
    cout << "------------------------------------\n";
    cout << "Average WT  = " << sumWT  / n << "\n";
    cout << "Average TAT = " << sumTAT / n << "\n";

    return 0;
}