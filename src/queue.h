#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#define MAX_Q_SIZE 100

template <typename T>
class Queue {
private:
    T list[MAX_Q_SIZE];
    int front_index, rear_index;

public:
    Queue() {
        front_index = 0;
        rear_index = 0;
    }

    int isFull() {
        if(front_index == ((rear_index + 1) % MAX_Q_SIZE)) {
            return 1;
        }
        return 0;
    }

    int isEmpty() {
        if(front_index == rear_index) {
            return 1;
        }
        return 0;
    }

    T front() {
        return list[(front_index + 1) % MAX_Q_SIZE];
    }

    void enqueue(T e) {
        if(isFull()) return;
        rear_index = (rear_index + 1) % MAX_Q_SIZE;
        list[rear_index] = e;
    }

    T dequeue() {
        T item = front();
        front_index = (front_index + 1) % MAX_Q_SIZE;
        return item;
    }

    int size() {
        return (rear_index - front_index + MAX_Q_SIZE) % MAX_Q_SIZE;
    }
};

#endif //ALGORITHM_QUEUE_H
