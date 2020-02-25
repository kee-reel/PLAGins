## Creating new plugin
Use custom wizard for QtCreator -- [link](/Resources/QtCreator%20wizard).
You should choose project directory according to your plugin type in "/Plugins" folder. If you create new interface -- add it into "/Interfaces/*" subdirectory.

## Interact with other plugin
To interact with other plugin you should know only interface of this plugin.

Every plugin has its own meta info -- it's stored in "PluginMeta.json'. Here is example of plugin meta:
```js
{
    "iplugin": {
		"interfaces": ["IUserTaskManager/1.0"],
		"references": {
			"IExtendableDataManager/1.0": 1
		},
		"info": {
			"name": "UserTaskManager",
			"about": "Core plugin of user task management"
		}
	}
}
```
| Field | Description |
| ------ | ------ |
| interfaces | List that contains all interfaces of this plugin |
| references | Map that contains all references of this plugin. Key is reference interface, value is required amount: 0 -- unlimited, [1-9999] -- require specific amount of references | 
| name | Human readable name of this plugin | 
| about | Human readable description of this plugin | 

## How to build
There are "plugins.pro" file in "/Plugins" folder - by using it you could build all plugins.
When you'll open project make sure that you disable "Shadow build" option.
![Shadow build](/Resources/Images/ShadowBuild.png)
