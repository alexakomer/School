#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];

  bool fail = false;

  for (int i=0; i < width; ++i)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];

    if (image[i] == nullptr) // failed to allocate
      fail = true;
  }

  if (fail)
  { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i)
      delete [] image[i]; // deleting nullptr is not a problem
    delete [] image; // delete array of pointers
    return nullptr;
  }

  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row)
  {
    for (int col=0; col<width; ++col)
      image[col][row] = { 0, 0, 0 }; //cout << "(" << col << ", " << row << ")" << endl;
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i < width; ++i)
    delete [] image[i]; // delete each individual array placed on the heap
  delete [] image;
  image = nullptr;
}

int* createSeam(int length)
{
  int* seam = new int[length];

  for (int i = 0; i < length; i++)
  {
    seam[i] = 0;
  }

  return seam;
}

void deleteSeam(int* seam)
{
  delete[] seam;
}

bool loadImage(string filename, Pixel** image, int width, int height)
{
  ifstream inputStream(filename);

  if (!inputStream.is_open())
  { // fail to open
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
  }

  char type[3];
  inputStream >> type;

  int w;
  int h;
  inputStream >> w >> h;
  if (inputStream.fail())
  {
    cout << "Error: read non-integer value" << endl;
    return false;
  }

  int colorMax = 0;
  inputStream >> colorMax;
  if (inputStream.fail())
  {
    cout << "Error: read non-integer value" << endl;
    return false;
  }

  // input validation
  if (toupper(type[0]) != 'P' || type[1] != '3')
  { // wrong file type
    cout << "Error: type is " << type << " instead of P3" << endl;
    return false;
  }

  if (width != w)
  {
    cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
    return false;
  }
  if (height != h)
  {
    cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
    return false;
  }

  // assign values
  for (int row = 0; row < height; row++)
  { // iterate rows
    for (int col = 0; col < width; col++)
    { // iterate columns

      int red;
      inputStream >> red; // input for red
      if (inputStream.fail())
      { // checks reading error
        if (inputStream.eof())
          cout << "Error: not enough color values" << endl;
        else
          cout << "Error: read non-integer value" << endl;
        return false;
      }

      int green;
      inputStream >> green; //input for green
      if (inputStream.fail())
      {
        if (inputStream.eof())
          cout << "Error: not enough color values" << endl;
        else
          cout << "Error: read non-integer value" << endl;
        return false;
      }

      int blue;
      inputStream >> blue; //input for blue
      if (inputStream.fail())
      {
        if (inputStream.eof())
          cout << "Error: not enough color values" << endl;
        else
          cout << "Error: read non-integer value" << endl;
        return false;
      }

      if (red < 0 || red > 255)
      { // color out of bounds
        cout << "Error: invalid color value " << red << endl;
        return false;
      }
      if (green < 0 || green > 255)
      {
        cout << "Error: invalid color value " << green << endl;
        return false;
      }
      if (blue < 0 || blue > 255)
      {
        cout << "Error: invalid color value " << blue << endl;
        return false;
      }

      image[col][row].r = red; // safe to assign
      image[col][row].g = green;
      image[col][row].b = blue;
    }
  }

  if (!inputStream.eof())
  { // checks if still data in file
    string val;
    inputStream >> val; // checks for empty space
    if (!inputStream.fail())
    {
      cout << "Error: too many color values" << endl;
      return false;
    }
  }

  return true; // load successful
}

bool outputImage(string filename, Pixel** image, int width, int height)
{
  ofstream imageStream(filename); // open file

  // check if opened properly
  if (!imageStream.is_open())
  {
    cout << "Error: failed to open output file " << filename << endl;
    return false;
  }

  // output preamble
  imageStream << "P3" << endl; // output type
  imageStream << width << " " << height << endl; // output width and type
  imageStream << "255" << endl; // output max size


  // output pixels
  for (int row = 0; row < height; row++)
  {
    for (int col = 0; col < width; col++)
    {
      imageStream << image[col][row].r << " "; // output red value of pixel
      imageStream << image[col][row].g << " "; // output green value of pixel
      imageStream << image[col][row].b << " "; // output blue value of pixel
      imageStream << endl;
    }
  }
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height)
{
  Pixel left_x;
  Pixel right_x;
  Pixel above_y;
  Pixel below_y;

  if(width == 0 || height == 0)
  {
    return 0;
  }

  if (width == 1 || height == 1)
  {
    if (width == 1)
    {
      left_x = image[x][y];
      right_x = image[x][y];
    }
    if (height == 1)
    {
      above_y = image[x][y];
      below_y = image[x][y];
    }
  }
  else
  {
    if (x == width - 1)
    { // find left and right bound for x
      left_x = image[x - 1][y];
      right_x = image[0][y];
    }
    else if (x == 0)
    {
      left_x = image[width-1][y];
      right_x = image[x + 1][y];
    }
    else
    {
      left_x = image[x - 1][y];
      right_x = image[x + 1][y];
    }

    if (y == height - 1)
    { //find upper and lower bound for y
      below_y = image[x][0];
      above_y = image[x][y - 1];
    }
    else if (y == 0)
    {
      below_y = image[x][y + 1];
      above_y = image[x][height-1];
    }
    else
    {
      below_y = image[x][y + 1];
      above_y = image[x][y - 1];
    }
  }

  int x_gradient = pow(left_x.r - right_x.r, 2) + pow(left_x.g - right_x.g, 2) + pow(left_x.b - right_x.b, 2);
  int y_gradient = pow(below_y.r - above_y.r, 2) + pow(below_y.g - above_y.g, 2) + pow(below_y.b - above_y.b, 2);
  int px_energy = x_gradient + y_gradient;

  return px_energy;
}

/* Implement in part 2 */
int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam)
{
  int seam_energy = 0; //total energy of seam
  int col = start_col;

  seam_energy += energy(image, col, 0, width, height); //first index of seam
  seam[0] = col;

  //loop through remaining rows
  for (int row = 1; row < height; row++)
  {
    int seam_col;

    if (col == 0)
    { //edge cases
      int bottom_col = col;
      int bottom_right_col = col + 1;

      int bottom = energy(image, bottom_col, row,width, height); //evaluate pixel energies
      int bottom_right = energy(image, bottom_right_col, row, width, height);

      if (bottom <= bottom_right)
      {
        seam_col = bottom_col;
        seam_energy += bottom;
      }
      else
      {
        seam_col = bottom_right_col;
        seam_energy += bottom_right;
      }

    }
    else if (col == width - 1)
    {
      int bottom_col = col;
      int bottom_left_col = col - 1;

      int bottom = energy(image, bottom_col, row, width, height); //evaluate pixel energies
      int bottom_left = energy(image, bottom_left_col, row, width, height);

      if (bottom <= bottom_left)
      {
        seam_col = bottom_col;
        seam_energy += bottom;
      }
      else
      {
        seam_col = bottom_left_col;
        seam_energy += bottom_left;
      }

    }
    else
    {
      int bottom_col = col;
      int bottom_left_col = col - 1;
      int bottom_right_col = col + 1;

      int bottom = energy(image, bottom_col, row, width, height); //evaluate pixel energies
      int bottom_left = energy(image, bottom_left_col, row, width, height);
      int bottom_right = energy(image, bottom_right_col, row, width, height);

      if (bottom <= bottom_left && bottom <= bottom_right)
      { //determine smallest
        seam_col = bottom_col;
        seam_energy += bottom;
      } else if (bottom_right <= bottom_left)
      {
        seam_col = bottom_right_col;
        seam_energy += bottom_right;
      }
      else
      {
        seam_col = bottom_left_col;
        seam_energy += bottom_left;
      }
    }
    seam[row] = seam_col;
    col = seam_col;
  }

  return seam_energy; //total energy of seam
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam)
{
  return 0;
}
#pragma GCC diagnostic pop


int* findMinVerticalSeam(Pixel** image, int width, int height)
{
  int* seam_min = createSeam(height);
  int seam_min_energy = 999999; // initialize to arbitrary large value

  for (int col = 0; col < width; col++)
  {
    int* vertical_seam = createSeam(height);
    int seam_energy = loadVerticalSeam(image, col, width, height, vertical_seam);

    if(seam_energy < seam_min_energy)
    {
      seam_min_energy = seam_energy;
      for (int i = 0; i < height; i++)
      {
        seam_min[i] = vertical_seam[i];
      }
    }
    deleteSeam(vertical_seam);
  }

  return seam_min;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height)
{

  cout << width << image[0][0].r << height;

  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam)
{
  for (int row = 0; row < height; row++)
  { //iterate through seam
    int seam_col = verticalSeam[row]; //find row and column to delete

    int index_c = 0;
    for (int col = 0; col < width; col++)
    {
      if (col != seam_col)
      {
        image[index_c][row] = image[col][row];
        index_c++;
      }
    }
  }
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam)
{
}
