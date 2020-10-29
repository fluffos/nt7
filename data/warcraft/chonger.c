// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小宝贝[2;37;0m[2;37;0m", ({"chong"}));        
        set("gender", "女性");                
        set("long", "=。=[2;37;0m
它是宠儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chonger");
        set("owner_name", "宠儿");
        set_temp("owner", "chonger");
        set_temp("owner_name", "宠儿");
        ::setup();
}
