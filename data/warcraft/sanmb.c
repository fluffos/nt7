// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("胭脂虎[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "胭脂虎[2;37;0m
它是补天士的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sanmb");
        set("owner_name", "补天士");
        set_temp("owner", "sanmb");
        set_temp("owner_name", "补天士");
        ::setup();
}
