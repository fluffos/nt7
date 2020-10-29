// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摸起[2;37;0m[2;37;0m", ({"moqi"}));        
        set("gender", "女性");                
        set("long", "111[2;37;0m
它是刻意仔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gzkey");
        set("owner_name", "刻意仔");
        set_temp("owner", "gzkey");
        set_temp("owner_name", "刻意仔");
        ::setup();
}
