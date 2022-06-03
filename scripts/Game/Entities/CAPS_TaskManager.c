[EntityEditorProps(category: "GameScripted/ScriptWizard", description: "ScriptWizard generated script file.")]
class CAPS_TaskManagerClass : SCR_BaseTaskManagerClass
{
	// prefab properties here
}

//------------------------------------------------------------------------------------------------
/*!
	Class generated via ScriptWizard.
*/
class CAPS_TaskManager : SCR_BaseTaskManager
{
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		// Do not initialize these tasks out of runtime
		// I guess this stops EOnInit from running in Workbench World Editor?
		if (!GetGame().InPlayMode())
			return;
		
		// only run this code on master ("server")
		if (m_RplComponent.IsMaster())
		{
			SetFactionForTasks();
		}
	}
	
	// this is the magic function that makes Tasks replicate properly :)
	// called on every machine for each player registered, including JIP
	// previously reigstered players are called again on JIP
	protected override void OnPlayerRegistered(int registeredPlayerID)
	{
		super.OnPlayerRegistered(registeredPlayerID);

		// Set Task Factions for newly joined players
		if (m_RplComponent.IsMaster())
		{
			SetFactionForTasks();			
		}
	}
	
	// TODO: we could cache the tasks instead of iterating children again. Not sure how expensive it is...
	protected void SetFactionForTasks()
	{
		FactionManager facMan = GetGame().GetFactionManager();
		if(!facMan) 
		{
			Print("Faction Manager not found!!", LogLevel.ERROR);
			return;
		}
		
		Print("TaskList: " + m_aTaskList.Count(), LogLevel.WARNING);
		
		// m_aTaskList comes from SCR_BaseTaskManager :)
		foreach(SCR_BaseTask baseTask : m_aTaskList)
		{
			CAPS_TriggerTask task = CAPS_TriggerTask.Cast(baseTask);
			if(task)
			{
				Faction taskFaction = facMan.GetFactionByKey(task.m_factionKey);
				Print("Setting Faction for Task " + task.GetName() + " to " + task.m_factionKey);
				SetTaskFaction(task, taskFaction);
			}
		}
	}
}
