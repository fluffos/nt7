// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m青龙[2;37;0m[2;37;0m", ({"ide"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是小夜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "redsoft");
        set("owner_name", "小夜");
        set_temp("owner", "redsoft");
        set_temp("owner_name", "小夜");
        ::setup();
}
