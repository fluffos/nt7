// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m灵塔武痴[2;37;0m[2;37;0m", ({"xxxx"}));        
        set("gender", "女性");                
        set("long", "塔上掉下来的武痴！[2;37;0m
它是灵塔囚徒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xxxlqxxxx");
        set("owner_name", "灵塔囚徒");
        set_temp("owner", "xxxlqxxxx");
        set_temp("owner_name", "灵塔囚徒");
        ::setup();
}
