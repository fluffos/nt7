// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老鼠夹[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "老鼠夹[2;37;0m
它是生肖鼠的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zooa");
        set("owner_name", "生肖鼠");
        set_temp("owner", "zooa");
        set_temp("owner_name", "生肖鼠");
        ::setup();
}
