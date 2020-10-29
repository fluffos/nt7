// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"xxdfs"}));        
        set("gender", "男性");                
        set("long", "魔幻兽[2;37;0m
它是习习的风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xxdf");
        set("owner_name", "习习的风");
        set_temp("owner", "xxdf");
        set_temp("owner_name", "习习的风");
        ::setup();
}
