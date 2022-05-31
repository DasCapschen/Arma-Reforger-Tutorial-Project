[EntityEditorProps(category: "GameScripted/ScriptWizard", description: "ScriptWizard generated script file.")]
class TaskScriptInvokerComponentClass : ScriptComponentClass
{
	// prefab properties here
}

//------------------------------------------------------------------------------------------------
/*!
	Class generated via ScriptWizard.
*/
class TaskScriptInvokerComponent : ScriptComponent
{
	protected ref ScriptInvoker onTaskFinished = new ScriptInvoker();
	
	ScriptInvoker GetOnTaskFinished()
	{
		return onTaskFinished;
	}
}
