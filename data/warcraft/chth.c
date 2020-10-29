// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玄武[2;37;0m[2;37;0m", ({"get"}));        
        set("gender", "男性");                
        set("long", "玄武[2;37;0m
它是成桃的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "chth");
        set("owner_name", "成桃");
        set_temp("owner", "chth");
        set_temp("owner_name", "成桃");
        ::setup();
}
