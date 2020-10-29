// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m捷安特[5m[1;37m越野车[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "mygift[2;37;0m
它是草稚京的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "caozhi");
        set("owner_name", "草稚京");
        set_temp("owner", "caozhi");
        set_temp("owner_name", "草稚京");
        ::setup();
}
