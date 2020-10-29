// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m瑞虎[2;37;0m[2;37;0m", ({"huw"}));        
        set("gender", "男性");                
        set("long", "一只昆仑山上的大老虎。[2;37;0m
它是虎王的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "shaol");
        set("owner_name", "虎王");
        set_temp("owner", "shaol");
        set_temp("owner_name", "虎王");
        ::setup();
}
