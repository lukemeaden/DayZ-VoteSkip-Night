ref VoteNightConfig m_VoteNightConfig;

class VoteConfig {
	string Name;
	string Property;

	void VoteConfig( string name, string property ) {
		Name = name;
		Property = property;
	}
}

class VoteNightConfig {

	protected static string VoteNightConfigJson = "$profile:\\VoteNight.json";

	[NonSerialized()]
	protected ref map< string, ref VoteConfig > VoteNightConfigMap = new map< string, ref VoteConfig >;

	void VoteNightConfig() {
		Default();
		Load();
		Save();
	}

	void Default() {
		AddCfg( "VotesRequiredPercentage", "50" );
		AddCfg( "Command", "$skip" );
	}

	void AddCfg( string name, string property )
	{
		VoteConfig Vote = new VoteConfig( name, property );
		VoteNightConfigMap.Insert( name, Vote );
	}

	void Load()
	{
		if ( FileExist( VoteNightConfigJson ) ) {
			JsonFileLoader< VoteNightConfig >.JsonLoadFile( VoteNightConfigJson, this );
		} else {
			JsonFileLoader< VoteNightConfig >.JsonSaveFile( VoteNightConfigJson, this );
			Print("-------------------------------------------");
			Print("-------------------------------------------");
			Print(VoteNightConfig);
			Print("-------------------------------------------");
			Print("-------------------------------------------");
		}
	}

	void Save()
	{

	}
}

ref VoteNightConfig VoteNightConfig() {
	if ( !m_VoteNightConfig ) {
		m_VoteNightConfig = new VoteNightConfig;
	}

	return m_VoteNightConfig;
}
