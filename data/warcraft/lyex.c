// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小青龙[2;37;0m[2;37;0m", ({"flydragon"}));        
        set("gender", "男性");                
        set("long", "一条上古时期的小青龙[2;37;0m
它是龙多多的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lyex");
        set("owner_name", "龙多多");
        set_temp("owner", "lyex");
        set_temp("owner_name", "龙多多");
        ::setup();
}
