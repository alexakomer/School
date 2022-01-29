using namespace std;
#include <iostream>
class TwoStacks
{
  private:
    int* arr;
    size_t capacity;
    size_t stack1_i;
    size_t stack2_i;

  public:
    // default constructor
    TwoStacks()
    {
      capacity = 10;
      arr = new int[capacity];
      size_t stack1_i = 0;
      size_t stack2_i = 1;
    }

    void resize()
    {
      int* temp = new int[capacity];
      for (int i = 0; i < capacity; i++)
        temp[i] = arr[i];

      capacity *= 2;
      delete arr;
      arr = temp;
    }

    void shiftRight()
    {
      for (int i = capacity - 1; i > stack1_i; i--)
      {
          arr[i - 1] = arr[i];
      }
      stack2_i++;
    }

    void push1(int num)
    {
      if(stack2_i == capacity - 1)
      {
        resize();
      }
      shiftRight();
      arr[stack1_i] = num;
      stack1_i++;
    }

    void push2(int num)
    {
      if(stack2_i == capacity - 1)
      {
        resize();
      }
      arr[stack2_i] = num;
      stack2_i++;
    }

    void display()
    {
      for (int i = 0; i < capacity; i++)
        cout << arr[i] << " ";
      cout << endl;
    }

    size_t stack1Index()
    {
      return stack1_i;
    }

    size_t stack2Index()
    {
      return stack2_i;
    }

};


int main()
{
  TwoStacks mcDouble;
  mcDouble.display();
  mcDouble.push1(1);
  mcDouble.push1(2);
  cout << "Stack 1 Index: " << mcDouble.stack1Index() << endl;
  cout << "Stack 2 Index: " << mcDouble.stack2Index() << endl;
  // mcDouble.push2(3);
  // mcDouble.push2(4);
  mcDouble.display();
}
