// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是鲁米那的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "flyingii");
        set("owner_name", "鲁米那");
        set_temp("owner", "flyingii");
        set_temp("owner_name", "鲁米那");
        ::setup();
}
