// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无[2;37;0m[2;37;0m", ({"gyill"}));        
        set("gender", "男性");                
        set("long", "nick $RED$卡迪拉克[2;37;0m
它是眼兄的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ilplayer");
        set("owner_name", "眼兄");
        set_temp("owner", "ilplayer");
        set_temp("owner_name", "眼兄");
        ::setup();
}
