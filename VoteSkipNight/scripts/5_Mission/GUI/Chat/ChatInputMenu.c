modded class ChatInputMenu
{
	// ------------------------------------------------------------
	// Override OnChange
	// ------------------------------------------------------------
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		if (!finished) return false;
		string text = m_edit_box.GetText();
		if ( text == GetExpansionVoteSkipNightConfig().Command )
		{
			PlayerIdentity sender = GetGame().GetPlayer().GetIdentity();
			if ( GetExpansionVoteSkipNightConfig().UseNotifications )
			{
				if ( GetGame().GetWorld().IsNight() )
				{
					NotificationSystem.CreateNotification( new StringLocaliser( "VOTE NIGHT SKIP" ), new StringLocaliser( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteRecieved ) ), EXPANSION_NOTIFICATION_ICON_T_Compass, COLOR_EXPANSION_NOTIFICATION_INFO, 7, sender );
				} else {
					NotificationSystem.CreateNotification( new StringLocaliser( "VOTE NIGHT SKIP" ), new StringLocaliser( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteDenied ) ), EXPANSION_NOTIFICATION_ICON_T_Compass, COLOR_EXPANSION_NOTIFICATION_ERROR, 7, sender );
				}
			} else {
				string name;
				GetGame().GetPlayerName( name );
				if ( GetGame().GetWorld().IsNight() )
				{
					MissionGameplay.Cast( GetGame().GetMission() ).m_Chat.Add( new ChatMessageEventParams( CCDirect, name, GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteRecieved, true ), "" ) );
				} else {
					MissionGameplay.Cast( GetGame().GetMission() ).m_Chat.Add( new ChatMessageEventParams( CCDirect, name, GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteDenied, true ), "" ) );
				}
			}
			Close();
		} else {
			super.OnChange(w, x, y, finished);
		}
		return true;
	}
}