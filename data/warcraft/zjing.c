// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "马三马小三[2;37;0m
它是马三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zjing");
        set("owner_name", "马三");
        set_temp("owner", "zjing");
        set_temp("owner_name", "马三");
        ::setup();
}
