/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2013-08-22 Tobias Peters <tobias.peters@kreativeffekt.at>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __QGearsPaletteFileSerializer_H__
#define __QGearsPaletteFileSerializer_H__

#include <OgrePixelFormat.h>

#include "common/TypeDefine.h"

#include "QGearsPaletteFile.h"
#include "QGearsSerializer.h"

namespace QGears
{
    class PaletteFileSerializer : public Serializer
    {
    public:
                        PaletteFileSerializer();
        virtual        ~PaletteFileSerializer();

        virtual void 	importPaletteFile( Ogre::DataStreamPtr &stream, PaletteFile* pDest );

        enum {
            BIT_MASK_RED    = 0x001F
           ,BIT_MASK_GREEN  = 0x03E0
           ,BIT_MASK_BLUE   = 0x7C00
           ,BIT_SIZE        = 0x001F
           ,BIT_MASK_RGB    = BIT_MASK_BLUE | BIT_MASK_GREEN | BIT_MASK_RED
           ,BIT_MASK_ALPHA  = 0x8000
        };

        struct Header
        {
            uint32 file_size;
            uint16 pal_x;
            uint16 pal_y;
            uint16 colors_per_page;
            uint16 page_count;
        };

        typedef PaletteFile::Color  Color;
        typedef PaletteFile::Page   Page;

    protected:
        virtual void 	readFileHeader( Ogre::DataStreamPtr &stream );
        virtual void    readObject( Ogre::DataStreamPtr &stream, Color &pDest );
        virtual void    readObject( Ogre::DataStreamPtr &stream, Page &pDest );
        using Serializer::readObject;

        virtual void    convertColour( uint16 &colour ) const;

        static const Ogre::PixelFormat  PIXEL_FORMAT;

        template<typename ValueType> void
        readVector( Ogre::DataStreamPtr &stream, std::vector<ValueType> &pDest, size_t count )
        {
            pDest.clear();
            pDest.reserve( count );
            for( size_t i( count ); i--; )
            {
                ValueType in_tmp;
                readObject( stream, in_tmp );
                pDest.push_back( in_tmp );
            }
        }

    private:
        Header  m_header;
    };
}

#endif // __QGearsPaletteFileSerializer_H__
