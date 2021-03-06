#include "firstlight.h"

namespace flt
{


Reader::Reader(Stream& stream) :
	m_stream(stream)
{
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

char Reader::Read()
{
	return m_stream.Read();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

int Reader::Read(char* cbuf, int len)
{
	return m_stream.Read(cbuf, len);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

int Reader::ReadLine(char* cbuf, int buflen)
{
	int lineLength = 0;
	char c = 0;
	
	while(true)
	{
		int count = m_stream.Read(&c, sizeof(char));

		// End of stream and no character read?
		if(count <= 0 && lineLength == 0)
			return -1;

		FLT_ASSERT(buflen > lineLength);

		if(count == 0 || buflen < lineLength + 1)
			break;

		if(c == '\r')
		{
			// Also skip the following '\n' ?
			count = m_stream.Read(&c, sizeof(char));
			
			// Oups, need to go back by one char
			if(c != '\n' && count > 0)
			{
	//			int before = m_stream.Tell();
				m_stream.Seek(-1, io::cur);
//				int after = m_stream.Tell();
				//int diff = after - before;
			}
			
			break;
		}
		else if(c == '\n')
		{
			break;
		}
		else
		{
			cbuf[lineLength++] = c;
		}
	}
	
	FLT_ASSERT(buflen > lineLength);
	cbuf[lineLength] = 0;
	return lineLength;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

void Reader::Skip(int n)
{
	m_stream.Seek(n, io::cur);
}


}