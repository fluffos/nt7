// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m锦[1;31m鸡[2;37;0m[2;37;0m", ({"jji"}));        
        set("gender", "男性");                
        set("long", "远古神兽变种[2;37;0m
它是莪晤的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tyw");
        set("owner_name", "莪晤");
        set_temp("owner", "tyw");
        set_temp("owner_name", "莪晤");
        ::setup();
}
