// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是张猛清的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skpd");
        set("owner_name", "张猛清");
        set_temp("owner", "skpd");
        set_temp("owner_name", "张猛清");
        ::setup();
}
