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
			// Print( "[VSN] VotePool = " + VotePool );
			// Print( "[VSN] VotePool.Count() = " + VotePool.Count() );
			if ( VotePool.Count() <= 0 ) 
			{
				VotePool = new set<string>;
			}
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		// Print( "[VSN] OnRPC()" );
		super.OnRPC(sender, rpc_type, ctx);	

		if ( GetGame().IsClient() )
		{
			// Print( "[VSN] OnRPC() IsClient() START" );
			PlayerBase c_player = PlayerBase.Cast( GetGame().GetPlayer() );
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY)
			{								
				string result;
				ctx.Read(result);

				if ( result == "win" )
				{
					VoteSkipNight.VSN_Alert( GetVSN().MessageVoteSuccess, c_player, "success" );
					VotePool.Clear();
				}
			}

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_NOTIFY_FAIL)
			{
				VoteSkipNight.VSN_Alert( GetVSN().MessageDuplicateVote, c_player, "error" );
			}

			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_SYNC_VOTEPOOL)
			{
				int votes_left = 0;
				ctx.Read(votes_left);

				if ( votes_left > 0 )
				{
					VoteSkipNight.VSN_Alert( GetVSN().MessageRemainingVotes, c_player, "error", true, false, true, "" + votes_left );
				}
			}
			// Print( "[VSN] OnRPC() IsClient() END" );
		}

		if ( GetGame().IsServer() )
		{
			// Print( "[VSN] OnRPC() IsServer() START" );
			if (rpc_type == VOTE_NIGHT.SKIPNIGHT_VOTE)
			{								
				int desired_id = VoteSkipNight.VotePool.Find( sender.GetId() );
				if ( !VoteSkipNight.VotePool.Get( desired_id ) )
				{
					if ( GetGame().GetWorld().IsNight() )
					{
						if ( !VoteSkipNight.m_HasVoteEnded )
						{
							VoteSkipNight.VotePool.Insert( sender.GetId() );
							VoteSkipNight.UpdatePlayerCount();
							VoteSkipNight.CalculateVoteWinner();

							int RequiredVotes = VoteSkipNight.returnRequiredVotes();
							int CurrentNumVotes = VoteSkipNight.VotePool.Count();
							int diff = RequiredVotes-CurrentNumVotes;

							//let players know how many votes are left.
							foreach ( Man player: VoteSkipNight.CurrentArrayOfPlys )
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
			// Print( "[VSN] OnRPC() IsServer() END" );										
		}
	}
}