#pragma once

class CSPacket
{
	private:

		u8 * pBuffer;					// Buffer that will be used to store packet data
		s16   m_length;					// Contains the Total Lenght of the Packet
		s16   m_position;				// Contains the Actual Position in the Packet Buffer (Index)
		s16   m_maxlength;				// Stores the max allowed lenght for that packet
		bool   m_IsReference;			// Sets if the Packet is a Reference Or Not !

	public:

		// Constructor
		inline CSPacket()
		{
			pBuffer = NULL;
			m_length = 0;
			m_position = 0;
			m_maxlength = 0;
			m_IsReference = false;
		}

		inline CSPacket(u8 *pIncommingBuffer, s32 nPacketLen, s32 nMaxPacketLen)
		{
			if ( pIncommingBuffer && nPacketLen > 0 && nMaxPacketLen > 0 )
			{
				m_IsReference = true;
				pBuffer = (u8 *)pIncommingBuffer;
				m_maxlength = (s16)nMaxPacketLen;
				m_length = (s16)nPacketLen;
				m_position = (s16)(nPacketLen-1);
			}
			else
			{
				m_IsReference = false;
				pBuffer = new u8[8];
				m_length = 8;
				m_position = 8;
				m_maxlength = 8;
			}
		}

		// Destructor
		inline ~CSPacket()
		{
			if ( !m_IsReference && m_length > 0 )
			{
				delete[] pBuffer;
			}
		}

		// Initializer
		void inline set(s32 nPacketLen)
		{
			if ( m_length == 0 && m_maxlength == 0 && nPacketLen <= MAX_PACKET_LEN)
			{
				pBuffer = new u8[nPacketLen];
				memset(pBuffer,0x00,nPacketLen);
				m_maxlength = (s16)nPacketLen;
				m_length = 0;
				m_position = 0;
			}
			else
				CLog::AddAnsi(RED, "Error setting CSPacket buffer size!!!");
		}

		// Clearer
		void inline clear()
		{
			if ( !m_IsReference && m_maxlength > 0 )
			{
				delete[] pBuffer;
				pBuffer = NULL;
				m_maxlength = 0;
				m_length = 0;
				m_position = 0;
				m_IsReference = false;
			}
		}

		// Current Position
		s32 GetCurrentPosition() { return m_position; }

		u8 inline *buffer(bool bMode)
		{ 
			return pBuffer; 
		}

		u8 inline *buffer()
		{
			return pBuffer;
		}
		
		s16 inline size(void) 
		{ 
			return m_length; 
		}

		s16 inline freeLeft()
		{
			return m_length - m_position;
		}

		s16 inline pos()
		{
			return m_position;
		}
	
		// Writting Routines
		template <typename type> inline void Write(type val)
		{
			// Checking Possible Overflow Before Writting
			if ( (m_length + sizeof(type)) <= m_maxlength )
			{
				*reinterpret_cast<type*>(pBuffer+m_position) = val;
				m_position += sizeof(type);
				m_length = m_position;
			}
//  		else
// 			{
// 				CLog::AddAnsi(RED, "Buffer overflow in CSPacket!!!");
// 				u32* crash = 0;
// 				*crash = 0;
// 			}
		}

		inline void Write(void *data, s32 len)
		{
			// Checking Possible Overflow Before Writting
			if ( (m_length + len) <= m_maxlength )
			{
				memcpy(pBuffer+m_position, data, len);
				m_position += (s16)len;
				m_length = m_position;
			}
			else
				CLog::AddAnsi(RED, "Buffer overflow in CSPacket!!!");
		}

		// Not working correctly!
		template <typename type> inline void RewriteAt(type val, s32 pos)
		{
			// Checking Possible Overflow Before Writting
			if ( (pos + sizeof(type)) <= m_maxlength )
			{
				*reinterpret_cast<type*>(pBuffer+pos) = val;
			}
			else
				CLog::AddAnsi(RED, "Buffer overflow in CSPacket!!!");
		}

		inline void RewriteAt(void *data, s32 len, s32 pos)
		{
			// Checking Possible Overflow Before Writting
			if ( (pos + len) <= m_maxlength )
			{
				memcpy(pBuffer+pos, data, len);
			}
			else
				CLog::AddAnsi(RED, "Buffer overflow in CSPacket!!!");
		}
	
		inline void Write(char *str)
		{
			Write(str, static_cast<s32>(strlen(str)+1));
		}

		inline void Write(WCHAR *str)
		{
			Write((char *)str, static_cast<s32>((wcslen(str)*2)+2));
		}

		inline void Write(string str)
		{
			Write((char *)str.c_str(), static_cast<s32>(str.length()+1));
		}

		inline void Write(wstring str)
		{
			Write((char *)str.c_str(), static_cast<s32>((str.length()*2)+2));
		}
	
		template <typename type> inline CSPacket & operator<<(type val)
		{
			Write(val);
			return *this;
		}

		// Reading Routines
		string inline GetString(s16 index) 
		{
			if ( index < m_maxlength )
				return reinterpret_cast<CHAR *>(pBuffer)+index;
			else
				return "";
		}
		
		wstring inline GetWString(s16 index) 
		{
			if ( index < m_maxlength )
				return reinterpret_cast<WCHAR *>(reinterpret_cast<char *>(pBuffer)+index); 
			else
				return L"";
		}

		u8 inline GetByte(s16 index) 
		{
			if ( index < m_maxlength )
				return pBuffer[index]; 
			else
				return 0; 
		}

		u8 inline *GetBytes(s16 index) 
		{ 
			if ( index < m_maxlength )
				return pBuffer+index; 
			else
				return NULL;
		}

		s16 GetWord(s16 index) 
		{ 
			if ( index < m_maxlength )
				return *((s16 *)(pBuffer + index)); 
			else
				return 0;
		}

		s32 GetDWord(s16 index) 
		{ 
			if ( index < m_maxlength )
				return *((s32 *)(pBuffer + index)); 
			else
				return 0; 
		}

		u64 GetQWord(s16 index) 
		{ 
			if ( index < m_maxlength )
				return *((u64 *)(pBuffer + index)); 
			else
				return 0; 
		}

};
