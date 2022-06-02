[EntityEditorProps(category: "GameScripted/ScriptWizard", description: "ScriptWizard generated script file.")]
class VipKilledTriggerComponentClass : ScriptComponentClass
{
	// prefab properties here
	
}

//------------------------------------------------------------------------------------------------
/*!
	Class generated via ScriptWizard.
*/
class VipKilledTriggerComponent : ScriptComponent
{

	[Attribute("", UIWidgets.EditBox, desc: "a list of VIPs Names that need to be killed")]
	ref array<string> vipNames;
	
	int countVips = 0;
	int countDead = 0;
	
	protected ref ScriptInvoker onVipsKilled = new ScriptInvoker();
	
	ScriptInvoker GetOnVipsKilled() {
		return onVipsKilled;
	}
	
	
	//------------------------------------------------------------------------------------------------
	override void EOnFrame(IEntity owner, float timeSlice)
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT | EntityEvent.FRAME);
		
		Print("OnPostInit");
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		// OnPostInit runs BEFORE EOnInit!!!!
		// OnPostInit = after init of the component
		// EOnInit = after init of entity
		Print("EOnInit, innit?");
	
		ArmaReforgerScripted game = GetGame();
		if(!game) {
			Print("Error! Game not found!", LogLevel.ERROR);
			return;
		}
		BaseWorld world = game.GetWorld();
		if(!world) {
			Print("Error! World not found!", LogLevel.ERROR);
			return;
		}
		
		foreach(string vipName : vipNames) 
		{
			IEntity vip = world.FindEntityByName(vipName);
			if(!vip) {
				Print("VIP with name " + vipName + " not found!");
				continue;
			}
			
			EventHandlerManagerComponent eventComp = EventHandlerManagerComponent.Cast(vip.FindComponent(EventHandlerManagerComponent));
			if(!eventComp) {
				Print("VIP with name " + vipName + " does not have a event handler manager!");
				continue;
			}
			
			countVips++;
			
			eventComp.RegisterScriptHandler("OnDestroyed", vip, OnVipKilled);
		}
	}
	
	void OnVipKilled(IEntity destroyedEntity)
	{
		// Note that we cannot check WHICH VIP died. We just know one of them did.
		Print("Vip killed");
		
		EventHandlerManagerComponent eventComp = EventHandlerManagerComponent.Cast(destroyedEntity.FindComponent(EventHandlerManagerComponent));
		eventComp.RemoveScriptHandler("OnDestroyed", destroyedEntity, OnVipKilled);
		
		countDead += 1;
		if(countDead >= countVips)
		{
			onVipsKilled.Invoke();
		}
	}

	//------------------------------------------------------------------------------------------------
	void VipKilledTriggerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~VipKilledTriggerComponent()
	{
	}

}
