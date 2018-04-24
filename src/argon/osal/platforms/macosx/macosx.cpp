#include <argon/osal/platforms/macosx/macosx.h>
#include <argon/osal/platforms/macosx/windowsystem.h>

void PlatformInit ()
{
	
	using Argon::OSAL::MacOSX::MacApplication;
	
	MacApplication * this_application = MacApplication::get_shared_instance ();
	this_application -> set_activation_policy ( MacApplication::kactivation_policy_regular );
	
};

void PlatformDeInit ()
{
	
	delete Argon::OSAL::MacOSX::MacApplication::shared_instance;
	
}
