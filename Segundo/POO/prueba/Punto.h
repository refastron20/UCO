#ifndef PUNTO_H
#define PUNTO_H

class punto{
private:
  int x_;
  int y_;
public:
  inline punto(int x=0, int y=0):x_(x), y_(y){};

  inline void setx(int x){x_=x;};
  inline int getx() const {return x_;};
  inline void sety(int y){y_=y;};
  inline int gety() const {return y_;};

  punto operator=(const punto &p);
  punto operator=(int &n);
  punto operator++(void);//prefijo
  punto operator++(int);//sufijo
  punto operator+(int n);//punto+n
  friend punto operator+(int n, const punto &p);//n+punto

};
#endif
