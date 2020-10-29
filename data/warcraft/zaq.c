// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("木棍[2;37;0m[2;37;0m", ({"hihi"}));        
        set("gender", "女性");                
        set("long", "一个木头[2;37;0m
它是麻生希的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zaq");
        set("owner_name", "麻生希");
        set_temp("owner", "zaq");
        set_temp("owner_name", "麻生希");
        ::setup();
}
