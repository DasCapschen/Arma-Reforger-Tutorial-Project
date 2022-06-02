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
		// is owner the same as this?
		super.EOnInit(owner);
		
		// just for curiosity
		if(owner == this)
		{
			Print("Owner is same as this");
		}
		if(owner == GetParent())
		{
			Print("Owner is same as parent object");
		}
		
		// Do not initialize these tasks out of runtime
		// I guess this stops EOnInit from running in Workbench World Editor?
		if (!GetGame().InPlayMode())
			return;
		
		// only run this code on master ("server")
		if (!m_RplComponent.IsMaster())
			return;
		
		SetFactionForTasks();
	}
	
	////////////////////////////////////////////////////////////////
	///// CALLED ON EVERY MACHINE FOR EVERY PLAYER REGISTERED //////
	// INCLUDING WHEN JIP, PREVIOUS REGISTERED PLAYERS ARE CALLED //
	////////////////////////////////////////////////////////////////
	protected override void OnPlayerRegistered(int registeredPlayerID)
	{
		super.OnPlayerRegistered(registeredPlayerID);

		// Reset faction on initial tasks for JIP (Authority only)
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
		
		IEntity child = GetChildren();
		if(!child) 
		{
			Print("I have no children, did you add a Hierarchy component?", LogLevel.WARNING);
			return;
		}
		
		while(child)
		{
			CAPS_TriggerTask task = CAPS_TriggerTask.Cast(child);
			if(task)
			{
				Faction taskFaction = facMan.GetFactionByKey(task.m_factionKey);
				
				Print("Setting Faction for Task " + task.GetName() + " to " + task.m_factionKey);
				
				SetTaskFaction(task, taskFaction);
			}
			
			child = child.GetSibling();
		}
	}
}
