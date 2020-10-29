// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"bris"}));        
        set("gender", "男性");                
        set("long", "时光上[2;37;0m
它是钱瑟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sirb");
        set("owner_name", "钱瑟");
        set_temp("owner", "sirb");
        set_temp("owner_name", "钱瑟");
        ::setup();
}
