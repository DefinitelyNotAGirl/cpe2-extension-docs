#include <globals.hxx>
/**
 * @brief this function is called just before the compiler exits normally
 */
void Finish() {
	Layout.save("./c2docs/generated/layout.json");
}