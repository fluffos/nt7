// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m[41;1m般若[2;37;0m[2;37;0m", ({"longxiangs"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是龙象的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "longxiang");
        set("owner_name", "龙象");
        set_temp("owner", "longxiang");
        set_temp("owner_name", "龙象");
        ::setup();
}
