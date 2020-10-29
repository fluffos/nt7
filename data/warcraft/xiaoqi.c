// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m烈火麒麟[2;37;0m[2;37;0m", ({"huo"}));        
        set("gender", "男性");                
        set("long", "烈火麒麟[2;37;0m
它是小七的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoqi");
        set("owner_name", "小七");
        set_temp("owner", "xiaoqi");
        set_temp("owner_name", "小七");
        ::setup();
}
