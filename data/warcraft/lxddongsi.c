// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("幻幻[2;37;0m[2;37;0m", ({"huansly"}));        
        set("gender", "男性");                
        set("long", "~~~~[2;37;0m
它是风冰月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lxddongsi");
        set("owner_name", "风冰月");
        set_temp("owner", "lxddongsi");
        set_temp("owner_name", "风冰月");
        ::setup();
}
