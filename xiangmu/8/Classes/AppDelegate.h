#pragma once
#include "AppMacro.h"

class AppDelegate :	private Application {
		
public:
	AppDelegate();
	~AppDelegate();
	/**?	@brief    Implement Director and Scene init code here.
	@return true    Initialize success, app continue.
	@return false   Initialize failed, app terminate.	*/
	virtual bool applicationDidFinishLaunching();

	/**?	@brief  The function be called when the application enter background
	@param  the pointer of the application	*/
	virtual void applicationDidEnterBackground();

	/**?	@brief  The function be called when the application enter foreground
	@param  the pointer of the application?	*/
	virtual void applicationWillEnterForeground();
};

