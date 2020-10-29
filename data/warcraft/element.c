// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小秘[2;37;0m[2;37;0m", ({"solo"}));        
        set("gender", "女性");                
        set("long", "黑丝迷死人[2;37;0m
它是司马悟空的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "element");
        set("owner_name", "司马悟空");
        set_temp("owner", "element");
        set_temp("owner_name", "司马悟空");
        ::setup();
}
