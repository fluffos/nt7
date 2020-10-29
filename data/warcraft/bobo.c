// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("摇篮[2;37;0m[2;37;0m", ({"icq"}));        
        set("gender", "男性");                
        set("long", "爱困[2;37;0m
它是净宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bobo");
        set("owner_name", "净宝");
        set_temp("owner", "bobo");
        set_temp("owner_name", "净宝");
        ::setup();
}
