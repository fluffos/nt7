// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("河马[2;37;0m[2;37;0m", ({"hema"}));        
        set("gender", "男性");                
        set("long", "河马[2;37;0m
它是莫打的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "newjared");
        set("owner_name", "莫打");
        set_temp("owner", "newjared");
        set_temp("owner_name", "莫打");
        ::setup();
}
