// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m啸天[2;37;0m[2;37;0m", ({"sigh"}));        
        set("gender", "男性");                
        set("long", "啸天[2;37;0m
它是枫语的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "sly");
        set("owner_name", "枫语");
        set_temp("owner", "sly");
        set_temp("owner_name", "枫语");
        ::setup();
}
