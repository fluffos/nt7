// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "猪[2;37;0m
它是童鞋五的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txw");
        set("owner_name", "童鞋五");
        set_temp("owner", "txw");
        set_temp("owner_name", "童鞋五");
        ::setup();
}
