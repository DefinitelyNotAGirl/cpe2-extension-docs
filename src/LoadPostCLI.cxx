#include <FlowChart.hxx>
#include <compiler/inc/event.hxx>
/**
 * @brief the compiler will call this function once it is done parsing the command line arguments
 */
extern const char* masterStyleSheet;
class function;
extern void SetFunction(function* func);
extern void CreateFunction(function* func);
extern void CallNode(function* func, std::vector<variable*>* args);
void LoadPostCLI() {
	content += "<!DOCTYPE html><html lang='en'>\n<head>\n";
	content += "<meta charset='UTF-8'>\n<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
	content += "<title>Document</title>";
	content += "<style>\n"+std::string(masterStyleSheet)+"</style>";
	content += "</head>\n<body>\n";
	Event::FunctionSwitch.EventHandlers.push_back(
		EventHandler<Event::Data::FunctionSwitch>(
			[](void* HandlerData, Event::Data::FunctionSwitch* EventData) {
				SetFunction(EventData->func);
			}
		)
	);
	Event::FunctionDeclaration.EventHandlers.push_back(
		EventHandler<Event::Data::FunctionDeclaration>(
			[](void* HandlerData, Event::Data::FunctionDeclaration* EventData) {
				CreateFunction(EventData->func);
			}
		)
	);
	Event::Call.EventHandlers.push_back(
		EventHandler<Event::Data::Call>(
			[](void* HandlerData, Event::Data::Call* EventData) {
				CallNode(EventData->func,EventData->args);
			}
		)
	);
}
