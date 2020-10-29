// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玄[1;34m武[2;37;0m[2;37;0m", ({"head"}));        
        set("gender", "男性");                
        set("long", "一头大大的乌龟！[2;37;0m
它是流氓的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "rogue");
        set("owner_name", "流氓");
        set_temp("owner", "rogue");
        set_temp("owner_name", "流氓");
        ::setup();
}
