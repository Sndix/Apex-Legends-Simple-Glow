#include "Utility.h"


DWORD64 GetEntityById(int Ent, DWORD64 Base)
{

	DWORD64 EntityList = Base + 0x1F6CAB8; // Obtaining EntityList pointer
	DWORD64 BaseEntity = RPM64(EntityList); // Getting the BaseEntity
	if (!BaseEntity) // Checking if there even is a BaseEntity if not than it makes no sense to try and read the Entitylist anyways
		return NULL;

	return RPM64(EntityList + (Ent << 5)); // Getting the Entity at the Given ID
}
void EnableHighlight(DWORD64 Entity, float r, float g, float b) {

	WPMBool(Entity + 0x380, true); // Enabling the Glow
	WPMInt(Entity + 0x2F0, 1); // Enabling the Glow
	WPMFloat(Entity + 0x1B0, r); // Setting a value for the Color Red between 0 and 255
	WPMFloat(Entity + 0x1B4, g); // Setting a value for the Color Green between 0 and 255
	WPMFloat(Entity + 0x1B8, b); // Setting a value for the Color Blue between 0 and 255

	for (int offset = 0x2B0; offset <= 0x2C8; offset += 0x4) //Setting the of the Glow at all necessary spots
		WPMFloat(Entity + offset, FLT_MAX); // Setting the time of the Glow to be the Max Float value so it never runs out

	WPMFloat(Entity + 0x2DC, FLT_MAX); //Set the Distance of the Glow to Max float value so we can see a long Distance
}
int main()
{
	DWORD64 Base = GetBase(); // Getting the Base

	while (true) {

		for (int i = 0; i < 100; i++) { // Enumerating through the first 100 Entities in the List because thats where all players are stored
			DWORD64 Entity = GetEntityById(i, Base); // Getting the Entity
			if (Entity == 0) // Checking if its valid
				continue;
			DWORD64 EntityHandle = RPM64(Entity + 0x500); 
			
			std::string Identifier = RPMString(EntityHandle); // Getting an Identifier that Tells us what the Entity is
			LPCSTR IdentifierC = Identifier.c_str(); // Converting the string because im stupid

			if (strcmp(IdentifierC, "player")) //Comparing if the Identifier states that the Entity is indeed a Player
				EnableHighlight(Entity, 120.f, 0.f, 0.f);	// Enabling the Glow for that Entity since it is a Player
		}

	}

}

