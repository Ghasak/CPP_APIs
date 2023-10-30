#include <iostream>
#include <iterator>
#include <list>
#include <math.h>

/* int main(int argc, char *argv[]) { */
/*  */
/*   std::list my_list1{8, 3, 5}; */
/*   std::list my_list2{3, 7, 3}; */
/*   std::list<int> list_final; */
/*  */
/*   int add{}; */
/*   std::list<int>::iterator it1{my_list1.begin()}; */
/*   std::list<int>::iterator it2{my_list2.begin()}; */
/*  */
/*   while (it1 != my_list1.end() && it2 != my_list2.end()) { */
/*  */
/*     int elem1{*it1}; */
/*     int elem2{*it2}; */
/*     std::cout << " Elem1 Address: " << elem1 << " Eleme1 Value: " << &(*it1)
 */
/*               << std::endl; */
/*  */
/*     if (abs(elem1 + elem2) >= 10 || add != 0) { */
/*  */
/*       auto result = (elem1 + elem2 + add) % 10; */
/*       std::cout << " Result: " << result << std::endl; */
/*       list_final.push_back(result); */
/*       add = 1; */
/*     } else */
/*       list_final.push_back(elem1 + elem2); */
/*  */
/*     ++it1; */
/*     ++it2; */
/*   } */
/*   for (const auto &val : list_final) */
/*     std::cout << val << std::endl; */
/*  */
/*   for (size_t i = 0; i < 10; i++) { */
/*     std::cout << "The value of i -> {" << i << "}" */
/*               << "\n"; */
/*   } */
/*   return 0; */
/* } */

class Vector2D {
private:
  double x_cord{};
  double y_cord{};

public:
  Vector2D(double x_cord = 0, double y_cord = 0)
      : x_cord{x_cord}, y_cord{y_cord} {}

  ~Vector2D() {}

  Vector2D add(const Vector2D &other) {
    return (Vector2D(this->x_cord + other.x_cord, this->y_cord + other.y_cord));
  }

  static Vector2D add_2(const Vector2D &vec1, const Vector2D vec2) {

    return (Vector2D(vec1.x_cord + vec2.x_cord, vec1.y_cord + vec2.y_cord));
  }
  void display() const {
    std::cout << "Vector is: (" << this->x_cord << "," << this->y_cord << ")"
              << std::endl;
  }
};

int main(int argc, char **argv) {

  std::cout << "-------------------" << std::endl;
  std::cout << "Vector Engine Start!!" << std::endl;
  std::cout << "-------------------" << std::endl;
  Vector2D vec1{1, 2};
  Vector2D vec2{2, 3};

  Vector2D vec3{Vector2D::add_2(vec1, vec2)}; // add of two vector
  vec3.display();

  // use of smart ptr

  std::unique_ptr<Vector2D> vec4 = std::make_unique<Vector2D>(1, 1);
  std::unique_ptr<Vector2D> vec5 = std::make_unique<Vector2D>(2, 2);

  std::unique_ptr<Vector2D> vec6 =
      std::make_unique<Vector2D>(Vector2D::add_2(*vec4, *vec5));
  vec6->display();

  for (int i = 0; i < 10; i++) {
    std::cout << "the value of i -> {" << i << "}" << std::endl;
  }

  for (int i = 0; i < 100; i++) {
    std::cout << "This is the value of i -> { " << i << " }" << std::endl;
  }
  return 0;
}
