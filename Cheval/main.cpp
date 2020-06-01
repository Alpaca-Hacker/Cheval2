//#include <vector>
//
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STBIW_WINDOWS_UTF8 
//
//#include <array>
//#include <iostream>
//
//#include "stb_image_write.h"
//
//int main()
//{
//	int const image_width = 256;
//	int const image_height = 256;
//
//	int const size = image_width * image_height * 3;
//	uint8_t* Data = new uint8_t[size];
//
//	int index = 0;
//	for (int j = image_height - 1; j >= 0; --j)
//	{
//		for (int i = 0; i < image_width; ++i)
//		{
//			auto r = static_cast<double>(i) / (image_width - 1);
//			auto g = static_cast<double>(j) / (image_height - 1);
//			auto b = 0.25;
//
//			auto ir = static_cast<uint8_t>(255.999 * r);
//			auto ig = static_cast<uint8_t>(255.999 * g);
//			auto ib = static_cast<uint8_t>(255.999 * b);
//
//			Data[index++] = ir;
//			Data[index++] = ig;
//			Data[index++] = ib;
//			//	data.push_back(static_cast<uint8_t>(255));
//		}
//	}
//
//	//stbi_write_jpg(char const* filename, int w, int h, int comp, const void* data, int quality);
//
//	auto success = stbi_write_jpg("image.jpg", image_width, image_height, 3, Data, 100);
//
//	std::cout << "Image result " << success << std::endl;
//	delete[] Data;
//	return success;
//}
