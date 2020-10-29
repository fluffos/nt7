// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m镖车[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "                               [2;37;0m
它是胡弄的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "first");
        set("owner_name", "胡弄");
        set_temp("owner", "first");
        set_temp("owner_name", "胡弄");
        ::setup();
}
