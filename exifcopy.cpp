// detrito, march 2009
// exifcopy: copia tutti i tags exif di un'immagine in un'altra
// v.0.0.1

#include <iostream>
#include <cassert>
#include <exiv2/exiv2.hpp>

#if EXIV2_MAJOR_VERSION >= 1 || (EXIV2_MAJOR_VERSION == 0 && EXIV2_MINOR_VERSION >= 27)
#define HAVE_EXIV2_ERROR_CODE
#endif

// variables
Exiv2::Image::AutoPtr src_image, dst_image;
Exiv2::ExifData * new_exif_data;

int main(int argc, char* const argv[])
try {	
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " [source-file] [destination-file]\n";
		return 1;
	}
	
	// open the source file
	src_image = Exiv2::ImageFactory::open(argv[1]);
	assert(src_image.get() != 0);
	dst_image = Exiv2::ImageFactory::open(argv[2]);
	assert(dst_image.get() != 0);
	src_image->readMetadata();

	// get the metadata	
	new_exif_data = &src_image->exifData();
	if (new_exif_data->empty()) {
		#ifdef HAVE_EXIV2_ERROR_CODE
			throw Exiv2::Error(Exiv2::kerErrorMessage, "no exif data found in the file");
		#else
			throw Exiv2::Error(1, "no exif data found in the file");
		#endif
	}
	
	// write the new metadata to the destination file
   dst_image->setExifData(*new_exif_data);
   dst_image->writeMetadata();
	return 0;
}

catch (Exiv2::AnyError& e) {
	std::cout << "caught exiv2 exception '" << e << "'\n";
	return -1;
}
