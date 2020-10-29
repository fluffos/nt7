// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血凤[2;37;0m[2;37;0m", ({"xuefeng"}));        
        set("gender", "女性");                
        set("long", "血凤[2;37;0m
它是血墨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zxs");
        set("owner_name", "血墨");
        set_temp("owner", "zxs");
        set_temp("owner_name", "血墨");
        ::setup();
}
