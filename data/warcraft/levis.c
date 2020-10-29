// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"zque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是有一天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "levis");
        set("owner_name", "有一天");
        set_temp("owner", "levis");
        set_temp("owner_name", "有一天");
        ::setup();
}
