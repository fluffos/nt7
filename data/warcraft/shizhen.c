// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m仙鹤[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "mygift[2;37;0m
它是李时珍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shizhen");
        set("owner_name", "李时珍");
        set_temp("owner", "shizhen");
        set_temp("owner_name", "李时珍");
        ::setup();
}
