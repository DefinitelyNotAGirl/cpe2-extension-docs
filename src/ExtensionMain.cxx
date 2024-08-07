//+
//+
//+ This file should just be left alone.
//+
//+
#include <compiler/inc/Routine.hxx>
#include <iostream>

extern std::vector<Routine> PostCLIRoutines;
extern std::vector<Routine> AbortRoutines;
extern std::vector<Routine> FinishRoutines;
extern void LoadPostCLI();
extern void Finish();
extern void Abort();
extern void RegisterExtension();
extern "C" void ExtensionMain() {
	PostCLIRoutines.push_back(Routine(nullptr,
		[](void*){
			LoadPostCLI();
		}
	));
	AbortRoutines.push_back(Routine(nullptr,
		[](void*){
			Abort();
		}
	));
	FinishRoutines.push_back(Routine(nullptr,
		[](void*){
			Finish();
		}
	));
}
