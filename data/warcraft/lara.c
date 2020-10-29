// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m致命螳螂[2;37;0m[2;37;0m", ({"laras"}));        
        set("gender", "男性");                
        set("long", "$HIB$致命螳螂[2;37;0m
它是福缘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lara");
        set("owner_name", "福缘");
        set_temp("owner", "lara");
        set_temp("owner_name", "福缘");
        ::setup();
}
