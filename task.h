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
void Sort(int variable);
void LoadTasks();
void SaveTasks();
}
#endif
