// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;34m捷豹[1;37m敞篷车[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "kick[2;37;0m
它是甄子丹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "starz");
        set("owner_name", "甄子丹");
        set_temp("owner", "starz");
        set_temp("owner_name", "甄子丹");
        ::setup();
}
