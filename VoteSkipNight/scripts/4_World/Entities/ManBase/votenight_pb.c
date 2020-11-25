//Class that are modded to be overridden!
modded class PlayerBase extends ManBase
{	
	const float Vote_Night_WarnInterval = 10;
	protected float m_VoteNightTimer = 0.0;

	static autoptr ref set<string> VotePool;

	override void Init()
	{
		super.Init();
		if ( GetGame().IsClient() )
		{
			if ( VotePool.Count() <= 0 ) 
			{
				VotePool = new set<string>;
			}
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);	
			
		if ( GetGame().IsClient() )
		{
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY)
			{								
				string result;
				ctx.Read(result);

				if ( result == "win" )
				{
					Print("[VSN] Vote was successful so skip to night");

					if ( GetExpansionVoteSkipNightConfig().UseNotifications )
					{
						NotificationSystem.CreateNotification( new StringLocaliser( "VOTE NIGHT SKIP" ), new StringLocaliser( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteSuccess ) ), EXPANSION_NOTIFICATION_ICON_T_Compass, COLOR_EXPANSION_NOTIFICATION_SUCCSESS, 7, sender );
					} else {
						this.Message( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageVoteSuccess, true ) , "colorAction" );
					}

					VotePool.Clear();
				}
			}

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL)
			{
				if ( GetExpansionVoteSkipNightConfig().UseNotifications )
				{
					NotificationSystem.CreateNotification( new StringLocaliser( "VOTE NIGHT SKIP" ), new StringLocaliser( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageDuplicateVote ) ), EXPANSION_NOTIFICATION_ICON_T_Compass, COLOR_EXPANSION_NOTIFICATION_SUCCSESS, 7, sender );
				} else {
					this.Message( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageDuplicateVote, true ), "colorAction" );
				}
			}

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL)
			{
				int votes_left = 0;
				ctx.Read(votes_left);

				if ( votes_left > 0 )
				{
					this.Message( GetExpansionVoteSkipNightConfig().GetMessage( GetExpansionVoteSkipNightConfig().MessageRemainingVotes, true, true, votes_left.ToString() ) , "colorAction");
				}
			}
		}

		if ( GetGame().IsServer() )
		{
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_VOTE)
			{								
				int desired_id = ExpansionVoteSkipNight.VotePool.Find( sender.GetId() );
				if ( !ExpansionVoteSkipNight.VotePool.Get( desired_id ) )
				{
					if ( GetGame().GetWorld().IsNight() )
					{
						if ( !ExpansionVoteSkipNight.m_HasVoteEnded )
						{
							ExpansionVoteSkipNight.VotePool.Insert( sender.GetId() );
							ExpansionVoteSkipNight.UpdatePlayerCount();
							ExpansionVoteSkipNight.CalculateVoteWinner();

							int RequiredVotes = Math.Ceil( ExpansionVoteSkipNight.CurrentNumOfPlys * 1 );
							int CurrentNumVotes = ExpansionVoteSkipNight.VotePool.Count();
							int diff = RequiredVotes-CurrentNumVotes;

							//let players know how many votes are left.
							foreach ( Man player: ExpansionVoteSkipNight.CurrentArrayOfPlys )
							{
								PlayerBase m_Player;
								m_Player = PlayerBase.Cast(player);

								ScriptRPC rpc2 = new ScriptRPC();
								rpc2.Write(diff);
								rpc2.Send( m_Player, VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL, true, m_Player.GetIdentity()) ;
							}
						}
					}
				}
				else
				{
					Param1<string> warn;
					warn = new Param1<string>( "" );
					this.RPCSingleParam( VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL, warn, true, this.GetIdentity() );
				}
			}											
		}
	}
}