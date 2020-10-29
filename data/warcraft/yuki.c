// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞毛腿[2;37;0m[2;37;0m", ({"oko"}));        
        set("gender", "男性");                
        set("long", "导弹一号[2;37;0m
它是疯小小的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "yuki");
        set("owner_name", "疯小小");
        set_temp("owner", "yuki");
        set_temp("owner_name", "疯小小");
        ::setup();
}
