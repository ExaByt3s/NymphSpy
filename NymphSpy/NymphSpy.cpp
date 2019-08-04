#include "Core/Includes/File.h"
#include "Core/Includes/Process.h"

#include <stdio.h>

int main() {
	sdk::list<NYMPHCORE_PHYSICAL_PROCESS> flList = Process::List();

	for (sdk::list<NYMPHCORE_PHYSICAL_PROCESS>::iterator file = flList.begin(); file != flList.end(); ++file) {
		printf_s(" [%i] %s\n", file.get().id, file.get().name.to_str());
	}
}