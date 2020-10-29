// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("聊米[2;37;0m[2;37;0m", ({"liaom"}));        
        set("gender", "男性");                
        set("long", "聊米[2;37;0m
它是米聊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mifanchat");
        set("owner_name", "米聊");
        set_temp("owner", "mifanchat");
        set_temp("owner_name", "米聊");
        ::setup();
}
