#include <compiler/inc/event.hxx>
#include <compiler/inc/function.h>
#include <compiler/inc/class_type.h>
#include <compiler/inc/Extension.hxx>
#include <globals.hxx>
#include <compiler/inc/Parser.hxx>
#include <filesystem>

void CreateFunctionEntry(function* func);
void CreateClassEntry(type* Type);
/**
 * @brief the compiler will call this function once it is done parsing the command line arguments
 */
void LoadPostCLI() {
	Event::FunctionFinalization.EventHandlers.push_back(
		EventHandler<Event::Data::FunctionFinalization>(
			[](void* HandlerData, Event::Data::FunctionFinalization* EventData) {
				CreateFunctionEntry(EventData->func);
			}
		)
	);
	ExtensionCallbacks.insert(std::pair<std::__1::string, ExtensionCallback>(
		"desc",
		[]() {
			if(!Description.empty())Description += " ";
			Description += ParserState.Line.restText().substr(1);
		}
	));
	ExtensionCallbacks.insert(std::pair<std::__1::string, ExtensionCallback>(
		"brief",
		[]() {
			if(!Description.empty())Description += " ";
			Description += ParserState.Line.restText().substr(1);
		}
	));
	ExtensionCallbacks.insert(std::pair<std::__1::string, ExtensionCallback>(
		"return",
		[]() {
			Return += ParserState.Line.restText().substr(1);
		}
	));
	Event::FunctionDeclaration.EventHandlers.push_back(
		EventHandler<Event::Data::FunctionDeclaration>(
			[](void* HandlerData, Event::Data::FunctionDeclaration* EventData) {
				CreateFunctionEntry(EventData->func);
				//.
				//. reset Description buffers
				//.
				{
					Description.clear();
					Return.clear();
					Parameters.clear();
				}
			}
		)
	);
	Event::TypeDeclaration.EventHandlers.push_back(
		EventHandler<Event::Data::TypeDeclaration>(
			[](void* HandlerData, Event::Data::TypeDeclaration* EventData) {
				if(!EventData->Type->incomplete)
					CreateClassEntry(EventData->Type);
			}
		)
	);
	Event::TypeFinalization.EventHandlers.push_back(
		EventHandler<Event::Data::TypeFinalization>(
			[](void* HandlerData, Event::Data::TypeFinalization* EventData) {
				CreateClassEntry(EventData->Type);
			}
		)
	);
	//.
	//. prepare layout.json
	//.
	{
		if(std::filesystem::exists("./c2docs/generated/layout.json")) {
			Layout.load("./c2docs/generated/layout.json");
		} else {
			Layout.add(JSON::object("pages",{}));
			Layout.add(JSON::object("sidebar",{}));
		}
	}
}
