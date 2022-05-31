[EntityEditorProps(category: "GameScripted/ScriptWizard", description: "ScriptWizard generated script file.")]
class CAPS_SimpleTaskManagerClass : GenericEntityClass
{
	// prefab properties here
}

class CAPS_SimpleTaskManager : GenericEntity
{
	[Attribute(desc: "Names of tasks to be completed")]
	ref array<string> taskNames;
	
	[Attribute("USSR", desc: "Faction that should win when all tasks are completed")]
	string factionKey;
	
	ref map<string, bool> isTaskCompleted = new map<string, bool>();
	
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		BaseWorld world = GetGame().GetWorld();
		if (!world)
		{
			Print("Err: No World found!", LogLevel.ERROR);
			return;
		}
		
		foreach(string taskName : taskNames)
		{
			IEntity task = world.FindEntityByName(taskName);
			if(!task)
			{
				Print("Task with name " + taskName + " was not found", LogLevel.WARNING);
				continue;
			}
			
			TaskScriptInvokerComponent invokerComp = TaskScriptInvokerComponent.Cast(task.FindComponent(TaskScriptInvokerComponent));
			if(!invokerComp)
			{
				Print("Task with name " + taskName + " was not found", LogLevel.WARNING);
				continue;
			}
			
			isTaskCompleted.Insert(taskName, false);
			
			invokerComp.GetOnTaskFinished().Insert(OnTaskFinished);	
		}
	}
	
	void OnTaskFinished(string taskName)
	{
		if (!isTaskCompleted.Contains(taskName)) return;
		
		isTaskCompleted.Set(taskName, true);
		
		bool allCompleted = true;
		foreach(string name, bool value : isTaskCompleted)
		{
			allCompleted = allCompleted && value;
		}
		
		if(allCompleted)
		{
			EndGame();
		}
	}
	
	void EndGame()
	{
		FactionManager facMan = GetGame().GetFactionManager();
		Faction fac = facMan.GetFactionByKey(factionKey);
		int facIdx = facMan.GetFactionIndex(fac);
		
		SCR_GameModeEndData data = SCR_GameModeEndData.CreateSimple(SCR_GameModeEndData.ENDREASON_EDITOR_FACTION_VICTORY, winnerFactionId: facIdx);
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		gameMode.EndGameMode(data);
	}

	//------------------------------------------------------------------------------------------------
	void CAPS_SimpleTaskManager(IEntitySource src, IEntity parent)
	{
		SetEventMask(EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	void ~CAPS_SimpleTaskManager()
	{
	}

}
