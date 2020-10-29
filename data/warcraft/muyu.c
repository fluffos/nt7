// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m鱼木[2;37;0m[2;37;0m", ({"muyua"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是木鱼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "muyu");
        set("owner_name", "木鱼");
        set_temp("owner", "muyu");
        set_temp("owner_name", "木鱼");
        ::setup();
}
