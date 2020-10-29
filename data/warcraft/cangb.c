// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m扫帚[2;37;0m[2;37;0m", ({"gbb"}));        
        set("gender", "男性");                
        set("long", "扫帚[2;37;0m
它是铁血神丐的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cangb");
        set("owner_name", "铁血神丐");
        set_temp("owner", "cangb");
        set_temp("owner_name", "铁血神丐");
        ::setup();
}
