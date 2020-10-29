// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m梨花泪[2;37;0m[2;37;0m", ({"study_emblem"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是傀儡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dummy");
        set("owner_name", "傀儡");
        set_temp("owner", "dummy");
        set_temp("owner_name", "傀儡");
        ::setup();
}
