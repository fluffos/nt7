// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[44;1m蠹[2;37;0m[2;37;0m", ({"worm"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是五蠹教主的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "doll");
        set("owner_name", "五蠹教主");
        set_temp("owner", "doll");
        set_temp("owner_name", "五蠹教主");
        ::setup();
}
