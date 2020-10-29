// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("胭脂虎[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "胭脂虎[2;37;0m
它是通天晓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sanmc");
        set("owner_name", "通天晓");
        set_temp("owner", "sanmc");
        set_temp("owner_name", "通天晓");
        ::setup();
}
