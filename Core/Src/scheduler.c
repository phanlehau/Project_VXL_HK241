#include "scheduler.h"

// Biến toàn cục
sTask SCH_tasks_G[SCH_MAX_TASKS];

uint8_t ReadyQueue[SCH_MAX_TASKS]; // Lưu chỉ số các tác vụ cần chạy
uint8_t ReadyQueueSize = 0;        // Kích thước hàng đợi
uint8_t TasksSize = 0;

// Hàm thêm tác vụ vào hàng đợi tại vị trí thích hợp
void SCH_Insert_Into_Queue(uint8_t taskIndex) {
    uint8_t i = 0;

    // Điều chỉnh delay tương đối khi thêm vào hàng đợi
    for (i = 0; i < ReadyQueueSize; i++) {
        if (SCH_tasks_G[taskIndex].Delay < SCH_tasks_G[ReadyQueue[i]].Delay) {
            SCH_tasks_G[ReadyQueue[i]].Delay -= SCH_tasks_G[taskIndex].Delay;
            break;
        }
        SCH_tasks_G[taskIndex].Delay -= SCH_tasks_G[ReadyQueue[i]].Delay;
    }

    // Dịch chuyển các phần tử còn lại trong hàng đợi
    for (uint8_t j = ReadyQueueSize; j > i; j--) {
        ReadyQueue[j] = ReadyQueue[j - 1];
    }

    // Thêm tác vụ vào vị trí phù hợp
    ReadyQueue[i] = taskIndex;
    ReadyQueueSize++;
}

// Hàm loại bỏ tác vụ khỏi đầu hàng đợi
uint8_t SCH_Remove_From_Queue() {
    if (ReadyQueueSize == 0) {
        return SCH_MAX_TASKS; // Hàng đợi trống
    }

    uint8_t taskIndex = ReadyQueue[0];

    // Điều chỉnh delay cho tác vụ tiếp theo trong hàng đợi
    if (ReadyQueueSize > 1) {
        SCH_tasks_G[ReadyQueue[1]].Delay += SCH_tasks_G[taskIndex].Delay;
    }

    // Dịch chuyển các phần tử còn lại về phía trước
    for (uint8_t i = 1; i < ReadyQueueSize; i++) {
        ReadyQueue[i - 1] = ReadyQueue[i];
    }

    ReadyQueueSize--;
    return taskIndex;
}

// Hàm khởi tạo
void SCH_Init(void) {
    ReadyQueueSize = 0;
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
}

// Thêm tác vụ
uint8_t SCH_Add_Task(void (*pFunction)(), uint16_t DELAY, uint16_t PERIOD) {
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++) {
        if (!SCH_tasks_G[i].pTask) {  // Tìm vị trí trống
            SCH_tasks_G[i].pTask = pFunction;
            SCH_tasks_G[i].Delay = DELAY / 10;
            SCH_tasks_G[i].Period = PERIOD / 10;
            SCH_tasks_G[i].RunMe = 0;

            // Thêm vào hàng đợi
            SCH_Insert_Into_Queue(i);
            TasksSize++;
            return i;  // Trả về chỉ số tác vụ
        }
    }
    return SCH_MAX_TASKS;  // Hết chỗ trống
}

// Xóa tác vụ
void SCH_Delete_Task(uint8_t index) {
    if (index < SCH_MAX_TASKS) {
        SCH_tasks_G[index].pTask = NULL;
        SCH_tasks_G[index].Delay = 0;
        SCH_tasks_G[index].Period = 0;
        SCH_tasks_G[index].RunMe = 0;
    }
}

// Cập nhật các tác vụ
void SCH_Update(void) {
    if (ReadyQueueSize == 0) return;

    // Giảm thời gian chờ của tác vụ đầu tiên
    uint8_t taskIndex = ReadyQueue[0];
    if (SCH_tasks_G[taskIndex].Delay > 0) {
        SCH_tasks_G[taskIndex].Delay--;
    }

    // Nếu Delay về 0, xử lý tác vụ
    if (SCH_tasks_G[taskIndex].Delay == 0) {
        SCH_tasks_G[taskIndex].RunMe = 1;

        // Loại bỏ khỏi đầu hàng đợi
        SCH_Remove_From_Queue();

        // Nếu là tác vụ định kỳ, tính toán lại Delay và thêm vào hàng đợi
        if (SCH_tasks_G[taskIndex].Period > 0) {
            SCH_tasks_G[taskIndex].Delay = SCH_tasks_G[taskIndex].Period;
            SCH_Insert_Into_Queue(taskIndex);
        }
    }
}

// Thực thi các tác vụ
void SCH_Dispatch_Tasks(void) {
	for (uint8_t i = 0; i < TasksSize; i++) {
	    //uint8_t taskIndex = ReadyQueue[i];
		  uint8_t taskIndex = i;
	    if (SCH_tasks_G[taskIndex].RunMe > 0) {
	        (*SCH_tasks_G[taskIndex].pTask)();
	        SCH_tasks_G[taskIndex].RunMe = 0;

	        if (SCH_tasks_G[taskIndex].Period == 0) {
	            SCH_Delete_Task(taskIndex);
	        }
	    }
	}
}
