modded class MissionServer extends MissionBase
{
	const float ADVERT_DELAY = GetVSN().MessageVoteAdvertDelay;
	float AdCheckTimer = 0.0;
	ref array<Man> GetPlys;

	override void OnInit()
	{
		super.OnInit();
		GetPlys = new array<Man>;
		GetVSN();
	}

	override void TickScheduler(float timeslice)
	{
		super.TickScheduler(timeslice);

		// Print( "[VSN] TickScheduler()" );
		if ( GetGame().GetWorld().IsNight() )
		{
			AdCheckTimer += timeslice;
			// Print( "[VSN] TickScheduler() IsNight()" + AdCheckTimer );

			if ( AdCheckTimer > ADVERT_DELAY )
			{
				// Print( "[VSN] TickScheduler() IsNight() should send message" );
				GetGame().GetPlayers( GetPlys );
				// Print( "[VSN] TickScheduler() IsNight() send message: " + GetVSN().GetMessage( GetVSN().MessageVoteAdvert ) );
				// Print( "[VSN] TickScheduler() IsNight() template message: " + GetVSN().GetMessage( GetVSN().MessageVoteAdvert, true, true, GetVSN().Command ) );
				Param1<string> params2;
				params2 = new Param1<string>( GetVSN().GetMessage( GetVSN().MessageVoteAdvert, true, true, GetVSN().Command ) );

				foreach ( Man ply: GetPlys )
				{
					PlayerBase play;
					Class.CastTo(play, ply);
					if ( play )
					{
						play.RPCSingleParam( ERPCs.RPC_USER_ACTION_MESSAGE, params2, true, play.GetIdentity() );
					}
				}
				AdCheckTimer = 0.0;
			}
		}
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		if ( identity )
		{
			string playerID = identity.GetPlainId();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendVoteSkipNightConfig", 1500, false, new Param1<ref PlayerBase >( player ));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendVoteSkipNightConfig", 3500, false, new Param1<ref PlayerBase >( player ));
		}
	}
	
	void SendVoteSkipNightConfig( PlayerBase player ){
		if (player.IsPlayerDisconnected()) { return; }
		PlayerIdentity identity = player.GetIdentity();
		if (identity){
			GetRPCManager().SendRPC("SHTHP", "RPCSendVoteSkipNightConfig", new Param1< VoteSkipNightConfig >( GetVSN() ), true, identity);
		}
	}
}