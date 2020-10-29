// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m招[5m[1;33m财[2;37;0m[1;35m进[5m[1;33m宝[2;37;0m[2;37;0m[2;37;0m", ({"treasure"}));        
        set("gender", "女性");                
        set("long", "招财进宝![2;37;0m
它是招财喵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "luckyluck");
        set("owner_name", "招财喵");
        set_temp("owner", "luckyluck");
        set_temp("owner_name", "招财喵");
        ::setup();
}
