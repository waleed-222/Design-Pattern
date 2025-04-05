#include "employee.hpp"
#include "employeecontroller.hpp"
#include "employeeview.hpp"

int main() {
  Employee model("Waleed", 25);
  EmployeeView view;
  EmployeeController controller(model, view);

  // Display initial state
  controller.updateView();

  // Modify employee details
  controller.setEmployeeName("Mostafa");
  controller.setEmployeeAge(23);

  // Display updated state
  controller.updateView();

  return 0;
}
