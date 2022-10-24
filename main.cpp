# include <fstream>
# include <string>
# include "my_ppm.cpp"

using namespace std;

int main() {
  ppm::PPM flee = ppm::read("flee.ppm");
  flee.invert();
  flee.write("flee_inverted.ppm");

  ppm::PPM image("P3", 256, 256);
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      image.set(i, j, {0, (uint8_t)i, (uint8_t)j});
    }
  }
  image.write("test.ppm");

  // string magic_number = "P3";
  // int width = 128;
  // int height = 128;
  // int max_value = 0xff;

  // ofstream ofs("test_out.ppm");
  // ofs << magic_number << endl;
  // ofs << width << " " << height << endl;
  // ofs << max_value << endl;

  // for (int i = 0; i < width; i++) {
  //   for (int j = 0; j < height; j++) {
  //     int r = 2 * i;
  //     int g = 2 * j;
  //     int b = 0;
  //     ofs << r << " " << g << " " << b << endl;
  //   }
  // }
}