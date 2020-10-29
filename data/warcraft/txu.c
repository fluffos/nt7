// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱[2;37;0m
它是童鞋玉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txu");
        set("owner_name", "童鞋玉");
        set_temp("owner", "txu");
        set_temp("owner_name", "童鞋玉");
        ::setup();
}
