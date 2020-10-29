// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m撸啦[2;37;0m[2;37;0m", ({"menttyo"}));        
        set("gender", "女性");                
        set("long", "坑爹的，又被撸啦！！！[2;37;0m
它是无尘剑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mentty");
        set("owner_name", "无尘剑");
        set_temp("owner", "mentty");
        set_temp("owner_name", "无尘剑");
        ::setup();
}
