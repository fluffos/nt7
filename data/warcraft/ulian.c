// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火云[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "嘿嘿[2;37;0m
它是楚楚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ulian");
        set("owner_name", "楚楚");
        set_temp("owner", "ulian");
        set_temp("owner_name", "楚楚");
        ::setup();
}
