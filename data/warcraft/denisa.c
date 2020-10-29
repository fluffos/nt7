// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("感恩[2;37;0m[2;37;0m", ({"aikuaile"}));        
        set("gender", "男性");                
        set("long", "感恩[2;37;0m
它是爱生活的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "denisa");
        set("owner_name", "爱生活");
        set_temp("owner", "denisa");
        set_temp("owner_name", "爱生活");
        ::setup();
}
