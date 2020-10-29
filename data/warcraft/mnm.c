// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血凤[2;37;0m[2;37;0m", ({"xxxf"}));        
        set("gender", "男性");                
        set("long", "sgfsgf[2;37;0m
它是赤血的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mnm");
        set("owner_name", "赤血");
        set_temp("owner", "mnm");
        set_temp("owner_name", "赤血");
        ::setup();
}
