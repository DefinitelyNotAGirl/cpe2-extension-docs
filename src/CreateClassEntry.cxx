#include <compiler/inc/function.h>
#include <HTML.hxx>
#include <globals.hxx>

std::string getFunctionExpression(function* f, bool showVariableNames = true);

using html::element;
void CreateClassEntry(type* Type) {
	std::cout << "create class entry: " << Type->name << std::endl;
	//.
	//. write doc page html
	//.
	std::string FilePageContent = "./c2docs/generated/"+Type->mangledName+".html";
	{
		element document(
			"div",
			{
				element::attribute("class","class-container"),
			},
			{
				element(
					"div",
					{
						element::attribute("class","class-memory")
					},
					([Type]{
						std::vector<element> memory;
						u64 offset = 0;
						for(variable& member : Type->members) {
							u64 PaddingSize = 0;
							while(offset < ((u64)member.storage)) {
								offset++;
								PaddingSize++;
							}
							if(PaddingSize) {
								memory.push_back(
									element(
										"div",
										{
											element::attribute("class","class-memory-item class-memory-padding"),
											element::attribute("style","height: calc("+std::to_string(PaddingSize)+" * var(--class-memory-pixel-height));line-height: calc("+std::to_string(PaddingSize)+" * var(--class-memory-pixel-height));")
										},
										"padding: "+std::to_string(PaddingSize)+" bytes"
									)
								);
							}
							if(member.dataType->size) {
								memory.push_back(
									element(
										"div",
										{
											element::attribute("class","class-memory-item class-memory-variable"),
											element::attribute("style","height: calc("+std::to_string(member.dataType->size)+" * var(--class-memory-pixel-height));line-height: calc("+std::to_string(member.dataType->size)+" * var(--class-memory-pixel-height));")
										},
										{
											element(
												"span",
												{
													element::attribute("class","class-member-expression")
												},
												{
													element(
														"span",
														{
															element::attribute("class","code-class")
														},
														member.dataType->name
													),
													element(
														"span",
														{
															element::attribute("class","code-variable")
														},
														member.name
													)
												}
											)
										}
									)
								);
							}
							offset+=member.dataType->size;
						}
						return memory;
					})()
				),
				element(
					"div",
					{
						element::attribute("class","class-members")
					},
					([Type]{
						std::vector<element> members;
						for(variable& member : Type->members) {
							members.push_back(
								element(
									"div",
									{
										element::attribute("class","class-member-container")
									},
									{
										element(
											"div",
											{
												element::attribute("class","class-member-title")
											},
											{
												element(
													"span",
													{
														element::attribute("class","class-member-expression")
													},
													{
														element(
															"span",
															{
																element::attribute("class","code-class")
															},
															member.dataType->name
														),
														element(
															"span",
															{
																element::attribute("class","code-variable")
															},
															member.name
														)
													}
												)
											}
										)
									}
								)
							);
						}
						return members;
					})()
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
			Layout["pages"][Type->name];
		} catch(JSONNoSuchChild) {
			Layout["pages"].add(
				JSON::object(
					Type->name, {
						JSON("type","class"),
						JSON("page-id","page-class-"+Type->name),
						JSON("page-content",FilePageContent),
						JSON::list(
							"members",([Type]{
								std::vector<JSON> members;
								for(variable& member : Type->members) {
									members.push_back(
										JSON::object(
											"",
											{
												JSON("name",member.name),
												JSON("type",member.dataType->name),
											}
										)
									);
								}
								return members;
							})()
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
			Layout["sidebar"][Type->name];
		} catch(JSONNoSuchChild) {
			Layout["sidebar"].add(
				JSON::object(
					Type->name, {
						JSON("type","class"),
						JSON("page-id","page-class-"+Type->name),
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