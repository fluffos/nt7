// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白白[2;37;0m[2;37;0m", ({"white"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是高岑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "vhdl");
        set("owner_name", "高岑");
        set_temp("owner", "vhdl");
        set_temp("owner_name", "高岑");
        ::setup();
}
