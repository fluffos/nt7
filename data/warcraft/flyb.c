// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是米虫的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "flyb");
        set("owner_name", "米虫");
        set_temp("owner", "flyb");
        set_temp("owner_name", "米虫");
        ::setup();
}
