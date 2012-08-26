
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "cNoteEntity.h"
#include "cWorld.h"
#include <json/json.h>


cNoteEntity::cNoteEntity(int a_BlockX, int a_BlockY, int a_BlockZ, cWorld * a_World)
	: cBlockEntity(E_BLOCK_NOTE_BLOCK, a_BlockX, a_BlockY, a_BlockZ, a_World)
	, m_Pitch( 0 )
{
}





cNoteEntity::~cNoteEntity()
{
}





void cNoteEntity::UsedBy( cPlayer * a_Player )
{
	IncrementPitch();
	MakeSound();
}





void cNoteEntity::MakeSound( void )
{
	char instrument;
	switch (m_World->GetBlock(m_PosX, m_PosY - 1, m_PosZ))
	{
		case E_BLOCK_PLANKS:
		case E_BLOCK_LOG:
		case E_BLOCK_NOTE_BLOCK:
		{
			// TODO: add other wood-based blocks if needed
			instrument = E_INST_DOUBLE_BASS;
			break;
		}
		
		case E_BLOCK_SAND:
		case E_BLOCK_GRAVEL:
		case E_BLOCK_SOULSAND:
		{
			instrument = E_INST_SNARE_DRUM;
			break;
		}
		
		case E_BLOCK_GLASS:
		case E_BLOCK_GLASS_PANE:
		case E_BLOCK_GLOWSTONE:
		{
			instrument = E_INST_CLICKS;
			break;
		}

		case E_BLOCK_STONE:
		case E_BLOCK_STONE_BRICKS:
		case E_BLOCK_COBBLESTONE:
		case E_BLOCK_OBSIDIAN:
		case E_BLOCK_NETHERRACK:
		case E_BLOCK_BRICK:
		case E_BLOCK_NETHER_BRICK:
		{
			// TODO: add other stone-based blocks if needed
			instrument = E_INST_BASS_DRUM;
			break;
		}

		default:
		{
			instrument = E_INST_HARP_PIANO;
			break;
		}
	}

	m_World->BroadcastBlockAction(m_PosX, m_PosY, m_PosZ, instrument, m_Pitch);
}





char cNoteEntity::GetPitch( void )
{
	return m_Pitch;
}





void cNoteEntity::SetPitch( char a_Pitch )
{
	m_Pitch = a_Pitch % 25;
}





void cNoteEntity::IncrementPitch( void )
{
	SetPitch( m_Pitch + 1 );
}





bool cNoteEntity::LoadFromJson( const Json::Value & a_Value )
{

	m_PosX = a_Value.get("x", 0).asInt();
	m_PosY = a_Value.get("y", 0).asInt();
	m_PosZ = a_Value.get("z", 0).asInt();

	m_Pitch = (char)a_Value.get("p", 0).asInt();

	return true;
}





void cNoteEntity::SaveToJson( Json::Value & a_Value )
{
	a_Value["x"] = m_PosX;
	a_Value["y"] = m_PosY;
	a_Value["z"] = m_PosZ;

	a_Value["p"] = m_Pitch;
}




