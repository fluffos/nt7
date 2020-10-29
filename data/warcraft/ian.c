// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m捷安特[2;37;0m[2;37;0m", ({"atx"}));        
        set("gender", "男性");                
        set("long", "ATX660[2;37;0m
它是浩然的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "ian");
        set("owner_name", "浩然");
        set_temp("owner", "ian");
        set_temp("owner_name", "浩然");
        ::setup();
}
