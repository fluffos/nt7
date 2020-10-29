// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("旺财[2;37;0m[2;37;0m", ({"dogg"}));        
        set("gender", "男性");                
        set("long", "汪汪汪[2;37;0m
它是康小妹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lee");
        set("owner_name", "康小妹");
        set_temp("owner", "lee");
        set_temp("owner_name", "康小妹");
        ::setup();
}
