// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("千年的[2;37;0m[2;37;0m", ({"mhs"}));        
        set("gender", "男性");                
        set("long", "千年的[2;37;0m
它是释迦摩尼的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jjf");
        set("owner_name", "释迦摩尼");
        set_temp("owner", "jjf");
        set_temp("owner_name", "释迦摩尼");
        ::setup();
}
