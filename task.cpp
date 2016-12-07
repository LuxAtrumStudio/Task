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
  int sortmethod = 5;
  std::string input = "";
  LoadTasks();
  while (running == true) {
    Prioritize();
    Sort(sortmethod);
    DisplayTasks();
    getline(std::cin, input);
    if (input == "a") {
      AddTask();
    }
    if (input == "q") {
      running = false;
    }
    if (input == "s") {
      sortmethod = SelectSort() - 1;
    }
    if (input[0] == 'd' && input.size() > 1) {
      input.erase(input.begin(), input.begin() + 2);
      int pointer = 0;
      if (CheckStr(input) == true) {
        pointer = stoi(input) - 1;
      }
      DeleteTask(pointer);
    }
    if (input[0] == 'e' && input.size() > 1) {
      input.erase(input.begin(), input.begin() + 2);
      int pointer = 0;
      if (CheckStr(input) == true) {
        pointer = stoi(input) - 1;
      }
      EditTask(pointer);
    }
    if (input[0] == 's' && input.size() > 1) {
      input.erase(input.begin(), input.begin() + 2);
      if (CheckStr(input) == true) {
        sortmethod = stoi(input) - 1;
      }
    }
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
  for (int i = 0; i < tasklist.size() && i < height - 6; i++) {
    std::string line = "";
    line += std::to_string(i + 1) + ". ";
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
  std::cout << "Add[a] | Compleate[d] | Edit[e] | Sort[s] | Quit[q]\n";
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

void task::Sort(int variable) {
  if (variable == 0) {
    for (int i = 1; i < tasklist.size(); i++) {
      int j = i;
      bool greater = false;
      for (int k = 0; k < tasklist[j - i].taskstr.size(); k++) {
        if (tasklist[j].taskstr.size() < k) {
          greater = true;
          break;
        }
        if (int(tasklist[j - 1].taskstr[k]) > int(tasklist[j].taskstr[k])) {
          greater = true;
          break;
        }
      }
      while (j > 0 && greater == true) {
        iter_swap(tasklist.begin() + j, tasklist.begin() + j - 1);
        j--;
      }
    }
  }
  if (variable == 1) {
  }
  if (variable >= 2 && variable <= 5) {
    for (int i = 1; i < tasklist.size(); i++) {
      int j = i;
      while (variable == 2 && j > 0 &&
             tasklist[j - 1].priority > tasklist[j].priority) {
        iter_swap(tasklist.begin() + j, tasklist.begin() + j - 1);
        j--;
      }
      while (variable == 3 && j > 0 &&
             tasklist[j - 1].date > tasklist[j].date) {
        iter_swap(tasklist.begin() + j, tasklist.begin() + j - 1);
        j--;
      }
      while (variable == 4 && j > 0 &&
             tasklist[j - 1].duedate > tasklist[j].duedate) {
        iter_swap(tasklist.begin() + j, tasklist.begin() + j - 1);
        j--;
      }
      while (variable == 5 && j > 0 &&
             tasklist[j - 1].prioritization > tasklist[j].prioritization) {
        iter_swap(tasklist.begin() + j, tasklist.begin() + j - 1);
        j--;
      }
    }
  }
}

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

void task::AddTask() {
  std::string text, group, datestr, temp;
  int priority, day, month, year, hour = 0, min = 0, sec = 0;
  text = induco::SGetValue("Task");
  group = induco::SGetValue("Task Group");
  priority = induco::GetValue("Priority [1-6]");
  getline(std::cin, temp);
  datestr = induco::SGetValue("Date \"DAY:MONTH:YEAR:HOUR:MIN:SEC\"");
  struct tm *newtime;
  time_t currenttime, duetime;
  time(&currenttime);
  newtime = localtime(&currenttime);
  day = newtime->tm_mday;
  month = newtime->tm_mon + 1;
  year = newtime->tm_year + 1900;
  int position = 0;
  std::string section = "";
  for (int i = 0; i < datestr.size(); i++) {
    if (datestr[i] == ':') {
      if (position == 0) {
        day = std::stoi(section);
      }
      if (position == 1) {
        month = std::stoi(section);
      }
      if (position == 2) {
        year = std::stoi(section);
      }
      if (position == 3) {
        hour = std::stoi(section);
      }
      if (position == 4) {
        min = std::stoi(section);
      }
      if (position == 5) {
        sec = std::stoi(section);
      }
      section = "";
      position++;
    } else {
      section += datestr[i];
    }
  }
  if (datestr.size() > 0) {
    if (position == 0) {
      day = std::stoi(section);
    }
    if (position == 1) {
      month = std::stoi(section);
    }
    if (position == 2) {
      year = std::stoi(section);
    }
    if (position == 3) {
      hour = std::stoi(section);
    }
    if (position == 4) {
      min = std::stoi(section);
    }
    if (position == 5) {
      sec = std::stoi(section);
    }
  }
  newtime->tm_mday = day;
  newtime->tm_mon = month - 1;
  newtime->tm_year = year - 1900;
  newtime->tm_hour = hour;
  newtime->tm_min = min;
  newtime->tm_sec = sec;
  duetime = mktime(newtime);
  tasklistlux.datafilevariables[0].stringvectorvalues.push_back(text);
  tasklistlux.datafilevariables[1].stringvectorvalues.push_back(group);
  tasklistlux.datafilevariables[2].intvectorvalues.push_back(priority);
  tasklistlux.datafilevariables[3].intvectorvalues.push_back(currenttime);
  tasklistlux.datafilevariables[4].intvectorvalues.push_back(duetime);
  tasklistlux.datafilevariables[5].doublevectorvalues.push_back(0);
  Task newtask;
  newtask.taskstr = text;
  newtask.group = group;
  newtask.priority = priority;
  newtask.date = currenttime;
  newtask.duedate = duetime;
  newtask.prioritization = 0;
  tasklist.push_back(newtask);
}

void task::DeleteTask(int pointer) {
  if (pointer < tasklistlux.datafilevariables[0].stringvectorvalues.size()) {
    tasklist.erase(tasklist.begin() + pointer);
    tasklistlux.datafilevariables[0].stringvectorvalues.erase(
        tasklistlux.datafilevariables[0].stringvectorvalues.begin() + pointer);
    tasklistlux.datafilevariables[1].stringvectorvalues.erase(
        tasklistlux.datafilevariables[1].stringvectorvalues.begin() + pointer);
    tasklistlux.datafilevariables[2].intvectorvalues.erase(
        tasklistlux.datafilevariables[2].intvectorvalues.begin() + pointer);
    tasklistlux.datafilevariables[3].intvectorvalues.erase(
        tasklistlux.datafilevariables[3].intvectorvalues.begin() + pointer);
    tasklistlux.datafilevariables[4].intvectorvalues.erase(
        tasklistlux.datafilevariables[4].intvectorvalues.begin() + pointer);
    tasklistlux.datafilevariables[5].doublevectorvalues.erase(
        tasklistlux.datafilevariables[5].doublevectorvalues.begin() + pointer);
  }
}

void task::EditTask(int pointer) {
  if (pointer < tasklistlux.datafilevariables[0].stringvectorvalues.size()) {
    bool edit = true;
    while (edit == true) {
      std::vector<std::string> options = {"Task", "Group", "Priority",
                                          "DueDate", "Done"};
      std::string temp;
      int select =
          induco::Menu("Edit Task " + std::to_string(pointer), options);
      getline(std::cin, temp);
      if (select == 1) {
        std::string taskstr = induco::SGetValue("Task");
        tasklistlux.datafilevariables[0].stringvectorvalues[pointer] = taskstr;
        tasklist[pointer].taskstr = taskstr;
      } else if (select == 2) {
        std::string groupstr = induco::SGetValue("Task Group");
        tasklistlux.datafilevariables[1].stringvectorvalues[pointer] = groupstr;
        tasklist[pointer].group = groupstr;

      } else if (select == 3) {
        int prio = induco::GetValue("Priority [1-6]");
        tasklistlux.datafilevariables[2].intvectorvalues[pointer] = prio;
        tasklist[pointer].priority = prio;
        getline(std::cin, temp);

      } else if (select == 4) {
        int priority, day, month, year, hour = 0, min = 0, sec = 0;
        struct tm *newtime;
        time_t currenttime, duetime;
        time(&currenttime);
        newtime = localtime(&currenttime);
        day = newtime->tm_mday;
        month = newtime->tm_mon + 1;
        year = newtime->tm_year + 1900;
        int position = 0;
        std::string section = "", datestr;
        datestr = induco::SGetValue("Date \"DAY:MONTH:YEAR:HOUR:MIN:SEC\"");
        for (int i = 0; i < datestr.size(); i++) {
          if (datestr[i] == ':') {
            if (position == 0) {
              day = std::stoi(section);
            }
            if (position == 1) {
              month = std::stoi(section);
            }
            if (position == 2) {
              year = std::stoi(section);
            }
            if (position == 3) {
              hour = std::stoi(section);
            }
            if (position == 4) {
              min = std::stoi(section);
            }
            if (position == 5) {
              sec = std::stoi(section);
            }
            section = "";
            position++;
          } else {
            section += datestr[i];
          }
        }
        if (position == 0) {
          day = std::stoi(section);
        }
        if (position == 1) {
          month = std::stoi(section);
        }
        if (position == 2) {
          year = std::stoi(section);
        }
        if (position == 3) {
          hour = std::stoi(section);
        }
        if (position == 4) {
          min = std::stoi(section);
        }
        if (position == 5) {
          sec = std::stoi(section);
        }
        newtime->tm_mday = day;
        newtime->tm_mon = month - 1;
        newtime->tm_year = year - 1900;
        newtime->tm_hour = hour;
        newtime->tm_min = min;
        newtime->tm_sec = sec;
        tasklistlux.datafilevariables[4].intvectorvalues[pointer] =
            mktime(newtime);
        tasklist[pointer].duedate = mktime(newtime);
      } else if (select == 5) {
        edit = false;
      }
    }
  }
}

int task::SelectSort() {
  int value = 0;
  std::vector<std::string> options = {"Alpha",        "Group",    "Priority",
                                      "Date Created", "Due Date", "Default"};
  value = induco::Menu("Sort Method", options);
  return (value);
}

bool task::CheckStr(std::string str) {
  for (int i = 0; i < str.size(); i++) {
    if (int(str[i]) < 48 || int(str[i]) > 57) {
      return (false);
    }
  }
  return (true);
}
