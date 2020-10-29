// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m哓哓[2;37;0m[2;37;0m", ({"bhbh"}));        
        set("gender", "男性");                
        set("long", "迷糊的[2;37;0m
它是易瞳的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "etn");
        set("owner_name", "易瞳");
        set_temp("owner", "etn");
        set_temp("owner_name", "易瞳");
        ::setup();
}
