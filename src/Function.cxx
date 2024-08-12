#include <FlowChart.hxx>

void CreateFunction(function* func) {
	if(func->isPrimitive)return;
	if(func->isExtern)return;
	Functions.insert(std::pair<function*,FunctionData>(func,FunctionData()));
	Functions.at(func).content += "<div class='function-name'>"+func->name+"</div>";
	Functions.at(func).xpos += 20;
	Functions.at(func).ypos += 2.5;
}

void SetFunction(function* func) {
	CurrentFunction = &Functions.at(func);
}

void CallNode(function* func, std::vector<variable*>* args) {
	if(CurrentFunction == nullptr)return;
	std::string expr;
	expr += "<span class='code type'>"+func->returnType->name+"</span>";
	expr += "<span class='code function'>"+func->name+"</span>";
	expr += "(";
	for(variable* arg : *args) {
		std::cout << "arg: " << arg << std::endl;
		std::cout << "arg->dataType: " << arg->dataType << std::endl;
		expr += "<span class='code type'>"+arg->dataType->name+"</span>";
		expr += "<span class='code function'>"+arg->name+"</span>,";
	}
	if(args->size() > 0)
		expr.pop_back();
	expr += ")";
	CurrentFunction->content += "<div class='call' style='top: "+std::to_string(CurrentFunction->ypos)+"vw'>"+expr+"</div>";
	CurrentFunction->ypos += 2.125;
}
