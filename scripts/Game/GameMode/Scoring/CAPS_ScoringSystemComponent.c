//------------------------------------------------------------------------------------------------
modded class SCR_ScoringSystemComponentClass: SCR_BaseScoringSystemComponentClass
{
};


//------------------------------------------------------------------------------------------------
/*!
	This component implements logic of handling certain score limits.
*/
modded class SCR_ScoringSystemComponent : SCR_BaseScoringSystemComponent
{
	override bool GetPlayerID(IEntity entity, out int playerID)
	{
		return true;
	}
	
	protected override void OnPlayerKilled(int playerId, IEntity player, IEntity killer)
	{
		Print("OnPlayerKilled: " + playerId, LogLevel.WARNING);
		super.OnPlayerKilled(playerId, player, killer);
	}
	
	override void AddKill(int playerId, int count = 1)
	{	
		Print("Server: Adding kill to player " + playerId, LogLevel.WARNING);
		super.AddKill(playerId, count);
	}	
};