
#pragma once

#include "ItemHandler.h"
#include "Blocks/BlockEnderchest.h"





class cItemEnderchestHandler final  :
	public cItemHandler
{
	using Super = cItemHandler;

public:

	using Super::Super;

private:

	virtual bool CommitPlacement(cPlayer & a_Player, const cItem & a_HeldItem, const Vector3i a_PlacePosition, const eBlockFace a_ClickedBlockFace, const Vector3i a_CursorPosition) const override
	{
		return a_Player.PlaceBlock(a_PlacePosition, E_BLOCK_ENDER_CHEST, cBlockEnderchestHandler::YawToMetaData(a_Player.GetYaw()));
	}
};
