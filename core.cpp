#include "induco.h"
#include "task.h"
#include <ctime>
#include <iostream>
#include <math.h>
#include <pessum.h>

int main() {
  bool running = true;
  std::string input = "";
  pessum::InitializePessumComponents();
  task::MainLoop();
  /*tasklist = pessum::luxreader::LoadLuxDataFile("tasks");
  ToggleSpaces(true);
  while (running == true) {
    Prioritize();
    DisplayTasks();
    getline(std::cin, input);
    if (input == "q") {
      running = false;
    }
    if (input == "a") {
      std::string text, group, datestr, temp;
      int priority, day, month, year, hour = 0, min = 0, sec = 0;
      text = induco::SGetValue("Task");
      group = induco::SGetValue("Task Group");
      priority = induco::GetValue("Priority [5-1]");
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
      duetime = mktime(newtime);
      tasklist.datafilevariables[0].stringvectorvalues.push_back(text);
      tasklist.datafilevariables[1].stringvectorvalues.push_back(group);
      tasklist.datafilevariables[2].intvectorvalues.push_back(priority);
      tasklist.datafilevariables[3].intvectorvalues.push_back(currenttime);
      tasklist.datafilevariables[4].intvectorvalues.push_back(duetime);
      tasklist.datafilevariables[5].doublevectorvalues.push_back(0);
    }
    if (input[0] == 'd') {
      input.erase(input.begin(), input.begin() + 2);
      int pointer = stoi(input) - 1;
      if (pointer < tasklist.datafilevariables[0].stringvectorvalues.size()) {
        tasklist.datafilevariables[0].stringvectorvalues.erase(
            tasklist.datafilevariables[0].stringvectorvalues.begin() + pointer);
        tasklist.datafilevariables[1].stringvectorvalues.erase(
            tasklist.datafilevariables[1].stringvectorvalues.begin() + pointer);
        tasklist.datafilevariables[2].intvectorvalues.erase(
            tasklist.datafilevariables[2].intvectorvalues.begin() + pointer);
        tasklist.datafilevariables[3].intvectorvalues.erase(
            tasklist.datafilevariables[3].intvectorvalues.begin() + pointer);
        tasklist.datafilevariables[4].intvectorvalues.erase(
            tasklist.datafilevariables[4].intvectorvalues.begin() + pointer);
        tasklist.datafilevariables[5].doublevectorvalues.erase(
            tasklist.datafilevariables[5].doublevectorvalues.begin() + pointer);
      }
    }
    if (input[0] == 'e') {
      input.erase(input.begin(), input.begin() + 2);
      int pointer = stoi(input) - 1;
      if (pointer < tasklist.datafilevariables[0].stringvectorvalues.size()) {
        bool edit = true;
        while (edit == true) {
          std::vector<std::string> options = {"Task", "Group", "Priority",
                                              "DueDate", "Done"};
          std::string temp;
          int select = induco::Menu("Edit Task " + input, options);
          getline(std::cin, temp);
          if (select == 1) {
            tasklist.datafilevariables[0].stringvectorvalues[pointer] =
                induco::SGetValue("Task");
          } else if (select == 2) {
            tasklist.datafilevariables[1].stringvectorvalues[pointer] =
                induco::SGetValue("Task Group");

          } else if (select == 3) {
            tasklist.datafilevariables[2].intvectorvalues[pointer] =
                induco::GetValue("Priority [5-1]");
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
            tasklist.datafilevariables[4].intvectorvalues[pointer] =
                mktime(newtime);
          } else if (select == 5) {
            edit = false;
          }
        }
      }
    }
  }
  ToggleSpaces(false);
  pessum::luxreader::SaveLuxDataFile("tasks", tasklist);
  */
  pessum::TerminatePessumComponents();
}
