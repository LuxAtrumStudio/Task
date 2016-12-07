#include "induco.h"
#include "task.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <math.h>
#include <pessum.h>
#include <vector>

namespace task {
pessum::luxreader::DataFile tasklistlux;
std::vector<Task> tasklist;
}

void task::MainLoop() {
  bool running = true;
  std::string input = "";
  LoadTasks();
  while (running == true) {
    DisplayTasks();
    getline(std::cin, input);
  }
  SaveTasks();
}

void task::DisplayTasks() {
  int width, height, groupsize;
  width = induco::GetSize();
  height = induco::GetSize(true);
  groupsize = width / 10;
  std::cout << "TASK LIST\n";
  std::string labelline;
  labelline = "INDEX";
  while (labelline.size() >= groupsize) {
    labelline.pop_back();
  }
  while (labelline.size() < groupsize) {
    labelline += " ";
  }
  labelline += "TASK";
  while (labelline.size() >= groupsize * 6) {
    labelline.pop_back();
  }
  while (labelline.size() < groupsize * 6) {
    labelline += " ";
  }
  labelline += "GROUP";
  while (labelline.size() >= groupsize * 8) {
    labelline.pop_back();
  }
  while (labelline.size() < groupsize * 8) {
    labelline += " ";
  }
  labelline += "DUEDATE\n";
  while (labelline.size() >= groupsize * 10) {
    labelline.pop_back();
  }
  induco::Line(width);
  std::cout << labelline;
  if (tasklist.size() == 0) {
    induco::SetColor(2);
    std::cout << "NO TASKS TODO\n";
    induco::SetColor(7);
  }
  for (int i = 0; i < tasklist.size(); i++) {
    std::string line = "";
    line += std::to_string(i);
    while (line.size() >= groupsize) {
      line.pop_back();
    }
    while (line.size() < groupsize) {
      line += " ";
    }
    line += tasklist[i].taskstr;
    while (line.size() >= groupsize * 6) {
      line.pop_back();
    }
    while (line.size() < groupsize * 6) {
      line += " ";
    }
    line += tasklist[i].group;
    while (line.size() >= groupsize * 8) {
      line.pop_back();
    }
    while (line.size() < groupsize * 8) {
      line += " ";
    }
    line += induco::DisplayDate(tasklist[i].duedate, false, false);
    while (line.size() >= groupsize * 10) {
      line.pop_back();
    }
    while (line.size() < groupsize * 10) {
      line += " ";
    }
    induco::SetColor(tasklist[i].priority);
    std::cout << line;
    std::cout << "\n";
    induco::SetColor(7);
  }
  for (int i = tasklist.size(); i < height - 6; i++) {
    std::cout << "\n";
  }
  induco::Line(width);
  std::cout << "Add[a] | Compleate[d] | Edit[e] | Quit[q]\n";
}

void task::Prioritize() {
  double priorityweight = 2, timeweight = 1;
  int currenttime;
  time_t ct;
  time(&ct);
  currenttime = ct;
  for (int i = 0;
       i < tasklistlux.datafilevariables[0].stringvectorvalues.size(); i++) {
    double priority = 0;
    priority =
        timeweight *
        ((tasklistlux.datafilevariables[4].intvectorvalues[i] - currenttime) /
         86400.0);
    priority -=
        (priorityweight * tasklistlux.datafilevariables[2].intvectorvalues[i]);
    tasklist[i].prioritization = priority;
    tasklistlux.datafilevariables[5].doublevectorvalues[i] = priority;
  }
}

void task::ToggleSpaces(bool spaces) {
  if (spaces == true) {
    for (int i = 0;
         i < tasklistlux.datafilevariables[0].stringvectorvalues.size(); i++) {
      std::string tempstr =
          tasklistlux.datafilevariables[0].stringvectorvalues[i];
      for (int j = 0; j < tempstr.size(); j++) {
        if (tempstr[j] == '_') {
          tempstr[j] = ' ';
        }
      }
      tasklistlux.datafilevariables[0].stringvectorvalues[i] = tempstr;
      tempstr = tasklistlux.datafilevariables[1].stringvectorvalues[i];
      for (int j = 0; j < tempstr.size(); j++) {
        if (tempstr[j] == '_') {
          tempstr[j] = ' ';
        }
      }
      tasklistlux.datafilevariables[1].stringvectorvalues[i] = tempstr;
    }
  }
  if (spaces == false) {
    for (int i = 0;
         i < tasklistlux.datafilevariables[0].stringvectorvalues.size(); i++) {
      std::string tempstr =
          tasklistlux.datafilevariables[0].stringvectorvalues[i];
      for (int j = 0; j < tempstr.size(); j++) {
        if (tempstr[j] == ' ') {
          tempstr[j] = '_';
        }
      }
      tasklistlux.datafilevariables[0].stringvectorvalues[i] = tempstr;
      tempstr = tasklistlux.datafilevariables[1].stringvectorvalues[i];
      for (int j = 0; j < tempstr.size(); j++) {
        if (tempstr[j] == ' ') {
          tempstr[j] = '_';
        }
      }
      tasklistlux.datafilevariables[1].stringvectorvalues[i] = tempstr;
    }
  }
}

void task::Sort(int variable) {}

void task::LoadTasks() {
  tasklistlux = pessum::luxreader::LoadLuxDataFile("tasks");
  ToggleSpaces(true);
  for (int i = 0;
       i < tasklistlux.datafilevariables[0].stringvectorvalues.size(); i++) {
    Task newtask;
    newtask.taskstr = tasklistlux.datafilevariables[0].stringvectorvalues[i];
    newtask.group = tasklistlux.datafilevariables[1].stringvectorvalues[i];
    newtask.priority = tasklistlux.datafilevariables[2].intvectorvalues[i];
    newtask.date = tasklistlux.datafilevariables[3].intvectorvalues[i];
    newtask.duedate = tasklistlux.datafilevariables[4].intvectorvalues[i];
    newtask.prioritization =
        tasklistlux.datafilevariables[5].doublevectorvalues[i];
    tasklist.push_back(newtask);
  }
}

void task::SaveTasks() {
  ToggleSpaces(false);
  pessum::luxreader::SaveLuxDataFile("tasks", tasklistlux);
}
