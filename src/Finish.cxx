#include <iostream>
#include <FlowChart.hxx>
/**
 * @brief this function is called just before the compiler exits normally
 */
void Finish() {
	for(const std::pair<function*, FunctionData>& func : Functions) {
		std::string fcontent = content;
		fcontent +=  func.second.content;
		fcontent += "</body>\n</html>\n";
		FILE* f = fopen(("FlowChart."+func.first->symbol+".html").c_str(),"w");
		fwrite(fcontent.c_str(),fcontent.size(),1,f);
		fclose(f);
	}
}