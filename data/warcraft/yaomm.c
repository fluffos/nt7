// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("某某某[2;37;0m[2;37;0m", ({"yaommm"}));        
        set("gender", "男性");                
        set("long", "某某某[2;37;0m
它是药摸摸的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaomm");
        set("owner_name", "药摸摸");
        set_temp("owner", "yaomm");
        set_temp("owner_name", "药摸摸");
        ::setup();
}
