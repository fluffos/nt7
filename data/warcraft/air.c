// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("空空儿[2;37;0m[2;37;0m", ({"aira"}));        
        set("gender", "女性");                
        set("long", "空空的空空儿[2;37;0m
它是空空空的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "air");
        set("owner_name", "空空空");
        set_temp("owner", "air");
        set_temp("owner_name", "空空空");
        ::setup();
}
