// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m玄武[2;37;0m[2;37;0m", ({"mecccpet"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是海天晴的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "meccc");
        set("owner_name", "海天晴");
        set_temp("owner", "meccc");
        set_temp("owner_name", "海天晴");
        ::setup();
}
