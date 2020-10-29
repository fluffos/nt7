// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "这是一火红如血的猛禽[2;37;0m
它是桃源阳的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wpjy");
        set("owner_name", "桃源阳");
        set_temp("owner", "wpjy");
        set_temp("owner_name", "桃源阳");
        ::setup();
}
