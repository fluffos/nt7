// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("最深[2;37;0m[2;37;0m", ({"aweroiut"}));        
        set("gender", "男性");                
        set("long", "最深[2;37;0m
它是盒子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "boxer");
        set("owner_name", "盒子");
        set_temp("owner", "boxer");
        set_temp("owner_name", "盒子");
        ::setup();
}
