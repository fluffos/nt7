// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小[1;33m黄[2;37;0m[2;37;0m[2;37;0m", ({"zdragon"}));        
        set("gender", "女性");                
        set("long", "lick[2;37;0m
它是大刀王五的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fireangle");
        set("owner_name", "大刀王五");
        set_temp("owner", "fireangle");
        set_temp("owner_name", "大刀王五");
        ::setup();
}
