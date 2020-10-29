// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是龙象二号的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xsb");
        set("owner_name", "龙象二号");
        set_temp("owner", "xsb");
        set_temp("owner_name", "龙象二号");
        ::setup();
}
