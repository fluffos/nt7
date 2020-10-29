// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "巨大的白虎[2;37;0m
它是轩辕九天的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "jiutian");
        set("owner_name", "轩辕九天");
        set_temp("owner", "jiutian");
        set_temp("owner_name", "轩辕九天");
        ::setup();
}
