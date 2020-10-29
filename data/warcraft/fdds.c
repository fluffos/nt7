// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小白龙[2;37;0m[2;37;0m", ({"boo"}));        
        set("gender", "男性");                
        set("long", "$HIW$小白龙[2;37;0m
它是呆死了的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fdds");
        set("owner_name", "呆死了");
        set_temp("owner", "fdds");
        set_temp("owner_name", "呆死了");
        ::setup();
}
