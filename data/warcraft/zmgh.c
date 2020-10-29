// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m飞得高[2;37;0m[2;37;0m", ({"fdg"}));        
        set("gender", "女性");                
        set("long", "飞得高[2;37;0m
它是走马观花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zmgh");
        set("owner_name", "走马观花");
        set_temp("owner", "zmgh");
        set_temp("owner_name", "走马观花");
        ::setup();
}
