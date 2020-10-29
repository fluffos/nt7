// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("奔驰[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "eat liang[2;37;0m
它是唐如风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "oppenheim");
        set("owner_name", "唐如风");
        set_temp("owner", "oppenheim");
        set_temp("owner_name", "唐如风");
        ::setup();
}
