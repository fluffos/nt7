// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m试管[2;37;0m[2;37;0m", ({"shiguan"}));        
        set("gender", "女性");                
        set("long", "试管里面有很多不明液体[2;37;0m
它是试一下的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fortest");
        set("owner_name", "试一下");
        set_temp("owner", "fortest");
        set_temp("owner_name", "试一下");
        ::setup();
}
