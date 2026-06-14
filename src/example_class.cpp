#include "example_class.h"
#include <godot_cpp/variant/utility_functions.hpp>

void ExampleClass::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
}

void ExampleClass::print_type(const Variant &p_variant) const {
	UtilityFunctions::print(vformat("Type: %d", p_variant.get_type()));
}
