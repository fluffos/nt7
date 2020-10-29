// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一号[2;37;0m[2;37;0m", ({"cafe"}));        
        set("gender", "男性");                
        set("long", "一号[2;37;0m
它是咖啡小子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ccfcafe");
        set("owner_name", "咖啡小子");
        set_temp("owner", "ccfcafe");
        set_temp("owner_name", "咖啡小子");
        ::setup();
}
