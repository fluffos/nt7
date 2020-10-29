// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m小红[2;37;0m[2;37;0m", ({"wuya"}));        
        set("gender", "女性");                
        set("long", "一只红色的小鸟[2;37;0m
它是乌丫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "uya");
        set("owner_name", "乌丫");
        set_temp("owner", "uya");
        set_temp("owner_name", "乌丫");
        ::setup();
}
