// detrito, march 2009
// netturbino: debella le foto da tags insidiosi se non malvagi
// v.0.0.2 -- updated january 2011

#include <iostream>
#include <cassert>
#include <exiv2/exiv2.hpp>

#if EXIV2_MAJOR_VERSION >= 1 || (EXIV2_MAJOR_VERSION == 0 && EXIV2_MINOR_VERSION >= 27)
#define HAVE_EXIV2_ERROR_CODE
#endif

// constants
const int _elements = 17; 
const char* _exif_keys[_elements] = {
"Exif.Image.Model",
"Exif.Image.Orientation",
"Exif.Image.YResolution",
"Exif.Image.XResolution",
"Exif.Image.ResolutionUnit",
"Exif.Image.DateTime",
"Exif.Image.Copyright",
"Exif.Photo.ExposureTime",
"Exif.Photo.FNumber",
"Exif.Photo.ExposureProgram",
"Exif.Photo.ISOSpeedRatings",
"Exif.Photo.ExifVersion",
"Exif.Photo.DateTimeOriginal",
"Exif.Photo.DateTimeDigitized",
"Exif.Photo.SceneType",
"Exif.Photo.FocalLength",
"Exif.Photo.UserComment",
};

// variables
int i;
char * exif_values[_elements];
Exiv2::Image::AutoPtr image;
Exiv2::ExifData::const_iterator  k;
Exiv2::ExifData new_exif_data;
Exiv2::ExifData * exif_data;

// print the metadata
void print_exif(Exiv2::ExifData& exif_data)
{
	for (Exiv2::ExifData::const_iterator j = exif_data.begin(); j != exif_data.end(); j++) {
		std::cout << std::hex << j->tag() << " - " << j->key() << " - " << std::dec << j->value() << "\n";
	}
}

int main(int argc, char* const argv[])
try {	
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " [image-file]\n";
		std::cout << "v.0.0.2" << "\n";
		return 1;
	}
	
	// open the file
	image = Exiv2::ImageFactory::open(argv[1]);
	assert(image.get() != 0);
	image->readMetadata();

	// memorize the metadata	
	exif_data = &image->exifData();
	if (exif_data->empty()) {
		#ifdef HAVE_EXIV2_ERROR_CODE
			throw Exiv2::Error(Exiv2::kerErrorMessage, "no exif data found in the file");
		#else
			throw Exiv2::Error(1, "no exif data found in the file");
		#endif
	}
	for (i=0; i<_elements; i++) {
		k = exif_data->findKey( Exiv2::ExifKey(_exif_keys[i]) );
		if (k == exif_data->end()) {
			std::cerr << "exif tag " << _exif_keys[i] << " not found\n";
		}
		else {
			new_exif_data.add(*k);
		}
	}
	
	// debug
	//print_exif(new_exif_data);
	
	// write the new metadata to the file
   image->setExifData(new_exif_data);
   image->writeMetadata();
	return 0;
}

catch (Exiv2::AnyError& e) {
	std::cout << "caught exiv2 exception '" << e << "'\n";
	return -1;
}

