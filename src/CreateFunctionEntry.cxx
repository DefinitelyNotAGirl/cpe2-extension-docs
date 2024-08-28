#include <compiler/inc/function.h>
#include <HTML.hxx>
#include <globals.hxx>

std::string getFunctionExpression(function* f, bool showVariableNames = true);

using html::element;
void CreateFunctionEntry(function* func) {
	std::cout << "create function entry: " << func->expression_ansi() << std::endl;
	//.
	//. write doc page html
	//.
	std::string FilePageContent = "./c2docs/generated/"+func->symbol+".html";
	{
		element document(
			"div",
			{
				element::attribute("class","overload-container"),
			},
			{
				element(
						"div",
						{
							element::attribute("class","overload-title")
						},
						{
							element(
								"span",
								{
									element::attribute("class","overload-expression"),
								},
								func->expression_html()
							),
							element(
								"span",
								{
									element::attribute("class","overload-symbol"),
								},
								"symbol: "+func->symbol
							),
						}
				),
				element(
					"div",
					{
						element::attribute("class","overload-content"),
					},
					{
						element(
							"div",
							{
								element::attribute("class","overload-description"),
							},
							Description
						),
						([](){
							if(Return.empty())	
								return element("__skip__",{},"");
							return element(
								"div",
								{},
								{
									element(
										"h2",
										{
											element::attribute("class","overload-symbol")
										},
										"Returns:"
									),
									element(
										"div",
										{
											element::attribute("class","overload-return"),
										},
										Return
									),
								}
							);
						})()
					}
				)
			}
		);
		document.save(FilePageContent);
	}
	//.
	//. page
	//.
	{
		try {
			Layout["pages"][func->name]["overloads"].add(
				JSON::object(
					{
						JSON("expression",getFunctionExpression(func)),
						JSON("page-content",FilePageContent),
					}
				)
			);
		} catch(JSONNoSuchChild) {
			Layout["pages"].add(
				JSON::object(
					func->name, {
						JSON("type","function"),
						JSON("page-id","page-function-"+func->name),
						JSON::list(
							"overloads",{
								JSON::object(
									{
										JSON("expression",getFunctionExpression(func)),
										JSON("page-content",FilePageContent),
									}
								)
							}
						)
					}
				)
			);
		}
	}
	//.
	//. sidebar
	//.
	{
		try {
			Layout["sidebar"][func->name];
		} catch(JSONNoSuchChild) {
			Layout["sidebar"].add(
				JSON::object(
					func->name, {
						JSON("type","function"),
						JSON("page-id","page-function-"+func->name),
					}
				)
			);
		}
	}
	//.
	//. reset Description buffers
	//.
	{
		Description.clear();
		Return.clear();
		Parameters.clear();
	}
}