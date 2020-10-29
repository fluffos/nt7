// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m阿斯顿马丁[2;37;0m[2;37;0m", ({"astonmartin"}));        
        set("gender", "男性");                
        set("long", "阿斯顿马丁DBS，它是著名间谍007最爱的一辆座驾。[2;37;0m
它是零零七的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "agent");
        set("owner_name", "零零七");
        set_temp("owner", "agent");
        set_temp("owner_name", "零零七");
        ::setup();
}
