// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m情丝[2;37;0m[2;37;0m", ({"qingsi"}));        
        set("gender", "男性");                
        set("long", "情丝[2;37;0m
它是肆无忌惮的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangsi");
        set("owner_name", "肆无忌惮");
        set_temp("owner", "dangsi");
        set_temp("owner_name", "肆无忌惮");
        ::setup();
}
