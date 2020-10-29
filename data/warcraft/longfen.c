// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m语嫣[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "男性");                
        set("long", "燕子乌的语嫣[2;37;0m
它是龙枫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "longfen");
        set("owner_name", "龙枫");
        set_temp("owner", "longfen");
        set_temp("owner_name", "龙枫");
        ::setup();
}
