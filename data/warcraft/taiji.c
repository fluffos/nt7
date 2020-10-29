// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "这就是上古神兽玄武。[2;37;0m
它是太极的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "taiji");
        set("owner_name", "太极");
        set_temp("owner", "taiji");
        set_temp("owner_name", "太极");
        ::setup();
}
