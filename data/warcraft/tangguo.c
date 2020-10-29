// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金屋[2;37;0m[2;37;0m", ({"jinwu"}));        
        set("gender", "女性");                
        set("long", "亮金金的屋子[2;37;0m
它是糖果的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tangguo");
        set("owner_name", "糖果");
        set_temp("owner", "tangguo");
        set_temp("owner_name", "糖果");
        ::setup();
}
