modded class ChatInputMenu extends UIScriptedMenu
{
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (!finished) return false;

		if (m_edit_box.GetText() != "")
		{
			if ( m_edit_box.GetText() == GetVSN().Command )
			{
				PlayerBase player = GetGame().GetPlayer();
				if ( GetGame().GetWorld().IsNight() )
				{
					ScriptRPC rpc = new ScriptRPC();
					rpc.Send(GetGame().GetPlayer(), VOTE_NIGHT.SKIPNIGHT_VOTE, true, GetGame().GetPlayer().GetIdentity());
					VoteSkipNight.VSN_Alert( GetVSN().MessageVoteRecieved, player );
				}
				else
				{
					VoteSkipNight.VSN_Alert( GetVSN().MessageVoteDenied, player, "error" );
				}
				Close();
			}
			else
			{
				super.OnChange(w, x, y, finished);
			}
		}

		return true;
	}
}