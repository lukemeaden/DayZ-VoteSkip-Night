class CfgPatches
{
	class VoteSkipNight
	{
		requiredAddons[]={};
	};
};
class CfgMods
{
	class VoteSkipNight
	{
		dir="ConfigurableVoteSkipNight";
		name="ConfigurableVoteSkipNight";
		credits="@Lewk_io, Mka0207";
		author="@Lewk_io, Mka0207";
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
					"ConfigurableVoteSkipNight/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ConfigurableVoteSkipNight/Scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ConfigurableVoteSkipNight/Scripts/5_Mission"
				};
			};
		};
	};
};
