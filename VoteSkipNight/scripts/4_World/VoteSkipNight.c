class VoteSkipNight
{
	static autoptr ref set<string> VotePool = new set<string>;
	static int CurrentNumOfPlys = 0;
	static ref array<Man> CurrentArrayOfPlys = new array<Man>;
	static bool m_HasVoteEnded = false;

	void VoteSkipNight(){}
	void ~VoteSkipNight(){}

	static void UpdatePlayerCount()
	{
		GetGame().GetWorld().GetPlayerList(VoteSkipNight.CurrentArrayOfPlys);

		if (IsMissionOffline())
		{
			// If the mission is offline then we'll assume that the mod is being tested, so force the count to 2 for easy testing
			VoteSkipNight.CurrentNumOfPlys = 2;
		}
		else
		{
			if ( VoteSkipNight.CurrentArrayOfPlys.Count() > 0 )
			{
				VoteSkipNight.CurrentNumOfPlys = VoteSkipNight.CurrentArrayOfPlys.Count();
			}
		}
	}

	static void VSN_Log( string message )
	{
		Print( "[VSN] " + message );
	}

	static void VSN_Alert( string message, PlayerBase player, string color = "default", bool forceMessage = false, bool usePrefix = false, bool useTemplate = false, string templateString = "" )
	{
		PlayerIdentity sender = player.GetIdentity();
		if ( !GetVSN().ShouldUseNotifications() )
		{
			string msgColor;
			switch (color)
			{
				case "error":
					msgColor = "colorImportant";
					break;
				case "success":
					msgColor = "colorFriendly";
					break;
				case "default":
					msgColor = "colorAction";
					break;
				default:
					msgColor = "colorAction";
					break;
			}
			player.Message( GetVSN().GetMessage( message, true, useTemplate, templateString ), msgColor);
		}
		else
		{
			int expColor;
			switch (color)
			{
				case "error":
					expColor = COLOR_EXPANSION_NOTIFICATION_ERROR;
					break;
				case "success":
					expColor = COLOR_EXPANSION_NOTIFICATION_SUCCSESS;
					break;
				case "default":
					expColor = COLOR_EXPANSION_NOTIFICATION_INFO;
					break;
				default:
					expColor = COLOR_EXPANSION_NOTIFICATION_INFO;
					break;
			}
			NotificationSystem.CreateNotification( new StringLocaliser( GetVSN().MessagePrefix ), new StringLocaliser( GetVSN().GetMessage( message, false, useTemplate, templateString ) ), EXPANSION_NOTIFICATION_ICON_T_Compass, expColor, 7, sender );
		}
	}

	static void ResetVotingData()
	{
		VotePool.Clear();
		CurrentNumOfPlys = 0;
		CurrentArrayOfPlys.Clear();
		m_HasVoteEnded = false;

		//Print("Reset Data!");
	}

	static void AnnounceWin()
	{
		foreach ( Man player: CurrentArrayOfPlys )
		{
			PlayerBase m_Player;
			m_Player = PlayerBase.Cast(player);

			ScriptRPC rpc2 = new ScriptRPC();
			rpc2.Write("win");
			rpc2.Send( m_Player, VOTE_NIGHT.SKIPNIGHT_NOTIFY, true, m_Player.GetIdentity());
		}

		//Set the time to day.
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		GetGame().GetWorld().SetDate(year, month, day, GetVSN().TimeToSkipTo, 0);
		//Print("Time has been set to day light!");

		ResetVotingData();
	}

	static float returnRequiredVotes()
	{
		return Math.Ceil( (CurrentNumOfPlys / 100) * GetVSN().VotesRequiredPercentage );
	}

	static bool isVoteSuccessful()
	{
		return VotePool.Count() >= returnRequiredVotes();
	}

	static void CalculateVoteWinner()
	{
		VSN_Log( "" + returnRequiredVotes() + " votes to pass, got " + VotePool.Count() );
		if ( isVoteSuccessful() )
		{
			VSN_Log( "" + VotePool.Count() + "/" + returnRequiredVotes() + ". Vote was successful" );
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( VoteSkipNight.AnnounceWin, 5000, false );
			m_HasVoteEnded = true;
		}
		/*else
		{
			VoteSkipNight.AnnounceFail();
		}*/
	}
}