// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("回答速度[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "女性");                
        set("long", "的发放[2;37;0m
它是再混九的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zaihuni");
        set("owner_name", "再混九");
        set_temp("owner", "zaihuni");
        set_temp("owner_name", "再混九");
        ::setup();
}
