// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m流光[2;37;0m[2;37;0m", ({"rainbow"}));        
        set("gender", "女性");                
        set("long", "$HIR$流光[2;37;0m
它是桃枝妖妖的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "flee");
        set("owner_name", "桃枝妖妖");
        set_temp("owner", "flee");
        set_temp("owner_name", "桃枝妖妖");
        ::setup();
}
