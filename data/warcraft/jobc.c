// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("呵呵[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "呵呵[2;37;0m
它是唐弹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jobc");
        set("owner_name", "唐弹");
        set_temp("owner", "jobc");
        set_temp("owner_name", "唐弹");
        ::setup();
}
