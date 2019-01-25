#include <vector>
using namespace std;

class Pixel {
   private:
    int col;
    int row;
    int color;

   public:
    Pixel(int, int, int);
    
    int getRow();
    int getCol();
    int getColor();

    void setRow(int);
    void setCol(int);
    void setColor(int);
};