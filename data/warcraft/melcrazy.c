// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎神[2;37;0m[2;37;0m", ({"best"}));        
        set("gender", "男性");                
        set("long", "虎神[2;37;0m
它是秋意的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "melcrazy");
        set("owner_name", "秋意");
        set_temp("owner", "melcrazy");
        set_temp("owner_name", "秋意");
        ::setup();
}
