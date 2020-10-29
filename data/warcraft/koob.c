// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m人力三轮[2;37;0m[2;37;0m", ({"boo"}));        
        set("gender", "女性");                
        set("long", "$HIW$人力三轮[2;37;0m
它是憨农民的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "koob");
        set("owner_name", "憨农民");
        set_temp("owner", "koob");
        set_temp("owner_name", "憨农民");
        ::setup();
}
