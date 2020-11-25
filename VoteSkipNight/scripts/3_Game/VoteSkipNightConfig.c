ref ExpansionVoteSkipNightConfig m_ExpansionVoteSkipNightConfig;

class ExpansionVoteSkipNightConfig
{
    protected static string ExpansionVoteSkipNightJSON = "$profile:\\ExpansionVoteSkipNight.json";

    bool UseNotifications = true;
    float VotesRequiredPercentage = 0.5;
    string Command = "$skip";
    string MessageVoteAdvert = "You can type $$0$$ to advance to daytime.";
    float MessageVoteAdvertDelay = 600;
    string MessageVoteRecieved = "You have submitted a vote.";
    string MessageVoteDenied = "Hold up, it isn't night time yet!";
    string MessageVoteSuccess = "Time has been set to day light!";
    string MessageDuplicateVote = "Error! duplicate vote canceled."
    string MessageRemainingVotes = "$$0$$ votes until night is forced.";

    void ExpansionVoteSkipNightConfig(){}

    void Load()
    {
        if (FileExist( ExpansionVoteSkipNightJSON ))
        {
            JsonFileLoader <ExpansionVoteSkipNightConfig>.JsonLoadFile( ExpansionVoteSkipNightJSON, this );
        } else {
            JsonFileLoader<ExpansionVoteSkipNightConfig>.JsonSaveFile(ExpansionVoteSkipNightJSON, this);
        }
    }

    string GetMessage( string message, bool usePrefix = false, bool useTemplate = false, string templateString = "" )
    {
        switch (true)
        {
            case (usePrefix && useTemplate):
                return "[Vote Skip Night] " + message.Replace( "$$0$$", templateString ) ;
            case usePrefix:
                return "[Vote Skip Night] " + message;
            case useTemplate:
                return message;
        }
        return message;
    }
}

static ref ExpansionVoteSkipNightConfig GetExpansionVoteSkipNightConfig()
{
	if (!m_ExpansionVoteSkipNightConfig)
	{
		m_ExpansionVoteSkipNightConfig = new ExpansionVoteSkipNightConfig;
		m_ExpansionVoteSkipNightConfig.Load();
	}
	return m_ExpansionVoteSkipNightConfig;
};
