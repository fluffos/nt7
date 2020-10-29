// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小火[2;37;0m[2;37;0m", ({"losi"}));        
        set("gender", "男性");                
        set("long", "哦[2;37;0m
它是伯瓦尔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hiee");
        set("owner_name", "伯瓦尔");
        set_temp("owner", "hiee");
        set_temp("owner_name", "伯瓦尔");
        ::setup();
}
