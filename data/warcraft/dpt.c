// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白马[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "白马[2;37;0m
它是多炮塔的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dpt");
        set("owner_name", "多炮塔");
        set_temp("owner", "dpt");
        set_temp("owner_name", "多炮塔");
        ::setup();
}
