// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("帮共[2;37;0m[2;37;0m", ({"banggo"}));        
        set("gender", "女性");                
        set("long", "帮共[2;37;0m
它是共帮的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gobang");
        set("owner_name", "共帮");
        set_temp("owner", "gobang");
        set_temp("owner_name", "共帮");
        ::setup();
}
