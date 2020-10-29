// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("如白[2;37;0m[2;37;0m", ({"las"}));        
        set("gender", "女性");                
        set("long", "没有[2;37;0m
它是文明的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zatty");
        set("owner_name", "文明");
        set_temp("owner", "zatty");
        set_temp("owner_name", "文明");
        ::setup();
}
