modded class MissionGameplay extends MissionBase
{
	void MissionGameplay()
	{
		GetRPCManager().AddRPC( "SHTHP", "RPCSendVoteSkipNightConfig", this, SingeplayerExecutionType.Both );
	}
	
	void RPCSendVoteSkipNightConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param1< VoteSkipNightConfig > data  //Player ID, Icon
		if ( !ctx.Read( data ) ) return;
		m_VoteSkipNightConfig = data.param1;
	}
};