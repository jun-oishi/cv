# include <fstream>
# include <string>
# include <vector>
# include <iostream>
# include <filesystem>

namespace ppm {

using namespace std;

using Pixel = vector<uint8_t>;
using Row = vector<Pixel>;
using Image = vector<Row>;

class PPM {
private:
  string magic_number;
  uint width, height, max_value;
  Image content;

public:
  PPM(string magic_number, uint width, uint height);
  void set(uint x, uint y, Pixel value);
  void write(string filename);
  void invert();
};

PPM read(string filename);

// end templates

PPM::PPM(string magic_number, unsigned int width, unsigned int height) {
  this->magic_number = magic_number;
  this->width = width;
  this->height = height;
  this->max_value = 0xff;
  if (magic_number == "P2") {
    this->content = Image(height, Row(width, Pixel(1, 0)));
  } else if (magic_number == "P3") {
    this->content = Image(height, Row(width, Pixel(3, 0)));
  } else {
    throw "unsupported magic number";
  }
};

PPM read(string filename) {
  while (true) { // check if file exists
    if (!filesystem::exists(filename)) {
      cout << "File `" << filename << "` does not exist." << endl;
      cout << "enter a valid filename (or `e` to exit): ";
      cin >> filename;
      if (filename == "e") {
        cout << "bye" << endl;
        exit(0);
      }
      continue;
    } else {
      break;
    }
  }

  ifstream ifs(filename);
  string magic_number = "unread";
  uint width = 0, height = 0, max_value = 0;

  while (true) { // read header
    string line;
    getline(ifs, line);
    if (line[0] == '#') {
      continue;
    }
    if (line[0] == 'P') {
      magic_number = line;
      continue;
    }
    if (line.find(' ') != string::npos) {
      width = stoi(line.substr(0, line.find(' ')));
      height = stoi(line.substr(line.find(' ') + 1));
      continue;
    }
    max_value = stoi(line);
    break;
  }

  if ((magic_number != "P2" && magic_number != "P3") ||
      (width == 0 || height == 0) || (max_value > 0xff || max_value == 0)) {
    throw "unsupported file";
  }

  PPM ppm(magic_number, width, height);
  for (uint y = 0; y < height; y++) { // read content
    for (uint x = 0; x < width; x++) {
      Pixel pixel;
      for (uint i = 0; i < (magic_number == "P2" ? 1 : 3); i++) {
        uint value;
        ifs >> value;
        pixel.push_back(value);
      }
      ppm.set(x, y, pixel);
    }
  }

  return ppm;
}

/**
 * @brief Set the value of a pixel
 * @param value vector of 1 or 3(r,g,b) values
 */
void PPM::set(uint x, uint y, Pixel value) {
  this->content.at(y).at(x) = value;
}

void PPM::write(string filename) {
  while (true) { // check if file exists
    if (filesystem::exists(filename)) {
      cout << "File `" << filename << "` already exists." << endl;
      cout << "enter a valid filename (or `o` to overwrite): ";
      cin >> filename;
      if (filename == "") {
        break;
      }
    } else {
      break;
    }
  }
  
  ofstream ofs(filename);
  ofs << this->magic_number << endl;
  ofs << this->width << " " << this->height << endl;
  ofs << this->max_value << endl;

  for (auto row : this->content) { // write content
    for (auto pixel : row) {
      for (auto value : pixel) {
        ofs << (int)value << " ";
      }
      ofs << endl;
    }
  }
}

/**
 * @brief invert the image
 * @note destructive
 */
void PPM::invert() {
  for (auto &row : this->content) {
    for (auto &pixel : row) {
      for (auto &value : pixel) {
        value = this->max_value - value;
      }
    }
  }
}

} // end namespace ppm