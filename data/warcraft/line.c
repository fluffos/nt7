// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m神都龙王[2;37;0m[2;37;0m", ({"shen"}));        
        set("gender", "女性");                
        set("long", "这就是传说中的神龙[2;37;0m
它是楚天行的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "line");
        set("owner_name", "楚天行");
        set_temp("owner", "line");
        set_temp("owner_name", "楚天行");
        ::setup();
}
