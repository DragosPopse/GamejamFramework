#include <Gamejam/Core/Core.hpp>

namespace jam
{
	class App;
}	

int main(int argc, char** argv);


jam::App* CreateApp();

#define JAM_APP(AppClass) jam::App* CreateApp() { return new AppClass(); }
