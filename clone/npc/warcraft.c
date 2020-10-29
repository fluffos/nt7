// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("WARCRAFT_NAME", ({"WARCRAFT_ID"}));        
        set("gender", "WARCRAFT_GENDER");                
        set("long", "LONG_DESCRIPTION");
        set("race_type", "RACE_TYPE");
        set("magic/type", "MAGIC_TYPE");
        set("owner", "OWNER_ID");
        set("owner_name", "OWNER_NAME");
        set_temp("owner", "OWNER_ID");
        set_temp("owner_name", "OWNER_NAME");
        ::setup();
}
