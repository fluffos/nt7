// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("悍马[1;37m[2;37;0m[2;37;0m", ({"hull"}));        
        set("gender", "男性");                
        set("long", "额[2;37;0m
它是笙深的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "will");
        set("owner_name", "笙深");
        set_temp("owner", "will");
        set_temp("owner_name", "笙深");
        ::setup();
}
