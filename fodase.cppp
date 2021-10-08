#include <fstream>
#include <iostream>

void write_txt_value(int v)
{
  std::ofstream txt_out("txt.out");
  txt_out << v;
}

int read_txt_value()
{
  std::ifstream txt_in("txt.out");
  int value;
  txt_in >> value;
  return value;
}

void write_bin_value(int v)
{
  std::fstream bin_out("bin.out",std::ios_base::binary|std::ios_base::out);
  bin_out.write((char*)&v,sizeof(int));
}

int read_bin_value()
{
  std::fstream bin_in("bin.out",std::ios_base::binary|std::ios_base::in);
  int value;
  bin_in.read((char*)&value,sizeof(int));
  return value;
}

int main()
{
  int value = -12345;
  write_txt_value(value);
  write_bin_value(value);
  std::cout << "Reading txt file value as integer: " << read_txt_value() << std::endl;
  std::cout << "Reading binary file value as integer: " << read_bin_value() << std::endl;
  return 0;
}