// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m大公鸡[2;37;0m[2;37;0m", ({"cock"}));        
        set("gender", "女性");                
        set("long", "没[2;37;0m
它是丙打杂的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ipxc");
        set("owner_name", "丙打杂");
        set_temp("owner", "ipxc");
        set_temp("owner_name", "丙打杂");
        ::setup();
}
