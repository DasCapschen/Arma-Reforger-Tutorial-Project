[EntityEditorProps(category: "GameScripted/Tasks", description: "ScriptWizard generated script file.")]
class CAPS_TriggerTaskClass : SCR_TriggerTaskClass
{
	// prefab properties here
}

class CAPS_TriggerTaskData : SCR_TriggerTaskData
{
};

[BaseContainerProps()]
class CAPS_TriggerTaskSupportClass : SCR_EditorTaskSupportClass
{
	override SCR_BaseTaskData CreateTaskData()
	{		
		return new CAPS_TriggerTaskData();
	}
	
	void CAPS_TriggerTaskSupportClass()
	{
		m_TypeName = CAPS_TriggerTask;
	}
};

class CAPS_TriggerTask : SCR_TriggerTask
{
	[Attribute("", desc: "Faction to create this task for")]
	string m_factionKey;
}
