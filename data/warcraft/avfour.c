// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "白虎[2;37;0m
它是里美老师的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "avfour");
        set("owner_name", "里美老师");
        set_temp("owner", "avfour");
        set_temp("owner_name", "里美老师");
        ::setup();
}
