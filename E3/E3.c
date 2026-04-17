#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    char name[50];
    int priority;
} Patient;

Patient heap[MAX_SIZE];
int size = 0;

// Helper to swap two patients
void swap(Patient *a, Patient *b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// 1. push: Add patient and heapify-up
void push(Patient p) {
    if (size >= MAX_SIZE) return;
    
    heap[size] = p;
    int current = size;
    size++;

    // Heapify-up
    while (current > 0 && heap[current].priority > heap[(current - 1) / 2].priority) {
        swap(&heap[current], &heap[(current - 1) / 2]);
        current = (current - 1) / 2;
    }
}

// 2. pop: Remove highest priority and heapify-down
Patient pop() {
    Patient top = heap[0];
    heap[0] = heap[size - 1];
    size--;

    int current = 0;
    while (2 * current + 1 < size) {
        int largest = 2 * current + 1; // Left child
        int right = 2 * current + 2;
        
        if (right < size && heap[right].priority > heap[largest].priority) {
            largest = right;
        }
        
        if (heap[current].priority >= heap[largest].priority) break;
        
        swap(&heap[current], &heap[largest]);
        current = largest;
    }
    return top;
}

// 3. peek: View the highest priority patient
void peek() {
    if (size > 0) {
        printf("Current highest priority: %s (Priority %d)\n", heap[0].name, heap[0].priority);
    }
}

int main() {
    // Adding 5 patients with different priorities
    Patient patients[] = {
        {"Nguyen Van A", 2},
        {"Tran Thi B", 5},
        {"Le Van C", 1},
        {"Pham Van D", 4},
        {"Hoang Thi E", 3}
    };

    for (int i = 0; i < 5; i++) {
        printf("Adding %s...\n", patients[i].name);
        push(patients[i]);
        peek();
    }

    printf("\n--- Order of Treatment ---\n");
    while (size > 0) {
        Patient p = pop();
        printf("Calling Patient: %-15s | Priority: %d\n", p.name, p.priority);
    }

    return 0;
}