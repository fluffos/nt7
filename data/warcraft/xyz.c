// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大[2;37;0m[2;37;0m", ({"big"}));        
        set("gender", "男性");                
        set("long", "头[2;37;0m
它是萧鹞子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xyz");
        set("owner_name", "萧鹞子");
        set_temp("owner", "xyz");
        set_temp("owner_name", "萧鹞子");
        ::setup();
}
