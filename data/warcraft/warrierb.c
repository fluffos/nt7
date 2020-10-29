// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m凤凰[2;37;0m[2;37;0m", ({"fenghuang"}));        
        set("gender", "女性");                
        set("long", "四圣兽之一的朱雀[2;37;0m
它是食神的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "warrierb");
        set("owner_name", "食神");
        set_temp("owner", "warrierb");
        set_temp("owner_name", "食神");
        ::setup();
}
