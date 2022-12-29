#pragma once
#include "../graphics/observer/subject.h"
#include "../shape.h"
class Drawing : public Subject
{
private:
    std::vector<Shape *>  _shapes;
public:
   Drawing(std::vector<Shape *> shapes){
    for(int i =0;i<shapes.size();i++){
        _shapes.push_back(shapes[i]);
    }
   }
   ~Drawing(){

   }
      std::vector<Shape *> shapes(){
        return _shapes;
      }
};