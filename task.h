#ifndef TASK_H_
#define TASK_H_
#include <pessum.h>
#include <vector>
namespace task {
struct Task {
  std::string taskstr, group;
  int priority;
  time_t date, duedate;
  double prioritization;
};
extern pessum::luxreader::DataFile tasklistlux;
extern std::vector<Task> tasklist;
void MainLoop();
void DisplayTasks();
void Prioritize();
void ToggleSpaces(bool spaces);
void Sort(int variable = 5);
void LoadTasks();
void SaveTasks();
void AddTask();
void DeleteTask(int pointer);
void EditTask(int pointer);
int SelectSort();
bool CheckStr(std::string str);
}
#endif
