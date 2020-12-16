ref VoteSkipNightConfig m_VoteSkipNightConfig;

class VoteSkipNightConfig
{
    protected static string VoteSkipNightJSON = "$profile:\\VoteSkipNight.json";

    bool UseNotifications = true;
    float VotesRequiredPercentage = 100;
    string Command = "!skip";
    float TimeToSkipTo = 4;
    bool UseVoteAdvert = true;
    string MessageVoteAdvert = "You can type $$0$$ to advance to daytime.";
    float MessageVoteAdvertDelay = 600;
    string MessageVoteRecieved = "You have submitted a vote.";
    string MessageVoteDenied = "Hold up, it isn't night time yet!";
    string MessageVoteSuccess = "Vote passed! Changing to daytime...";
    string MessageDuplicateVote = "Error! duplicate vote canceled.";
    string MessageRemainingVotes = "$$0$$ votes until night is forced.";
    string MessagePrefix = "Vote Skip Night";

    void VoteSkipNightConfig(){}

    void Load()
    {
        Print( "[VSN] Load config" );
        if (FileExist( VoteSkipNightJSON ))
        {
            JsonFileLoader <VoteSkipNightConfig>.JsonLoadFile( VoteSkipNightJSON, this );
        } else {
            JsonFileLoader<VoteSkipNightConfig>.JsonSaveFile(VoteSkipNightJSON, this);
        }
    }

    string GetMessage( string message, bool usePrefix = false, bool useTemplate = false, string templateString = "" )
    {
        switch (true)
        {
            case (usePrefix && useTemplate):
                return "[" + MessagePrefix + "] " + message.Replace( "$$0$$", templateString ) ;
            case usePrefix:
                return "[" + MessagePrefix + "] " + message;
            case useTemplate:
                return message;
        }
        return message;
    }

    static bool IsModLoaded(string type_name_from_mod)
    {
        // From InclementDab
        // https://discord.com/channels/452035973786632194/492295576470290433/786835185215864834
        return (type_name_from_mod.ToType().ToString().Length() > 0);
    }

    bool ShouldUseNotifications()
    {
        if (IsModLoaded("ExpansionVehicleBase")) return UseNotifications;
        return false;
    }
}

static ref VoteSkipNightConfig GetVSN()
{
	if (!m_VoteSkipNightConfig)
	{
		m_VoteSkipNightConfig = new VoteSkipNightConfig;
		m_VoteSkipNightConfig.Load();
	}
	return m_VoteSkipNightConfig;
};
