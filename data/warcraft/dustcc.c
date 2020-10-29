// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m如家[2;37;0m[2;37;0m", ({"dust"}));        
        set("gender", "女性");                
        set("long", "如家酒店跑堂[2;37;0m
它是客官小心的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dustcc");
        set("owner_name", "客官小心");
        set_temp("owner", "dustcc");
        set_temp("owner_name", "客官小心");
        ::setup();
}
