modded class ChatInputMenu 
{
	// ------------------------------------------------------------
	// Override OnChange
	// ------------------------------------------------------------
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		super.OnChange( w, x, y, finished );
        if ( !finished ) return false;

		string text = m_edit_box.GetText();
        Print( text )

        // MissionGameplay gameplayMission = MissionGameplay.Cast( GetGame().GetMission() );
        // bool useExpansionChat = false;
        // switch (gameplayMission.GetChatChannel())
        // {
        //     case ExpansionChatChannels.CCGlobal:
        //     case ExpansionChatChannels.CCTeam:
        //     case ExpansionChatChannels.CCTransport:
        //     case ExpansionChatChannels.CCAdmin:
        //         useExpansionChat = true;
        //         break;
        // }

        // Print("useExpansionChat:" + useExpansionChat)

        return true;
	}
}