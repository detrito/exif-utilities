// exifprint.cpp, $Rev: 1686 $
// Author: Andreas Huggel (ahu) <ahuggel@gmx.net>
// Sample program to print the Exif metadata of an image

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <exiv2/exiv2.hpp>

#if EXIV2_MAJOR_VERSION >= 1 || (EXIV2_MAJOR_VERSION == 0 && EXIV2_MINOR_VERSION >= 27)
#define HAVE_EXIV2_ERROR_CODE
#endif

int main(int argc, char* const argv[])
try {

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " file\n";
        return 1;
    }

    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(argv[1]);
    assert(image.get() != 0);
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
		#ifdef HAVE_EXIV2_ERROR_CODE
			throw Exiv2::Error(Exiv2::kerErrorMessage, "no exif data found in the file");
		#else
			throw Exiv2::Error(1, "no exif data found in the file");
		#endif
    }
    Exiv2::ExifData::const_iterator end = exifData.end();
    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
        std::cout << std::setw(44) << std::setfill(' ') << std::left
                  << i->key() << " "
                  << "0x" << std::setw(4) << std::setfill('0') << std::right
                  << std::hex << i->tag() << " "
                  << std::setw(9) << std::setfill(' ') << std::left
                  << i->typeName() << " "
                  << std::dec << std::setw(3)
                  << std::setfill(' ') << std::right
                  << i->count() << "  "
                  << std::dec << i->value()
                  << "\n";
    }

    return 0;
}
catch (Exiv2::AnyError& e) {
    std::cout << "Caught Exiv2 exception '" << e << "'\n";
    return -1;
}

