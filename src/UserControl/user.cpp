#include"mouseCursor.cpp"

class User {
private:
  Viewer2D * viewer;

  //control

  MouseCursor * cursor;

public:
  User(Viewer2D * v) {
    viewer = v;
    cursor = new MouseCursor(viewer);
  }

  User() {
    viewer = new Viewer2D();
    cursor = new MouseCursor(viewer);
  }

  //getters

  MouseCursor * getMouseCursor() { return cursor; }

  Viewer2D * getViewer() { return viewer; }

  //setters

  void setViewer(Viewer2D * v) {
    viewer = v;
    cursor->setViewer(v);
  }

  //virtuals

  virtual void update() {
    cursor->update();
  }

};
