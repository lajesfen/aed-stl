#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#define MAX_Q_SIZE 100

struct element {
    int key;
};

class queue {
private:
    element list[MAX_Q_SIZE];
    int front, rear;

public:
    int isfull() {
        if(front == ((rear + 1) % MAX_Q_SIZE)) {
            return 1;
        }
        return 0;
    }

    int isempty() {
        if(front == rear) {
            return 1;
        }
        return 0;
    }

    element _front() {
        return list[(front + 1) % MAX_Q_SIZE];
    }

    void enqueue(element e) {
        rear = (rear + 1) % MAX_Q_SIZE;
        list[rear] = e;
    }

    void dequeue() {
        front = (front + 1) % MAX_Q_SIZE;
    }
};

#endif //ALGORITHM_QUEUE_H
