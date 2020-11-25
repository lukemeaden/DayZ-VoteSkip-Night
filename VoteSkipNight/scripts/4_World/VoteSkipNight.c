class ExpansionVoteSkipNight
{
	static autoptr ref set<string> VotePool = new set<string>;
	static int CurrentNumOfPlys = 0;
	static ref array<Man> CurrentArrayOfPlys = new array<Man>;
	static bool m_HasVoteEnded = false;

	void ExpansionVoteSkipNight(){}
	void ~ExpansionVoteSkipNight(){}

	static void UpdatePlayerCount()
	{
		GetGame().GetWorld().GetPlayerList(ExpansionVoteSkipNight.CurrentArrayOfPlys);

		if ( ExpansionVoteSkipNight.CurrentArrayOfPlys.Count() > 0 )
		{
			ExpansionVoteSkipNight.CurrentNumOfPlys = ExpansionVoteSkipNight.CurrentArrayOfPlys.Count();
		}
	}

	static void ResetVotingData()
	{
		VotePool.Clear();
		CurrentNumOfPlys = 0;
		CurrentArrayOfPlys.Clear();
		m_HasVoteEnded = false;
	}

	static void AnnounceWin()
	{

		foreach ( Man player: CurrentArrayOfPlys )
		{
			PlayerBase m_Player;
			m_Player = PlayerBase.Cast(player);

			ScriptRPC rpc2 = new ScriptRPC();
			rpc2.Write("win");
			rpc2.Send( m_Player, VOTE_NIGHT.SKIPNIGHT_NOTIFY, true, m_Player.GetIdentity()) ;
		}

		//Set the time to day.
		int year, month, day, hour, minute;
		GetGame().GetWorld().GetDate(year, month, day, hour, minute);
		GetGame().GetWorld().SetDate(year, month, day, 4, 0);
		
		Print("[VSN] AnnounceWin()");

		ResetVotingData();
	}

	static void CalculateVoteWinner()
	{
		if ( VotePool.Count() >= Math.Ceil( CurrentNumOfPlys * GetExpansionVoteSkipNightConfig().VotesRequiredPercentage ) )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ExpansionVoteSkipNight.AnnounceWin, 500, false );
			m_HasVoteEnded = true;
		}
	}
}