class CfgPatches
{
	class ExpansionVoteSkipNight
	{
		requiredAddons[]={
			"DayZExpansion_Core",
			"DayZExpansion_Scripts"
		};
	};
};
class CfgMods
{
	class ExpansionVoteSkipNight
	{
		dir="ExpansionVoteSkipNight";
		name="ExpansionVoteSkipNight";
		credits="Mka0207";
		author="Mka0207";
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"ExpansionVoteSkipNight/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ExpansionVoteSkipNight/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ExpansionVoteSkipNight/Scripts/5_Mission"
				};
			};
		};
	};
};
